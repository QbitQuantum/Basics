int main(int argc, char **argv)
{
    int pid;
    sigset_t mask;

    Signal(SIGCHLD, handler);
    initjobs(); /* Initialize the job list */

    while (1) {
	Sigemptyset(&mask);
	Sigaddset(&mask, SIGCHLD); 
	Sigprocmask(SIG_BLOCK, &mask, NULL); /* Block SIGCHLD */
    
	/* Child process */
	if ((pid = Fork()) == 0) {
	    Sigprocmask(SIG_UNBLOCK, &mask, NULL); /* Unblock SIGCHLD */
	    Execve("/bin/ls", argv, NULL);
	}

	/* Parent process */
	addjob(pid);  /* Add the child to the job list */
	Sigprocmask(SIG_UNBLOCK, &mask, NULL);  /* Unblock SIGCHLD */
    }
    exit(0);
}