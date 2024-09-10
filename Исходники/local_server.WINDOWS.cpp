bool
LocalServer::read_data(void* buffer, int len)
{
	OVERLAPPED overlapped;
	overlapped.Offset = 0;
	overlapped.OffsetHigh = 0;
	overlapped.hEvent = 0;
	DWORD bytes;
	BOOL done = ReadFile(m_pipe, buffer, len, &bytes, &overlapped);
	if (done == FALSE) {
		DWORD error = GetLastError();
		if (error != ERROR_IO_PENDING) {
			dprintf(D_ALWAYS, "ReadFileError: %u\n", error);
			return false;
		}
		if (GetOverlappedResult(m_pipe, &overlapped, &bytes, TRUE) == FALSE) {
			dprintf(D_ALWAYS, "GetOverlappedResult error: %u\n", GetLastError());
			return false;
		}
	}
	ASSERT(bytes == len);

	return true;
}