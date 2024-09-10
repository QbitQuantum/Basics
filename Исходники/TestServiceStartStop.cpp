bool StartStopWindowsService(std::string sServiceName, int iStartorStop)
{
	bool bResult = false;

	SC_HANDLE ScManager = NULL; 
	SC_HANDLE ScService = NULL;

	ScManager=::OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS|GENERIC_ALL); 

	if(ScManager == NULL) 
	{
		bResult = false; 
	}
	else
	{

		ScService =::OpenService(ScManager,sServiceName.data (),SERVICE_ALL_ACCESS);

		if(ScService == NULL)
		{
            DWORD WINAPI errCode = GetLastError();

			bResult = false; 
		}
		else
		{

			DWORD dwCurrentState = 0;
			SERVICE_STATUS lpSERVICE_STATUS = {0};
			QueryServiceStatus(ScService, &lpSERVICE_STATUS);

			switch(lpSERVICE_STATUS.dwCurrentState)
			{
			case SERVICE_PAUSED: //service in paused state
				dwCurrentState = SERVICE_PAUSED;
				break;
			case SERVICE_RUNNING: // The service is running.
				dwCurrentState = SERVICE_RUNNING;
				break;
			case SERVICE_STOPPED:// The service is stopped
				dwCurrentState = SERVICE_STOPPED;
				break;
			case SERVICE_START_PENDING: // The service is starting 
				dwCurrentState = SERVICE_START_PENDING;
				break;
			case SERVICE_STOP_PENDING : // The service is stopped 
				dwCurrentState = SERVICE_STOP_PENDING;
				break;
			default: //unknown state
				break;
			}

			if ( (dwCurrentState == SERVICE_STOPPED || dwCurrentState == SERVICE_PAUSED || dwCurrentState == SERVICE_STOP_PENDING ) && iStartorStop == 1 )
			{
                std::cout << "starting service..";
				bResult = (::StartService(ScService,0,NULL) == S_OK);
			}
			else if ( (dwCurrentState == SERVICE_RUNNING || dwCurrentState == SERVICE_START_PENDING) && iStartorStop == 0 )
			{
                std::cout << "stopping service..";
				bResult = (::ControlService(ScService,SERVICE_CONTROL_STOP,&lpSERVICE_STATUS) != 0);
			}
		}// else if(ScService==NULL)

	}//else if(ScManager==NULL) 

	if (ScManager)
		::CloseServiceHandle(ScManager);
	if (ScService)
		::CloseServiceHandle(ScService);

	return bResult; 
}