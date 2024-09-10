BOOL
MSWindowsWatchdog::doStartProcess(String& command, HANDLE userToken, LPSECURITY_ATTRIBUTES sa)
{
	// clear, as we're reusing process info struct
	ZeroMemory(&m_processInfo, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpDesktop = "winsta0\\Default"; // TODO: maybe this should be \winlogon if we have logonui.exe?
	si.hStdError = m_stdOutWrite;
	si.hStdOutput = m_stdOutWrite;
	si.dwFlags |= STARTF_USESTDHANDLES;

	LPVOID environment;
	BOOL blockRet = CreateEnvironmentBlock(&environment, userToken, FALSE);
	if (!blockRet) {
		LOG((CLOG_ERR "could not create environment block"));
		throw XArch(new XArchEvalWindows);
	}

	DWORD creationFlags = 
		NORMAL_PRIORITY_CLASS |
		CREATE_NO_WINDOW |
		CREATE_UNICODE_ENVIRONMENT;

	// re-launch in current active user session
	LOG((CLOG_INFO "starting new process"));
	BOOL createRet = CreateProcessAsUser(
		userToken, NULL, LPSTR(command.c_str()),
		sa, NULL, TRUE, creationFlags,
		environment, NULL, &si, &m_processInfo);

	DestroyEnvironmentBlock(environment);
	CloseHandle(userToken);

	return createRet;
}