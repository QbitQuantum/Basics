/**
 * Creates the service.
 *
 * @returns 0 on success.
 * @returns -1 on failure.
 */
static int suplibOsUpdateService(void)
{
    /*
     * Assume it didn't exist, so we'll create the service.
     */
    SC_HANDLE   hSMgr = OpenSCManager(NULL, NULL, SERVICE_CHANGE_CONFIG);
    DWORD LastError = GetLastError(); NOREF(LastError);
    AssertMsg(hSMgr, ("OpenSCManager(,,delete) failed LastError=%Rwa\n", LastError));
    if (hSMgr)
    {
        SC_HANDLE hService = OpenService(hSMgr, SERVICE_NAME, SERVICE_CHANGE_CONFIG);
        if (hService)
        {
            char szDriver[RTPATH_MAX];
            int rc = RTPathExecDir(szDriver, sizeof(szDriver) - sizeof("\\VBoxDrv.sys"));
            if (RT_SUCCESS(rc))
            {
                strcat(szDriver, "\\VBoxDrv.sys");

                SC_LOCK hLock = LockServiceDatabase(hSMgr);
                if (ChangeServiceConfig(hService,
                                        SERVICE_KERNEL_DRIVER,
                                        SERVICE_DEMAND_START,
                                        SERVICE_ERROR_NORMAL,
                                        szDriver,
                                        NULL, NULL, NULL, NULL, NULL, NULL))
                {

                    UnlockServiceDatabase(hLock);
                    CloseServiceHandle(hService);
                    CloseServiceHandle(hSMgr);
                    return 0;
                }
                else
                {
                    DWORD LastError = GetLastError(); NOREF(LastError);
                    AssertMsgFailed(("ChangeServiceConfig failed LastError=%Rwa\n", LastError));
                }
            }
            UnlockServiceDatabase(hLock);
            CloseServiceHandle(hService);
        }
        else
        {
            DWORD LastError = GetLastError(); NOREF(LastError);
            AssertMsgFailed(("OpenService failed LastError=%Rwa\n", LastError));
        }
        CloseServiceHandle(hSMgr);
    }
    return -1;
}