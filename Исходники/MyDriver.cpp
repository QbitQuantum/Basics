DWORD MyDriver::StopDriver(void)
{
	
	if(!started)
		return DRV_SUCCESS;


	SC_HANDLE SCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	DWORD retCode;
	
	if (SCManager == NULL) 
		return DRV_ERROR_SCM;

   
    SERVICE_STATUS  status;

    SC_HANDLE SCService = OpenServiceA(SCManager, driverName, SERVICE_ALL_ACCESS);
    
	if (SCService != NULL)
	{
		
		CloseHandle(driverHandle); 
		driverHandle = NULL; 

		if(!ControlService(SCService, SERVICE_CONTROL_STOP, &status))
			retCode = DRV_ERROR_STOPPING;

		else
			retCode = DRV_SUCCESS;
	}

	else
		retCode = DRV_ERROR_SERVICE;


    CloseServiceHandle(SCService);
	SCService = NULL;

	CloseServiceHandle(SCManager);
	SCManager = NULL;


	if(retCode == DRV_SUCCESS)
		started = FALSE;

    return retCode;
}