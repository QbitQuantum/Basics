BOOL LogServer::CreateLogPipe()
{
    logme("LogServer::CreateLogPipe: cmd=%s", GetExternalCmd());
    m_fpLog = _popen(GetExternalCmd(), "wb");
    if (m_fpLog == NULL)
    {
        fprintf(stderr, "LogServer: failed to open pipe (%s). err=%d\n", GetExternalCmd(), GetLastError());
        return FALSE;
    }
    return TRUE;

#if 0
    // Create the program
    HANDLE hProgStdinRd, hProgStdinWr;
    SECURITY_ATTRIBUTES saAttr;

    // Set the bInheritHandle flag so pipe handles are inherited.
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create a pipe for the child process's STDIN.
    if (! CreatePipe(&hProgStdinRd, &hProgStdinWr, &saAttr, 0))
    {
        printf("JaxerLogger: Create Stdin pipe failed.\n");
        return FALSE;
    }

    // Ensure that the write handle to the child process's pipe for STDIN is not inherited.
    SetHandleInformation( hProgStdinWr, HANDLE_FLAG_INHERIT, 0);

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION) );

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO) );
    si.cb = sizeof(STARTUPINFO);
    si.hStdInput = hProgStdinRd;
    si.dwFlags |= STARTF_USESTDHANDLES;

    logme("JaxerLog: pipe cmd=%s", GetExternalCmd());
    BOOL rc = CreateProcess(NULL,
                            (TCHAR*)GetExternalCmd(),
                            NULL,  /* default process security descriptor */
                            NULL,  /* default thread security descriptor */
                            TRUE,  /* inherit handles */
                            CREATE_NO_WINDOW | CREATE_BREAKAWAY_FROM_JOB,
                            NULL,  /* inherit environment */
                            NULL,  /* inherit current directory */
                            &si,
                            &pi);

    if (!rc)
    {
        char s[256];
        sprintf(s,"JaxerLogger: Create process (%s) failed. err=%d\n", GetExternalCmd(),
                GetLastError());
        char *t = s;
        logme(s);
        return FALSE;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    m_fdLog = hProgStdinWr;
}