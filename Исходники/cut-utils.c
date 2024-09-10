gboolean
cut_win32_kill_process (GPid pid, guint exit_code)
{
    return TerminateProcess(pid, exit_code) ? TRUE : FALSE;
}