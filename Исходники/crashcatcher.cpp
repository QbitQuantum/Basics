static void crash_catcher(int signum, siginfo_t *siginfo, void *context)
{
    //ucontext_t *ucontext = (ucontext_t*)context;
    pid_t dbg_pid;
    int fd[2];

    /* Make sure the effective uid is the real uid */
    if(getuid() != geteuid())
    {
        raise(signum);
        return;
    }

    safe_write(STDERR_FILENO, fatal_err, sizeof(fatal_err)-1);
    if(pipe(fd) == -1)
    {
        safe_write(STDERR_FILENO, pipe_err, sizeof(pipe_err)-1);
        raise(signum);
        return;
    }

    crash_info.signum = signum;
    crash_info.pid = getpid();
    crash_info.has_siginfo = !!siginfo;
    if(siginfo)
        crash_info.siginfo = *siginfo;
    if(cc_user_info)
        cc_user_info(crash_info.buf, crash_info.buf+sizeof(crash_info.buf));

    /* Fork off to start a crash handler */
    switch((dbg_pid=fork()))
    {
    /* Error */
    case -1:
        safe_write(STDERR_FILENO, fork_err, sizeof(fork_err)-1);
        raise(signum);
        return;

    case 0:
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);

        execl(argv0, argv0, crash_switch, NULL);

        safe_write(STDERR_FILENO, exec_err, sizeof(exec_err)-1);
        _exit(1);

    default:
#ifdef __linux__
        prctl(PR_SET_PTRACER, dbg_pid, 0, 0, 0);
#endif
        safe_write(fd[1], &crash_info, sizeof(crash_info));
        close(fd[0]);
        close(fd[1]);

        /* Wait; we'll be killed when gdb is done */
        do {
            int status;
            if(waitpid(dbg_pid, &status, 0) == dbg_pid &&
                    (WIFEXITED(status) || WIFSIGNALED(status)))
            {
                /* The debug process died before it could kill us */
                raise(signum);
                break;
            }
        } while(1);
    }
}