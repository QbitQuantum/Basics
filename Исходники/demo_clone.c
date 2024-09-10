int
main(int argc, char *argv[])
{
    const int STACK_SIZE = 65536;       /* Stack size for cloned child */
    char *stack;                        /* Start of stack buffer area */
    char *stackTop;                     /* End of stack buffer area */
    int flags;                          /* Flags for cloning child */
    ChildParams cp;                     /* Passed to child function */
    const mode_t START_UMASK = S_IWOTH; /* Initial umask setting */
    struct sigaction sa;
    char *p;
    int status;
    ssize_t s;
    pid_t pid;

    printf("Parent: PID=%ld PPID=%ld\n", (long) getpid(), (long) getppid());

    /* Set up an argument structure to be passed to cloned child, and
       set some process attributes that will be modified by child */

    cp.exitStatus = 22;                 /* Child will exit with this status */

    umask(START_UMASK);                 /* Initialize umask to some value */
    cp.umask = S_IWGRP;                 /* Child sets umask to this value */

    cp.fd = open("/dev/null", O_RDWR);  /* Child will close this fd */
    if (cp.fd == -1)
        errExit("open");

    cp.signal = SIGTERM;                /* Child will change disposition */
    if (signal(cp.signal, SIG_IGN) == SIG_ERR)
        errExit("signal");

    /* Initialize clone flags using command-line argument (if supplied) */

    flags = 0;
    if (argc > 1) {
        for (p = argv[1]; *p != '\0'; p++) {
            if      (*p == 'd') flags |= CLONE_FILES;
            else if (*p == 'f') flags |= CLONE_FS;
            else if (*p == 's') flags |= CLONE_SIGHAND;
            else if (*p == 'v') flags |= CLONE_VM;
            else usageError(argv[0]);
        }
    }

    /* Allocate stack for child */

    stack = malloc(STACK_SIZE);
    if (stack == NULL)
        errExit("malloc");
    stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

    /* Establish handler to catch child termination signal */

    if (CHILD_SIG != 0) {
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = grimReaper;
        if (sigaction(CHILD_SIG, &sa, NULL) == -1)
            errExit("sigaction");
    }

    /* Create child; child commences execution in childFunc() */

    if (clone(childFunc, stackTop, flags | CHILD_SIG, &cp) == -1)
        errExit("clone");

    /* Parent falls through to here. Wait for child; __WCLONE option is
       required for child notifying with signal other than SIGCHLD. */

    pid = waitpid(-1, &status, (CHILD_SIG != SIGCHLD) ? __WCLONE : 0);
    if (pid == -1)
        errExit("waitpid");

    printf("    Child PID=%ld\n", (long) pid);
    printWaitStatus("    Status: ", status);

    /* Check whether changes made by cloned child have affected parent */

    printf("Parent - checking process attributes:\n");
    if (umask(0) != START_UMASK)
        printf("    umask has changed\n");
    else
        printf("    umask has not changed\n");

    s = write(cp.fd, "Hello world\n", 12);
    if (s == -1 && errno == EBADF)
        printf("    file descriptor %d has been closed\n", cp.fd);
    else if (s == -1)
        printf("    write() on file descriptor %d failed (%s)\n",
                cp.fd, strerror(errno));
    else
        printf("    write() on file descriptor %d succeeded\n", cp.fd);

    if (sigaction(cp.signal, NULL, &sa) == -1)
        errExit("sigaction");
    if (sa.sa_handler != SIG_IGN)
        printf("    signal disposition has changed\n");
    else
        printf("    signal disposition has not changed\n");

    exit(EXIT_SUCCESS);
}