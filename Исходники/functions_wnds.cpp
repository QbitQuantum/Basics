int _changeAccess(LPCTSTR lpServiceName){
	
	int returnValue = 0;
	
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	
	schSCManager = OpenSCManager(NULL,
								 SERVICES_ACTIVE_DATABASE, 
								 SC_MANAGER_ALL_ACCESS);
	
	if(!schSCManager){
		returnValue = GetLastError();
	}else{
		schService = OpenService(schSCManager, 
								 lpServiceName,  
								 READ_CONTROL|WRITE_DAC);
		
		if(!schService){	
			returnValue = GetLastError();
		}else{	
			
			PSECURITY_DESCRIPTOR psd = NULL;
			DWORD dwSize, dwBytesNeeded  = 0;
			
			if(!QueryServiceObjectSecurity(schService,
										   DACL_SECURITY_INFORMATION, 
										   &psd,           // using NULL does not work on all versions
										   0, 
										   &dwBytesNeeded)){
				
				dwSize = dwBytesNeeded;
				
				std::vector<unsigned int> buf(dwSize);
				
				psd = (PSECURITY_DESCRIPTOR)&buf[0];
				
				if(!QueryServiceObjectSecurity(schService,
											   DACL_SECURITY_INFORMATION, 
											   psd, 
											   dwSize, 
											   &dwBytesNeeded)){
					returnValue = GetLastError();
				}else{
					
					BOOL bDaclPresent = FALSE;
					PACL pacl = NULL;
					PACL pNewAcl = NULL;
					BOOL bDaclDefaulted = FALSE;
					
					if(!GetSecurityDescriptorDacl(psd, 
												  &bDaclPresent, 
												  &pacl,
												  &bDaclDefaulted)){
						returnValue = GetLastError();
					}else{
						EXPLICIT_ACCESS ea;
						
						BuildExplicitAccessWithName(&ea, 
													L"GUEST",
													SERVICE_START|SERVICE_STOP|
													SERVICE_CHANGE_CONFIG|SERVICE_QUERY_CONFIG|DELETE,
													SET_ACCESS, 
													NO_INHERITANCE);
						
						if(SetEntriesInAcl(1, &ea, pacl, &pNewAcl)!=ERROR_SUCCESS){
							returnValue = GetLastError();
						}else{
							SECURITY_DESCRIPTOR  sd;
							if(!InitializeSecurityDescriptor(&sd, 
															 SECURITY_DESCRIPTOR_REVISION)){
								returnValue = GetLastError();
							}else{
								if(SetSecurityDescriptorDacl(&sd, TRUE, pNewAcl, FALSE)){
									if(!SetServiceObjectSecurity(schService, 
																 DACL_SECURITY_INFORMATION, 
																 &sd)){
										returnValue = GetLastError();	
									}
								}
							}
							LocalFree((HLOCAL)pNewAcl);
						}
					}
				}					
			}
			
			CloseServiceHandle(schService);	
			
		}
		
		CloseServiceHandle(schSCManager);	
		
	}	
	
	return returnValue;
}