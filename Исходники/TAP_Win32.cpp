bool CEXIETHERNET::RecvInit()
{
	// Set up recv event

	if ((mHRecvEvent = CreateEvent(nullptr, false, false, nullptr)) == nullptr)
	{
		ERROR_LOG(SP1, "Failed to create recv event:%x", GetLastError());
		return false;
	}

	ZeroMemory(&mReadOverlapped, sizeof(mReadOverlapped));

	RegisterWaitForSingleObject(&mHReadWait, mHRecvEvent, ReadWaitCallback,
		this, INFINITE, WT_EXECUTEDEFAULT);

	mReadOverlapped.hEvent = mHRecvEvent;

	return true;
}