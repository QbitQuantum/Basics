LPENUM_SERVICE_STATUS
TV2_GetDependants(LPWSTR lpServiceName,
                  LPDWORD lpdwCount)
{
    SC_HANDLE hSCManager;
    SC_HANDLE hService;
    LPENUM_SERVICE_STATUSW lpDependencies = NULL;
    DWORD dwBytesNeeded;
    DWORD dwCount;

    /* Set the first items in each tree view */
    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_ALL_ACCESS);
    if (hSCManager)
    {
        hService = OpenServiceW(hSCManager,
                                lpServiceName,
                                SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS | SERVICE_QUERY_CONFIG);
        if (hService)
        {
            /* Does this have any dependencies? */
            if (!EnumDependentServicesW(hService,
                                        SERVICE_STATE_ALL,
                                        NULL,
                                        0,
                                        &dwBytesNeeded,
                                        &dwCount) &&
                GetLastError() == ERROR_MORE_DATA)
            {
                lpDependencies = (LPENUM_SERVICE_STATUSW)HeapAlloc(GetProcessHeap(),
                                                                  0,
                                                                  dwBytesNeeded);
                if (lpDependencies)
                {
                    /* Get the list of dependents */
                    if (EnumDependentServicesW(hService,
                                               SERVICE_STATE_ALL,
                                               lpDependencies,
                                               dwBytesNeeded,
                                               &dwBytesNeeded,
                                               &dwCount))
                    {
                        /* Set the count */
                        *lpdwCount = dwCount;
                    }
                    else
                    {
                        HeapFree(ProcessHeap,
                                 0,
                                 lpDependencies);

                        lpDependencies = NULL;
                    }
                }
            }

            CloseServiceHandle(hService);
        }

        CloseServiceHandle(hSCManager);
    }

    return lpDependencies;
}