/** @copydoc VBOXSERVICE::pfnInit */
static DECLCALLBACK(int) VBoxServiceTimeSyncInit(void)
{
    /*
     * If not specified, find the right interval default.
     * Then create the event sem to block on.
     */
    if (!g_TimeSyncInterval)
        g_TimeSyncInterval = g_DefaultInterval * 1000;
    if (!g_TimeSyncInterval)
        g_TimeSyncInterval = 10 * 1000;

    VbglR3GetSessionId(&g_idTimeSyncSession);
    /* The status code is ignored as this information is not available with VBox < 3.2.10. */

    int rc = RTSemEventMultiCreate(&g_TimeSyncEvent);
    AssertRC(rc);
#ifdef RT_OS_WINDOWS
    if (RT_SUCCESS(rc))
    {
        /*
         * Adjust privileges of this process so we can make system time adjustments.
         */
        if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &g_hTokenProcess))
        {
            TOKEN_PRIVILEGES tkPriv;
            RT_ZERO(tkPriv);
            tkPriv.PrivilegeCount = 1;
            tkPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &tkPriv.Privileges[0].Luid))
            {
                DWORD cbRet = sizeof(g_TkOldPrivileges);
                if (AdjustTokenPrivileges(g_hTokenProcess, FALSE, &tkPriv, sizeof(TOKEN_PRIVILEGES), &g_TkOldPrivileges, &cbRet))
                    rc = VINF_SUCCESS;
                else
                {
                    DWORD dwErr = GetLastError();
                    rc = RTErrConvertFromWin32(dwErr);
                    VBoxServiceError("VBoxServiceTimeSyncInit: Adjusting token privileges (SE_SYSTEMTIME_NAME) failed with status code %u/%Rrc!\n", dwErr, rc);
                }
            }
            else
            {
                DWORD dwErr = GetLastError();
                rc = RTErrConvertFromWin32(dwErr);
                VBoxServiceError("VBoxServiceTimeSyncInit: Looking up token privileges (SE_SYSTEMTIME_NAME) failed with status code %u/%Rrc!\n", dwErr, rc);
            }
            if (RT_FAILURE(rc))
            {
                CloseHandle(g_hTokenProcess);
                g_hTokenProcess = NULL;
            }
        }
        else
        {
            DWORD dwErr = GetLastError();
            rc = RTErrConvertFromWin32(dwErr);
            VBoxServiceError("VBoxServiceTimeSyncInit: Opening process token (SE_SYSTEMTIME_NAME) failed with status code %u/%Rrc!\n", dwErr, rc);
            g_hTokenProcess = NULL;
        }
    }

    if (GetSystemTimeAdjustment(&g_dwWinTimeAdjustment, &g_dwWinTimeIncrement, &g_bWinTimeAdjustmentDisabled))
        VBoxServiceVerbose(3, "VBoxServiceTimeSyncInit: Initially %ld (100ns) units per %ld (100 ns) units interval, disabled=%d\n",
                           g_dwWinTimeAdjustment, g_dwWinTimeIncrement, g_bWinTimeAdjustmentDisabled ? 1 : 0);
    else
    {
        DWORD dwErr = GetLastError();
        rc = RTErrConvertFromWin32(dwErr);
        VBoxServiceError("VBoxServiceTimeSyncInit: Could not get time adjustment values! Last error: %ld!\n", dwErr);
    }
#endif /* RT_OS_WINDOWS */

    return rc;
}