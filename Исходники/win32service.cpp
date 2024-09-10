/** This callback is called by windows when the service is started */
VOID ServiceMain(DWORD argc, LPCSTR *argv)
{
	g_ServiceStatusHandle = RegisterServiceCtrlHandler(TEXT("InspIRCd"), (LPHANDLER_FUNCTION)ServiceCtrlHandler);
	if( !g_ServiceStatusHandle )
		return;

	g_ServiceStatus.dwCheckPoint = 1;
	g_ServiceStatus.dwControlsAccepted = 0;
	g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	g_ServiceStatus.dwWaitHint = 5000;
	g_ServiceStatus.dwWin32ExitCode = NO_ERROR;
	g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;

	if( !SetServiceStatus( g_ServiceStatusHandle, &g_ServiceStatus ) )
		return;

	char szModuleName[MAX_PATH];
	if(GetModuleFileNameA(NULL, szModuleName, MAX_PATH))
	{
		if(!argc)
			argc = 1;

		g_ServiceData.argc = argc;

		// Note: since this memory is going to stay allocated for the rest of the execution,
		//		 it doesn't make sense to free it, as it's going to be "freed" on process termination
		try {
			g_ServiceData.argv = new char*[argc];

			uint32_t allocsize = strnlen_s(szModuleName, MAX_PATH) + 1;
			g_ServiceData.argv[0] = new char[allocsize];
			strcpy_s(g_ServiceData.argv[0], allocsize, szModuleName);

			for(uint32_t i = 1; i < argc; i++)
			{
				allocsize = strnlen_s(argv[i], MAX_PATH) + 1;
				g_ServiceData.argv[i] = new char[allocsize];
				strcpy_s(g_ServiceData.argv[i], allocsize, argv[i]);
			}

			*(strrchr(szModuleName, '\\') + 1) = NULL;
			SetCurrentDirectoryA(szModuleName);

			HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkerThread, NULL, 0, NULL);
			if (hThread != NULL)
			{
				WaitForSingleObject(hThread, INFINITE);
				CloseHandle(hThread);
			}
		}
		catch(...)
		{
			g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
			g_ServiceStatus.dwWin32ExitCode = ERROR_OUTOFMEMORY;
			SetServiceStatus( g_ServiceStatusHandle, &g_ServiceStatus );
		}
	}
	if(g_ServiceStatus.dwCurrentState == SERVICE_STOPPED)
		return;

	g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
	g_ServiceStatus.dwWin32ExitCode = GetLastError();
	SetServiceStatus( g_ServiceStatusHandle, &g_ServiceStatus );
}