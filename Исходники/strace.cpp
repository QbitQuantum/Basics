void
stAttachDebugger(
    DWORD           processId,
    std::string     fnIncludes,
    std::string     fnExcludes,
    bool            activeProcess = true)
/*++

Routine Description:
    
    Our mini-debugger implementation. It does following
    things:
    - Attach to a running process
    - On first breakpoint, inject the IAT patching DLL into target
    - Print information of any exception in target process
    - Print the debug spew from target process

Arguments:

    processId - PID of the process to attach
    
    fnIncludes - List of include filters

    fnExclude - List of exclude filters

    activeProcess - If we are attaching to an already running process
        then we pass activeProcess = true, this causes us to call
        DebugActiveProcess and not wait for process creation event

--*/
{
    int threadCount = 0;
    bool processInfected = false;

    if (activeProcess)
    {
        if (!DebugActiveProcess(processId))
        {
            gView->PrintError(L"\nCould not attach to the process (PID = %d).", processId);
            stHandleError(GetLastError());
            goto funcExit;
        }
    }

    HMODULE hMod = GetModuleHandle(L"Kernel32.dll");

    if (hMod)
    {
        PFNDEBUGSETPROCESSKILLONEXIT pfnDebugSetProcessKillOnExit =
                (PFNDEBUGSETPROCESSKILLONEXIT)GetProcAddress(hMod, "DebugSetProcessKillOnExit");

        if (pfnDebugSetProcessKillOnExit)
        {
            pfnDebugSetProcessKillOnExit(FALSE);
        }
    }

    gProcessId = processId;

    DEBUG_EVENT debugEvent;
    DWORD       dwContinueStatus = DBG_CONTINUE;

    bool keepAlive = true;

    while(keepAlive)
    {
        WaitForDebugEvent(&debugEvent, INFINITE);
        dwContinueStatus = DBG_CONTINUE;

        if (debugEvent.dwProcessId == processId)
        {
            switch (debugEvent.dwDebugEventCode)
            {
                case EXCEPTION_DEBUG_EVENT:
                {
                    switch (debugEvent.u.Exception.ExceptionRecord.ExceptionCode)
                    {
                        case EXCEPTION_BREAKPOINT:
                        {
                            //IHU_DBG_LOG(TRC_STRACE, HX_LEVEL_INFO, (L"EXCEPTION_BREAKPOINT\n"));

                            if (!processInfected)
                            {
                                if (gRemovePatchOnExit)
                                {
                                    HRSRC       hRes;
                                    HGLOBAL     hResG;
                                    LPVOID      pRes;
                                    DWORD       dwResSize;

                                    hRes = FindResource(
                                                    NULL,
                                                    MAKEINTRESOURCE(IDR_BIN_DLL),
                                                    L"BIN");

                                    hResG       = LoadResource(NULL, hRes);
                                    pRes        = LockResource(hResG);
                                    dwResSize   = SizeofResource(NULL, hRes);

                                    wchar_t tempPath[MAX_PATH];
                                    wchar_t tempFile[MAX_PATH];
                                    GetTempPath(MAX_PATH, tempPath);
                                    GetTempFileName(tempPath, L"", 0, tempFile);

                                    gInjectorDllPath = tempFile;

                                    HANDLE oFile = CreateFile(
                                                        gInjectorDllPath.c_str(),
                                                        GENERIC_READ | GENERIC_WRITE,
                                                        0,
                                                        NULL,
                                                        CREATE_ALWAYS,
                                                        FILE_ATTRIBUTE_NORMAL,
                                                        NULL);

                                    if (oFile == INVALID_HANDLE_VALUE)
                                    {
                                        gView->PrintError(
                                                L"Failed to create the temporary DLL [%s]. Error code = %x\n",
                                                gInjectorDllPath.c_str(),
                                                GetLastError());
                                        return;
                                    }

                                    DWORD bytesWritten;

                                    if (!WriteFile(
                                                oFile,
                                                pRes,
                                                dwResSize,
                                                &bytesWritten,
                                                NULL))
                                    {
                                        gView->PrintError(
                                                L"Failed to write the temporary DLL. Error code = %x\n",
                                                GetLastError());
                                        return;
                                    }
                                    
                                    CloseHandle(oFile);
                                }
                                else
                                {
                                    wchar_t exePath[MAX_PATH];

                                    if (GetModuleFileName(
                                                        NULL,
                                                        exePath,
                                                        MAX_PATH))
                                    {
                                        std::wstring dllPath = exePath;
                                        int slashPos = dllPath.find_last_of(L'\\');
                                        if (slashPos != -1)
                                        {
                                            dllPath = dllPath.substr(0, slashPos + 1);
                                        }
                                        dllPath += L"stserum.dll";

                                        gInjectorDllPath = dllPath;
                                    }
                                }

                                ihiInjectDll(
                                            ghProcess,
                                            (LPCWSTR)gInjectorDllPath.c_str(),
                                            (LPCSTR)fnIncludes.c_str(),
                                            (LPCSTR)fnExcludes.c_str());

                                processInfected = true;
                            }

                            break;
                        }
                        default:
                        {
                            if (debugEvent.u.Exception.dwFirstChance)
                            {
                                gView->PrintWarning(L"Exception = %x, Address = %x (first-chance!)\n",
                                    debugEvent.u.Exception.ExceptionRecord.ExceptionCode,
                                    debugEvent.u.Exception.ExceptionRecord.ExceptionAddress);
                            }
                            else
                            {
                                gView->PrintError(L"Exception = %x, Address = %x (second-chance!)\n",
                                    debugEvent.u.Exception.ExceptionRecord.ExceptionCode,
                                    debugEvent.u.Exception.ExceptionRecord.ExceptionAddress);
                            }

                            //
                            // If this was a second chance exception, it will cause
                            // the process to terminate
                            //
                            dwContinueStatus = DBG_EXCEPTION_NOT_HANDLED;
                            break;
                        }
                    }

                    break;
                }
                case CREATE_THREAD_DEBUG_EVENT:
                {
                    ++threadCount;
                    break;
                }
                case CREATE_PROCESS_DEBUG_EVENT:
                {
                    if (ghProcess == INVALID_HANDLE_VALUE)
                    {
                        ghProcess = debugEvent.u.CreateProcessInfo.hProcess;
                    }
                    //IHU_DBG_LOG(TRC_STRACE, HX_LEVEL_INFO, (L"Create Process\n"));                    
                    break;
                }
                case EXIT_THREAD_DEBUG_EVENT:
                {
                    --threadCount;
                    break;
                }
                case EXIT_PROCESS_DEBUG_EVENT:
                {
                    gView->PrintMessage(
                        L"Target process has been terminated. Exit Code = %d.\n",
                        debugEvent.u.ExitProcess.dwExitCode);

                    keepAlive = false;
                    break;
                }
                case LOAD_DLL_DEBUG_EVENT:
                {
                    break;
                }
                case UNLOAD_DLL_DEBUG_EVENT:
                {
                    break;
                }
                case OUTPUT_DEBUG_STRING_EVENT:
                {
                    DWORD cbRead = 0;

                    ReadProcessMemory(  ghProcess,
                                        debugEvent.u.DebugString.lpDebugStringData,
                                        gDbgString,
                                        debugEvent.u.DebugString.nDebugStringLength,
                                        &cbRead);

                    if (debugEvent.u.DebugString.fUnicode)
                    {
                        if (gDbgString[0] == L'$')
                        {   
                            gView->PrintTrace(L"%ws", &gDbgString[1]);
                        }
                        else if (gDbgString[0] == L'#')
                        {
                            gView->PrintError(L"%ws", &gDbgString[1]);
                        }
                        else
                        {
                            gView->PrintTraceOrig(L"%ws", gDbgString);
                        }
                        
                    }
                    else
                    {
                        if (gDbgString[0] == L'$')
                        {   
                            gView->PrintTraceA("%s", &gDbgString[1]);
                        }
                        else if (gDbgString[0] == L'#')
                        {
                            gView->PrintErrorA("%s", &gDbgString[1]);
                        }
                        else
                        {
                            gView->PrintTraceOrigA("%s", gDbgString);
                        }
                    }

                    break;
                }
            }
        }

        ContinueDebugEvent( debugEvent.dwProcessId,
                            debugEvent.dwThreadId,
                            dwContinueStatus);
    }

    //
    // If we need to remove the patching on exit, it means we created a
    // temporary injector dll, we should delete that now
    //
    if (gRemovePatchOnExit)
    {
        DeleteFile(gInjectorDllPath.c_str());
    }

    //IHU_DBG_LOG(TRC_STRACE, HX_LEVEL_INFO, (L"Total thread count = %d\n", threadCount));

funcExit:

    return;
}