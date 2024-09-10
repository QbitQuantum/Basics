extern "C" CDECL int
rust_run_program(const char* argv[],
                 void* envp,
                 const char* dir,
                 int in_fd, int out_fd, int err_fd) {
    int pid = fork();
    if (pid != 0) return pid;

    sigset_t sset;
    sigemptyset(&sset);
    sigprocmask(SIG_SETMASK, &sset, NULL);

    if (in_fd) dup2(in_fd, 0);
    if (out_fd) dup2(out_fd, 1);
    if (err_fd) dup2(err_fd, 2);
    /* Close all other fds. */
    for (int fd = getdtablesize() - 1; fd >= 3; fd--) close(fd);
    if (dir) { chdir(dir); }

#ifdef __APPLE__
    if (envp) {
        *_NSGetEnviron() = (char **)envp;
    }
    execvp(argv[0], (char * const *)argv);
#else
    if (!envp) { envp = environ; }
    execvpe(argv[0], (char * const *)argv, (char * const *)envp);
#endif

    exit(1);
}