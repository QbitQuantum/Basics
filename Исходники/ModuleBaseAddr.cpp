DWORD GetBaseAddr( const char *process_name )
{
    DWORD pid = GetProcessID(process_name);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pid);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hSnapshot);
        return -1;
    }
    MODULEENTRY32 me;
    me.dwSize = sizeof(MODULEENTRY32);
    Module32First(hSnapshot,&me);

    return (DWORD)me.modBaseAddr;

    CloseHandle(hSnapshot);

    return -1;
}