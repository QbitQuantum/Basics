QList<DWORD> * getDxProcessesIDs(QList<DWORD> * processes, LPCWSTR wstrSystemRootPath) {

    DWORD aProcesses[1024];
    HMODULE hMods[1024];
    DWORD cbNeeded;
    DWORD cProcesses;
    char debug_buf[255];
    WCHAR executableName[MAX_PATH];
    unsigned int i;

    //     Get the list of process identifiers.
    processes->clear();

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return NULL;

    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the names of the modules for each process.

    for ( i = 0; i < cProcesses; i++ )
    {
        if (aProcesses[i] != GetCurrentProcessId()) {
            HANDLE hProcess;
            hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ,
                                    FALSE, aProcesses[i] );
            if (NULL == hProcess)
                goto nextProcess;

            GetModuleFileNameExW(hProcess, 0, executableName, sizeof (executableName));

            if (wcsstr(executableName, wstrSystemRootPath) != NULL) {
                goto nextProcess;
            }

            PathStripPathW(executableName);

            ::WideCharToMultiByte(CP_ACP, 0, executableName, -1, debug_buf, 255, NULL, NULL);
            DEBUG_MID_LEVEL << Q_FUNC_INFO << debug_buf;

            for (unsigned k=0; k < SIZEOF_ARRAY(pwstrExcludeProcesses); k++) {
                if (wcsicmp(executableName, pwstrExcludeProcesses[k])== 0) {
                    DEBUG_MID_LEVEL << Q_FUNC_INFO << "skipping " << pwstrExcludeProcesses;
                    goto nextProcess;
                }
            }

            // Get a list of all the modules in this process.

            if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
            {
                bool isDXPresent = false;
                for ( DWORD j = 0; j < (cbNeeded / sizeof(HMODULE)); j++ )
                {
                    WCHAR szModName[MAX_PATH];

                    if ( GetModuleFileNameExW( hProcess, hMods[j], szModName,
                                              sizeof(szModName) / sizeof(WCHAR)))
                    {

                        PathStripPathW(szModName);
                        ::WideCharToMultiByte(CP_ACP, 0, szModName, -1, debug_buf, 255, NULL, NULL);
                        DEBUG_HIGH_LEVEL << Q_FUNC_INFO << debug_buf;

                        if(wcsicmp(szModName, lightpackHooksDllName) == 0) {
                            goto nextProcess;
                        } else {
                            if (wcsicmp(szModName, L"d3d9.dll") == 0 ||
                                wcsicmp(szModName, L"dxgi.dll") == 0 )
                                isDXPresent = true;
                        }
                    }
                }
                if (isDXPresent)
                    processes->append(aProcesses[i]);

            }
nextProcess:
            // Release the handle to the process.
            CloseHandle( hProcess );
        }
    }

    return processes;
}