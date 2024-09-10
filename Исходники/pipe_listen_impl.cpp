void CL_PipeListen_Impl::cancel_accept()
{
#ifdef WIN32
	if (!async_io)
		throw CL_Exception("CL_PipeConnection is not in an async I/O state");

	BOOL result = CancelIo(handle);
	if (result == FALSE)
		throw CL_Exception("CancelIo failed");

	DWORD bytes_transfered = 0;
	result = GetOverlappedResult(handle, &accept_overlapped, &bytes_transfered, TRUE);
	if (result == TRUE)
	{
		result = DisconnectNamedPipe(handle);
	}
	else if (GetLastError() != ERROR_OPERATION_ABORTED)
	{
		throw CL_Exception("GetOverlappedResult failed");
	}
	async_io = false;
#endif
}