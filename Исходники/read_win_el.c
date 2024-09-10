/* Start the event logging for each el */
int startEL(char *app, os_el *el)
{
    DWORD NumberOfRecords = 0;

    /* Open the event log */
    el->h = OpenEventLog(NULL, app);
    if (!el->h) {
        merror(EVTLOG_OPEN, ARGV0, app);
        return (-1);
    }

    el->name = app;
    if (GetOldestEventLogRecord(el->h, &el->record) == 0) {
        /* Unable to read oldest event log record */
        merror(EVTLOG_GETLAST, ARGV0, app);
        CloseEventLog(el->h);
        el->h = NULL;
        return (-1);
    }

    if (GetNumberOfEventLogRecords(el->h, &NumberOfRecords) == 0) {
        merror(EVTLOG_GETLAST, ARGV0, app);
        CloseEventLog(el->h);
        el->h = NULL;
        return (-1);
    }

    if (NumberOfRecords <= 0) {
        return (0);
    }

    return ((int)NumberOfRecords);
}