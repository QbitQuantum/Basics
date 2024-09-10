/**
 * Inspect all loaded modules for the specified process
 * @param   dwProcessId     Process id
 */
void VBoxServicePageSharingInspectModules(DWORD dwProcessId)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        printf("VBoxServicePageSharingInspectModules: CreateToolhelp32Snapshot failed with %d\n", GetLastError());
        return;
    }

    printf("VBoxServicePageSharingInspectModules\n");

    MODULEENTRY32 ModuleInfo;
    BOOL          bRet;

    ModuleInfo.dwSize = sizeof(ModuleInfo);
    bRet = Module32First(hSnapshot, &ModuleInfo);
    do
    {
        /** todo when changing this make sure VBoxService.exe is excluded! */
        char *pszDot = strrchr(ModuleInfo.szModule, '.');
        if (    pszDot
            &&  (pszDot[1] == 'e' || pszDot[1] == 'E'))
            continue;   /* ignore executables for now. */

        VBoxServicePageSharingCheckModule(&ModuleInfo);
    }
    while (Module32Next(hSnapshot, &ModuleInfo));

    CloseHandle(hSnapshot);
}