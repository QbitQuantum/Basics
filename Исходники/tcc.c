static int execvp_win32(const char *prog, char **argv)
{
    int ret = spawnvp(P_NOWAIT, prog, (const char *const*)argv);
    if (-1 == ret)
        return ret;
    cwait(&ret, ret, WAIT_CHILD);
    exit(ret);
}