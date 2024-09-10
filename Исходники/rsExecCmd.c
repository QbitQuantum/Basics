int
execCmd (execCmd_t *execCmdInp, int stdOutFd, int stdErrFd)
{
    char cmdPath[LONG_NAME_LEN];
    char *av[LONG_NAME_LEN];
    int status;
    char *cmdDir;

    cmdDir = getenv("irodsServerCmdDir");
    if (cmdDir) {
        if (cmdDir[strlen(cmdDir)-1] == '/') {
            cmdDir[strlen(cmdDir)-1] = 0;
        }
    }
    else {
        cmdDir = CMD_DIR;
    }

    snprintf (cmdPath, LONG_NAME_LEN, "%s/%s", cmdDir, execCmdInp->cmd); 

    initCmdArg (av, execCmdInp->cmdArgv, cmdPath);

    closeAllL1desc (ThisComm);

#ifndef windows_platform
    /* set up the pipe as the stdin, stdout and stderr */
  
    close (0);
    close (1);
    close (2);

    dup2 (stdOutFd, 0);
    dup2 (stdOutFd, 1);
    dup2 (stdErrFd, 2);
    close (stdOutFd);
    close (stdErrFd);

#ifdef RUN_SERVER_AS_ROOT
    /* if we're running with root real uid, drop all root
       privilege and setuid() to the irods service user
       before running the request command */
    status = dropRootPrivilege();
    if (status < 0) {
        return (status);
    }
#endif

    status = execv (av[0], av);

#else /* Windows: Can Windows redirect the stdin, etc, to a pipe? */
	status = _spawnv(_P_NOWAIT, av[0], av);
#endif

    return (status);
}