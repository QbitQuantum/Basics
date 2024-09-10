int main(int argc, char **argv) {
    int i, n;
    char **origenv;
    char **newenv;
    char *cwd;
    FILE *log = fopen(abs_builddir "/commandhelper.log", "w");

    if (!log)
        goto error;

    for (i = 1 ; i < argc ; i++) {
        fprintf(log, "ARG:%s\n", argv[i]);
    }

    origenv = environ;
    n = 0;
    while (*origenv != NULL) {
        n++;
        origenv++;
    }

    if (VIR_ALLOC_N(newenv, n) < 0) {
        exit(EXIT_FAILURE);
    }

    origenv = environ;
    n = i = 0;
    while (*origenv != NULL) {
        newenv[i++] = *origenv;
        n++;
        origenv++;
    }
    qsort(newenv, n, sizeof(newenv[0]), envsort);

    for (i = 0 ; i < n ; i++) {
        /* Ignore the variables used to instruct the loader into
         * behaving differently, as they could throw the tests off. */
        if (!STRPREFIX(newenv[i], "LD_"))
            fprintf(log, "ENV:%s\n", newenv[i]);
    }

    for (i = 0 ; i < sysconf(_SC_OPEN_MAX) ; i++) {
        int f;
        int closed;
        if (i == fileno(log))
            continue;
        closed = fcntl(i, F_GETFD, &f) == -1 &&
            errno == EBADF;
        if (!closed)
            fprintf(log, "FD:%d\n", i);
    }

    fprintf(log, "DAEMON:%s\n", getpgrp() == getsid(0) ? "yes" : "no");
    if (!(cwd = getcwd(NULL, 0)))
        return EXIT_FAILURE;
    if (strlen(cwd) > strlen(".../commanddata") &&
        STREQ(cwd + strlen(cwd) - strlen("/commanddata"), "/commanddata"))
        strcpy(cwd, ".../commanddata");
    fprintf(log, "CWD:%s\n", cwd);
    VIR_FREE(cwd);

    VIR_FORCE_FCLOSE(log);

    char buf[1024];
    ssize_t got;

    fprintf(stdout, "BEGIN STDOUT\n");
    fflush(stdout);
    fprintf(stderr, "BEGIN STDERR\n");
    fflush(stderr);

    for (;;) {
        got = read(STDIN_FILENO, buf, sizeof(buf));
        if (got < 0)
            goto error;
        if (got == 0)
            break;
        if (safewrite(STDOUT_FILENO, buf, got) != got)
            goto error;
        if (safewrite(STDERR_FILENO, buf, got) != got)
            goto error;
    }

    fprintf(stdout, "END STDOUT\n");
    fflush(stdout);
    fprintf(stderr, "END STDERR\n");
    fflush(stderr);

    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}