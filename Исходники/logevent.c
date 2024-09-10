static int
ReportEventAlt(WORD eventType,
	       DWORD eventId,
	       WORD insertStrCount,
	       char **insertStr,
	       int status)
{
    HANDLE eventLog = NULL;
    BOOL result;

    /* open write handle to the event log */
    eventLog = RegisterEventSource(NULL /* local machine */,
				   AFSREG_SVR_APPLOG_SUBKEY);
    if (eventLog == NULL) {
	return -1;
    }

    /* log the event */
    result = ReportEvent(eventLog, eventType, 0 /* category */, eventId,
			 NULL /* SID */,
			 insertStrCount, (status ? sizeof(status) : 0),
			 insertStr, &status);

    (void) DeregisterEventSource(eventLog);

    return (result ? 0 : -1);
}