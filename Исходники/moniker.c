static BOOL start_rpcss(void)
{
    PROCESS_INFORMATION pi;
    STARTUPINFOW si;
    WCHAR cmd[MAX_PATH];
    static const WCHAR rpcss[] = {'\\','r','p','c','s','s','.','e','x','e',0};
    BOOL rslt;
    void *redir;

    TRACE("\n");

    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    GetSystemDirectoryW( cmd, MAX_PATH - sizeof(rpcss)/sizeof(WCHAR) );
    strcatW( cmd, rpcss );

    Wow64DisableWow64FsRedirection( &redir );
    rslt = CreateProcessW( cmd, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi );
    Wow64RevertWow64FsRedirection( redir );

    if (rslt)
    {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        Sleep(100);
    }

    return rslt;
}