// Asks child process to shutdown. If it is unable to shutdown after some time - kills it.
void TearDownChildProcess(Config* pconfig) {
    DWORD wfso_result;

    EnterCriticalSection(&g_tear_down_crit);
    if(g_pchild_proc_info) {
        // Post WM_CLOSE to all windows whose PID matches child process's.
        EnumWindows((WNDENUMPROC)TerminateAppEnum, (LPARAM)g_pchild_proc_info->dwProcessId);
        // Send ctrl + break event to ask app to close.
        GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, g_pchild_proc_info->dwProcessId);
        // Wait for process to exit.
        wfso_result = WaitForSingleObject(g_pchild_proc_info->hProcess,
                                          pconfig->process_wait_timeout_msec_);

        if (!wfso_result == WAIT_OBJECT_0) {
            if(wfso_result == WAIT_TIMEOUT) {
                fprintf(stderr, "\n->Timeout.\n");
            }
            fprintf(stderr, "Waiting for child process failed. Terminating child process.");
            if(!TerminateProcess(g_pchild_proc_info->hProcess, 1)) {
                ErrorExit(TEXT("Unable to terminate child process."));
            }
        }
        WaitForSingleObject(g_hchild_tracking_thread, INFINITE);
    }
    g_pchild_proc_info = NULL;
    LeaveCriticalSection(&g_tear_down_crit);
}