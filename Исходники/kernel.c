/***********************************************************************
 *           KERNEL thread finalisation routine
 */
static void thread_detach(void)
{
    /* free the 16-bit stack */
    WOWGlobalFree16( kernel_get_thread_data()->stack_sel );
    NtCurrentTeb()->WOW32Reserved = 0;
    if (NtCurrentTeb()->Tib.SubSystemTib) TASK_ExitTask();
}