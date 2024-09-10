bool IsServiceInstalled()
{
	bool ret = false;
	SC_HANDLE schSCManager = OpenSCManager(
		NULL,                   
		NULL,                    
		SC_MANAGER_ALL_ACCESS);  
	if (NULL == schSCManager) {	
		return ret;
	}
	SC_HANDLE schService = OpenService(
		schSCManager,         
		srvName,         
		SERVICE_ALL_ACCESS); 
	if (schService != NULL) {
		SERVICE_STATUS_PROCESS ssStatus;
		DWORD dwBytesNeeded;
		if (QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssStatus,
			sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded)) {
			if (ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING) {
				ret = true;
			}
		}
	} 

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
	return ret;
}