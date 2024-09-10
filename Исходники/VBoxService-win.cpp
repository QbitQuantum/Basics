/** Reports our current status to the SCM. */
static BOOL vgsvcWinSetStatus(DWORD dwStatus, DWORD dwCheckPoint)
{
    if (g_hWinServiceStatus == NULL) /* Program could be in testing mode, so no service environment available. */
        return FALSE;

    VGSvcVerbose(2, "Setting service status to: %ld\n", dwStatus);
    g_dwWinServiceLastStatus = dwStatus;

    SERVICE_STATUS ss;
    RT_ZERO(ss);

    ss.dwServiceType              = SERVICE_WIN32_OWN_PROCESS;
    ss.dwCurrentState             = dwStatus;
    /* Don't accept controls when in start pending state. */
    if (ss.dwCurrentState != SERVICE_START_PENDING)
    {
        ss.dwControlsAccepted     = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;

        /* Don't use SERVICE_ACCEPT_SESSIONCHANGE on Windows 2000 or earlier.  This makes SCM angry. */
        char szOSVersion[32];
        int rc = RTSystemQueryOSInfo(RTSYSOSINFO_RELEASE, szOSVersion, sizeof(szOSVersion));
        if (RT_SUCCESS(rc))
        {
            if (RTStrVersionCompare(szOSVersion, "5.1") >= 0)
                ss.dwControlsAccepted |= SERVICE_ACCEPT_SESSIONCHANGE;
        }
        else
            VGSvcError("Error determining OS version, rc=%Rrc\n", rc);
    }

    ss.dwWin32ExitCode            = NO_ERROR;
    ss.dwServiceSpecificExitCode  = 0; /* Not used */
    ss.dwCheckPoint               = dwCheckPoint;
    ss.dwWaitHint                 = 3000;

    BOOL fStatusSet = SetServiceStatus(g_hWinServiceStatus, &ss);
    if (!fStatusSet)
        VGSvcError("Error reporting service status=%ld (controls=%x, checkpoint=%ld) to SCM: %ld\n",
                   dwStatus, ss.dwControlsAccepted, dwCheckPoint, GetLastError());
    return fStatusSet;
}