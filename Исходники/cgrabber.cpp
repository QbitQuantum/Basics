int mainproc() {
	memset(&pi, 0, sizeof(pi));

	SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;

#ifndef REDIRECTIO
	//Windows does this automatically but since we have a separate app and all, let's make sure.
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
#else
	HANDLE hWriteStdIn, hReadStdOut, hReadStdErr;
	makeOutputPipe(&hWriteStdIn, &si.hStdInput);
	makeInputPipe(&si.hStdOutput, &hReadStdOut);
	makeInputPipe(&si.hStdError, &hReadStdErr);
#endif
	TCHAR* moduleFilename = GetModuleFilenameStr(0);
	TCHAR* appName = replaceFilename(moduleFilename, L"Grabber.exe");
	TCHAR* cmdLine = buildCommandLine(GetCommandLine(), L" -c");

	if (!CreateProcess(appName, cmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
		ThrowLastOsError(L"Cannot run the core application.");
	CloseHandle(pi.hThread);

	delete cmdLine;
	delete appName;
	delete moduleFilename;

#ifndef REDIRECTIO
	DWORD res = WaitForSingleObject(pi.hProcess, INFINITE);
#else
	//These went to children process
	CloseHandle(si.hStdInput);
	CloseHandle(si.hStdError);
	CloseHandle(si.hStdOutput);

	HANDLE hInputThread = RunTranslationThread(GetStdHandle(STD_INPUT_HANDLE), hWriteStdIn);
#ifdef THREADEDOUTPUT
	HANDLE hOutputThread = RunTranslationThread(hReadStdOut, GetStdHandle(STD_OUTPUT_HANDLE));
	HANDLE hErrorThread = RunTranslationThread(hReadStdErr, GetStdHandle(STD_ERROR_HANDLE));
#else
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hStdError = GetStdHandle(STD_ERROR_HANDLE);
#endif

	DWORD res = 0;
	do {
#ifndef THREADEDOUTPUT
		TryTranslateOutput(hReadStdOut, hStdOutput);
		TryTranslateOutput(hReadStdErr, hStdError);
#endif
		res = WaitForSingleObject(pi.hProcess, 5);
	} while (res == WAIT_TIMEOUT);


#ifndef THREADEDOUTPUT
	//final part
	TryTranslateOutput(hReadStdOut, hStdOutput);
	TryTranslateOutput(hReadStdErr, hStdError);
#endif

	TerminateThread(hInputThread, -1); //the process ended, no point in even writing there
	CloseHandle(hInputThread);

#ifdef THREADEDOUTPUT
	WaitForSingleObject(hOutputThread, INFINITE); //wait until it reads everything there is
	CloseHandle(hOutputThread);
	WaitForSingleObject(hErrorThread, INFINITE);
	CloseHandle(hErrorThread);
#endif

	CloseHandle(hWriteStdIn);
	CloseHandle(hReadStdErr);
	CloseHandle(hReadStdOut);
#endif

	if (res != WAIT_OBJECT_0)
		ThrowLastOsError(L"Cannot wait on the main process");

	DWORD ExitCode = 0;
	if (!GetExitCodeProcess(pi.hProcess, &ExitCode))
		ThrowLastOsError(L"Cannot retrieve execution result");
	CloseHandle(pi.hProcess);
	return ExitCode;
}