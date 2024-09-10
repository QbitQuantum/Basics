//
//  FUNCTION: SvcQueryConfig
//
//  PURPOSE: Query the service status and trigger-start configuration
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//    This function does not require administrative priviledge
//
void SvcQueryConfig()
{
	// Open the local default service control manager database
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if (!schSCManager)
	{
		wprintf(L"OpenSCManager failed w/err 0x%08lx\n", GetLastError());
		return;
	}

	// Try to open the service to query its status and config
	SC_HANDLE schService = OpenService(schSCManager, SERVICE_NAME, 
		SERVICE_QUERY_STATUS | SERVICE_QUERY_CONFIG);

	if (NULL != schService)
	{
		wprintf(L"%s was installed.\n", SERVICE_DISPLAY_NAME);

		DWORD cbBytesNeeded;

		// 
		// Query the status of the service
		// 

		SERVICE_STATUS_PROCESS ssp;
		if (QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, 
			sizeof(ssp), &cbBytesNeeded))
		{
			wprintf(L"Service status: ");
			switch (ssp.dwCurrentState)
			{
			case SERVICE_STOPPED: wprintf(L"Stopped\n"); break;
			case SERVICE_RUNNING: wprintf(L"Running\n"); break;
			case SERVICE_PAUSED: wprintf(L"Paused\n"); break;
			case SERVICE_START_PENDING:
			case SERVICE_STOP_PENDING:
			case SERVICE_CONTINUE_PENDING:
			case SERVICE_PAUSE_PENDING: wprintf(L"Pending\n"); break;
			}
		}
		else
		{
			wprintf(L"QueryServiceStatusEx failed w/err 0x%08lx\n", GetLastError());
		}

		// 
		// Query the trigger-start configuration of the service
		// 

		BOOL fIsTriggerStart;
		if (GetServiceTriggerInfo(schService, &fIsTriggerStart))
		{
			wprintf(L"Is trigger-start: %s", fIsTriggerStart ? L"Yes" : L"No");
		}
		else
		{
			wprintf(L"GetServiceTriggerInfo failed w/err 0x%08lx\n", GetLastError());
		}
		
		CloseServiceHandle(schService);
	}
	else
	{
		DWORD dwErr = GetLastError();
		if (dwErr == ERROR_SERVICE_DOES_NOT_EXIST)
		{
			wprintf(L"%s was not installed.\n", SERVICE_DISPLAY_NAME);
		}
		else
		{
			wprintf(L"OpenService failed w/err 0x%08lx\n", dwErr);
		}
	}

	CloseServiceHandle(schSCManager);
}