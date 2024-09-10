/**
 * Check whether a valid handle has been returned. If not, then terminate.
 **/
void checkHandle(
    void *handle,
    char *info )
{
     if (!handle) {
        fprintf(stderr, "Error in %s: Creation failed: invalid handle\n", info);
        /* Generate Ctrl-C event to terminate process */
        GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);

        /* Wait in infinite loop as process will be terminated,
         * This is needed on windows as calling exit() or ExitProcess()
         * will fail to cleanup resources properly.
         */
        for (;;) {
            Sleep(300000); /* 5 minutes */
        }
     }
}