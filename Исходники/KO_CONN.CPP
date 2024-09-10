static bool BuildConnStr ( char* pStrConn, Word pMaxLen, pODBCConn pConn, struct ODBCKV* KVInput,
                           Word iKVInputPairs, struct ODBCKV* KVFileDSN, Word iKVFileDSNPairs ) {
    Word    iPos = 0;
    Char    p[32];                              // arbitary for string port number as string
    // initializations
    memset ( pStrConn, 0, pMaxLen );
    // convert port number to string
    _itoa ( pConn->ServerPort, p, 10 );
    
    // transfer all strings from struct
    if ( !AddKVToConnStr ( "DRIVER", "{KylinODBCDriver}", &iPos, pStrConn, pMaxLen ) ) {
        __ODBCLOG ( _ODBCLogMsg ( LogLevel_DEBUG, "AddKVToConnStr failed in %s", "Driver" ) );
        return FALSE;
    }
    
    if ( !AddKVToConnStr ( "SERVER", pConn->Server, &iPos, pStrConn, pMaxLen ) ) {
        __ODBCLOG ( _ODBCLogMsg ( LogLevel_DEBUG, "AddKVToConnStr failed in %s", "Server" ) );
        return FALSE;
    }
    
    if ( !AddKVToConnStr ( "PROJECT", pConn->Project, &iPos, pStrConn, pMaxLen ) ) {
        __ODBCLOG ( _ODBCLogMsg ( LogLevel_DEBUG, "AddKVToConnStr failed in %s", "Project" ) );
        return FALSE;
    }
    
    if ( !AddKVToConnStr ( "PORT", p, &iPos, pStrConn, pMaxLen ) ) {
        __ODBCLOG ( _ODBCLogMsg ( LogLevel_DEBUG, "AddKVToConnStr failed in %s", "Port" ) );
        return FALSE;
    }
    
    if ( !AddKVToConnStr ( "UID", pConn->UserName, &iPos, pStrConn, pMaxLen ) ) {
        __ODBCLOG ( _ODBCLogMsg ( LogLevel_DEBUG, "AddKVToConnStr failed in %s", "Uid" ) );
        return FALSE;
    }
    
    if ( !AddKVToConnStr ( "PWD", pConn->Password, &iPos, pStrConn, pMaxLen ) ) {
        __ODBCLOG ( _ODBCLogMsg ( LogLevel_DEBUG, "AddKVToConnStr failed in %s", "Pwd" ) );
        return FALSE;
    }
    
    return TRUE;
}