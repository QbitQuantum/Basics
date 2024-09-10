int
main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr,
                "usage:\n"
                "  inject <dllname.dll> <command> [args] ...\n"
                "  inject <dllname.dll> <process-id>\n"
                "  inject <dllname.dll> !<process-name>\n"
        );
        return 1;
    }

    BOOL bAttach = FALSE;
    DWORD dwProcessId = ~0;
    if (isNumber(argv[2])) {
        dwProcessId = atol(argv[2]);
        bAttach = TRUE;
    } else if (argv[2][0] == '!') {
        const char *szProcessName = &argv[2][1];
        if (!getProcessIdByName(szProcessName, &dwProcessId)) {
            fprintf(stderr, "error: failed to find process %s\n", szProcessName);
            return 1;
        }
        bAttach = TRUE;
        fprintf(stderr, "dwProcessId = %lu\n", dwProcessId);
    }

    HANDLE hSemaphore = NULL;
    const char *szDll = argv[1];
    if (!USE_SHARED_MEM) {
        SetEnvironmentVariableA("INJECT_DLL", szDll);
    } else {
        hSemaphore = CreateSemaphore(NULL, 1, 1, "inject_semaphore");
        if (hSemaphore == NULL) {
            fprintf(stderr, "error: failed to create semaphore\n");
            return 1;
        }

        DWORD dwWait = WaitForSingleObject(hSemaphore, 0);
        if (dwWait == WAIT_TIMEOUT) {
            fprintf(stderr, "info: waiting for another inject instance to finish\n");
            dwWait = WaitForSingleObject(hSemaphore, INFINITE);
        }
        if (dwWait != WAIT_OBJECT_0) {
            fprintf(stderr, "error: failed to enter semaphore gate\n");
            return 1;
        }

        SetSharedMem(szDll);
    }

    BOOL bAttachDwm = FALSE;
    PROCESS_INFORMATION processInfo;
    HANDLE hProcess;
    if (bAttach) {
        BOOL bRet;
        HANDLE hToken   = NULL;
        bRet = OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
        if (!bRet) {
            fprintf(stderr, "error: OpenProcessToken returned %u\n", (unsigned)bRet);
            return 1;
        }

        LUID Luid;
        bRet = LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid);
        if (!bRet) {
            fprintf(stderr, "error: LookupPrivilegeValue returned %u\n", (unsigned)bRet);
            return 1;
        }

        TOKEN_PRIVILEGES tp;
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = Luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        bRet = AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof tp, NULL, NULL);
        if (!bRet) {
            fprintf(stderr, "error: AdjustTokenPrivileges returned %u\n", (unsigned)bRet);
            return 1;
        }

        DWORD dwDesiredAccess =
            PROCESS_CREATE_THREAD |
            PROCESS_QUERY_INFORMATION |
            PROCESS_QUERY_LIMITED_INFORMATION |
            PROCESS_VM_OPERATION |
            PROCESS_VM_WRITE |
            PROCESS_VM_READ |
            PROCESS_TERMINATE;
        hProcess = OpenProcess(
            dwDesiredAccess,
            FALSE /* bInheritHandle */,
            dwProcessId);
        if (!hProcess) {
            logLastError("failed to open process");
            return 1;
        }

        char szProcess[MAX_PATH];
        DWORD dwRet = GetModuleFileNameEx(hProcess, 0, szProcess, sizeof szProcess);
        assert(dwRet);
        if (dwRet &&
            stricmp(getBaseName(szProcess), "dwm.exe") == 0) {
            bAttachDwm = TRUE;
        }
    } else {
        std::string commandLine;
        char sep = 0;
        for (int i = 2; i < argc; ++i) {
            const char *arg = argv[i];

            if (sep) {
                commandLine.push_back(sep);
            }

            if (needsQuote(arg)) {
                quoteArg(commandLine, arg);
            } else {
                commandLine.append(arg);
            }

            sep = ' ';
        }

        STARTUPINFO startupInfo;
        memset(&startupInfo, 0, sizeof startupInfo);
        startupInfo.cb = sizeof startupInfo;

        // Create the process in suspended state
        if (!CreateProcessA(
               NULL,
               const_cast<char *>(commandLine.c_str()), // only modified by CreateProcessW
               0, // process attributes
               0, // thread attributes
               TRUE, // inherit handles
               CREATE_SUSPENDED,
               NULL, // environment
               NULL, // current directory
               &startupInfo,
               &processInfo)) {
            DWORD dwLastError = GetLastError();
            fprintf(stderr, "error: failed to execute %s (%lu)\n",
                    commandLine.c_str(), dwLastError);
            if (dwLastError == ERROR_ELEVATION_REQUIRED) {
                fprintf(stderr, "error: target program requires elevated priviledges and must be started from an Administrator Command Prompt, or UAC must be disabled\n");
            }
            return 1;
        }

        hProcess = processInfo.hProcess;
    }

    /*
     * XXX: Mixed architecture don't quite work.  See also
     * http://www.corsix.org/content/dll-injection-and-wow64
     */
    {
        typedef BOOL (WINAPI *PFNISWOW64PROCESS)(HANDLE, PBOOL);
        PFNISWOW64PROCESS pfnIsWow64Process;
        pfnIsWow64Process = (PFNISWOW64PROCESS)
            GetProcAddress(GetModuleHandleA("kernel32"), "IsWow64Process");
        if (pfnIsWow64Process) {
            BOOL isParentWow64 = FALSE;
            BOOL isChildWow64 = FALSE;
            if (pfnIsWow64Process(GetCurrentProcess(), &isParentWow64) &&
                pfnIsWow64Process(hProcess, &isChildWow64) &&
                isParentWow64 != isChildWow64) {
                fprintf(stderr, "error: binaries mismatch: you need to use the "
#ifdef _WIN64
                        "32-bits"
#else
                        "64-bits"
#endif
                        " apitrace binaries to trace this application\n");
                TerminateProcess(hProcess, 1);
                return 1;
            }
        }
    }

    if (bAttachDwm && IsWindows8OrGreater()) {
        // Switch to Microsoft Basic Display Driver before injecting, so that
        // we don't trace with it.
        devconDisable(DEVCON_CLASS_DISPLAY);
        Sleep(1000);
    }

    const char *szDllName;
    szDllName = "injectee.dll";

    char szDllPath[MAX_PATH];
    GetModuleFileNameA(NULL, szDllPath, sizeof szDllPath);
    getDirName(szDllPath);
    strncat(szDllPath, szDllName, sizeof szDllPath - strlen(szDllPath) - 1);

#if 1
    if (!injectDll(hProcess, szDllPath)) {
        TerminateProcess(hProcess, 1);
        return 1;
    }
#endif

    DWORD exitCode;

    if (bAttach) {
        if (bAttachDwm) {
            restartDwmComposition(hProcess);
        }

        exitCode = 0;
    } else {
        // Start main process thread
        ResumeThread(processInfo.hThread);

        // Wait for it to finish
        WaitForSingleObject(hProcess, INFINITE);

        if (pSharedMem && !pSharedMem->bReplaced) {
            fprintf(stderr, "warning: %s was never used: application probably does not use this API\n", szDll);
        }

        exitCode = ~0;
        GetExitCodeProcess(hProcess, &exitCode);

        CloseHandle(processInfo.hThread);
    }

    CloseHandle(hProcess);

    if (hSemaphore) {
        ReleaseSemaphore(hSemaphore, 1, NULL);
        CloseHandle(hSemaphore);
    }

    return (int)exitCode;
}