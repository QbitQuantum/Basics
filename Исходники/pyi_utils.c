/* Start frozen application in a subprocess. The frozen application runs
 * in a subprocess.
 */
int pyi_utils_create_child(const char *thisfile, const int argc, char *const argv[])
{
    pid_t pid = 0;
    int rc = 0;
    int i;

    argv_pyi = (char**)calloc(argc+1,sizeof(char*));
    argc_pyi = 0;

    for (i = 0; i < argc; i++)
    {
#if defined(__APPLE__) && defined(WINDOWED)
      // if we are on a Mac, it passes a strange -psnxxx argument.  Filter it out.
      if (strstr(argv[i],"-psn") == argv[i])  
        {
           // skip
        }
      else
#endif
        {
           argv_pyi[argc_pyi++] = strdup(argv[i]);
        }
    }

#if defined(__APPLE__) && defined(WINDOWED)
    process_apple_events();
#endif


    pid = fork();

    /* Child code. */
    if (pid == 0)
        /* Replace process by starting a new application. */
        execvp(thisfile, argv_pyi);
    /* Parent code. */
    else
    {
        child_pid = pid;

        /* Redirect termination signals received by parent to child process. */
        signal(SIGINT, &_signal_handler);
        signal(SIGKILL, &_signal_handler);
        signal(SIGTERM, &_signal_handler);
    }

    wait(&rc);

    /* Parent code. */
    if(child_pid != 0 )
    {
        /* When child process exited, reset signal handlers to default values. */
        signal(SIGINT, SIG_DFL);
        signal(SIGKILL, SIG_DFL);
        signal(SIGTERM, SIG_DFL);

        for (i = 0; i < argc_pyi; i++) free(argv_pyi[i]);
        free(argv_pyi);
    }
    if (WIFEXITED(rc))
        return WEXITSTATUS(rc);
    /* Process ended abnormally */
    if (WIFSIGNALED(rc))
        /* Mimick the signal the child received */
        raise(WTERMSIG(rc));
    return 1;
}