void
gas_start_reading (gas_client_info *ci)
{
	DWORD flags=0, bytes=0;

	gas_trim_buffer (ci->rb);
	GAS_CI_SET_MARK_AT_TAIL (ci->rb);

	if (ci->overlapped!=NULL) {
		memset(ci->overlapped, 0, sizeof(WSAOVERLAPPED));
		ci->operation = GAS_OP_READ;
	}
	WSABUF wsabuf = { GAS_CI_GET_FREE_SPACE(ci->rb), GAS_CI_GET_DATA_TAIL(ci->rb) };

	if (WSARecv(ci->socket, &wsabuf, 1, &bytes, &flags, (WSAOVERLAPPED *)ci->overlapped, NULL) == SOCKET_ERROR) {
		ci->error = GAS_TRUE;
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING && err != WSAECONNABORTED)
			gas_error_message ("Error %d in WSARecv\n", err);
	}
	else
		gas_debug_message (GAS_IO, "Immediate read\n");
}