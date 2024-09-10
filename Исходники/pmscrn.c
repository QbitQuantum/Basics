unsigned GetSystemDir( char *buff, int max )
/***********************************************/
{
    // inst
    PRFPROFILE                  prof;
    int                         i;
    char                        c;
    int                         len;

    prof.cchUserName = 0L;
    prof.cchSysName = 0L;

    if( PrfQueryProfile( GUIGetHAB(), &prof ) ) {
        if( prof.cchSysName > 0 ) {
            _AllocA( prof.pszSysName, prof.cchSysName );
            _AllocA( prof.pszUserName, prof.cchUserName );
            PrfQueryProfile( GUIGetHAB(), &prof );
        }

        strcpy( buff, prof.pszSysName );
        if( prof.cchSysName <= max ) {
            len = prof.cchSysName;
        } else {
            len = max;
        }

        for( i = len - 1; i >= 0; i-- ) {
            c = buff[i];
            buff[i] = '\0';
            if( c == '\\' ) {
                break;
            }
        }
    } else {
        buff[0] = '\0';
    }
    return( strlen( buff ) );
} /* _wpi_getinidirectory */