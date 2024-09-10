int LLProcessLauncher::launch(void)
{
	// If there was already a process associated with this object, kill it.
	kill();
	orphan();

	int result = 0;
	
	PROCESS_INFORMATION pinfo;
	STARTUPINFOA sinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	
	std::string args = mExecutable;
	for(int i = 0; i < (int)mLaunchArguments.size(); i++)
	{
		args += " ";
		args += mLaunchArguments[i];
	}
	
	// So retarded.  Windows requires that the second parameter to CreateProcessA be a writable (non-const) string...
	char *args2 = new char[args.size() + 1];
	strcpy(args2, args.c_str());

	const char * working_directory = 0;
	if(!mWorkingDir.empty()) working_directory = mWorkingDir.c_str();
	if( ! CreateProcessA( NULL, args2, NULL, NULL, FALSE, 0, NULL, working_directory, &sinfo, &pinfo ) )
	{
		result = GetLastError();

		LPTSTR error_str = 0;
		if(
			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				result,
				0,
				(LPTSTR)&error_str,
				0,
				NULL) 
			!= 0) 
		{
			char message[256];
			wcstombs(message, error_str, 256);
			message[255] = 0;
			llwarns << "CreateProcessA failed: " << message << llendl;
			LocalFree(error_str);
		}

		if(result == 0)
		{
			// Make absolutely certain we return a non-zero value on failure.
			result = -1;
		}
	}
	else
	{
		// foo = pinfo.dwProcessId; // get your pid here if you want to use it later on
		// CloseHandle(pinfo.hProcess); // stops leaks - nothing else
		mProcessHandle = pinfo.hProcess;
		CloseHandle(pinfo.hThread); // stops leaks - nothing else
	}		
	
	delete[] args2;
	
	return result;
}