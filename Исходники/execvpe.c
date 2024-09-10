int execvpe(const char *path, char * const argv[], char * const envp[])
{
    return spawnvpe(P_OVERLAY, path, argv, envp);
}