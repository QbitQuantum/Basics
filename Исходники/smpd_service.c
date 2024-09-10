/*
  FUNCTION: smpd_add_error_to_message_log(char *msg)

  PURPOSE: Allows any thread to log an error message

  PARAMETERS:
    lpszMsg - text for message

  RETURN VALUE:
    none

  COMMENTS:
*/
void smpd_add_error_to_message_log(char *msg)
{
    TCHAR   szMsg[256];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[2];
    DWORD dwErr;

    dwErr = GetLastError();

    /* Use event logging to log the error. */
    hEventSource = RegisterEventSource(NULL, TEXT(SMPD_SERVICE_NAME));

    _stprintf(szMsg, TEXT("%s error: %d"), TEXT(SMPD_SERVICE_NAME), dwErr);
    lpszStrings[0] = szMsg;
    lpszStrings[1] = msg;

    if (hEventSource != NULL) {
	ReportEvent(hEventSource, /* handle of event source */
	    EVENTLOG_ERROR_TYPE,  /* event type */
	    0,                    /* event category */
	    0,                    /* event ID */
	    NULL,                 /* current user's SID */
	    2,                    /* strings in lpszStrings */
	    0,                    /* no bytes of raw data */
	    (LPCTSTR*)lpszStrings,/* array of error strings */
	    NULL);                /* no raw data */

	(VOID) DeregisterEventSource(hEventSource);
    }
}