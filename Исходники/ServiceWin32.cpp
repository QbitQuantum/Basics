bool WinServiceUninstall()
{
    SC_HANDLE serviceControlManager = OpenSCManager(0, 0, SC_MANAGER_CONNECT);

    if (serviceControlManager)
    {
        SC_HANDLE service = OpenService(serviceControlManager,
            serviceName, SERVICE_QUERY_STATUS | DELETE);
        if (service)
        {
            SERVICE_STATUS serviceStatus2;
            if (QueryServiceStatus(service, &serviceStatus2))
            {
                if (serviceStatus2.dwCurrentState == SERVICE_STOPPED)
                    DeleteService(service);
            }
            CloseServiceHandle(service);
        }

        CloseServiceHandle(serviceControlManager);
    }
    return true;
}