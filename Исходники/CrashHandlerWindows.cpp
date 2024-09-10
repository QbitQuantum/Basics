void CrashHandlerWindows::writeCrashDump(PEXCEPTION_POINTERS pExceptionPointers) {

    // Build the temporary path to store the minidump
    CHAR* tempPathBuffer = m_pCrashInfo->miniDumpTmpFile;
    GetTempPath(MAX_PATH, m_pCrashInfo->miniDumpTmpFile);
    DWORD tick = GetTickCount();
    char tickChar[24];
    _ultoa(tick, tickChar, 10);
    strcat(&tempPathBuffer[0], tickChar);
    strcat(&tempPathBuffer[0], ".dmp");

    // Create the minidump file
    HANDLE hFile = CreateFile(tempPathBuffer, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE)
        return;

    MINIDUMP_TYPE miniDumpType = (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory);

    MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
    exceptionInfo.ThreadId = GetCurrentThreadId();
    exceptionInfo.ExceptionPointers = pExceptionPointers;
    exceptionInfo.ClientPointers = TRUE;

    MINIDUMP_CALLBACK_INFORMATION callbackInfo;
    callbackInfo.CallbackRoutine = miniDumpCallback;
    callbackInfo.CallbackParam = 0;

    // Write the minidump
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, miniDumpType, &exceptionInfo, NULL, NULL);
    CloseHandle(hFile);
}