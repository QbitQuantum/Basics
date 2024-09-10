void CSystemService::Install(LPCWSTR displayname)
{
	WCHAR startcmd[MAX_PATH+5];
	TCHAR filename[MAX_PATH];
	if(0==::GetModuleFileName(nullptr,filename,MAX_PATH)) return;
	if(0==swprintf_s(startcmd,L"\"%s\" -s",filename))return;

	SC_HANDLE newService=nullptr, scm=nullptr;
	SERVICE_STATUS status;
	__try
	{
		scm = OpenSCManager(0, 0,
			SC_MANAGER_CREATE_SERVICE);
		if (!scm)
			__leave;
		// Install the new service
		newService = OpenServiceW(scm,ServiceTable[0].lpServiceName,SERVICE_ALL_ACCESS);
		if(newService)
		{
			QUERY_SERVICE_CONFIG* querybuff=nullptr;
			DWORD bufsz=0;
			if(QueryServiceConfig(newService,querybuff,0,&bufsz)==FALSE)
			{
				if(ERROR_INSUFFICIENT_BUFFER==GetLastError())
				{
					querybuff=(QUERY_SERVICE_CONFIG*)malloc(bufsz);
					if(querybuff)
					{
						if(QueryServiceConfig(newService,querybuff,bufsz,&bufsz))
						{
							wchar_t* firstQuotes=nullptr,*secondQuotes=nullptr;
							firstQuotes=wcschr(querybuff->lpBinaryPathName,'"');
							if(firstQuotes)
							{
								secondQuotes=wcschr(firstQuotes+1,'"');
								if(secondQuotes)
								{
									wchar_t tempfilename[MAX_PATH];
									wcsncpy_s(tempfilename,firstQuotes+1,secondQuotes-firstQuotes-1);
									if(_wcsicmp(tempfilename,filename)!=0)
									{
										if(StopService(newService))
										{
											if(CopyFile(filename,tempfilename,FALSE))
											{
												wcscpy_s(startcmd,querybuff->lpBinaryPathName);
											}
										}
									}
								}
							}
						}
						free(querybuff);
					}
				}
			}
			if(!ChangeServiceConfigW(newService,
				SERVICE_WIN32_SHARE_PROCESS|SERVICE_INTERACTIVE_PROCESS,
				SERVICE_AUTO_START,
				SERVICE_ERROR_NORMAL,
				startcmd,
				0,0,dependens,0,0,0))
				__leave;
		}
		else
		{
			newService = CreateServiceW(
				scm, ServiceTable[0].lpServiceName,
				displayname?displayname:ServiceTable[0].lpServiceName,
				SERVICE_ALL_ACCESS,
				SERVICE_WIN32_SHARE_PROCESS|SERVICE_INTERACTIVE_PROCESS,
				SERVICE_AUTO_START,
				SERVICE_ERROR_NORMAL,
				startcmd,
				0, 0, dependens, 0, 0);
		}
		if (newService)
		{
			SERVICE_FAILURE_ACTIONS sfa;
			ZeroMemory(&sfa,sizeof(sfa));
			sfa.dwResetPeriod=INFINITE;
			sfa.cActions=3;
			SC_ACTION sact[3];
			ZeroMemory(sact,sizeof(sact));
			sfa.lpsaActions=sact;
			sact[0].Delay=500;
			sact[0].Type=SC_ACTION_RESTART;
			sact[1].Delay=500;
			sact[1].Type=SC_ACTION_RESTART;
			sact[2].Delay=500;
			sact[2].Type=SC_ACTION_RESTART;
			ChangeServiceConfig2(newService,SERVICE_CONFIG_FAILURE_ACTIONS,&sfa);

			if(QueryServiceStatus(newService,&status))
			{
				if(status.dwCurrentState==SERVICE_STOPPED)
				{
					StartService(newService,0,0);
				}
			}
		}
	}
	__finally
	{
		if(newService)CloseServiceHandle(newService);
		if(scm)CloseServiceHandle(scm);
	}
}