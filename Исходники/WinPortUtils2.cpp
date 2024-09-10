// ---- C.spawn ---- 
int VMPI_spawn(int *pid, const char *path, char *const argv[], char *const envp[])
{
    /* note:
       see http://msdn.microsoft.com/en-us/library/zb9ehy71.aspx
       _spawnvpe() return the pid, not the status
     */
    //return posix_spawn( pid, path, NULL, NULL, argv, envp );
    (void)pid;
    int mode = _P_NOWAIT;
    return (int) _spawnvpe( mode, path, argv, envp );
}