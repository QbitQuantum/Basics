BOOL CIperfThread::InitInstance()
{
    // TODO:  スレッドごとの初期化をここで実行します。
    HANDLE hOldIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOldOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hOldErr = GetStdHandle(STD_ERROR_HANDLE);

    STARTUPINFOA si;
    memset(&si,0,sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;


    m_uniqid = mkhash(m_CmdLine, m_uniqid) ;
    m_uniqid += (WORD)m_nThreadID;
    m_uniqid += (WORD)m_nThreadID >> 4;

    FreeConsole();
    AllocConsole();

    CreateIperfPipe();

    if(CreateProcess(NULL, m_CmdLine, NULL, NULL, TRUE, 0,
        NULL, NULL, &si, &m_ProcessInfo) == FALSE ) {
        return FALSE;
    }

    EnumWindows(WindowHidden, (LPARAM)(PROCESS_INFORMATION *)&m_ProcessInfo);
    WaitForInputIdle(m_ProcessInfo.hProcess, INFINITE);
    SetStdHandle(STD_OUTPUT_HANDLE,hOldOut);
    SetStdHandle(STD_INPUT_HANDLE,hOldIn);
    SetStdHandle(STD_ERROR_HANDLE,hOldErr);
    EnumWindows(WindowHidden, (LPARAM)(PROCESS_INFORMATION *)&m_ProcessInfo);
    return TRUE;
}