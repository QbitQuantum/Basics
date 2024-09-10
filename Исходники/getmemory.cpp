int main(void)
{
    // how can we know the number of process
    DWORD aProcessIds[1024];
    DWORD cResultSize;

    // enumProcess
    if (!EnumProcesses(aProcessIds, sizeof (aProcessIds), &cResultSize))
    {
        DWORD err = GetLastError();
        _ftprintf(stderr, TEXT("ERROR: can't enum processes: %lu\n"), err);
        return 1;
    }

    DWORD cNbProcess = cResultSize / sizeof (DWORD);
    // iter on them
    for (DWORD i = 0; i < cNbProcess; ++i)
    {
        // OpenProcess
        DWORD dProcessId = aProcessIds[i];
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dProcessId);
        if (!hProcess)
        {
            DWORD err = GetLastError();
            _ftprintf(stderr, TEXT("ERROR: can't open Process with pid %lu: %lu\n"), dProcessId, err);
            continue;
        }

        TCHAR tmpFileName[MAX_PATH] = { 0 };
        PTCHAR szFileName = NULL;
        if (!GetModuleFileNameEx(hProcess, 0, szFileName, sizeof(szFileName)/sizeof(TCHAR)))
        {
            DWORD err = GetLastError();
            _ftprintf(stderr, TEXT("ERROR: can't get module name for pid %lu: %lu\n"), dProcessId, err);
            szFileName = TEXT("<unknown>");
        }
        else
        {
            szFileName = tmpFileName;
        }

        // Iterate on pages
        long unsigned int p = 0;
        MEMORY_BASIC_INFORMATION info;
        while (1)
        {
            // prevent overflow on MmUserProbeAddress
            if (p >= (long unsigned int)0x7FFF0000)
                break;
            SIZE_T tmp = VirtualQueryEx(hProcess, (LPCVOID)p, &info, sizeof (info));
            if (!tmp)
            {
                DWORD err = GetLastError();
                _ftprintf(stderr, TEXT("ERROR: can't query virtual information for pid %lu in address %p: %lu\n"), dProcessId, (LPCVOID)p, err);
                break;
            }
            // stop when we didn't read the page information
            if (sizeof (info) != tmp)
                break;
            printline(hProcess, dProcessId, szFileName, &info);
            p += info.RegionSize;
        }
        CloseHandle(hProcess);
    }
    return 0;
}