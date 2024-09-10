deBool deProcess_start (deProcess* process, const char* commandLine, const char* workingDirectory)
{
	SECURITY_ATTRIBUTES	securityAttr;
	STARTUPINFO			startInfo;

	/* Pipes. */
	HANDLE		stdInRead	= DE_NULL;
	HANDLE		stdInWrite	= DE_NULL;
	HANDLE		stdOutRead	= DE_NULL;
	HANDLE		stdOutWrite	= DE_NULL;
	HANDLE		stdErrRead	= DE_NULL;
	HANDLE		stdErrWrite	= DE_NULL;

	if (process->state == PROCESSSTATE_RUNNING)
	{
		deProcess_setError(process, "Process already running");
		return DE_FALSE;
	}
	else if (process->state == PROCESSSTATE_FINISHED)
	{
		/* Process finished, clean up old cruft. */
		deProcess_cleanupHandles(process);
		process->state = PROCESSSTATE_NOT_STARTED;
	}

	deMemset(&startInfo, 0, sizeof(startInfo));
	deMemset(&securityAttr, 0, sizeof(securityAttr));

	/* Security attributes for inheriting handle. */
	securityAttr.nLength				= sizeof(SECURITY_ATTRIBUTES);
	securityAttr.bInheritHandle			= TRUE;
	securityAttr.lpSecurityDescriptor	= DE_NULL;

	/* Create pipes. \todo [2011-10-03 pyry] Clean up handles on error! */
	if (!CreatePipe(&stdInRead, &stdInWrite, &securityAttr, 0) ||
		!SetHandleInformation(stdInWrite, HANDLE_FLAG_INHERIT, 0))
	{
		deProcess_setErrorFromWin32(process, "CreatePipe() failed");
		CloseHandle(stdInRead);
		CloseHandle(stdInWrite);
		return DE_FALSE;
	}

	if (!CreatePipe(&stdOutRead, &stdOutWrite, &securityAttr, 0) ||
		!SetHandleInformation(stdOutRead, HANDLE_FLAG_INHERIT, 0))
	{
		deProcess_setErrorFromWin32(process, "CreatePipe() failed");
		CloseHandle(stdInRead);
		CloseHandle(stdInWrite);
		CloseHandle(stdOutRead);
		CloseHandle(stdOutWrite);
		return DE_FALSE;
	}

	if (!CreatePipe(&stdErrRead, &stdErrWrite, &securityAttr, 0) ||
		!SetHandleInformation(stdErrRead, HANDLE_FLAG_INHERIT, 0))
	{
		deProcess_setErrorFromWin32(process, "CreatePipe() failed");
		CloseHandle(stdInRead);
		CloseHandle(stdInWrite);
		CloseHandle(stdOutRead);
		CloseHandle(stdOutWrite);
		CloseHandle(stdErrRead);
		CloseHandle(stdErrWrite);
		return DE_FALSE;
	}

	/* Setup startup info. */
	startInfo.cb = sizeof(startInfo);
	startInfo.hStdError		 = stdErrWrite;
	startInfo.hStdOutput	 = stdOutWrite;
	startInfo.hStdInput		 = stdInRead;
	startInfo.dwFlags		|= STARTF_USESTDHANDLES;

	if (!CreateProcess(DE_NULL, (LPTSTR)commandLine, DE_NULL, DE_NULL, TRUE /* inherit handles */, 0, DE_NULL, workingDirectory, &startInfo, &process->procInfo))
	{
		/* Store error info. */
		deProcess_setErrorFromWin32(process, "CreateProcess() failed");

		/* Close all handles. */
		CloseHandle(stdInRead);
		CloseHandle(stdInWrite);
		CloseHandle(stdOutRead);
		CloseHandle(stdOutWrite);
		CloseHandle(stdErrRead);
		CloseHandle(stdErrWrite);

		return DE_FALSE;
	}

	process->state = PROCESSSTATE_RUNNING;

	/* Close our ends of handles.*/
	CloseHandle(stdErrWrite);
	CloseHandle(stdOutWrite);
	CloseHandle(stdInRead);

	/* Construct stdio file objects \note May fail, not detected. */
	process->standardIn		= deFile_createFromHandle((deUintptr)stdInWrite);
	process->standardOut	= deFile_createFromHandle((deUintptr)stdOutRead);
	process->standardErr	= deFile_createFromHandle((deUintptr)stdErrRead);

	return DE_TRUE;
}