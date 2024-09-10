DWORD GetProcessIdFromName(LPCTSTR szProcessName)
{
    PROCESSENTRY32 pe;
    DWORD id = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    pe.dwSize = sizeof(PROCESSENTRY32);
    if( !Process32First(hSnapshot,&pe) )
        return 0;
    while(1)
    {
        pe.dwSize = sizeof(PROCESSENTRY32);
        if( Process32Next(hSnapshot,&pe)==FALSE )
            break;
        if(wcscmp(pe.szExeFile,szProcessName) == 0)
        {
            id = pe.th32ProcessID;
            break;
        }

    }
    CloseHandle(hSnapshot);
    return id;
}