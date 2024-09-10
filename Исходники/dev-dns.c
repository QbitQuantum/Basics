*/	DEVICE_CMD Close_DNS(REBREQ *sock)
/*
**		Note: valid even if not open.
**
***********************************************************************/
{
	// Terminate a pending request:
#ifdef HAS_ASYNC_DNS
	if (GET_FLAG(sock->flags, RRF_PENDING)) {
		CLR_FLAG(sock->flags, RRF_PENDING);
		if (sock->handle) WSACancelAsyncRequest(sock->handle);
	}
#endif
	if (sock->net.host_info) OS_Free(sock->net.host_info);
	sock->net.host_info = 0;
	sock->handle = 0;
	SET_CLOSED(sock);
	return DR_DONE; // Removes it from device's pending list (if needed)
}