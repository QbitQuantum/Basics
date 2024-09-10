bool SendAck(HANDLE pipe)
{
	DWORD written, ack = 0;
	if (!WriteFile(pipe, &ack, sizeof(DWORD), &written, NULL) && written != sizeof(DWORD)) {
#ifdef DEBUG_IPC
		CUtils::Log(_T("SendAck: WriteFile failed. (%d)"), GetLastError());
#endif
		return false;
	}
	if (!FlushFileBuffers(pipe)) {
#ifdef DEBUG_IPC
		CUtils::Log(_T("SendAck: FlushFileBuffers failed. (%d)"), GetLastError());
#endif
		return false;
	}
	if (!DisconnectNamedPipe(pipe)) {
#ifdef DEBUG_IPC
		CUtils::Log(_T("SendAck: DisconnectNamedPipe failed. (%d)"), GetLastError());
#endif
		return false;
	}
	return true;
}