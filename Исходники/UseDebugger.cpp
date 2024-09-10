BOOL
CUseDebugger::DebugAttachedProcess()
{
    m_pUI->ShowInfo("Please Enter the PID:\r\n");
    system("taskmgr");

    //get pid
    int argc;
    int pargv[MAXBYTE];
    m_pUI->GetInput(&argc, pargv, g_szBuf, MAXBUF);

    DWORD dwPID = strtoul(g_szBuf, NULL, 10);
    assert(dwPID != 0 && dwPID != ULONG_MAX);

    if (DebugActiveProcess(dwPID))
    {
        this->DebugProcess();
        return TRUE;
    }
    
    return FALSE;
}