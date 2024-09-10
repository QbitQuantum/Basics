bool socket_t::b_recfrom()
{
	bool result;

	int ret = WSARecvFrom();

	if(ret == SOCKET_ERROR) {
		int socket_error = _WSAGetLastError();
		if(socket_error == WSA_IO_PENDING) {
			D(bug("WSARecvFrom() i/o pending\r\n"));
			result = true;
		} else {
			D(bug("_WSAGetLastError() returned %d\r\n", socket_error));
			result = false;
		}
	} else /*if(ret == 0) */ {
		D(bug("WSARecvFrom() ok\r\n"));
		// Completion routine call is already scheduled.
		result = true;
	}
	return result;
}