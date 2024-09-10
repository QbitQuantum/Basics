static DWORD RunChildProcessCmdl( const char *cmdl, LPPROCESS_INFORMATION pinfo, LPHANDLE readpipe )
{
    HANDLE              cp;
    HANDLE              parent_std_output;
    HANDLE              parent_std_error;
    HANDLE              pipe_input;
    HANDLE              pipe_output;
    SECURITY_ATTRIBUTES sa;
    DWORD               rc = 0;

    sa.nLength = sizeof( sa );
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    if( !CreatePipe( &pipe_input, &pipe_output, &sa, 0 ) ) {
        return( GetLastError() );
    }
    cp = GetCurrentProcess();
    DuplicateHandle( cp, GetStdHandle( STD_OUTPUT_HANDLE ), cp, &parent_std_output, 0, TRUE, DUPLICATE_SAME_ACCESS );
    DuplicateHandle( cp, GetStdHandle( STD_ERROR_HANDLE ), cp, &parent_std_error, 0, TRUE, DUPLICATE_SAME_ACCESS );
    SetStdHandle( STD_OUTPUT_HANDLE, pipe_output );
    SetStdHandle( STD_ERROR_HANDLE, pipe_output );
    if( !DuplicateHandle( cp, pipe_input, cp, readpipe, 0, FALSE, DUPLICATE_SAME_ACCESS ) ) {
        rc = GetLastError();
    }
    CloseHandle( pipe_input );
    if( rc == 0 ) {
        STARTUPINFO     sinfo;
        memset( &sinfo, 0, sizeof( sinfo ) );
        sinfo.cb = sizeof( sinfo );
        if( !CreateProcess( NULL, (LPSTR)cmdl, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, pinfo ) ) {
            rc = GetLastError();
        }
    }
    CloseHandle( pipe_output );
    SetStdHandle( STD_OUTPUT_HANDLE, parent_std_output );
    SetStdHandle( STD_ERROR_HANDLE, parent_std_error );
    CloseHandle( parent_std_output );
    CloseHandle( parent_std_error );
    return( rc );
}