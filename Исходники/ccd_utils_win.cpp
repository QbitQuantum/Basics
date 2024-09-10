int shutdownCcd()
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    std::wstring ccdName = L"ccd.exe";

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            if (_wcsicmp(entry.szExeFile, ccdName.c_str()) == 0) {  
                HANDLE hHandle;
                DWORD dwExitCode = 0;
                hHandle = ::OpenProcess(PROCESS_ALL_ACCESS, 0, entry.th32ProcessID);
                      
                ::GetExitCodeProcess(hHandle,&dwExitCode);
                ::TerminateProcess(hHandle,dwExitCode);
            }
        }
    }
    CloseHandle(snapshot);
    return 0;
}