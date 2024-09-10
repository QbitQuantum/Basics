bool ControlSSDPService(bool start)
{
	bool result = false;
	
	SC_HANDLE hscm = NULL;
	hscm = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if(hscm == NULL)
		return result;

	SC_HANDLE hsrv = NULL;
	hsrv = OpenService(hscm, _T("ssdpsrv"), SERVICE_ALL_ACCESS);
	if(hsrv)
	{
		SERVICE_STATUS srvstatus;

		if(QueryServiceStatus(hsrv, &srvstatus))
		{
			HANDLE hevent = CreateEvent(0, true, false, _T("dummyevent"));
			
			// if service_*_pending then wait for complete operation
			switch(srvstatus.dwCurrentState)
			{
			case SERVICE_START_PENDING :
			case SERVICE_STOP_PENDING :
				for(int i = 0; i < 10; ++i)
				{
					if(!QueryServiceStatus(hsrv, &srvstatus))
						break;
					if(srvstatus.dwCurrentState == SERVICE_RUNNING || srvstatus.dwCurrentState == SERVICE_STOPPED)
						break;
					WaitForSingleObject(hevent, 1000);
				}
				break;
			}

			// operation completed, so change current state
			if(QueryServiceStatus(hsrv, &srvstatus))
			{
				switch(srvstatus.dwCurrentState)
				{
				case SERVICE_RUNNING : // stop it
					if(!start && ControlService(hsrv, SERVICE_CONTROL_STOP, &srvstatus))
						result = true;
					break;
				case SERVICE_STOPPED : // start it
					if(start && StartService(hsrv, 0, NULL))
						result = true;
					break;
				}

				// wait for complete operation
				if(result)
				{
					for(int i = 0; i < 10; ++i)
					{
						if(!QueryServiceStatus(hsrv, &srvstatus))
							break;
						if(srvstatus.dwCurrentState == SERVICE_RUNNING || srvstatus.dwCurrentState == SERVICE_STOPPED)
						{
							// notify scm
							//ControlService(hsrv, SERVICE_CONTROL_INTERROGATE, &srvstatus);
							break;
						}
						WaitForSingleObject(hevent, 1000);
					}
				}
			}
		}
		
		CloseServiceHandle(hsrv);
	}

	CloseServiceHandle(hscm);
	
	return result;
}