HRESULT CHTFileTransferSystemServiceModule::RegisterAppId(bool bService) throw() 
{
	HRESULT hr = S_OK; 
	BOOL res = CAtlServiceModuleT<CHTFileTransferSystemServiceModule, IDS_SERVICENAME>::RegisterAppId(bService);   
	if(bService) 
	{ 
		if(IsInstalled()) 
		{                 
			SC_HANDLE hSCM = ::OpenSCManagerW(NULL, NULL, SERVICE_CHANGE_CONFIG); 
			SC_HANDLE hService = NULL; 
			if (hSCM == NULL) 
				hr = AtlHresultFromLastError(); 
			else 
			{ 
				hService = ::OpenService(hSCM, m_szServiceName, SERVICE_CHANGE_CONFIG); 
				if(hService != NULL) 
				{ 
					const int m_szServiceNameLen = 4096; 
					const int m_szServiceDescriptionLen = 2000; 
					CAString strServiceDescription = L"HTFileTransferSystemService"; 
					SERVICE_DESCRIPTION sdBuf = {strServiceDescription.GetBuffer(0)};
					strServiceDescription.ReleaseBuffer();
					res = ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &sdBuf); 
					if (res)
					{
						res = ChangeServiceConfig( 
							hService,        // handle of service 
							SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type: no change 
							SERVICE_AUTO_START,  // service start type 
							SERVICE_NO_CHANGE, // error control: no change 
							NULL,              // binary path: no change 
							NULL,              // load order group: no change 
							NULL,              // tag ID: no change 
							NULL,              // dependencies: no change 
							NULL,              // account name: no change 
							NULL,              // password: no change 
							NULL);
						if (res != 0)
						{
							hr = AtlHresultFromLastError();
						}
					}
					else
					{
						hr = AtlHresultFromLastError();
					}
					::CloseServiceHandle(hService); 
				} 
				else 
				{
					hr = AtlHresultFromLastError(); 
				}
				::CloseServiceHandle(hSCM); 
			} 
		} 
	} 
	return   hr; 
}