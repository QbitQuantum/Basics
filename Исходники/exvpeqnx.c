_WCRTLINK int (execvpe)(
    const char *path,           /* path name of path to be executed */
    const char *const argv[],   /* array of pointers to arguments   */
    const char *const envp[] )  /* array of pointers to environment strings */
{
    return( spawnvpe( P_OVERLAY, path, argv, envp ) );
}