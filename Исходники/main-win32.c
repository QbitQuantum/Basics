static void nx_win32_svc_uninstall()
{
    SC_HANDLE service_manager = NULL;
    SC_HANDLE service_handle = NULL;
    SERVICE_STATUS query_status;
    nx_exception_t e;

    // Connect to service manager
    service_manager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if ( service_manager == NULL )
    {
        nx_win32_error("Cannot initialize access to the service manager");
    }

    try
    {
        // Connect to service
        service_handle = OpenService(service_manager, "nxlog", SERVICE_ALL_ACCESS | DELETE);
        if ( service_handle == NULL )
        {
            nx_win32_error("Couldn't open nxlog service");
        }
        else
        {
            // Check that the service is stopped
            if ( QueryServiceStatus(service_handle, &query_status) &&
                    (query_status.dwCurrentState == SERVICE_RUNNING) )
            {
                throw_msg("Service is running, please stop it first.");
            }
            else
            {   // we can remove
                if ( DeleteService(service_handle) == FALSE )
                {
                    nx_win32_error("Couldn't delete service");
                }
                else
                {
                    log_info("Service successfully uninstalled");
                }
            }
            // Close connection to service
            CloseServiceHandle(service_handle);
        }
        // Close connection to service manager
        CloseServiceHandle(service_manager);
    }
    catch(e)
    {
        if ( service_handle != NULL )
        {
            CloseServiceHandle(service_handle);

        }
        if ( service_manager != NULL )
        {
            CloseServiceHandle(service_manager);

        }
        rethrow(e);
    }
}