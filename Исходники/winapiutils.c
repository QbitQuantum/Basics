OSProcess *
GetOSProcesses(DWORD *n, DWORD *exitTag, DWORD *lastErrorCode) {
    // Create toolhelp snapshot.
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(INVALID_HANDLE_VALUE == snapshot) {
        *exitTag = 1;
        return NULL;
    }

    PROCESSENTRY32W process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    DWORD i = 0;
    OSProcess *procs = malloc(sizeof(*procs) * 2048);
    if (NULL == procs) {
        *exitTag = 2;
        return NULL;
    }

    // Walkthrough a snapshot of all OS processes.
    if (Process32FirstW(snapshot, &process)) {
        do {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process.th32ProcessID);
            if (NULL == hProcess) {
                // Ignore the process.
                continue;
            }

            procs[i].PID = process.th32ProcessID;
            procs[i].PPID = process.th32ParentProcessID;
            procs[i].IsRemote = IsRemote(process.th32ProcessID, exitTag, lastErrorCode);
            if (0 != *exitTag) {
                CloseHandle(hProcess);
                *exitTag = 0;
                continue;
            }
            procs[i].ExecName = GetProcessNameInDeviceForm(hProcess, exitTag, lastErrorCode);
            if (0 != *exitTag) {
                CloseHandle(hProcess);
                *exitTag = 0;
                continue;
            }
            procs[i].CommandLine = GetProcessCommandLine(hProcess, exitTag, lastErrorCode);
            if (0 != *exitTag) {
                free(procs[i].ExecName);
                CloseHandle(hProcess);
                *exitTag = 0;
                continue;
            }
            procs[i].UProfile = GetProcessUserProfile(hProcess, exitTag);
            if (0 != *exitTag) {
                free(procs[i].ExecName);
                free(procs[i].CommandLine);
                FreeUserProfile(procs[i].UProfile);
                CloseHandle(hProcess);
                *exitTag = 0;
                continue;
            }

            CloseHandle(hProcess);
            // Increment index only if OSProccesEx has been filled correctly.
            ++i;
        } while (Process32NextW(snapshot, &process));
    } else {
        // Could not retrieve information about the first process.
        *exitTag = 3;
        free(procs);
        procs = NULL;
    }
    CloseHandle(snapshot);
    *n = i;
    return procs;
}