EXPORT
BOOL CreateProcessA(LPCTSTR lpApplicationName, LPTSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCTSTR lpCurrentDirectory, LPSTARTUPINFO lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation){
	pid_t pid = vfork();
	//printf("Creating process %s %s\n", lpApplicationName, lpCommandLine);
	if(pid == 0){
		char commandline[256];
		strncpy(commandline, lpCommandLine, 255);
		commandline[255] = 0;
//		ptrace(PT_TRACE_ME, 0, 0, 0);
		// parse command line;
		int i=0;
		char *p = strchr(commandline, ' ');
		char *q = commandline;
		char *argv[16];
		while(p){
			*p = 0;
			argv[i++] = q;
			fflush(stdout);
			q = p + 1;
			p = strchr(commandline, ' ');
		}
		argv[i] = q;
		argv[i+1] = 0;
		//printf("Execing %s %s %s", argv[0], argv[1], argv[2]);
		fflush(stdout);
		execv(argv[0], argv);
		perror("Failed to execv!"); 
	} else {
		DebugActiveProcess(pid);
//		ptrace(PT_ATTACH, pid, 0, 0);
//		ptrace(PT_DETACH, pid, 0, 0);
		lpProcessInformation->dwProcessId = pid;
		lpProcessInformation->hProcess = pid;
	}
	return 1;
}