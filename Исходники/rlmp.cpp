FILE *
PipeSpawn(
    char* cmdstring,
    void* localEnvVars
)
{
    int PipeHandle[2];
    HANDLE WriteHandle, ErrorHandle;
    STARTUPINFO StartupInfo;
    PROCESS_INFORMATION ProcessInformation;
    BOOL Status;
    FILE* pstream;

    ASSERT(cmdstring != NULL);

    // Open the pipe where we'll collect the output.

    _pipe(PipeHandle, 20 * 1024, _O_TEXT|_O_NOINHERIT);   // 20K bytes buffer

    DuplicateHandle(GetCurrentProcess(),
                    (HANDLE)_get_osfhandle(PipeHandle[1]),
                    GetCurrentProcess(),
                    &WriteHandle,
                    0L,
                    TRUE,
                    DUPLICATE_SAME_ACCESS);

    DuplicateHandle(GetCurrentProcess(),
                    (HANDLE)_get_osfhandle(PipeHandle[1]),
                    GetCurrentProcess(),
                    &ErrorHandle,
                    0L,
                    TRUE,
                    DUPLICATE_SAME_ACCESS);

    _close(PipeHandle[1]);

    pstream = _fdopen(PipeHandle[0], "rt");
    if (pstream == NULL) {
        LogError("Creation of I/O filter stream failed - error = %d\n",
            cmdstring, errno);
        CloseHandle(WriteHandle);
        CloseHandle(ErrorHandle);
        WriteHandle = INVALID_HANDLE_VALUE;
        ErrorHandle = INVALID_HANDLE_VALUE;
        _close(PipeHandle[0]);
        return NULL;
    }

    memset(&StartupInfo, 0, sizeof(STARTUPINFO));
    StartupInfo.cb = sizeof(STARTUPINFO);
    StartupInfo.hStdOutput = WriteHandle;
    StartupInfo.hStdError = ErrorHandle;
    StartupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    StartupInfo.dwFlags = STARTF_USESTDHANDLES;

    memset(&ProcessInformation, 0, sizeof(PROCESS_INFORMATION));
    ProcessInformation.hThread  = INVALID_HANDLE_VALUE;
    ProcessInformation.hProcess = INVALID_HANDLE_VALUE;

    // And start the process.

#ifndef NODEBUG
    if (FDebug) {
        printf("Creating process '%s'\n", cmdstring);
        fflush(stdout);
    }
#endif

    Status = CreateProcess(NULL, cmdstring, NULL, NULL, TRUE, 0, localEnvVars, NULL,
                &StartupInfo, &ProcessInformation);

    CloseHandle(WriteHandle);
    CloseHandle(ErrorHandle);
    WriteHandle = INVALID_HANDLE_VALUE;
    ErrorHandle = INVALID_HANDLE_VALUE;

    if (Status == 0) {
        LogError("Exec of '%s' failed - error = %d\n",
            cmdstring, GetLastError());
        fclose(pstream);        // This will close the read handle
        pstream = NULL;
        ProcHandle = INVALID_HANDLE_VALUE;
    } else {
        CloseHandle(ProcessInformation.hThread);
        ProcessInformation.hThread = INVALID_HANDLE_VALUE;

        ProcHandle = ProcessInformation.hProcess;
    }

    return pstream;
}