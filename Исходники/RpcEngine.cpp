HANDLE RpcEngine::acceptClient() {

	if (!mhServerPipe) {
		return NULL;
	}
	DWORD status;
	DWORD nCount;
	HANDLE events[2];

	nCount = 0;
	events[nCount++] = mhStopEvent;
	events[nCount++] = mhServerPipe;

	status = WaitForMultipleObjects(nCount, events, FALSE, INFINITE);
/*	if (status == WAIT_OBJECT_0) {
		return NULL;
	} else if (status == WAIT_OBJECT_0 +1) {*/
	if (WaitForSingleObject(mhStopEvent, 0) == WAIT_OBJECT_0) {
		WLog_Print(logger_RPCEngine, WLOG_TRACE, "got shutdown signal");
		return NULL;
	}
	if (WaitForSingleObject(mhServerPipe, 0) == WAIT_OBJECT_0) {
		BOOL fConnected;
		DWORD dwPipeMode;

		fConnected = ConnectNamedPipe(mhServerPipe, NULL);

		if (!fConnected)
			fConnected = (GetLastError() == ERROR_PIPE_CONNECTED);

		if (!fConnected) {
			WLog_Print(logger_RPCEngine, WLOG_ERROR, "could not connect client");

			return NULL;
		}

		mhClientPipe = mhServerPipe;

		dwPipeMode = PIPE_WAIT;
		SetNamedPipeHandleState(mhClientPipe, &dwPipeMode, NULL, NULL);
		WLog_Print(logger_RPCEngine, WLOG_TRACE, "connect client with handle %x",mhClientPipe);

		return mhClientPipe;
	}
	return NULL;

}