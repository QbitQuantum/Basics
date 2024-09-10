static void doScriptExec(ARGV_const_t argv, ARGV_const_t prefixes,
                         FD_t scriptFd, FD_t out)
{
    int pipes[2];
    int flag;
    int fdno;
    int xx;
    int open_max;

    (void) signal(SIGPIPE, SIG_DFL);
    pipes[0] = pipes[1] = 0;
    /* make stdin inaccessible */
    xx = pipe(pipes);
    xx = close(pipes[1]);
    xx = dup2(pipes[0], STDIN_FILENO);
    xx = close(pipes[0]);

    /* XXX Force FD_CLOEXEC on all inherited fdno's. */
    open_max = sysconf(_SC_OPEN_MAX);
    if (open_max == -1) {
        open_max = 1024;
    }
    for (fdno = 3; fdno < open_max; fdno++) {
        flag = fcntl(fdno, F_GETFD);
        if (flag == -1 || (flag & FD_CLOEXEC))
            continue;
        xx = fcntl(fdno, F_SETFD, FD_CLOEXEC);
        /* XXX W2DO? debug msg for inheirited fdno w/o FD_CLOEXEC */
    }

    if (scriptFd != NULL) {
        int sfdno = Fileno(scriptFd);
        int ofdno = Fileno(out);
        if (sfdno != STDERR_FILENO)
            xx = dup2(sfdno, STDERR_FILENO);
        if (ofdno != STDOUT_FILENO)
            xx = dup2(ofdno, STDOUT_FILENO);
        /* make sure we don't close stdin/stderr/stdout by mistake! */
        if (ofdno > STDERR_FILENO && ofdno != sfdno)
            xx = Fclose (out);
        if (sfdno > STDERR_FILENO && ofdno != sfdno)
            xx = Fclose (scriptFd);
    }

    {   char *ipath = rpmExpand("%{_install_script_path}", NULL);
        const char *path = SCRIPT_PATH;

        if (ipath && ipath[5] != '%')
            path = ipath;

        xx = setenv("PATH", path, 1);
        free(ipath);
    }

    for (ARGV_const_t pf = prefixes; pf && *pf; pf++) {
        char *name = NULL;
        int num = (pf - prefixes);

        rasprintf(&name, "RPM_INSTALL_PREFIX%d", num);
        setenv(name, *pf, 1);
        free(name);

        /* scripts might still be using the old style prefix */
        if (num == 0) {
            setenv("RPM_INSTALL_PREFIX", *pf, 1);
        }
    }

    if (chdir("/") == 0) {
        /* XXX Don't mtrace into children. */
        unsetenv("MALLOC_CHECK_");

        if (xx == 0) {
            xx = execv(argv[0], argv);
        }
    }
    _exit(127); /* exit 127 for compatibility with bash(1) */
}