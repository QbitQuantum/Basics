void add2MsgLog(TCHAR* log)
{
    TCHAR msg[sizeof(SERVICE_NAME)/sizeof(TCHAR) + 100];
    HANDLE hEventSrouce;
    const TCHAR* logStr[2];
    DWORD dwErr;
    if (!bDebug) {
        dwErr = GetLastError();
        hEventSrouce = RegisterEventSource(NULL, SERVICE_NAME);
        _stprintf_s(msg, sizeof(msg)/sizeof(msg[0]), _T("%s error: %d"), SERVICE_NAME, dwErr);
        logStr[0] = msg;
        logStr[1] = log;

        if (hEventSrouce) {
            ReportEvent(hEventSrouce,
                        EVENTLOG_ERROR_TYPE,
                        0,
                        0,
                        NULL,
                        2,
                        0,
                        logStr,
                        NULL);
            DeregisterEventSource(hEventSrouce);

        }
    }
}