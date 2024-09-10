DWORD ProcessAccessHelp::getProcessByName(const WCHAR * processName)
{
    DWORD dwPID = 0;
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if( !Process32FirstW( hProcessSnap, &pe32 ) )
    {
#ifdef DEBUG_COMMENTS
        Scylla::debugLog.log(L"getProcessByName :: Error getting first Process");
#endif
        CloseHandle( hProcessSnap );
        return 0;
    }

    do
    {
        if(!_wcsicmp(pe32.szExeFile, processName))
        {
            dwPID = pe32.th32ProcessID;
            break;
        }
    } while(Process32NextW(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    return dwPID;
}