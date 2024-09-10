void
exitshell_savedstatus(void)
{
    struct jmploc loc1, loc2;
    char *p;
    volatile int sig = 0;
    sigset_t sigs;

    if (!exiting) {
        if (in_dotrap && last_trapsig) {
            sig = last_trapsig;
            exiting_exitstatus = sig + 128;
        } else
            exiting_exitstatus = oexitstatus;
    }
    exitstatus = oexitstatus = exiting_exitstatus;
    if (setjmp(loc1.loc)) {
        goto l1;
    }
    if (setjmp(loc2.loc)) {
        goto l2;
    }
    handler = &loc1;
    if ((p = trap[0]) != NULL && *p != '\0') {
        trap[0] = NULL;
        evalstring(p, 0);
    }
l1:
    handler = &loc2;			/* probably unnecessary */
    flushall();
#if JOBS
    setjobctl(0);
#endif
l2:
    if (sig != 0 && sig != SIGSTOP && sig != SIGTSTP && sig != SIGTTIN &&
            sig != SIGTTOU) {
        signal(sig, SIG_DFL);
        sigemptyset(&sigs);
        sigaddset(&sigs, sig);
        sigprocmask(SIG_UNBLOCK, &sigs, NULL);
        kill(getpid(), sig);
        /* If the default action is to ignore, fall back to _exit(). */
    }
    _exit(exiting_exitstatus);
}