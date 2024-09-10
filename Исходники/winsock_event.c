/** handle is_signal events and see if signalled */
static void _getdns_handle_signal(struct _getdns_event* ev)
{
	DWORD ret;
	//log_assert(ev->is_signal && ev->hEvent);
	/* see if the event is signalled */
	ret = WSAWaitForMultipleEvents(1, &ev->hEvent, 0 /* any object */,
		0 /* return immediately */, 0 /* not alertable for IOcomple*/);
	if(ret == WSA_WAIT_IO_COMPLETION || ret == WSA_WAIT_FAILED) {
		log_err("getdns: WSAWaitForMultipleEvents(signal) failed: %s",
			wsa_strerror(WSAGetLastError()));
		return;
	}
	if(ret == WSA_WAIT_TIMEOUT) {
		/* not signalled */
		return;
	}

	/* reset the signal */
	if(!WSAResetEvent(ev->hEvent))
		log_err("getdns: WSAResetEvent failed: %s",
			wsa_strerror(WSAGetLastError()));
	/* do the callback (which may set the signal again) */
	fptr_ok(fptr_whitelist_event(ev->ev_callback));
	(*ev->ev_callback)(ev->ev_fd, ev->ev_events, ev->ev_arg);
}