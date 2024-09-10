void CALLBACK Export( HWND, HINSTANCE, LPTSTR lpCmdLine, int )
{
    if( !lpCmdLine )
        ExitProcess( 0 );
    Handle onp( CreateFile( lpCmdLine, GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0 ) );

    if( !onp || onp == INVALID_HANDLE_VALUE )
        ExitProcess( 0 );
    
    wchar_t* env = GetEnvironmentStringsW();
    int i;
    for( i = 0; *(int*)(env + i); i++ );

    i *= sizeof(*env);
    i += 2 * sizeof(*env);

    DWORD written;

    WriteFile( onp, env, i, &written, 0 );

    FreeEnvironmentStringsW( env );

    return;
}