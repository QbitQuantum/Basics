int _tmain(int argc, _TCHAR* argv[])
{
    bool parentprocess = false;
    DWORD createflags = 0;
    WCHAR* cmdline = nullptr;
    int pid = 0;
    int illevel = -1;

    if (!ParseArgs(argc, argv, &pid, &parentprocess, &createflags, &cmdline, &illevel))
    {
        printf("NewProcessFromToken: [options] pid cmdline\n");
        printf("Options:\n");
        printf("-p : Use parent process technique to create the new process\n");
        printf("-j : Try and break away from the current process job\n");
        printf("-c : Create a new console for the process\n");
        printf("-il level: Set the process IL level\n");
        printf("* level:\n");
        printf("  u - Untrusted\n");
        printf("  l - Low\n");
        printf("  m - Medium\n");
        printf("  h - High\n");
        printf("  s - System\n");
        printf("  0xXXXX - Arbitrary IL\n");
    }
    else
    {
        if (pid == 0)
        {
            pid = GetCurrentProcessId();
        }

        EnableDebugPrivilege();
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,
                                      FALSE, pid);
        if (hProcess)
        {
            if (!parentprocess)
            {
                HANDLE hToken;

                if (OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken))
                {
                    HANDLE hDupToken;

                    if (DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, nullptr, SecurityImpersonation, TokenPrimary, &hDupToken))
                    {
                        if (illevel >= 0)
                        {
                            SetTokenIL(hDupToken, illevel);
                        }

                        STARTUPINFO startInfo = { 0 };
                        PROCESS_INFORMATION procInfo = { 0 };

                        startInfo.cb = sizeof(startInfo);

                        if (CreateProcessAsUserW(hDupToken, nullptr, cmdline, nullptr, nullptr, FALSE, createflags, nullptr, nullptr, &startInfo, &procInfo))
                        {
                            printf("Created process %d\n", procInfo.dwProcessId);
                        }
                        else
                        {
                            printf("Error CreateProcessAsUser: %ls\n", GetErrorMessage().c_str());
                            if (CreateProcessWithTokenW(hDupToken, 0, nullptr, cmdline, createflags, nullptr, nullptr, &startInfo, &procInfo))
                            {
                                printf("Created process %d\n", procInfo.dwProcessId);
                            }
                            else
                            {
                                printf("Error CreateProcessWithToken: %ls\n", GetErrorMessage().c_str());
                            }
                        }
                    }
                    else
                    {
                        printf("Error Duplicating Token: %ls\n", GetErrorMessage().c_str());
                    }
                }
                else
                {
                    printf("Error OpenProcessToken: %ls\n", GetErrorMessage().c_str());
                }
            }
            else
            {
                SIZE_T size = 0;

                InitializeProcThreadAttributeList(nullptr, 1, 0, &size);

                std::vector<BYTE> attrlist(size);
                LPPROC_THREAD_ATTRIBUTE_LIST pattrlist = (LPPROC_THREAD_ATTRIBUTE_LIST)&attrlist[0];

                InitializeProcThreadAttributeList(pattrlist, 1, 0, &size);

                if (UpdateProcThreadAttribute(pattrlist, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &hProcess, sizeof(hProcess), nullptr, nullptr))
                {
                    STARTUPINFOEX startInfo = { 0 };
                    PROCESS_INFORMATION procInfo = { 0 };

                    startInfo.StartupInfo.cb = sizeof(startInfo);
                    startInfo.lpAttributeList = pattrlist;

                    if (CreateProcess(nullptr, cmdline, nullptr, nullptr, FALSE, CREATE_SUSPENDED | EXTENDED_STARTUPINFO_PRESENT | createflags,
                                      nullptr, nullptr, &startInfo.StartupInfo, &procInfo))
                    {
                        printf("Created process %d\n", procInfo.dwProcessId);
                        if (illevel >= 0)
                        {
                            HANDLE hToken;

                            if (OpenProcessToken(procInfo.hProcess, TOKEN_ALL_ACCESS, &hToken))
                            {
                                SetTokenIL(hToken, illevel);
                            }
                        }

                        ResumeThread(procInfo.hThread);
                    }
                    else
                    {
                        printf("Error: CreateProcess %ls\n", GetErrorMessage().c_str());
                    }
                }

                DeleteProcThreadAttributeList(pattrlist);
            }

        }
        else
        {
            printf("Error OpenProcess: %ls\n", GetErrorMessage().c_str());
        }
    }

    return 0;
}