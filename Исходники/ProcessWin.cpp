void ProcessWin::ForkAndExec()
{
    nativeIn->CreateHandles();
    nativeOut->CreateHandles();
    nativeErr->CreateHandles();

    STARTUPINFO startupInfo;
    startupInfo.cb          = sizeof(STARTUPINFO);
    startupInfo.lpReserved  = NULL;
    startupInfo.lpDesktop   = NULL;
    startupInfo.lpTitle     = NULL;
    startupInfo.dwFlags     = STARTF_FORCEOFFFEEDBACK | STARTF_USESTDHANDLES;
    startupInfo.cbReserved2 = 0;
    startupInfo.lpReserved2 = NULL;
    //startupInfo.hStdInput = nativeIn->GetReadHandle();
    //startupInfo.hStdOutput = nativeOut->GetWriteHandle();
    //startupInfo.hStdError = nativeErr->GetWriteHandle();
    
    HANDLE hProc = GetCurrentProcess();
    nativeIn->DuplicateRead(hProc, &startupInfo.hStdInput);
    nativeOut->DuplicateWrite(hProc, &startupInfo.hStdOutput);
    nativeErr->DuplicateWrite(hProc, &startupInfo.hStdError);
    
    std::string commandLine(ArgListToString(args));
    std::wstring commandLineW(::UTF8ToWide(commandLine));
    logger->Debug("Launching: %s", commandLine.c_str());

    PROCESS_INFORMATION processInfo;
    BOOL rc = CreateProcessW(NULL,
        (wchar_t*) commandLineW.c_str(),
        NULL,
        NULL,
        TRUE,
        CREATE_NO_WINDOW, // If this is a console application,
           NULL,             // don't open a console window.
        NULL,
        &startupInfo,
        &processInfo);
    
    //CloseHandle(nativeIn->GetReadHandle());
    
    CloseHandle(startupInfo.hStdInput);
    CloseHandle(startupInfo.hStdOutput);
    CloseHandle(startupInfo.hStdError);
    
    if (!rc) {
        std::string message = "Error launching: " + commandLine;
        logger->Error(message);
        throw ValueException::FromString(message);
    }
    else {
        CloseHandle(processInfo.hThread);
        this->pid = processInfo.dwProcessId;
        this->process = processInfo.hProcess;
        this->running = true;
    }
}