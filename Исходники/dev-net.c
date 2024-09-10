*/	 DEVICE_CMD Close_Socket(REBREQ *sock)
/*
**		Close a socket.
**
**		Returns 0 on success.
**		On failure, error code is OS local.
**
***********************************************************************/
{
	sock->error = 0;

	if (GET_FLAG(sock->state, RSM_OPEN)) {

		sock->state = 0;  // clear: RSM_OPEN, RSM_CONNECT

		// If DNS pending, abort it:
		if (sock->net.host_info) {  // indicates DNS phase active
#ifdef HAS_ASYNC_DNS
			if (sock->handle) WSACancelAsyncRequest(sock->handle);
#endif
			OS_Free(sock->net.host_info);
			sock->socket = sock->length; // Restore TCP socket (see Lookup)
		}

		if (CLOSE_SOCKET(sock->socket)) {
			sock->error = GET_ERROR;
			return DR_ERROR;
		}
	}

	return DR_DONE;
}