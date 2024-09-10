TProcess startSubProcess(void* self, int argc, char* argv[])
{
    IProcessManager _    = (IProcessManager)self;
    IErrorLogger    elog = _->errorLogger;

    STARTUPINFO          si;
    PROCESS_INFORMATION  pi;
    SECURITY_ATTRIBUTES  sa;
    BackendParams		 paramSm;
    char		         paramSmStr[32];
    char                 commandLine[MAX_PATH * 2];
    int                  cmdCharCount;
    HANDLE               paramMap;
    DeadChildInfo        childInfo;
    HANDLE               tokenHandle = NULL;

    int                  i, j;

    ASSERT(elog, argv != NULL, -1);
    ASSERT(elog, argv[0] != NULL, -1);
    ASSERT(elog, argv[1] != NULL, -1);
    ASSERT(elog, argv[2] == NULL, -1);

    /* Set up shared memory for parameter passing */
    ZeroMemory(&sa, sizeof(sa));
    sa.nLength        = sizeof(sa);
    sa.bInheritHandle = TRUE;

    if (!OpenProcessToken(
                GetCurrentProcess(),
                TOKEN_ALL_ACCESS,
                &tokenHandle))
    {
        elog->log(LOG_ERROR,
                  ERROR_CODE_OPEN_PROCESS_TOKEN,
                  "could not open process token: error code %lu",
                  GetLastError());

        return -1;
    }

    if (!SetPrivilege(
                _,
                tokenHandle,
                SE_CREATE_GLOBAL_NAME,
                True))
    {
        elog->log(LOG_ERROR,
                  ERROR_CODE_SET_PRIVILEDGE_FAILED,
                  "could not open process token: error code %lu",
                  GetLastError());

        return -1;
    }

    /* If the first parameter is INVALID_HANDLE_VALUE,
     * the calling process must also specify a size
     * for the file mapping object. In this scenario,
     * CreateFileMapping creates a file mapping object
     * of a specified size that is backed by the system paging file
     * instead of by a file in the file system.
     */
    paramMap = CreateFileMapping(INVALID_HANDLE_VALUE,
                                 &sa,
                                 PAGE_READWRITE,
                                 0,
                                 sizeof(SBackendParams),
                                 sharedMemParamsName);

    if (paramMap == NULL || paramMap == INVALID_HANDLE_VALUE)
    {
        int error = GetLastError();

        elog->log(LOG_ERROR,
                  ERROR_CODE_CREATE_FILE_MAP_FAILED,
                  "could not create file mapping: error code %lu",
                  error);

        return -1;
    }

    sharedMemID       = paramMap;
    sharedMemSegmSize = sizeof(SBackendParams);

    /* Maps a view of a file mapping into the address space of a calling process. */
    paramSm = MapViewOfFile(paramMap, FILE_MAP_WRITE, 0, 0, sizeof(SBackendParams));
    if (!paramSm)
    {
        elog->log(LOG_ERROR,
                  ERROR_CODE_MAP_MEMORY_TO_FILE,
                  "could not map backend parameter memory: error code %lu",
                  GetLastError());

        CloseHandle(paramSm);
        return -1;
    }

    sprintf(paramSmStr, "%lu", (DWORD)paramSm);
    argv[2] = paramSmStr;

    cmdCharCount = sizeof(commandLine);
    commandLine[cmdCharCount - 1] = '\0';
    commandLine[cmdCharCount - 2] = '\0';

    snprintf(commandLine, cmdCharCount - 1, "\"%s\"", ExecPath);

    i = 0;
    while (argv[++i] != NULL)
    {
        j = strlen(commandLine);
        snprintf(commandLine + j, sizeof(commandLine) - 1 - j, " \"%s\"", argv[i]);
    }

    if (commandLine[sizeof(commandLine) - 2] != '\0')
    {
        elog->log(LOG_ERROR,
                  ERROR_CODE_PROC_CMD_LINE_TO_LONG,
                  "subprocess command line too long");
        return -1;
    }

    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);

    /* Create the subprocess in a suspended state.
     * This will be resumed later,
     * once we have written out the parameter file.
     * If this parameter TRUE, each inheritable handle
     * in the calling process is inherited by the new process.
     * If the parameter is FALSE, the handles are not inherited.
     * Note that inherited handles have the same value
     * and access rights as the original handles.
     */
    if (!CreateProcess(NULL, commandLine, NULL,
                       NULL, TRUE, CREATE_SUSPENDED,
                       NULL, NULL, &si, &pi))
    {
        elog->log(LOG_ERROR,
                  ERROR_CODE_CREATE_PROCESS_FAILED,
                  "CreateProcess call failed: (error code %lu)",
                  GetLastError());

        return -1;
    }

    if (!fillBackandParams(
                _,
                paramSm,
                pi.hProcess,
                pi.dwProcessId))
    {
        /* Delete the process */
        if (!TerminateProcess(pi.hProcess, 255))
            elog->log(LOG_ERROR,
                      ERROR_CODE_TERMINATE_PROCESS_FAILED,
                      "Terminate process failed: (error code %lu)",
                      GetLastError());

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return -1;
    }

    /* Drop the handler to the shared memory.
     * Now the shared memory has already been passed
     * along to the child process.
     */
    if (!UnmapViewOfFile(paramSm))
        elog->log(LOG_ERROR,
                  ERROR_CODE_UNMAP_VIEW_OF_FILE,
                  "could not unmap view of backend parameter file: error code %lu",
                  GetLastError());

    if (!CloseHandle(paramMap))
        elog->log(LOG_ERROR,
                  ERROR_CODE_CLOSE_HANDLER_FAILED,
                  "could not close handle to backend parameter file: error code %lu",
                  GetLastError());

    /* All variables are written out, so we can resume the thread */
    if (ResumeThread(pi.hThread) == -1)
    {
        /* Delete the process */
        if (!TerminateProcess(pi.hProcess, 255))
        {
            elog->log(LOG_ERROR,
                      ERROR_CODE_TERMINATE_PROCESS_FAILED,
                      "Terminate process failed: (error code %lu)",
                      GetLastError());

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            return -1;
        }

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        elog->log(LOG_ERROR,
                  ERROR_CODE_RESUME_THREAD_FAILED,
                  "Terminate process failed: (error code %lu)",
                  GetLastError());
        return -1;
    }

    childInfo = malloc(sizeof(SDeadChildInfo));
    if (childInfo == NULL)
        elog->log(LOG_FATAL,
                  ERROR_CODE_OUT_OF_MEMORY,
                  "out of memory");

    childInfo->procHandle = pi.hProcess;
    childInfo->procId     = pi.dwProcessId;

    /* Directs a wait thread in the thread pool to wait on the object.
     * The wait thread queues the specified callback function to the thread pool
     * when one of the following occurs:
     *  - The specified object is in the signaled state.
     *  - The time-out interval elapses.
     * When a process terminates, the state of the process object
     * becomes signaled, releasing any threads
     * that had been waiting for the process to terminate.
     */
    if (!RegisterWaitForSingleObject(
                &childInfo->waitHandle,
                pi.hProcess,
                deadChildProcCallBack,
                childInfo,
                INFINITE,
                WT_EXECUTEONLYONCE | WT_EXECUTEINWAITTHREAD))
        elog->log(LOG_ERROR,
                  ERROR_CODE_REGISTER_WAIT_HANDLER_FAILED,
                  "Could not register process for wait: error code %lu",
                  GetLastError());

    /* Don't close pi.hProcess here -
     * the wait thread needs access to it.
     */
    CloseHandle(pi.hThread);

    return pi.hProcess;
}