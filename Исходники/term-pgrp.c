int main(int argc, char **argv)
{
    int pid, fds[2], pid1;
    char buf[200];

    err_setarg0(argv[0]);
    err_setlogopts(ERR_PID|ERR_MICRO);
    dump_pgrps();
    if (pipe(fds) != 0)
        err_syserr("failed to create pipe: ");
    pid = fork();

    if (pid == 0)
    {
        close(fds[0]);
        for (int i = 0; i < 3; i++)
        {
            printf("Prompt %d: ", i); fflush(0);
            if (scanf("%199s", buf) != 1)
            {
                int errnum = errno;
                err_remark("Child1:\n");
                dump_pgrps();
                errno = errnum;
                err_sysrem("scanf() failed: ");
                clearerr(stdin);
            }
            else
            {
                /* Write the null terminator too */
                ssize_t rbytes = strlen(buf) + 1;
                ssize_t wbytes = write(fds[1], buf, rbytes);
                if (wbytes != rbytes)
                    err_sysrem("short write (read %zu, write %zu)\n",
                               rbytes, wbytes);
            }
            sleep(3);
        }
    }
    else
    {
        pid1 = fork();

        if (pid1 == 0)
        {
            close(fds[1]);
            for (int i = 0; i < 3; i++)
            {
                if (read(fds[0], buf, sizeof(buf)) > 0)
                    printf("Input %d:  %s\n", i, buf);
                else
                {
                    int errnum = errno;
                    err_remark("Child2:\n");
                    dump_pgrps();
                    errno = errnum;
                    err_sysrem("read() failed: ");
                }
            }
        }
        else if (argc > 2)
        {
            err_remark("Kids are %d and %d\n", pid, pid1);
            sleep(5);
            err_remark("Parent exits\n");
        }
        else if (argc > 1 && argv != 0) // Avoid compilation warning for unused argv
        {
            err_remark("Kids are %d and %d\n", pid, pid1);
            int status;
            int corpse = wait(&status);
            err_remark("Parent gets PID %d status 0x%.4X\n", corpse, status);
        }
    }
    return 0;
}