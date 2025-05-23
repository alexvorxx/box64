#if !(defined(GO) && defined(GOM) && defined(GO2) && defined(DATA))
#error Meh...
#endif

GO(dbus_address_entries_free, vFbp_)
GO(dbus_address_entry_get_method, pFp)
GO(dbus_address_entry_get_value, pFpp)
GO(dbus_address_escape_value, pFp)
GO(dbus_address_unescape_value, pFpbppuuuuup_)
GO(dbus_bus_add_match, vFppbppuuuuup_)
GO(dbus_bus_get, pFubppuuuuup_)
GO(dbus_bus_get_id, pFpbppuuuuup_)
GO(dbus_bus_get_private, pFubppuuuuup_)
GO(dbus_bus_get_unique_name, pFp)
GO(dbus_bus_get_unix_user, LFppbppuuuuup_)
GO(dbus_bus_name_has_owner, uFppbppuuuuup_)
GO(dbus_bus_register, uFpbppuuuuup_)
GO(dbus_bus_release_name, iFppbppuuuuup_)
GO(dbus_bus_remove_match, vFppbppuuuuup_)
GO(dbus_bus_request_name, iFppubppuuuuup_)
GO(dbus_bus_set_unique_name, uFpp)
GO(dbus_bus_start_service_by_name, uFppupbppuuuuup_)
GOM(dbus_connection_add_filter, uFEpppp)
GO(dbus_connection_allocate_data_slot, uFp)
GO(dbus_connection_borrow_message, pFp)
GO(dbus_connection_can_send_type, uFpi)
GO(dbus_connection_close, vFp)
GO(dbus_connection_dispatch, uFp)
GO(dbus_connection_flush, vFp)
GO(dbus_connection_free_data_slot, vFp)
GO(dbus_connection_free_preallocated_send, vFpp)
GO(dbus_connection_get_adt_audit_session_data, uFpbp_p)
GO(dbus_connection_get_data, pFpi)
GO(dbus_connection_get_dispatch_status, uFp)
GO(dbus_connection_get_is_anonymous, uFp)
GO(dbus_connection_get_is_authenticated, uFp)
GO(dbus_connection_get_is_connected, uFp)
GO(dbus_connection_get_max_message_size, lFp)
GO(dbus_connection_get_max_received_size, lFp)
GO(dbus_connection_get_object_path_data, uFppbp_)
GO(dbus_connection_get_outgoing_size, lFp)
GO(dbus_connection_get_server_id, pFp)
GO(dbus_connection_get_socket, uFpp)
GO(dbus_connection_get_unix_fd, uFpp)
GO(dbus_connection_get_unix_process_id, uFpbL_)
GO(dbus_connection_get_unix_user, uFpbL_)
GO(dbus_connection_get_windows_user, uFpbp_)
GO(dbus_connection_has_messages_to_send, uFp)
//GOM(dbus_connection_list_registered, uFEppbp_)
GO(dbus_connection_open, pFpbppuuuuup_)
GO(dbus_connection_open_private, pFpbppuuuuup_)
GO(dbus_connection_pop_message, pFp)
GO(dbus_connection_preallocate_send, pFp)
GO(dbus_connection_read_write, uFpi)
GO(dbus_connection_read_write_dispatch, uFpi)
GO(dbus_connection_ref, pFp)
//GOM(dbus_connection_register_fallback, uFEppbpppppp_p)
//GOM(dbus_connection_register_object_path, uFEppbpppppp_p)
GOM(dbus_connection_remove_filter, vFEppp)
GO(dbus_connection_return_message, vFpp)
GO(dbus_connection_send, uFppp)
GO(dbus_connection_send_preallocated, vFpppp)
GO(dbus_connection_send_with_reply, uFppbp_i)
GO(dbus_connection_send_with_reply_and_block, pFppibppuuuuup_)
GO(dbus_connection_set_allow_anonymous, vFpu)
GO(dbus_connection_set_change_sigpipe, vFu)
GOM(dbus_connection_set_data, uFEpipp)
GOM(dbus_connection_set_dispatch_status_function, vFEpppp)
GO(dbus_connection_set_exit_on_disconnect, vFpu)
GO(dbus_connection_set_max_message_size, vFpl)
GO(dbus_connection_set_max_received_size, vFpl)
GO(dbus_connection_set_route_peer_messages, vFpu)
GOM(dbus_connection_set_timeout_functions, uFEpppppp)
//GOM(dbus_connection_set_unix_user_function, vFEpppp)
GOM(dbus_connection_set_wakeup_main_function, vFEpppp)
GOM(dbus_connection_set_watch_functions, uFEpppppp)
//GOM(dbus_connection_set_windows_user_function, vFEpppp)
GO(dbus_connection_steal_borrowed_message, vFpp)
//GOM(dbus_connection_try_register_fallback, uFEppbpppppp_pbppuuuuup_)
GOM(dbus_connection_try_register_object_path, uFEppppbppuuuuup_)
GO(dbus_connection_unref, vFp)
GO(dbus_connection_unregister_object_path, uFpp)
GO(dbus_error_free, vFbppuuuuup_)
GO(dbus_error_has_name, uFbppuuuuup_p)
GO(dbus_error_init, vFbppuuuuup_)
GO(dbus_error_is_set, uFbppuuuuup_)
GO(dbus_free, vFp)
GOM(dbus_free_string_array, vFEp)
GO(dbus_get_local_machine_id, pFv)
GO(dbus_get_version, vFppp)
//GO(dbus_internal_do_not_use_create_uuid, 
//GO(dbus_internal_do_not_use_get_uuid, 
GO(dbus_malloc, pFL)
GO(dbus_malloc0, pFL)
GO(dbus_message_allocate_data_slot, uFp)
GOM(dbus_message_append_args, uFEpiV)
GOM(dbus_message_append_args_valist, uFEpip)    //%%
GO(dbus_message_copy, pFp)
GO(dbus_message_demarshal, pFpibppuuuuup_)
GO(dbus_message_demarshal_bytes_needed, iFpi)
GO(dbus_message_free_data_slot, vFp)
GOM(dbus_message_get_args, uFEpbppuuuuup_iV)
GO(dbus_message_get_allow_interactive_authorization, uFp)
GOM(dbus_message_get_args_valist, uFEpbppuuuuup_ip) //%%
GO(dbus_message_get_auto_start, uFp)
GO(dbus_message_get_data, pFpi)
GO(dbus_message_get_destination, pFp)
GO(dbus_message_get_error_name, pFp)
GO(dbus_message_get_interface, pFp)
GO(dbus_message_get_member, pFp)
GO(dbus_message_get_no_reply, uFp)
GO(dbus_message_get_path, pFp)
//GOM(dbus_message_get_path_decomposed, uFEpbp_)
GO(dbus_message_get_reply_serial, uFp)
GO(dbus_message_get_sender, pFp)
GO(dbus_message_get_serial, uFp)
GO(dbus_message_get_signature, pFp)
GO(dbus_message_get_type, iFp)
GO(dbus_message_has_destination, uFpp)
GO(dbus_message_has_interface, uFpp)
GO(dbus_message_has_member, uFpp)
GO(dbus_message_has_path, uFpp)
GO(dbus_message_has_sender, uFpp)
GO(dbus_message_has_signature, uFpp)
GO(dbus_message_is_error, uFpp)
GO(dbus_message_is_method_call, uFppp)
GO(dbus_message_is_signal, uFppp)
GO(dbus_message_iter_abandon_container, vFbppuiiiiiiiiipp_bppuiiiiiiiiipp_)
GOM(dbus_message_iter_append_basic, uFEbppuiiiiiiiiipp_ip)
GO(dbus_message_iter_append_fixed_array, uFbppuiiiiiiiiipp_ipi)
GO(dbus_message_iter_close_container, uFbppuiiiiiiiiipp_bppuiiiiiiiiipp_)
GO(dbus_message_iter_get_arg_type, iFbppuiiiiiiiiipp_)
GO(dbus_message_iter_get_array_len, iFbppuiiiiiiiiipp_)
GO(dbus_message_iter_get_basic, vFbppuiiiiiiiiipp_p)
GO(dbus_message_iter_get_element_type, iFbppuiiiiiiiiipp_)
GO(dbus_message_iter_get_element_count, iFbppuiiiiiiiiipp_)
GO(dbus_message_iter_get_fixed_array, vFbppuiiiiiiiiipp_pp)
GO(dbus_message_iter_get_signature, pFbppuiiiiiiiiipp_)
GO(dbus_message_iter_has_next, uFbppuiiiiiiiiipp_)
GO(dbus_message_iter_init, uFpbppuiiiiiiiiipp_)
GO(dbus_message_iter_init_append, vFpbppuiiiiiiiiipp_)
GO(dbus_message_iter_next, uFbppuiiiiiiiiipp_)
GO(dbus_message_iter_open_container, uFbppuiiiiiiiiipp_ipbppuiiiiiiiiipp_)
GO(dbus_message_iter_recurse, vFbppuiiiiiiiiipp_bppuiiiiiiiiipp_)
GO(dbus_message_lock, vFp)
GO(dbus_message_marshal, uFpbp_p)
GO(dbus_message_new, pFi)
GO(dbus_message_new_error, pFppp)
//GOM(dbus_message_new_error_printf, pFEpppV)
GO(dbus_message_new_method_call, pFpppp)
GO(dbus_message_new_method_return, pFp)
GO(dbus_message_new_signal, pFppp)
GO(dbus_message_ref, pFp)
GO(dbus_message_set_allow_interactive_authorization, vFpu)
GO(dbus_message_set_auto_start, vFpu)
//GOM(dbus_message_set_data, uFEpipp)
GO(dbus_message_set_destination, uFpp)
GO(dbus_message_set_error_name, uFpp)
GO(dbus_message_set_interface, uFpp)
GO(dbus_message_set_member, uFpp)
GO(dbus_message_set_no_reply, vFpu)
GO(dbus_message_set_path, uFpp)
GO(dbus_message_set_reply_serial, uFpu)
GO(dbus_message_set_sender, uFpp)
GO(dbus_message_set_serial, vFpu)
GO(dbus_message_type_from_string, iFp)
GO(dbus_message_type_to_string, pFi)
GO(dbus_message_unref, vFp)
GO(dbus_move_error, vFbppuuuuup_bppuuuuup_)
//GOM(dbus_parse_address, uFEpbp_pbppuuuuup_)
GO(dbus_pending_call_allocate_data_slot, uFp)
GO(dbus_pending_call_block, vFp)
GO(dbus_pending_call_cancel, vFp)
GO(dbus_pending_call_free_data_slot, vFp)
GO(dbus_pending_call_get_completed, uFp)
GO(dbus_pending_call_get_data, pFpi)
GO(dbus_pending_call_ref, pFp)
//GOM(dbus_pending_call_set_data, uFEpipp)
//GOM(dbus_pending_call_set_notify, uFEpppp)
GO(dbus_pending_call_steal_reply, pFp)
GO(dbus_pending_call_unref, vFp)
GO(dbus_realloc, pFpL)
GO(dbus_server_allocate_data_slot, uFp)
GO(dbus_server_disconnect, vFp)
GO(dbus_server_free_data_slot, vFp)
GO(dbus_server_get_address, pFp)
GO(dbus_server_get_data, pFpi)
GO(dbus_server_get_id, pFp)
GO(dbus_server_get_is_connected, uFp)
GO(dbus_server_listen, pFpbppuuuuup_)
GO(dbus_server_ref, pFp)
GO(dbus_server_set_auth_mechanisms, uFpbp_)
//GOM(dbus_server_set_data, uFEpipp)
//GOM(dbus_server_set_new_connection_function, vFEpppp)
//GOM(dbus_server_set_timeout_functions, uFEpppppp)
//GOM(dbus_server_set_watch_functions, uFEpppppp)
GO(dbus_server_unref, vFp)
//GOM(dbus_set_error, vFEbppuuuuup_ppV)
GO(dbus_set_error_const, vFbppuuuuup_pp)
GO(dbus_set_error_from_message, uFbppuuuuup_p)
GO(dbus_shutdown, vFv)
GO(dbus_signature_iter_get_current_type, iFbppuii_)
GO(dbus_signature_iter_get_element_type, iFbppuii_)
GO(dbus_signature_iter_get_signature, pFbppuii_)
GO(dbus_signature_iter_init, vFbppuii_p)
GO(dbus_signature_iter_next, uFbppuii_)
GO(dbus_signature_iter_recurse, vFbppuii_bppuii_)
GO(dbus_signature_validate, uFpbppuuuuup_)
GO(dbus_signature_validate_single, uFpbppuuuuup_)
//GOM(dbus_threads_init, uFEbupppppppppppppppppp_)
GO(dbus_threads_init_default, uFv)
GO(dbus_timeout_get_data, pFp)
GO(dbus_timeout_get_enabled, uFp)
GO(dbus_timeout_get_interval, iFp)
GO(dbus_timeout_handle, uFp)
GOM(dbus_timeout_set_data, vFEppp)
GO(dbus_type_is_basic, uFi)
GO(dbus_type_is_container, uFi)
GO(dbus_type_is_fixed, uFi)
GO(dbus_type_is_valid, uFi)
GO(dbus_validate_bus_name, uFpbppuuuuup_)
GO(dbus_validate_error_name, uFpbppuuuuup_)
GO(dbus_validate_interface, uFpbppuuuuup_)
GO(dbus_validate_member, uFpbppuuuuup_)
GO(dbus_validate_path, uFpbppuuuuup_)
GO(dbus_validate_utf8, uFpbppuuuuup_)
GO(dbus_watch_get_data, pFp)
GO(dbus_watch_get_enabled, uFp)
GO(dbus_watch_get_fd, iFp)
GO(dbus_watch_get_flags, uFp)
GO(dbus_watch_get_socket, iFp)
GO(dbus_watch_get_unix_fd, iFp)
GO(dbus_watch_handle, uFpu)
GOM(dbus_watch_set_data, vFEppp)
