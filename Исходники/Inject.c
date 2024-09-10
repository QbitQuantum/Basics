/********************************************
 * Return PID using the Toolhelp functions. *
 ********************************************/
DWORD GetPIDFromNameToolhelp(char *szProcessName)
{
    typedef HANDLE (WINAPI *CREATESNAPSHOT) (DWORD, DWORD);
    typedef BOOL   (WINAPI *PROCESSWALK)    (HANDLE, LPPROCESSENTRY32);

    HINSTANCE       hKernel;
    CREATESNAPSHOT  CreateToolhelp32Snapshot;
    PROCESSWALK     Process32First;
    PROCESSWALK     Process32Next;

    HANDLE          hSnapshot;
    PROCESSENTRY32  pe32;
    BOOL            bRes;
    char            *p;
    DWORD           dwPID = -1;

    // Check szProcessName
    if (!szProcessName)
        return -1;

    // Get Kernel32 handle
    if (!(hKernel = GetModuleHandle("Kernel32.dll")))
        return -1;

    // We must link to these functions explicitly.
    // Otherwise it will fail on Windows NT which doesn't have Toolhelp
    // functions defined in Kernel32.
    CreateToolhelp32Snapshot = (CREATESNAPSHOT) GetProcAddress(hKernel, "CreateToolhelp32Snapshot");
    Process32First = (PROCESSWALK) GetProcAddress(hKernel, "Process32First");
    Process32Next = (PROCESSWALK) GetProcAddress(hKernel, "Process32Next");
    if (!CreateToolhelp32Snapshot || !Process32First || !Process32Next)
    {
        FreeLibrary(hKernel);
        SetLastError(ERROR_PROC_NOT_FOUND);
        return -1;
    }

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return -1;

    pe32.dwSize = sizeof(pe32);
    bRes = Process32First(hSnapshot, &pe32);

    while (bRes)
    {
        // Strip off full path
        p = strrchr(pe32.szExeFile, '\\');
        if (p)
            p++;
        else
            p = pe32.szExeFile;

        // Process found ?
        if (stricmp(p, szProcessName) == 0)
        {
            dwPID = pe32.th32ProcessID;
            break;
        }

        bRes = Process32Next(hSnapshot, &pe32);
    }

    CloseHandle(hSnapshot);
    return dwPID;
}