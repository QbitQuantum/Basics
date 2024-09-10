VOID RplAlertRaise( IN DWORD ErrorCode)
/*++

Routine Description:

    Sends an ADMIN alert. The input is a LanManager error message.

    This is a combination of the original Send_alert() routine &&
    RaiseAlert() routine from logonsrv\server\error.c

Arguments:
    ErrorCode - the alert to be raised, text in alertmsg.h

Return Value:
    None.

Notes:
    Failing to post an alert is considered unimportant.  This is why this
    function is VOID.

--*/
{
    char        message[ ALERTSZ + sizeof(STD_ALERT) + sizeof(ADMIN_OTHER_INFO)];
    PSTD_ALERT          alert = (PSTD_ALERT)message;
    PADMIN_OTHER_INFO   other = (PADMIN_OTHER_INFO)ALERT_OTHER_INFO( alert);
    LARGE_INTEGER       time;
    HANDLE              fileHandle;
    DWORD               inBytes;
    DWORD               outBytes;

    NtQuerySystemTime( &time);
    RtlTimeToSecondsSince1970( &time, &alert->alrt_timestamp );

    //  Original code used alrt_servicename == SERVICE_SERVER
    wcscpy( alert->alrt_servicename, SERVICE_RIPL);
    wcscpy( alert->alrt_eventname, ALERT_ADMIN_EVENT );

    other->alrtad_errcode = ErrorCode;
    other->alrtad_numstrings = 0;


    //  NetAlertRaise() is gone, must use mailslots instead.  So, first
    //  open the Alerter mailslot to write to it.

    fileHandle = CreateFile(
            ALERTER_MAILSLOT,
            GENERIC_WRITE,
            FILE_SHARE_WRITE | FILE_SHARE_READ,
            (LPSECURITY_ATTRIBUTES) NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    if ( fileHandle == INVALID_HANDLE_VALUE) {
        RplDump( RG_DebugLevel & RPL_DEBUG_MISC,(
            "AlertRaise: Error opening alerter mailslot, error=%d",
            GetLastError()));
        return;
    }

    inBytes = min( sizeof( message),
                   (DWORD)( (PCHAR)ALERT_VAR_DATA(other) - (PCHAR)message));

    // Write alert notification to mailslot to be read by Alerter service
    if ( !WriteFile(
                    fileHandle,
                    message,
                    inBytes,
                    &outBytes,
                    NULL)       ||      inBytes != outBytes) {

        RplDump( RG_DebugLevel & RPL_DEBUG_MISC,(
            "AlertRaise: Error writing to alerter mailslot %d",
            GetLastError()));

    } else if ( ! CloseHandle( fileHandle)) {

        RplDump( RG_DebugLevel & RPL_DEBUG_MISC,(
            "AlertRaise: Error closing alerter mailslot %d",
            GetLastError()
            ));
    }
    (VOID)CloseHandle( fileHandle);
}