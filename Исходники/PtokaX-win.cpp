static int UninstallService(const char * sServiceName) {
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	     
	if(schSCManager == NULL) {
	    printf("OpenSCManager failed (%d)!", GetLastError());
	    return EXIT_FAILURE;
	}
	
	SC_HANDLE schService = OpenService(schSCManager, sServiceName, SERVICE_QUERY_STATUS | SERVICE_STOP | DELETE);
	     
	if(schService == NULL) {
	    printf("OpenService failed (%d)!", GetLastError());
	    CloseServiceHandle(schSCManager);
	    return EXIT_FAILURE;
	}
	
	SERVICE_STATUS_PROCESS ssp;
	DWORD dwBytesNeeded;
	
	if(QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded) != 0) {
	    if(ssp.dwCurrentState != SERVICE_STOPPED && ssp.dwCurrentState != SERVICE_STOP_PENDING) {
	        ControlService(schService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp);
	    }
	}
	
	if(DeleteService(schService) == false) {
	    printf("DeleteService failed (%d)!", GetLastError());
	    CloseServiceHandle(schService);
	    CloseServiceHandle(schSCManager);
	    return EXIT_FAILURE;
	} else {
	    printf("PtokaX service '%s' deleted successfully.", sServiceName);
	    CloseServiceHandle(schService);
	    CloseServiceHandle(schSCManager);
	    return EXIT_SUCCESS;
	}
}