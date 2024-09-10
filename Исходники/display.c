BOOL ExecMyself( LPCTSTR lpCommandLine )
{
    DWORD dwSession, r;
    HANDLE hToken;
    LPVOID lpEnv;
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInformation;
    TCHAR szApplicationName[ 1024 ];
    TCHAR szCommandLine[ 1024 ];

    r = GetModuleFileName( NULL, szApplicationName, _countof( szApplicationName ) );
    if( r == 0 || r >= _countof( szApplicationName ) ){
        DebugMsg( _T("GetModuleFileName:%d"), GetLastError() );
        return FALSE;
    }

    if( StringCchPrintf( szCommandLine, _countof( szCommandLine ), _T("\"%s\" %s"), szApplicationName, lpCommandLine ) != S_OK ) return FALSE;
    dwSession = WTSGetActiveConsoleSessionId();
    if( dwSession == 0xFFFFFFFF ){
        DebugMsg( _T("WTSGetActiveConsoleSessionId:%d"), GetLastError() );
        return FALSE;
    }
    if( !WTSQueryUserToken( dwSession, &hToken ) ){
        DebugMsg( _T("WTSQueryUserToken:%d"), GetLastError() );
        return FALSE;
    }
    if( !CreateEnvironmentBlock( &lpEnv, hToken, FALSE ) ){
        DebugMsg( _T("CreateEnvironmentBlock:%d"), GetLastError() );
        return FALSE;
    }

    ZeroMemory( &startupInfo, sizeof(STARTUPINFO) );
    startupInfo.cb = sizeof(STARTUPINFO);
    startupInfo.lpDesktop = _T( "winsta0\\default" );
    if( !CreateProcessAsUser( hToken, szApplicationName, szCommandLine, NULL, NULL, 
        FALSE, CREATE_UNICODE_ENVIRONMENT, lpEnv, NULL, &startupInfo, &processInformation) )
    {
        DebugMsg( _T("CreateProcessAsUser:%d"), GetLastError() );
        return FALSE;
    }

    CloseHandle(processInformation.hThread);
    CloseHandle(processInformation.hProcess);

    return TRUE;
}