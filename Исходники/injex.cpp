/**
	@brief	herp derp.
	
	@private

	@bug	Sometimes on windows XP, if a process is started up to be 
			injected into, the process will exit before completing 
			startup if the DLL unloads itself before process startup
			is complete.
**/
int main(int argc, CHAR* argv[])
{
	char *dllArg = NULL;
	char *programPath = NULL;
	char *procArgs = NULL;
	WCHAR procNameBuffer[MAX_PATH] = {0};
	PWCHAR procName = NULL;
	DWORD pid = 0;
	DWORD waitMs = 0;
	BOOL startProcess;
	DWORD injectionMethod = 0;
	
	unsigned char dllCount = 0;
	char *dllList[128];

	if(argc==1){
		Usage();
	}

	// Get Windows Version Information.
	OSVERSIONINFOEX OsInfo = {0};
	OsInfo.dwOSVersionInfoSize = sizeof(OsInfo);
	GetVersionEx((LPOSVERSIONINFO)&OsInfo);

	// These are used later to make decisions on how to do things.
	BOOL is2kOrAbove = FALSE;
	BOOL isXpOrAbove = FALSE;
	BOOL isVistaOrAbove = FALSE;
	BOOL is7OrAbove = FALSE;

	if(OsInfo.dwMajorVersion >= 6){
		isVistaOrAbove = TRUE;
		if(OsInfo.dwMinorVersion >= 1){
			is7OrAbove = TRUE;
		}
	}

	if(OsInfo.dwMajorVersion >= 5){
		is2kOrAbove = TRUE;
		if(OsInfo.dwMinorVersion >= 1){
			isXpOrAbove = TRUE;
		}
	}

	// This really wont event get shown, the program just crashes when run.
	if(isXpOrAbove == FALSE){
		printf("ERROR: Injex is not compatible with this version of windows.");
		ExitProcess(-1);
	}

	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"-d") == 0){

			// Add the DLL list
			dllList[dllCount] = (char*)malloc(MAX_PATH);

			// Get the full path to the DLL to inject, the application loading will need this.
			GetFullPathNameA(argv[++i],MAX_PATH,dllList[dllCount],NULL);

			// Inc the dll count.
			dllCount++;

		} else if(strcmp(argv[i],"-b") == 0) {
			programPath = argv[++i];
			startProcess = TRUE;

		} else if(strcmp(argv[i],"-p") == 0) {
			if(isNumeric(argv[i+1]))
				pid = atoi(argv[++i]);
			else{
				printf("ERROR: Invalid Process Id specified \"%s\"; Process Id should be numeric.\n",argv[i+1]);
				Usage();
			}
			startProcess = FALSE;

		} else if(strcmp(argv[i],"-a") == 0) {
			procArgs = argv[++i];

		} else if(strcmp(argv[i],"-h") == 0) {
			Usage();

		} else if(strcmp(argv[i],"-w") == 0) {
			if(isXpOrAbove == FALSE){
				printf("ERROR: Process suspension is only supported on Windows XP/2003 or above.\n");
				Usage();
			}

			waitMs = atoi(argv[++i]);

		} else if (strcmp(argv[i],"-n") == 0) {
			
			if(isXpOrAbove == FALSE){
				printf("ERROR: Selecting a process by name is only supported on Windows XP or above. Please use process id instead.\n");
				Usage();
			}

			i++;
			procName = procNameBuffer;
			MultiByteToWideChar(CP_UTF8, 0, argv[i], INT(strlen(argv[i])), procName, MAX_PATH);

			startProcess = FALSE;

		} else if (strcmp(argv[i],"-i") == 0) {
			if(isNumeric(argv[i+1]))
				injectionMethod = atoi(argv[++i]);
			else{
				printf("ERROR: Invalid injection method, injection methods are provided by number.\n");
				Usage();
			}

		} else {
			printf("ERROR: Unknown command line option \"%s\"\n",argv[i]);
			Usage();
		}
	}

	// Validate their command line options.
	if(pid == 0 && programPath == NULL && procName == 0){
		printf("ERROR: Please specify either a Process ID, a binary to launch, or the name of a running process.\n");
		Usage();
	}

	// Check to make sure the specified a DLL.
	if(dllCount == 0){
		printf("ERROR: Please specify a DLL to inject.\n");
		Usage();
	}

	// Ensure that they selected an injection method that is within range.
	if(injectionMethod>1){
		printf("ERROR: Invalid injection method selected.\n");
		Usage();
	}

	// The handle of the process we will inject into.
	HANDLE proc=INVALID_HANDLE_VALUE;

	// Used for keeping track of the suspended threads.
	DWORD threadCount = 0;

	// Assuming 1MB stacks, 2048*1MB =~ 2GB. I am ASSUMING that the thread count in an application will never exceed this due to hardware contraints. 
	#define MAX_THREADS 2048
	HANDLE threads[MAX_THREADS];

	// Get the handle to the process to inject into and store it in proc.
	if(startProcess){
		// startProcess means that we need to start it up...
		PROCESS_INFORMATION		pi;
		STARTUPINFOA			si;
		GetStartupInfoA(&si);

		// Assemble the command line to start the process.
		char CommandLine[8191] = {0};
		sprintf(CommandLine,"\"%s\"", programPath);
		if(procArgs != NULL){
			strcat(CommandLine, " ");
			strcat(CommandLine, procArgs);
		}
		
		DWORD dwFlags = 0;
		if(waitMs) dwFlags |= CREATE_SUSPENDED;
		
		printf("Starting new process to inject into:\n%s\n",CommandLine);
		if(CreateProcessA(NULL,CommandLine,NULL,NULL,0,dwFlags,NULL,NULL,&si,&pi) == 0)
		{
			ErrorExit(TEXT("CreateProcessA"), "Check your process path.");
		}

		if(waitMs){
			threadCount = 1;
			threads[0] = pi.hThread;
		}

		proc = pi.hProcess;
	}
	else{

		// The process is already running, we need to get a handle to it with the correct permissions.
		if(procName != NULL){
			// Open a handle to the process if they specified it with a name.
			proc = GetProcessHandleFromName(procName);

			if(proc == NULL){
				printf("ERROR: Failed to find a process by the name of '%S' that we have permissions to inject into. Make sure that your have proper permissions and the process is running.\n", procName);
				ExitProcess(-1);
			}

		} else {
			// Open a handle to the process specified by PID.
			proc = GetProcessHandleFromPid(pid);

			if(proc == NULL)
			{
				ErrorExit(TEXT("OpenProcess"), "Check the Process Id that you provided.");
			}
		}

		if(waitMs){
			/** @todo Add the ability to suspend already running processes. */
		}
	}
	
	// Inject each dll listed.
	for(DWORD i=0;i<dllCount;i++){
		printf("Injecting %s into pid %d.\n", dllList[i], GetProcessId(proc));
		DWORD dwThreadExitCode;

		switch(injectionMethod){
			case 0:
				printf("Using LoadLibrary injection (Richter Method).\n");
				dwThreadExitCode = LoadLibraryInjection(proc, dllList[i]);
				break;

			case 1:
				printf("Using Thread Hijacking...\n");
				dwThreadExitCode = ThreadHijackInjection(proc, dllList[i]);
				break;
		}

		if(dwThreadExitCode == 0){
			printf("ERROR: The target process failed to load %s. Check the DLL path you specified.\n",dllList[i]);
			printf("DLL Injection Failed!");
		} else {
			printf("%s Injection Successful!\n",dllList[i]);
		}

		// Free up that memory...
		free(dllList[i]);
	}

	if(waitMs && startProcess){
		printf("Waiting %ims for DLL to lay hooks before resuming the process.\n",waitMs);
		Sleep(waitMs);
		for(DWORD i=0;i<threadCount;i++){
			printf("Resuming threads in process %d...\n", GetProcessId(proc));
			ResumeThread(threads[i]);
			CloseHandle(threads[i]);
		}
	}

	// No need for this handle anymore.
	CloseHandle(proc);

	return 0;
}