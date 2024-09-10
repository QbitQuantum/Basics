VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	DWORD   status = 0; 
	DWORD   specificError = 0xfffffff; 
 
	ServiceStatus.dwServiceType        = SERVICE_WIN32; 
	ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
	ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE; 
	ServiceStatus.dwWin32ExitCode      = 0; 
	ServiceStatus.dwServiceSpecificExitCode = 0; 
	ServiceStatus.dwCheckPoint         = 0; 
	ServiceStatus.dwWaitHint           = 0; 
 
	hServiceStatusHandle = RegisterServiceCtrlHandler(pServiceName, ServiceHandler); 
	if (hServiceStatusHandle==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "RegisterServiceCtrlHandler failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
		return; 
	} 
 
	// Initialization complete - report running status 
	ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
	ServiceStatus.dwCheckPoint         = 0; 
	ServiceStatus.dwWaitHint           = 0;  
	if(!SetServiceStatus(hServiceStatusHandle, &ServiceStatus)) 
	{ 
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	} 

	AttachProcessNames();
	for(int iLoop = 0; iLoop < MAX_NUM_OF_PROCESS; iLoop++)
	{
		pProcInfo[iLoop].hProcess = 0;
		StartProcess(iLoop);
	}
}