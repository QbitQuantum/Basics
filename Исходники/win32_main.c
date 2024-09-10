static void
unregister_service(int argc, char *argv[])
{
	SC_HANDLE service, scm;
	BOOL success;
	SERVICE_STATUS status;

	sw_debug(SW_LOG_NOTICE, "starting...\n");

	//
	// Open a connection to the SCM
	//
	scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
	if (!scm)
	{
		service_error_handler("In OpenScManager", GetLastError());
		exit(0);
	}

	// Get the service's handle
	service = OpenService(scm, SERVICE_NAME, SERVICE_ALL_ACCESS | DELETE);
	if (!service)
	{
		service_error_handler("In OpenService", GetLastError());
	}
	
	//
	// Stop the service if necessary
	//
	success = QueryServiceStatus(service, &status);
	if (!success)
	{
		service_error_handler("In QueryServiceStatus", GetLastError());
	}

	if (status.dwCurrentState != SERVICE_STOPPED)
	{
		sw_debug(SW_LOG_NOTICE, "stopping service...\n");
		success = ControlService(service, SERVICE_CONTROL_STOP, &status);
		if (!success)
		{
			service_error_handler("In ControlService", GetLastError());
		}
		Sleep(500);
	}
	
	//
	// Remove the service
	//
	success = DeleteService(service);
	if (success)
	{
		sw_debug(SW_LOG_NOTICE, "service unregistered\n");
	}
	else
	{
		service_error_handler("DeleteService", GetLastError());
	}

	//
	// Clean up
	//
	CloseServiceHandle(service);
	CloseServiceHandle(scm);
}