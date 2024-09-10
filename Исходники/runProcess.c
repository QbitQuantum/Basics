ProcHandle
runProcess (char *const args[], char *workingDirectory, char **environment, 
	    int fdStdInput, int fdStdOutput, int fdStdError,
	    int set_inthandler, long inthandler, 
	    int set_quithandler, long quithandler)
{
    int pid;
    struct sigaction dfl;

    switch(pid = fork())
    {
    case -1:
	return -1;
	
    case 0:
    {
	pPrPr_disableITimers();
	
	if (workingDirectory) {
	    if (chdir (workingDirectory) < 0) {
                // See #1593.  The convention for the exit code when
                // exec() fails seems to be 127 (gleened from C's
                // system()), but there's no equivalent convention for
                // chdir(), so I'm picking 126 --SimonM.
                _exit(126);
	    }
	}
	
	/* Set the SIGINT/SIGQUIT signal handlers in the child, if requested 
	 */
        (void)sigemptyset(&dfl.sa_mask);
        dfl.sa_flags = 0;
	if (set_inthandler) {
	    dfl.sa_handler = (void *)inthandler;
	    (void)sigaction(SIGINT, &dfl, NULL);
	}
	if (set_quithandler) {
	    dfl.sa_handler = (void *)quithandler;
	    (void)sigaction(SIGQUIT,  &dfl, NULL);
	}

	dup2 (fdStdInput,  STDIN_FILENO);
	dup2 (fdStdOutput, STDOUT_FILENO);
	dup2 (fdStdError,  STDERR_FILENO);
	
	if (environment) {
	    execvpe(args[0], args, environment);
	} else {
	    execvp(args[0], args);
	}
    }
    _exit(127);
    }
    
    return pid;
}