__declspec(dllexport) bool TITCALL DumpRegionsW(HANDLE hProcess, wchar_t* szDumpFolder, bool DumpAboveImageBaseOnly)
{
    int i;
    DWORD cbNeeded = NULL;
    wchar_t szDumpName[MAX_PATH];
    wchar_t szDumpFileName[MAX_PATH];
    MEMORY_BASIC_INFORMATION MemInfo;
    ULONG_PTR DumpAddress = NULL;
    HMODULE EnumeratedModules[1024] = {0};
    bool AddressIsModuleBase = false;

    if(hProcess != NULL)
    {
        if (!EnumProcessModules(hProcess, EnumeratedModules, sizeof(EnumeratedModules), &cbNeeded))
        {
            return false;
        }

        while(VirtualQueryEx(hProcess, (LPVOID)DumpAddress, &MemInfo, sizeof MEMORY_BASIC_INFORMATION) != NULL)
        {
            AddressIsModuleBase = false;
            for(i = 0; i < (int)(cbNeeded / sizeof(HMODULE)); i++)
            {
                if(EnumeratedModules[i] == (HMODULE)MemInfo.AllocationBase)
                {
                    AddressIsModuleBase = true;
                    i = 1024;
                }
                else if(EnumeratedModules[i] == 0)
                {
                    i = 1024;
                }
            }
            if(!(MemInfo.Protect & PAGE_NOACCESS) && AddressIsModuleBase == false)
            {
                if(DumpAboveImageBaseOnly == false || (DumpAboveImageBaseOnly == true && EnumeratedModules[0] < (HMODULE)MemInfo.BaseAddress))
                {
                    RtlZeroMemory(&szDumpName, MAX_PATH);
                    RtlZeroMemory(&szDumpFileName, MAX_PATH);
                    lstrcpyW(szDumpFileName, szDumpFolder);
                    if(szDumpFileName[lstrlenW(szDumpFileName)-1] != L'\\')
                    {
                        szDumpFileName[lstrlenW(szDumpFileName)] = L'\\';
                    }
                    wsprintfW(szDumpName, L"Dump-%x_%x.dmp", (ULONG_PTR)MemInfo.BaseAddress, (ULONG_PTR)MemInfo.RegionSize);
                    lstrcatW(szDumpFileName, szDumpName);
                    DumpMemoryW(hProcess, (LPVOID)MemInfo.BaseAddress, (ULONG_PTR)MemInfo.RegionSize, szDumpFileName);
                }
            }
            DumpAddress = DumpAddress + (ULONG_PTR)MemInfo.RegionSize;
        }
        return true;
    }
    return false;
}