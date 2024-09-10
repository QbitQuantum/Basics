/* 
* Add new socket to the watcher.
*/
int tnet_transport_add_socket(const tnet_transport_handle_t *handle, tnet_fd_t fd, tnet_socket_type_t type, tsk_bool_t take_ownership, tsk_bool_t isClient)
{
	tnet_transport_t *transport = (tnet_transport_t*)handle;
	transport_context_t* context;
	int ret = -1;

	if(!transport){
		TSK_DEBUG_ERROR("Invalid server handle.");
		return ret;
	}

	if(!(context = (transport_context_t*)transport->context)){
		TSK_DEBUG_ERROR("Invalid context.");
		return -2;
	}

	if(TNET_SOCKET_TYPE_IS_TLS(type)){
		transport->tls.have_tls = 1;
	}

	addSocket(fd, type, transport, take_ownership, isClient);
	if(WSAEventSelect(fd, context->events[context->count - 1], FD_ALL_EVENTS) == SOCKET_ERROR){
		removeSocket((context->count - 1), context);
		TNET_PRINT_LAST_ERROR("WSAEventSelect have failed.");
		return -1;
	}

	/* Signal */
	if(WSASetEvent(context->events[0])){
		TSK_DEBUG_INFO("New socket added to the network transport.");
		return 0;
	}

	// ...
	
	return -1;
}