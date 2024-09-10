BOOL
StartDriver(LPCWSTR lpDriverName)
{
    SC_HANDLE hSCManager;
    SC_HANDLE hService;
    BOOL bRet;

    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_ALL_ACCESS);
    if (!hSCManager)
        return FALSE;

    hService = OpenServiceW(hSCManager,
                            lpDriverName,
                            SERVICE_ALL_ACCESS);
    if (!hService)
    {
        CloseServiceHandle(hSCManager);
        return FALSE;
    }

    bRet = StartServiceW(hService, 0, NULL);
    if (!bRet)
    {
        if (GetLastError() == ERROR_SERVICE_ALREADY_RUNNING)
        {
            wprintf(L"%s.sys already running\n", DRIVER_NAME);
            bRet = TRUE;
        }
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    return bRet;
}