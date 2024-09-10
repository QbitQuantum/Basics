DWORD ipcSendRequest(HANDLE hSignal, HANDLE hWaitFor, THeaderIPC *pipch, DWORD dwTimeoutMsecs)
{
	// signal ST to work
	SetEvent(hSignal);
	// wait for reply, it should open a handle to hWaitFor... 
	while (true) {
		switch ( WaitForSingleObjectEx(hWaitFor, dwTimeoutMsecs, true)) {
		case WAIT_OBJECT_0:
			return pipch->fRequests;

		case WAIT_IO_COMPLETION:
			// APC call...
			break;

		default:
			return REPLY_FAIL;
		}
	}
}