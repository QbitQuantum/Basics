bool wsa_recv_empty(socket_t fd, WSAOVERLAPPED& ovl)
{
	DWORD bytes = 0;
	DWORD flags = 0;
	WSABUF ws_buf = { 0, &s_zero };

	memset(&ovl, 0, sizeof(ovl));
	int ret = WSARecv(fd, &ws_buf, 1, &bytes, &flags, &ovl, nullptr);
	if (ret == 0)
	{
		return true;
	}
	else if (ret == SOCKET_ERROR)
	{
		int err = get_socket_error();
		if (err == WSA_IO_PENDING)
		{
			return true;
		}
	}
	return false;
}