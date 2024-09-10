ProcessHandleImpl* ProcessImpl::launchImpl(const std::string& command, const ArgsImpl& args, const std::string& initialDirectory, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe, const EnvImpl& env)
{
	std::string commandLine = command;
	for (ArgsImpl::const_iterator it = args.begin(); it != args.end(); ++it)
	{
		commandLine.append(" ");
		commandLine.append(*it);
	}		

	std::wstring ucommandLine;
	UnicodeConverter::toUTF16(commandLine, ucommandLine);

	STARTUPINFOW startupInfo;
	GetStartupInfoW(&startupInfo); // take defaults from current process
	startupInfo.cb          = sizeof(STARTUPINFOW);
	startupInfo.lpReserved  = NULL;
	startupInfo.lpDesktop   = NULL;
	startupInfo.lpTitle     = NULL;
	startupInfo.dwFlags     = STARTF_FORCEOFFFEEDBACK;
	startupInfo.cbReserved2 = 0;
	startupInfo.lpReserved2 = NULL;

	HANDLE hProc = GetCurrentProcess();
	bool mustInheritHandles = false;
	if (inPipe)
	{
		DuplicateHandle(hProc, inPipe->readHandle(), hProc, &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
		mustInheritHandles = true;
		inPipe->close(Pipe::CLOSE_READ);
	}
	else if (GetStdHandle(STD_INPUT_HANDLE))
	{
		DuplicateHandle(hProc, GetStdHandle(STD_INPUT_HANDLE), hProc, &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
		mustInheritHandles = true;
	}
	else 
	{
		startupInfo.hStdInput = 0;
	}
	// outPipe may be the same as errPipe, so we duplicate first and close later.
	if (outPipe)
	{
		DuplicateHandle(hProc, outPipe->writeHandle(), hProc, &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
		mustInheritHandles = true;
	}
	else if (GetStdHandle(STD_OUTPUT_HANDLE))
	{
		DuplicateHandle(hProc, GetStdHandle(STD_OUTPUT_HANDLE), hProc, &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
		mustInheritHandles = true;
	}
	else 
	{
		startupInfo.hStdOutput = 0;
	}
	if (errPipe)
	{
		DuplicateHandle(hProc, errPipe->writeHandle(), hProc, &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
		mustInheritHandles = true;
	}
	else if (GetStdHandle(STD_ERROR_HANDLE))
	{
		DuplicateHandle(hProc, GetStdHandle(STD_ERROR_HANDLE), hProc, &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
		mustInheritHandles = true;
	}
	else
	{
		startupInfo.hStdError = 0;
	}
	if (outPipe) outPipe->close(Pipe::CLOSE_WRITE);
	if (errPipe) errPipe->close(Pipe::CLOSE_WRITE);

	if (mustInheritHandles)
	{
		startupInfo.dwFlags |= STARTF_USESTDHANDLES;
	}

	std::wstring uinitialDirectory;
	UnicodeConverter::toUTF16(initialDirectory, uinitialDirectory);
	const wchar_t* workingDirectory = uinitialDirectory.empty() ? 0 : uinitialDirectory.c_str();

	const char* pEnv = 0;
	std::vector<char> envChars;
	if (!env.empty())
	{
		envChars = getEnvironmentVariablesBuffer(env);
		pEnv = &envChars[0];
	}
		
	PROCESS_INFORMATION processInfo;
	DWORD creationFlags = GetConsoleWindow() ? 0 : CREATE_NO_WINDOW;
	BOOL rc = CreateProcessW(
		NULL, // applicationName
		const_cast<wchar_t*>(ucommandLine.c_str()), 
		NULL, // processAttributes
		NULL, // threadAttributes
		mustInheritHandles,
		creationFlags,
		(LPVOID) pEnv, 
		workingDirectory,
		&startupInfo, 
		&processInfo
	);
	if (startupInfo.hStdInput) CloseHandle(startupInfo.hStdInput);
	if (startupInfo.hStdOutput) CloseHandle(startupInfo.hStdOutput);
	if (startupInfo.hStdError) CloseHandle(startupInfo.hStdError);
	if (rc)
	{
		CloseHandle(processInfo.hThread);
		return new ProcessHandleImpl(processInfo.hProcess, processInfo.dwProcessId);
	}
	else throw SystemException("Cannot launch process", command);
}