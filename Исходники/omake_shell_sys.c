/*
 * Terminate the process.
 * Try to do this by sending the CTRL_C event.
 * If that fails, just terminate it.
 */
static int kill_process(Process *processp)
{
    /*
     * Set the killed flag.
     * For threads, this will generate an exception
     * then next time it calls check_thread.
     */
    processp->killed = 1;
    if(processp->is_thread)
        return 0;

    /* Get the process id */
    if(processp->wid == 0)
        return -1;

#if 0
    /* Resume it so it can handle the exception */
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, processp->wid);
    resume_process(processp);
#endif

    /* A lot of processes ignore the CTRL_C_EVENT, so just temrinate it */
    TerminateProcess(processp->handle, 1);
    return 0;
}