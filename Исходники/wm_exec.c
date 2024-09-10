int wm_exec(char *command, char **output, int *status, int secs) {
    HANDLE hThread;
    DWORD dwCreationFlags;
    STARTUPINFO sinfo = { 0 };
    PROCESS_INFORMATION pinfo = { 0 };
    ThreadInfo tinfo = { 0 };
    int retval = 0;

    sinfo.cb = sizeof(STARTUPINFO);
    sinfo.dwFlags = STARTF_USESTDHANDLES;

    // Create stdout pipe and make it inheritable

    if (!CreatePipe(&tinfo.pipe, &sinfo.hStdOutput, NULL, 0)) {
        merror("%s: ERROR: CreatePipe()", ARGV0);
        return -1;
    }

    sinfo.hStdError = sinfo.hStdOutput;

    if (!SetHandleInformation(sinfo.hStdOutput, HANDLE_FLAG_INHERIT, 1)) {
        merror("%s: ERROR: SetHandleInformation()", ARGV0);
        return -1;
    }

    // Create child process and close inherited pipes

    dwCreationFlags = wm_task_nice < -10 ? HIGH_PRIORITY_CLASS :
                      wm_task_nice < 0 ? ABOVE_NORMAL_PRIORITY_CLASS :
                      wm_task_nice == 0 ? NORMAL_PRIORITY_CLASS :
                      wm_task_nice < 10 ? BELOW_NORMAL_PRIORITY_CLASS :
                      IDLE_PRIORITY_CLASS;

    if (!CreateProcess(NULL, command, NULL, NULL, TRUE, dwCreationFlags, NULL, NULL, &sinfo, &pinfo)) {
        merror("%s: ERROR: CreateProcess(): %ld", ARGV0, GetLastError());
        return -1;
    }

    CloseHandle(sinfo.hStdOutput);

    // Create reading thread

    hThread = CreateThread(NULL, 0, Reader, &tinfo, 0, NULL);

    if (!hThread) {
        merror("%s: ERROR: CreateThread(): %ld", ARGV0, GetLastError());
        return -1;
    }

    // Get output

    switch (WaitForSingleObject(pinfo.hProcess, secs * 1000)) {
    case 0:
        if (status) {
            DWORD exitcode;
            GetExitCodeProcess(pinfo.hProcess, &exitcode);
            *status = exitcode;
        }

        break;

    case WAIT_TIMEOUT:
        TerminateProcess(pinfo.hProcess, 1);
        retval = WM_ERROR_TIMEOUT;
        break;

    default:
        merror("%s: ERROR: WaitForSingleObject()", ARGV0);
        TerminateProcess(pinfo.hProcess, 1);
        retval = -1;
    }

    // Output

    WaitForSingleObject(hThread, INFINITE);

    if (retval >= 0)
        *output = tinfo.output ? tinfo.output : strdup("");
    else
        free(tinfo.output);

    // Cleanup

    CloseHandle(hThread);
    CloseHandle(pinfo.hProcess);
    CloseHandle(pinfo.hThread);

    return retval;
}