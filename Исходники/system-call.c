int command_start(wchar_t *cmd, COMMAND_HANDLE *commandHandle, LPWSTR* pEnv, DWORD flags)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hReadOut = INVALID_HANDLE_VALUE, hWriteOut = INVALID_HANDLE_VALUE, hReadIn = INVALID_HANDLE_VALUE, hWriteIn = INVALID_HANDLE_VALUE, hReadError = INVALID_HANDLE_VALUE, hWriteError = INVALID_HANDLE_VALUE;
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	si.cb = sizeof(STARTUPINFOW);

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hReadOut, &hWriteOut, &sa, 0)) {
		giterr_set(GITERR_OS, "Could not create pipe");
		return -1;
	}
	if (!CreatePipe(&hReadIn, &hWriteIn, &sa, 0)) {
		giterr_set(GITERR_OS, "Could not create pipe");
		CloseHandle(hReadOut);
		CloseHandle(hWriteOut);
		return -1;
	}
	if (commandHandle->errBuf && !CreatePipe(&hReadError, &hWriteError, &sa, 0)) {
		giterr_set(GITERR_OS, "Could not create pipe");
		CloseHandle(hReadOut);
		CloseHandle(hWriteOut);
		CloseHandle(hReadIn);
		CloseHandle(hWriteIn);
		return -1;
	}

	si.hStdOutput = hWriteOut;
	si.hStdInput = hReadIn;
	si.hStdError = hWriteError;

	// Ensure the read/write handle to the pipe for STDOUT resp. STDIN are not inherited.
	if (!SetHandleInformation(hReadOut, HANDLE_FLAG_INHERIT, 0) || !SetHandleInformation(hWriteIn, HANDLE_FLAG_INHERIT, 0) || (commandHandle->errBuf && !SetHandleInformation(hReadError, HANDLE_FLAG_INHERIT, 0))) {
		giterr_set(GITERR_OS, "SetHandleInformation failed");
		CloseHandle(hReadOut);
		CloseHandle(hWriteOut);
		CloseHandle(hReadIn);
		CloseHandle(hWriteIn);
		safeCloseHandle(&hReadError);
		safeCloseHandle(&hWriteError);
		return -1;
	}

	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

	if (!CreateProcessW(NULL, cmd, NULL, NULL, TRUE, CREATE_UNICODE_ENVIRONMENT | flags, pEnv ? *pEnv : NULL, NULL, &si, &pi)) {
		giterr_set(GITERR_OS, "Could not start external tool");
		CloseHandle(hReadOut);
		CloseHandle(hWriteOut);
		CloseHandle(hReadIn);
		CloseHandle(hWriteIn);
		safeCloseHandle(&hReadError);
		safeCloseHandle(&hWriteError);
		return -1;
	}

	AllowSetForegroundWindow(pi.dwProcessId);
	WaitForInputIdle(pi.hProcess, 10000);

	CloseHandle(hReadIn);
	CloseHandle(hWriteOut);
	if (commandHandle->errBuf) {
		HANDLE asyncReadErrorThread;
		CloseHandle(hWriteError);
		commandHandle->err = hReadError;
		asyncReadErrorThread = commmand_start_reading_thread(&commandHandle->err, commandHandle->errBuf);
		if (!asyncReadErrorThread) {
			CloseHandle(hReadOut);
			CloseHandle(hWriteIn);
			CloseHandle(hReadError);
			return -1;
		}
		commandHandle->asyncReadErrorThread = asyncReadErrorThread;
	}

	commandHandle->pi = pi;
	commandHandle->out = hReadOut;
	commandHandle->in = hWriteIn;
	commandHandle->running = TRUE;
	return 0;
}