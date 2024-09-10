// Start service
VOID WINAPI CmdStart (DWORD, LPTSTR* ) 
{
	DWORD status = 0; 
	DWORD specificError = 0;

	ServiceStatus.dwServiceType        = SERVICE_WIN32; 
	ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
	ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE; 
	ServiceStatus.dwWin32ExitCode      = 0; 
	ServiceStatus.dwServiceSpecificExitCode = 0; 
	ServiceStatus.dwCheckPoint         = 0; 
	ServiceStatus.dwWaitHint           = 0; 

	ServiceStatusHandle = RegisterServiceCtrlHandler( 
		SERVICENAME, CmdCtrlHandler ); 

	if (ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0) 
		return; 

	// Initialization complete - report running status. 
	ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
	ServiceStatus.dwCheckPoint         = 0; 
	ServiceStatus.dwWaitHint           = 0; 

	if (!SetServiceStatus (ServiceStatusHandle, &ServiceStatus)) 
		status = GetLastError(); 
	else
	{
		//we do all things in the thread of _ServiceMain, wo also could do things here
		//while(true)
		//{
		//}

		// Start the main thread
		g_hServiceEvents[0] = CreateEvent( NULL, FALSE, FALSE, NULL );
		g_hServiceEvents[1] = CreateEvent( NULL, FALSE, FALSE, NULL );
		g_hServiceEvents[2] = CreateEvent( NULL, FALSE, FALSE, NULL );
		_beginthread( _ServiceMain, 0, NULL );
	}

	return; 
} 