/**************************************************************************
 *           WINHELP entry point
 *
 * FIXME: should go into winhlp32.exe, but we don't support 16-bit modules in executables yet.
 */
void WINAPI WINHELP_EntryPoint( CONTEXT86 *context )
{
    static const WCHAR winhlp32W[] = {'\\','w','i','n','h','l','p','3','2','.','e','x','e',0};
    PDB16 *psp;
    INT len, total;
    WCHAR *cmdline, *p;
    PROCESS_INFORMATION info;
    STARTUPINFOW startup;
    DWORD count, exit_code = 1;

    InitTask16( context );

    TRACE( "(ds=%x es=%x fs=%x gs=%x, bx=%04x cx=%04x di=%04x si=%x)\n",
            context->SegDs, context->SegEs, context->SegFs, context->SegGs,
            context->Ebx, context->Ecx, context->Edi, context->Esi );

    psp = GlobalLock16( context->SegEs );
    len = MultiByteToWideChar( CP_ACP, 0, (char *)psp->cmdLine + 1, psp->cmdLine[0], NULL, 0 );
    total = (GetSystemDirectoryW( NULL, 0 ) + len + 1) * sizeof(WCHAR) + sizeof(winhlp32W);
    cmdline = HeapAlloc( GetProcessHeap(), 0, total );
    GetSystemDirectoryW( cmdline, total );
    lstrcatW( cmdline, winhlp32W );
    p = cmdline + lstrlenW(cmdline);
    if (len)
    {
        *p++ = ' ';
        MultiByteToWideChar( CP_ACP, 0, (char *)psp->cmdLine + 1, psp->cmdLine[0], p, len );
        p[len] = 0;
    }

    memset( &startup, 0, sizeof(startup) );
    startup.cb = sizeof(startup);

    if (CreateProcessW( NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &startup, &info ))
    {
        /* Give 10 seconds to the app to come up */
        if (wait_input_idle( info.hProcess, 10000 ) == WAIT_FAILED)
            WARN("WaitForInputIdle failed: Error %d\n", GetLastError() );
        ReleaseThunkLock( &count );

        WaitForSingleObject( info.hProcess, INFINITE );
        GetExitCodeProcess( info.hProcess, &exit_code );
        CloseHandle( info.hThread );
        CloseHandle( info.hProcess );
    }
    else
        ReleaseThunkLock( &count );

    HeapFree( GetProcessHeap(), 0, cmdline );
    ExitThread( exit_code );
}