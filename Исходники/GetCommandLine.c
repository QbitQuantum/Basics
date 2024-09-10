/*
 * Previously called zzledt... Called by Fortran...
 * Now renamed to EventLoopPrompt
 * @TODO remove unused arg buf_size, menusflag, modex & dummy1
 */
void C2F(eventloopprompt) (char *buffer, int *buf_size, int *len_line, int *eof)
{

    if (getScilabMode() == SCILAB_API)
    {
        return;
    }

    if (!initialJavaHooks && getScilabMode() != SCILAB_NWNI)
    {
        initialJavaHooks = TRUE;
        // Execute the initial hooks registered in Scilab.java
        ExecuteInitialHooks();
    }

    /* if not an interactive terminal */
#ifdef _MSC_VER
    /* if file descriptor returned is -2 stdin is not associated with an input stream */
    /* example : echo plot3d | scilex -nw -e */
    if (!isatty(fileno(stdin)) && (fileno(stdin) != -2) && getScilabMode() != SCILAB_STD)
#else
    if (!isatty(fileno(stdin)) && getScilabMode() != SCILAB_STD)
#endif
    {
        /* remove newline character if there */
        if (__CommandLine != NULL)
        {
            /* read a line into the buffer, but not too
             * big */
            *eof = (fgets(__CommandLine, *buf_size, stdin) == NULL);
            *len_line = (int)strlen(__CommandLine);
            /* remove newline character if there */
            if (__CommandLine[*len_line - 1] == '\n')
            {
                (*len_line)--;
            }
            return;
        }
    }

    if (!initialized)
    {
        initAll();
    }

    __LockSignal(pReadyForLaunch);

    if (__CommandLine)
    {
        FREE(__CommandLine);
        __CommandLine = NULL;
    }
    __CommandLine = strdup("");

    if (ismenu() == 0)
    {
        if (!WatchGetCmdLineThreadAlive)
        {
            if (WatchGetCmdLineThread)
            {
                __WaitThreadDie(WatchGetCmdLineThread);
            }
            if (getScilabMode() != SCILAB_NWNI)
            {

                char *cwd = NULL;

                int err = 0;

                UpdateBrowseVar(TRUE);
                cwd = scigetcwd(&err);
                if (cwd)
                {
                    FileBrowserChDir(cwd);
                    FREE(cwd);
                }
            }
            __CreateThread(&WatchGetCmdLineThread, &watchGetCommandLine);
            WatchGetCmdLineThreadAlive = TRUE;
        }
        if (!WatchStoreCmdThreadAlive)
        {
            if (WatchStoreCmdThread)
            {
                __WaitThreadDie(WatchStoreCmdThread);
            }
            __CreateThread(&WatchStoreCmdThread, &watchStoreCommand);
            WatchStoreCmdThreadAlive = TRUE;
        }

        __Wait(&TimeToWork, pReadyForLaunch);
    }
    __UnLockSignal(pReadyForLaunch);

    /*
    ** WARNING : Old crappy f.... code
    ** do not change reference to buffer
    ** or fortran will be lost !!!!
    */
    if (__CommandLine)
    {
        strcpy(buffer, __CommandLine);
    }
    else
    {
        strcpy(buffer, "");
    }
    *len_line = (int)strlen(buffer);

    *eof = FALSE;
}