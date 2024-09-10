bool_t hdhomerun_sock_connect(hdhomerun_sock_t sock, uint32_t remote_addr, uint16_t remote_port, uint64_t timeout)
{
	WSAEVENT wsa_event = WSACreateEvent();
	if (wsa_event == WSA_INVALID_EVENT) {
		return FALSE;
	}

	if (WSAEventSelect(sock, wsa_event, FD_CONNECT) == SOCKET_ERROR) {
		WSACloseEvent(wsa_event);
		return FALSE;
	}

	/* Connect (non-blocking). */
	struct sockaddr_in sock_addr;
	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = htonl(remote_addr);
	sock_addr.sin_port = htons(remote_port);

	if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) != 0) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			WSACloseEvent(wsa_event);
			return FALSE;
		}
	}

	/* Wait for connect to complete (both success and failure will signal). */
	DWORD ret = WaitForSingleObjectEx(wsa_event, (DWORD)timeout, FALSE);
	WSACloseEvent(wsa_event);

	if (ret != WAIT_OBJECT_0) {
		return FALSE;
	}

	/* Detect success/failure. */
	int sockaddr_size = sizeof(sock_addr);
	if (getpeername(sock, (struct sockaddr *)&sock_addr, &sockaddr_size) != 0) {
		return FALSE;
	}

	return TRUE;
}