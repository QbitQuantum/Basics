bool ClientSession::PostRecv()
{
	if (!IsConnected())
		return false;

	if (0 == mCircularBuffer->GetFreeSpaceSize())
		return false;

	RioIoContext* recvContext = new RioIoContext(this, IO_RECV);

	recvContext->BufferId = mRioBufferId;
	recvContext->Length = static_cast<ULONG>(mCircularBuffer->GetFreeSpaceSize());
	recvContext->Offset = mCircularBuffer->GetWritableOffset();
	
	DWORD recvbytes = 0;
	DWORD flags = 0;

	/// start async recv
	if (!RIO.RIOReceive(mRequestQueue, (PRIO_BUF)recvContext, 1, flags, recvContext))
	{
		printf_s("[DEBUG] RIOReceive error: %d\n", GetLastError());
		ReleaseContext(recvContext);
		return false;
	}

	return true;
}