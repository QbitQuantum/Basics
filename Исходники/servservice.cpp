BOOL sendStatusToSCMgr(DWORD dwCurrentState,
                       DWORD dwWin32ExitCode,
                       DWORD dwCheckPoint,
                       DWORD dwWaitHint) {
    BOOL result;
    if (dwCurrentState == SERVICE_START_PENDING)
		serviceStatus.dwControlsAccepted = 0;
    else
		serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP |
		SERVICE_ACCEPT_PAUSE_CONTINUE;
    serviceStatus.dwCurrentState = dwCurrentState;
    serviceStatus.dwWin32ExitCode = dwWin32ExitCode;
    serviceStatus.dwCheckPoint = dwCheckPoint;
    serviceStatus.dwWaitHint = dwWaitHint;
    if (!(result = SetServiceStatus(serviceStatusHandle, &serviceStatus))) {
        logServiceMessage(_T("SetServiceStatus"), EVENTLOG_ERROR_TYPE);
    }
    return result;
}