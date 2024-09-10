BOOL Go(const char *commandLine)
{
	HANDLE stdInRead, stdInWrite;

	if (!CreatePipes(&stdInRead, &stdInWrite)) return FALSE;


	PROCESS_INFORMATION piProcInfo; 
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE; 

	
	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );

	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO); 
	siStartInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	siStartInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	siStartInfo.hStdInput = stdInRead;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	siStartInfo.wShowWindow = SW_HIDE;
	siStartInfo.dwFlags |= STARTF_USESHOWWINDOW;
	// Create the child process. 

	if (!CreateProcess(NULL, 
		const_cast<char *>(commandLine),   // command line 
		NULL,          // process security attributes 
		NULL,          // primary thread security attributes 
		TRUE,          // handles are inherited 
		CREATE_BREAKAWAY_FROM_JOB,             // creation flags 
		NULL,          // use parent's environment 
		NULL,          // use parent's current directory 
		&siStartInfo,  // STARTUPINFO pointer 
		&piProcInfo))  // receives PROCESS_INFORMATION 
	{
		return FALSE;
	}

	HANDLE ghJob = CreateJobObject( NULL, NULL);

	JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };
	jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	if( ghJob == NULL || SetInformationJobObject( ghJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli)) == FALSE) {
		std::cerr << "Error initializing close-process job";
		return 1;
	}

	if (!AssignProcessToJobObject( ghJob, piProcInfo.hProcess)) {
		DWORD error = GetLastError();
		std::cerr << "AssignProcessToJobObject failed: " << error << std::endl;
		return FALSE;
	}

	// Close handles to the child process and its primary thread.
	// Some applications might keep these handles to monitor the status
	// of the child process, for example. 

	CloseHandle(piProcInfo.hThread);
	MonitorProcessClose(piProcInfo.hProcess);

	WriteToPipe(stdInWrite, piProcInfo.hProcess);
	
	CloseHandle(piProcInfo.hProcess);
	CloseHandle(stdInRead);
	CloseHandle(stdInWrite);


	return 0;
}