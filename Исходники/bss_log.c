static void xsyslog(BIO *bp, int priority, const char *string)
{
    LPCSTR lpszStrings[2];
    WORD evtype = EVENTLOG_ERROR_TYPE;
    char pidbuf[DECIMAL_SIZE(DWORD) + 4];

    if (bp->ptr == NULL)
        return;

    switch (priority) {
    case LOG_EMERG:
    case LOG_ALERT:
    case LOG_CRIT:
    case LOG_ERR:
        evtype = EVENTLOG_ERROR_TYPE;
        break;
    case LOG_WARNING:
        evtype = EVENTLOG_WARNING_TYPE;
        break;
    case LOG_NOTICE:
    case LOG_INFO:
    case LOG_DEBUG:
        evtype = EVENTLOG_INFORMATION_TYPE;
        break;
    default:
        /*
         * Should never happen, but set it
         * as error anyway.
         */
        evtype = EVENTLOG_ERROR_TYPE;
        break;
    }

    sprintf(pidbuf, "[%lu] ", GetCurrentProcessId());
    lpszStrings[0] = pidbuf;
    lpszStrings[1] = string;

    ReportEventA(bp->ptr, evtype, 0, 1024, NULL, 2, 0, lpszStrings, NULL);
}