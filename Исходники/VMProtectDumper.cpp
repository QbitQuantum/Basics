int main()
{
	int argc;
	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (argc < 3)
		die(printf("[!] Need a file name to analyze and a filename for the memory dump\n"));

	strOutFileName = argv[2];
#ifndef _DEBUG
	printf("[!] PRIMA di eseguire questo, guarda il certificato e verifica che la firma sia valida senno' esegui questo programma solo su una VM disposable!!!\n");
	printf("[!] Premi 'k' e invio per andare avanti\n");
	if (getchar() != 'k')
		exit(printf("[*] Exiting..\n"));
#endif

	STARTUPINFO pStartupInfo;
	PROCESS_INFORMATION pProcessInfo;
	SecureZeroMemory(&pStartupInfo, sizeof(STARTUPINFO));
	SecureZeroMemory(&pProcessInfo, sizeof(PROCESS_INFORMATION));
	pStartupInfo.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(argv[1], NULL, NULL, NULL, FALSE, DEBUG_PROCESS, NULL, NULL, &pStartupInfo, &pProcessInfo))
		exit(printf("[!] Cannot start %S, got => %08x\n", argv[1], GetLastError()));

	printf("[*] Process %d started\n", GetProcessId(hProcess));

	hProcess = pProcessInfo.hProcess;	
	while (1)
	{
		DEBUG_EVENT pEvent;
		if (!WaitForDebugEvent(&pEvent, INFINITE))
			break;

		DWORD dwStatus = DBG_CONTINUE;

		switch (pEvent.dwDebugEventCode)
		{
		case EXCEPTION_DEBUG_EVENT:
			dwStatus = HandleException(&pEvent);
			break;
		case LOAD_DLL_DEBUG_EVENT:
			HandleDll(&pEvent);
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			break; // FIXME
		case CREATE_PROCESS_DEBUG_EVENT:
		case CREATE_THREAD_DEBUG_EVENT:
		case EXIT_THREAD_DEBUG_EVENT:
		case UNLOAD_DLL_DEBUG_EVENT:
		case OUTPUT_DEBUG_STRING_EVENT:
		case RIP_EVENT:
			break;
		default:
			printf("[!] Got unknown debug event => %d\n", pEvent.dwDebugEventCode);
			TerminateProcess(pProcessInfo.hProcess, 0);
			ExitProcess(0);
		}

		ContinueDebugEvent(pEvent.dwProcessId, pEvent.dwThreadId, dwStatus);
	}

	TerminateProcess(pProcessInfo.hProcess, 0);
}