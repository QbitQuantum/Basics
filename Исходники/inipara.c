HANDLE WINAPI search_process(LPCWSTR lpstr, DWORD m_parent)
{
    BOOL   b_more;
    PROCESSENTRY32W pe32;
    HANDLE hSnapshot = INVALID_HANDLE_VALUE;
    DWORD  chi_pid[PROCESS_NUM] = {0};
    HANDLE m_handle = NULL;
    volatile int    i = 1;
    static   int    h_num = 1;
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if( hSnapshot == INVALID_HANDLE_VALUE )
    {
#ifdef _LOGDEBUG
        logmsg("CreateToolhelp32Snapshot (of processes) error %lu\n",GetLastError() );
#endif
        return m_handle;
    }
    chi_pid[0] = m_parent;
    pe32.dwSize=sizeof(pe32);
    b_more = Process32FirstW(hSnapshot,&pe32);
    while (b_more)
    {
        if ( m_parent == pe32.th32ParentProcessID )
        {
            chi_pid[i++] = pe32.th32ProcessID;
            if (i>=PROCESS_NUM)
            {
                break;
            }
        }
        if ( lpstr && pe32.th32ParentProcessID>4 && StrStrIW((LPWSTR)lpstr,(LPCWSTR)pe32.szExeFile) )
        {
            m_handle = (HANDLE)pe32.th32ProcessID;
            break;
        }
        b_more = Process32NextW(hSnapshot,&pe32);
    }
    CloseHandle(hSnapshot);
    if ( !m_handle && chi_pid[0] )
    {
        for ( i=1 ; i<PROCESS_NUM&&h_num<PROCESS_NUM; ++i )
        {
            HANDLE tmp = OpenProcess(PROCESS_TERMINATE, FALSE, chi_pid[i]);
            if ( NULL != tmp )
            {
                g_handle[h_num++] =  tmp;
                search_process(NULL, chi_pid[i]);
            }
        }
    }
    return m_handle;
}