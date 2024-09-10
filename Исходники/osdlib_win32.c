void osd_process_kill(void)
{
    TerminateProcess(GetCurrentProcess(), -1);
}