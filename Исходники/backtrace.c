static void yaz_invoke_gdb(void)
{
    int fd = yaz_panic_fd;
    pid_t pid;
    int fds[2];
    if (pipe(fds) == -1)
    {
        const char *cp = "backtrace: pipe failed\n";
        write(fd, cp, strlen(cp));
        return;
    }
    pid = fork();
    if (pid == (pid_t) (-1))
    {   /* error */
        const char *cp = "backtrace: fork failure\n";
        write(fd, cp, strlen(cp));
    }
    else if (pid == 0)
    {   /* child */
        char *arg[20];
        int arg_no = 0;
        char pidstr[40];
        const char *cp = "backtrace: could not exec gdb\n";

        close(fds[1]);
        close(0);
        dup(fds[0]);
        if (fd != 1)
        {
            close(1);
            dup(fd);
        }
        if (fd != 2)
        {
            close(2);
            dup(fd);
        }
        arg[arg_no++] = "/usr/bin/gdb";
        arg[arg_no++] = "-n";
        arg[arg_no++] = "-batch";
        arg[arg_no++] = "-ex";
        arg[arg_no++] = "info threads";
        arg[arg_no++] = "-ex";
        arg[arg_no++] = "thread apply all bt";
        arg[arg_no++] = static_progname;
        sprintf(pidstr, NMEM_INT_PRINTF, (nmem_int_t) getppid());
        arg[arg_no++] = pidstr;
        arg[arg_no] = 0;
        execv(arg[0], arg);
        write(2, cp, strlen(cp)); /* exec failure if we make it this far */
        _exit(1);
    }
    else
    {  /* parent */
        int sec = 0;

        close(fds[0]);
        write(fds[1], "quit\n", 5);
        while (1)
        {
            int status;
            pid_t s = waitpid(pid, &status, WNOHANG);
            if (s != 0)
                break;
            if (sec == 9)
                kill(pid, SIGTERM);
            if (sec == 10)
                kill(pid, SIGKILL);
            if (sec == 11)
                break;
            if (sec > 3)
                write(fds[1], "quit\n", 5);
            sleep(1);
            sec++;
        }
        close(fds[1]);
    }
}