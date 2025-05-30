/*
 * Copyright 2022-2025 André Zwing
 * Copyright 2023 Alexandre Julliard
 */
#include <stddef.h>
#include <stdio.h>
#include <windows.h>
#include <ntstatus.h>
#include <winternl.h>
#include <winnt.h>

#include "compiler.h"
#include "os.h"
#include "custommem.h"
#include "env.h"
#include "emu/x64emu_private.h"
#include "emu/x87emu_private.h"
#include "x64trace.h"
#include "box64context.h"
#include "box64cpu.h"
#include "box64cpu_util.h"
#include "rbtree.h"
#include "wine/debug.h"

uintptr_t box64_pagesize = 4096;

uint32_t default_gs = 0x2b;
uint32_t default_fs = 0;

int box64_rdtsc = 0;
uint8_t box64_rdtsc_shift = 0;
int box64_is32bits = 0;
int box64_wine = 0; // this is for the emulated x86 Wine.

static uint32_t x86emu_parity_tab[8] =
{
    0x96696996,
    0x69969669,
    0x69969669,
    0x96696996,
    0x69969669,
    0x96696996,
    0x96696996,
    0x69969669,
};

static UINT16 DECLSPEC_ALIGN(4096) bopcode[4096/sizeof(UINT16)];
static UINT16 DECLSPEC_ALIGN(4096) unxcode[4096/sizeof(UINT16)];

typedef UINT64 unixlib_handle_t;
NTSTATUS (WINAPI *__wine_unix_call_dispatcher)( unixlib_handle_t, unsigned int, void * );

int is_addr_unaligned(uintptr_t addr)
{
    // FIXME
    return 0;
}

typedef void (*wrapper_t)(x64emu_t* emu, uintptr_t fnc);
int isSimpleWrapper(wrapper_t fun)
{
    return 0;
}

int isRetX87Wrapper(wrapper_t fun)
{
    return 0;
}

int arm64_asimd = 0;
int arm64_aes = 0;
int arm64_pmull = 0;
int arm64_crc32 = 0;
int arm64_atomics = 0;
int arm64_sha1 = 0;
int arm64_sha2 = 0;
int arm64_uscat = 0;
int arm64_flagm = 0;
int arm64_flagm2 = 0;
int arm64_frintts = 0;
int arm64_afp = 0;
int arm64_rndr = 0;

static box64context_t box64_context;
box64context_t *my_context = &box64_context;


void WINAPI BTCpuFlushInstructionCache2(LPCVOID addr, SIZE_T size)
{
    // NYI
    // invalidate all paged interleaved with this range.
    unprotectDB((uintptr_t)addr, (size_t)size, 1);
}

void* WINAPI BTCpuGetBopCode(void)
{
    return (UINT32*)&bopcode;
}

void* WINAPI __wine_get_unix_opcode(void)
{
    return (UINT32*)&unxcode;
}

NTSTATUS WINAPI BTCpuGetContext(HANDLE thread, HANDLE process, void* unknown, WOW64_CONTEXT* ctx)
{
    return NtQueryInformationThread( thread, ThreadWow64Context, ctx, sizeof(*ctx), NULL );
}

void WINAPI BTCpuNotifyMemoryFree(PVOID addr, SIZE_T size, ULONG free_type)
{
    // NYI
}

void WINAPI BTCpuNotifyMemoryProtect(PVOID addr, SIZE_T size, DWORD new_protect)
{
    // NYI
}

void WINAPI BTCpuNotifyUnmapViewOfSection(PVOID addr, ULONG flags)
{
    // NYI
}

NTSTATUS WINAPI BTCpuProcessInit(void)
{
    HMODULE module;
    UNICODE_STRING str;
    void **p__wine_unix_call_dispatcher;

#define STATIC_ASSERT(COND, MSG) typedef char static_assertion_##MSG[(!!(COND))*2-1]
/* otherwise adjust arm64_epilog.S and arm64_next.S */
STATIC_ASSERT(offsetof(x64emu_t, win64_teb) == 3120, offset_of_b_must_be_4);
#undef STATIC_ASSERT

    LoadEnvVariables();

    memset(bopcode, 0xc3, sizeof(bopcode));
    memset(unxcode, 0xc3, sizeof(unxcode));
    bopcode[0] = 0x2ecd;
    unxcode[0] = 0x2ecd;

    init_custommem_helper(&box64_context);
    box64_context.db_sizes = rbtree_init("db_sizes");

    if ((ULONG_PTR)bopcode >> 32 || (ULONG_PTR)unxcode >> 32)
    {
        __wine_dbg_output( "box64cpu loaded above 4G, disabling\n" );
        return STATUS_INVALID_ADDRESS;
    }

    RtlInitUnicodeString( &str, L"ntdll.dll" );
    LdrGetDllHandle( NULL, 0, &str, &module );
    p__wine_unix_call_dispatcher = RtlFindExportedRoutineByName( module, "__wine_unix_call_dispatcher" );
    __wine_unix_call_dispatcher = *p__wine_unix_call_dispatcher;

    RtlInitializeCriticalSection(&box64_context.mutex_dyndump);
    RtlInitializeCriticalSection(&box64_context.mutex_trace);
    RtlInitializeCriticalSection(&box64_context.mutex_tls);
    RtlInitializeCriticalSection(&box64_context.mutex_thread);
    RtlInitializeCriticalSection(&box64_context.mutex_bridge);
    RtlInitializeCriticalSection(&box64_context.mutex_lock);

    InitX64Trace(&box64_context);

    return STATUS_SUCCESS;
}

NTSTATUS WINAPI BTCpuResetToConsistentState(EXCEPTION_POINTERS* ptrs)
{
    // NYI
    return STATUS_SUCCESS;
}

NTSTATUS WINAPI BTCpuSetContext(HANDLE thread, HANDLE process, void* unknown, WOW64_CONTEXT* ctx)
{
    return NtSetInformationThread( thread, ThreadWow64Context, ctx, sizeof(*ctx) );
}

void WINAPI BTCpuSimulate(void)
{
    WOW64_CPURESERVED *cpu = NtCurrentTeb()->TlsSlots[WOW64_TLS_CPURESERVED];
    x64emu_t *emu = NtCurrentTeb()->TlsSlots[0]; // FIXME
    WOW64_CONTEXT *ctx = (WOW64_CONTEXT *)(cpu + 1);
    CONTEXT entry_context;

    RtlCaptureContext(&entry_context);
    NtCurrentTeb()->TlsSlots[WOW64_TLS_MAX_NUMBER] = &entry_context;

    R_EAX = ctx->Eax;
    R_EBX = ctx->Ebx;
    R_ECX = ctx->Ecx;
    R_EDX = ctx->Edx;
    R_ESI = ctx->Esi;
    R_EDI = ctx->Edi;
    R_EBP = ctx->Ebp;
    R_RIP = ctx->Eip;
    R_ESP = ctx->Esp;
    R_CS  = ctx->SegCs & 0xffff;
    R_DS  = ctx->SegDs & 0xffff;
    R_ES  = ctx->SegEs & 0xffff;
    R_FS  = ctx->SegFs & 0xffff;
    R_GS  = ctx->SegGs & 0xffff;
    R_SS  = ctx->SegSs & 0xffff;
    emu->eflags.x64 = ctx->EFlags;
    emu->segs_offs[_FS] = calculate_fs();
    emu->win64_teb = (uint64_t)NtCurrentTeb();

    if (box64env.dynarec)
        DynaRun(emu);
    else
        Run(emu, 0);
}

NTSTATUS WINAPI BTCpuThreadInit(void)
{
    WOW64_CONTEXT *ctx;
    x64emu_t *emu = RtlAllocateHeap( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*emu) );

    RtlWow64GetCurrentCpuArea( NULL, (void **)&ctx, NULL );
    emu->context = &box64_context;

    // setup cpu helpers
    for (int i=0; i<16; ++i)
        emu->sbiidx[i] = &emu->regs[i];
    emu->sbiidx[4] = &emu->zero;
    emu->x64emu_parity_tab = x86emu_parity_tab;

    reset_fpu(emu);

    NtCurrentTeb()->TlsSlots[0] = emu;  // FIXME
    return STATUS_SUCCESS;
}

NTSTATUS WINAPI BTCpuTurboThunkControl(ULONG enable)
{
    if (enable) return STATUS_NOT_SUPPORTED;
    return STATUS_SUCCESS;
}

void x86IntImpl(x64emu_t *emu, int code)
{
    int inst_off = box64env.dynarec ? 2 : 0;

    if (code == 0x2e)  /* NT syscall */
    {
        WOW64_CPURESERVED *cpu = NtCurrentTeb()->TlsSlots[WOW64_TLS_CPURESERVED];
        WOW64_CONTEXT *ctx = (WOW64_CONTEXT *)(cpu + 1);
        int id = R_EAX;
        BOOL is_unix_call = FALSE;

        if (ULongToPtr(R_RIP-inst_off) == &unxcode)
            is_unix_call = TRUE;
        else if (ULongToPtr(R_RIP-inst_off) != &bopcode)
            return;

        R_RIP = Pop32(emu);
        ctx->Eip = R_RIP;
        ctx->Esp = R_ESP;
        ctx->Ebx = R_EBX;
        ctx->Esi = R_ESI;
        ctx->Edi = R_EDI;
        ctx->Ebp = R_EBP;
        ctx->EFlags = emu->eflags.x64;
        cpu->Flags = 0;

        if (is_unix_call)
        {
            uintptr_t handle_low = Pop32(emu);
            uintptr_t handle_high = Pop32(emu);
            unsigned int code = Pop32(emu);
            uintptr_t args = Pop32(emu);

            ctx->Esp = R_ESP;
            R_EAX = __wine_unix_call_dispatcher( handle_low | (handle_high << 32), code, (void *)args );
        }
        else
        {
            R_EAX = Wow64SystemServiceEx( id, ULongToPtr(ctx->Esp+4) );
        }

        R_EBX = ctx->Ebx;
        R_ESI = ctx->Esi;
        R_EDI = ctx->Edi;
        R_EBP = ctx->Ebp;
        R_ESP = ctx->Esp;
        R_RIP = ctx->Eip;
        if (cpu->Flags & WOW64_CPURESERVED_FLAG_RESET_STATE)
        {
            cpu->Flags &= ~WOW64_CPURESERVED_FLAG_RESET_STATE;
            R_EAX = ctx->Eax;
            R_ECX = ctx->Ecx;
            R_EDX = ctx->Edx;
            R_FS  = ctx->SegFs & 0xffff;
            emu->segs_offs[_FS] = calculate_fs();
            emu->eflags.x64 = ctx->EFlags;
        }
    }
    else
    {
        RtlRaiseStatus( STATUS_ACCESS_VIOLATION );
    }
}

/* Calls a 2-argument function `Func` setting the parent unwind frame information to the given SP and PC */
static void __attribute__((naked)) SEHFrameTrampoline2Args(void* Arg0, int Arg1, void* Func, uint64_t Sp, uint64_t Pc)
{
    asm( ".seh_proc SEHFrameTrampoline2Args\n\t"
         "stp x3, x4, [sp, #-0x10]!\n\t"
         ".seh_pushframe\n\t"
         "stp x29, x30, [sp, #-0x10]!\n\t"
         ".seh_save_fplr_x 16\n\t"
         ".seh_endprologue\n\t"
         "blr x2\n\t"
         "ldp x29, x30, [sp], 0x20\n\t"
         "ret\n\t"
         ".seh_endproc" );
}

void x86Int(void* emu, int code)
{
    CONTEXT *entry_context = NtCurrentTeb()->TlsSlots[WOW64_TLS_MAX_NUMBER];
    SEHFrameTrampoline2Args(emu, code, (void*)x86IntImpl, entry_context->Sp, entry_context->Pc);
    NtCurrentTeb()->TlsSlots[WOW64_TLS_MAX_NUMBER] = entry_context;
}

NTSTATUS WINAPI LdrDisableThreadCalloutsForDll(HMODULE);

BOOL WINAPI DllMainCRTStartup(HINSTANCE inst, DWORD reason, void* reserved)
{
    if (reason == DLL_PROCESS_ATTACH) LdrDisableThreadCalloutsForDll(inst);
    return TRUE;
}
