// establish a connection to the specified pipe and returns its handle
// static
HANDLE Client::connectPipe(const wchar_t* pipeName) {
	bool hasErrors = false;
	HANDLE pipe = INVALID_HANDLE_VALUE;
	for (;;) {
		pipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (pipe != INVALID_HANDLE_VALUE) {
			// the pipe is successfully created
			// security check: make sure that we're connecting to the correct server
			ULONG serverPid;
			if (GetNamedPipeServerProcessId(pipe, &serverPid)) {
				// FIXME: check the command line of the server?
				// See this: http://www.codeproject.com/Articles/19685/Get-Process-Info-with-NtQueryInformationProcess
				// Too bad! Undocumented Windows internal API might be needed here. :-(
			}
			break;
		}
		// being busy is not really an error since we just need to wait.
		if (GetLastError() != ERROR_PIPE_BUSY) {
			hasErrors = true; // otherwise, pipe creation fails
			break;
		}
		// All pipe instances are busy, so wait for 2 seconds.
		if (!WaitNamedPipe(pipeName, 2000)) {
			hasErrors = true;
			break;
		}
	}

	if (!hasErrors) {
		// The pipe is connected; change to message-read mode.
		DWORD mode = PIPE_READMODE_MESSAGE;
		if (!SetNamedPipeHandleState(pipe, &mode, NULL, NULL)) {
			hasErrors = true;
		}
	}

	// the pipe is created, but errors happened, destroy it.
	if (hasErrors && pipe != INVALID_HANDLE_VALUE) {
		DisconnectNamedPipe(pipe);
		CloseHandle(pipe);
		pipe = INVALID_HANDLE_VALUE;
	}
	return pipe;
}