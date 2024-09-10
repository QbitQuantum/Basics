BOOL WINAPI EjectLibW(DWORD dwProcessId, PCWSTR pszLibFile)
{

    BOOL bOk = FALSE; // Assume that the function fails
    HANDLE hthSnapshot = NULL;
    HANDLE hProcess = NULL, hThread = NULL;

    __try
    {
        // Grab a new snapshot of the process
        hthSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
        if (hthSnapshot == INVALID_HANDLE_VALUE) __leave;

        // Get the HMODULE of the desired library
        MODULEENTRY32W me = { sizeof(me) };
        BOOL bFound = FALSE;
        BOOL bMoreMods = Module32FirstW(hthSnapshot, &me);
        for (; bMoreMods; bMoreMods = Module32NextW(hthSnapshot, &me))
        {
            bFound = (_wcsicmp(me.szModule,  pszLibFile) == 0) ||
                     (_wcsicmp(me.szExePath, pszLibFile) == 0);
            if (bFound) break;
        }
        if (!bFound) __leave;

        // Get a handle for the target process.
        hProcess = OpenProcess(
                       PROCESS_QUERY_INFORMATION |
                       PROCESS_CREATE_THREAD     |
                       PROCESS_VM_OPERATION,  // For CreateRemoteThread
                       FALSE, dwProcessId);
        if (hProcess == NULL) __leave;

        // Get the real address of FreeLibrary in Kernel32.dll
        PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
                                             GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "FreeLibrary");
        if (pfnThreadRtn == NULL) __leave;

        // Create a remote thread that calls FreeLibrary()
        hThread = CreateRemoteThread(hProcess, NULL, 0,
                                     pfnThreadRtn, me.modBaseAddr, 0, NULL);
        if (hThread == NULL) __leave;

        // Wait for the remote thread to terminate
        WaitForSingleObject(hThread, INFINITE);

        bOk = TRUE; // Everything executed successfully
    }
    __finally   // Now we can clean everything up
    {

        if (hthSnapshot != NULL)
            CloseHandle(hthSnapshot);

        if (hThread     != NULL)
            CloseHandle(hThread);

        if (hProcess    != NULL)
            CloseHandle(hProcess);
    }

    return(bOk);
}