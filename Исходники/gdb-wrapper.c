int main(int argc, char** argv) {
	enum {
		 envbufsize = 1024*32
		,exebufsize = 1024
		,cmdbufsize = envbufsize
	};

	char *envbuf, *sep, *resbuf, *cmdbuf;
	DWORD len, exitCode;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	DIE_IF_FALSE(
		(envbuf = malloc(envbufsize))
	);
	DIE_IF_FALSE(
		(cmdbuf = malloc(cmdbufsize))
	);
	*cmdbuf = 0;

	DIE_IF_FALSE(
		GetEnvironmentVariable("PATH", envbuf, envbufsize)
	);
    dbg_printf("env: %s\n", envbuf);

	DIE_IF_FALSE(
		GetModuleFileName(0, cmdbuf, exebufsize)
	);
    dbg_printf("curdir: %s\n", cmdbuf);

	DIE_IF_FALSE(
		(sep = strrchr(cmdbuf, '\\'))
	);
	*(sep+1) = 0;
	strcat(cmdbuf, GDB_TO_PYTHON_REL_DIR);
	dbg_printf("sep: %s\n", cmdbuf);

	len = strlen(envbuf)+strlen(cmdbuf)
		+1  /* for envronment separator */
		+1; /* for zero-terminator */
	
	DIE_IF_FALSE(
		(resbuf = malloc(len))
	);

	DIE_IF_FALSE(
		(snprintf(resbuf, len, "%s;%s", cmdbuf, envbuf) > 0)
	);
    dbg_printf("PATH: %s\n", resbuf);

	DIE_IF_FALSE(
		SetEnvironmentVariable("PATH", resbuf)
	);

	*(sep+1) = 0;
	strcat(cmdbuf, PYTHONHOME_REL_DIR);
	dbg_printf("PYTHONHOME: %s\n", cmdbuf);
	DIE_IF_FALSE(
		SetEnvironmentVariable("PYTHONHOME", cmdbuf)
	);
	
	*(sep+1) = 0;
	strcat(cmdbuf, GDB_EXECUTABLE_ORIG_FILENAME" ");
	
	if ( argc > 1 ) {
		for ( ++argv; *argv; ++argv ) {
			len = strlen(cmdbuf);
			snprintf(cmdbuf+len, cmdbufsize-len, "%s ", *argv);
		}
	}
	dbg_printf("cmd: %s\n", cmdbuf);

	HANDLE ghJob = CreateJobObject(NULL, "Gdb-Wrapper\0"/*NULL*/);
	if ( ghJob == NULL ) {
		dbg_printf("Could not create job object\n");
	} else {
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };
		// Configure all child processes associated with the job to terminate when the last handle to the job is closed
		jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
		if ( SetInformationJobObject(ghJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli)) == 0 ) {
			dbg_printf("Could not SetInformationJobObject\n");
		}
	}

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags |= STARTF_USESTDHANDLES;
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	memset(&pi, 0, sizeof(pi));

	DIE_IF_FALSE(
		CreateProcess(
			 0			// exe name
			,cmdbuf	// command line
			,0			// process security attributes
			,0			// primary thread security attributes
			,TRUE		// handles are inherited
			,0			// creation flags
			,0			// use parent's environment
			,0			// use parent's current directory
			,&si		// STARTUPINFO pointer
			,&pi		// receives PROCESS_INFORMATION
		)
	);

	if ( ghJob != NULL && AssignProcessToJobObject(ghJob, pi.hProcess) == 0 ) {
		dbg_printf("Could not AssignProcessToObject\n");
	}

	// Do not handle Ctrl-C in the wrapper
	SetConsoleCtrlHandler(NULL, TRUE);

	WaitForSingleObject(pi.hProcess, INFINITE);
	
	DIE_IF_FALSE(
		GetExitCodeProcess(pi.hProcess, &exitCode)
	);

	if ( ghJob != NULL )
		CloseHandle(ghJob);
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	free(envbuf);
	free(resbuf);
	free(cmdbuf);
	
	dbg_printf("exiting with exitCode %d", exitCode);

	return exitCode;
}