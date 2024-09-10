BOOL StartExplorer(DWORD timeout, NS_UNUSED BOOL kill)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    TCHAR shellpath[MAX_PATH];

    OutputDebugString(_T("nsRE::StartExplorer"));

    if (FindWindow(SHELLWND, NULL))
        NS_FAILED(NULL, _T("Explorer already running"));

    GetWindowsDirectory(shellpath, MAX_PATH - 1);
    shellpath[MAX_PATH - 1] = 0;
    _tcsncat(shellpath, SHELL, MAX_PATH - 1);
    shellpath[MAX_PATH - 1] = 0;

    FakeStartupIsDone();

    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    memset(&si, 0, sizeof(STARTUPINFO));

    si.cb = sizeof(STARTUPINFO);

    if(!CreateProcess(NULL,     /* No module name (use command line) */
        shellpath,              /* Command line */
        NULL,                   /* Process handle not inheritable */
        NULL,                   /* Thread handle not inheritable */
        FALSE,                  /* Set handle inheritance to FALSE */
        0,                      /* No creation flags */
        NULL,                   /* Use parent's environment block */
        NULL,                   /* Use parent's starting directory */
        &si,                    /* Pointer to STARTUPINFO structure */
        &pi))                   /* Pointer to PROCESS_INFORMATION structure */
        NS_FAILED(NULL, _T("Cannot spawn explorer process"));

    switch (WaitForInputIdle(pi.hProcess, timeout))
    {
        case 0            : break; /* OK */
        case WAIT_TIMEOUT :
            if (timeout == IGNORE) break; /* OK as requested */
            NS_FAILED(pi.hProcess, _T("Timeout while waiting for explorer process"));
        case WAIT_FAILED  : NS_FAILED(pi.hProcess, _T("Error while waiting for explorer process"));
        default           : NS_FAILED(pi.hProcess, _T("This should not be reached"));
    }

    return TRUE;
}