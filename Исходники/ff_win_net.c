int ff_win_net_complete_overlapped_io(SOCKET socket, WSAOVERLAPPED *overlapped)
{
	struct ff_fiber *current_fiber;
	int int_bytes_transferred = -1;
	BOOL result;
	DWORD flags;
	DWORD bytes_transferred;

	current_fiber = ff_fiber_get_current();
	ff_win_completion_port_register_overlapped_data(net_ctx.completion_port, overlapped, current_fiber);
	ff_core_yield_fiber();
	ff_win_completion_port_deregister_overlapped_data(net_ctx.completion_port, overlapped);

	result = WSAGetOverlappedResult(socket, overlapped, &bytes_transferred, FALSE, &flags);
	if (result != FALSE)
	{
		int_bytes_transferred = (int) bytes_transferred;
	}
	else
	{
		int last_error;

		last_error = WSAGetLastError();
		ff_log_debug(L"the overlapped operation on the socket=%llu, overlapped=%p failed. WSAGetLastError()=%d", (uint64_t) socket, overlapped, last_error);
	}

	return int_bytes_transferred;
}