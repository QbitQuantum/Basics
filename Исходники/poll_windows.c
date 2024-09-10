static __inline BOOL cancel_io(int _index)
{
	if ((_index < 0) || (_index >= MAX_FDS)) {
		return FALSE;
	}

	if ( (poll_fd[_index].fd < 0) || (poll_fd[_index].handle == INVALID_HANDLE_VALUE)
	  || (poll_fd[_index].handle == 0) || (poll_fd[_index].overlapped == NULL) ) {
		return TRUE;
	}
	if (CancelIoEx_Available) {
		return (*pCancelIoEx)(poll_fd[_index].handle, poll_fd[_index].overlapped);
	}
	if (_poll_fd[_index].thread_id == GetCurrentThreadId()) {
		return CancelIo(poll_fd[_index].handle);
	}
	usbi_warn(NULL, "Unable to cancel I/O that was started from another thread");
	return FALSE;
}