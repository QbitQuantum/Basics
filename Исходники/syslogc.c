/******************************************************************************
 * openlog
 *
 * Open connection to system logger.
 */
ROKEN_LIB_FUNCTION void ROKEN_LIB_CALL
openlog( char* ident, int option, int facility )
{
    BOOL failed = FALSE;
    SOCKADDR_IN sa_local;
    DWORD n;
    int size;

    if ( !initialized )
        return;

    EnterCriticalSection(&cs_syslog);

    if( syslog_opened )
        goto done;

    failed = TRUE;

    syslog_facility = facility? facility : LOG_USER;

    if( option & LOG_PID )
        sprintf_s( syslog_procid_str, sizeof(syslog_procid_str), "[%lu]", GetCurrentProcessId() );
    else
        syslog_procid_str[0] = '\0';

    /* FIXME: handle other options */

    n = sizeof(local_hostname);
    if( !GetComputerName( local_hostname, &n ) )
        goto done;

    syslog_socket = INVALID_SOCKET;

    init_logger_addr();

    for( n = 0;; n++ )
    {
        syslog_socket = socket( AF_INET, SOCK_DGRAM, 0 );
        if( INVALID_SOCKET == syslog_socket )
            goto done;

        memset( &sa_local, 0, sizeof(SOCKADDR_IN) );
        sa_local.sin_family = AF_INET;
        if( bind( syslog_socket, (SOCKADDR*) &sa_local, sizeof(SOCKADDR_IN) ) == 0 )
            break;
        rk_closesocket( syslog_socket );
        syslog_socket = INVALID_SOCKET;
        if( n == 100 )
            goto done;
        Sleep(0);
    }

    /* get size of datagramm */
    size = sizeof(datagramm_size);
    if( getsockopt( syslog_socket, SOL_SOCKET, SO_MAX_MSG_SIZE, (char*) &datagramm_size, &size ) )
        goto done;
    if( datagramm_size - strlen(local_hostname) - (ident? strlen(ident) : 0) < 64 )
        goto done;
    if( datagramm_size > SYSLOG_DGRAM_SIZE )
        datagramm_size = SYSLOG_DGRAM_SIZE;

    if (ident)
        strcpy_s(syslog_ident, sizeof(syslog_ident), ident);

    syslog_facility = (facility ? facility : LOG_USER);
    failed = FALSE;

 done:
    if( failed ) {
        if( syslog_socket != INVALID_SOCKET )
            rk_closesocket( syslog_socket );
    }
    syslog_opened = !failed;

    LeaveCriticalSection(&cs_syslog);
}