int
main(int argc, char *argv[])
{
#ifdef WINDOWS
    HANDLE hchild;
    int child;
#else
    pid_t child;
#endif
    int rc;
    int arg_offs = 1;
    const char *outfile = NULL;
    const char *pidfile = NULL;

    if (argc < 2) {
        return usage(argv[0]);
    }
    while (argv[arg_offs][0] == '-') {
        if (strcmp(argv[arg_offs], "-env") == 0) {
            if (argc <= arg_offs + 2)
                return usage(argv[0]);
#if VERBOSE
            fprintf(stderr, "setting env var \"%s\" to \"%s\"\n", argv[arg_offs + 1],
                    argv[arg_offs + 2]);
#endif
#ifdef WINDOWS
            rc = SetEnvironmentVariable(argv[arg_offs + 1], argv[arg_offs + 2]);
#else
            rc = setenv(argv[arg_offs + 1], argv[arg_offs + 2], 1 /*overwrite*/);
#endif
            if (rc != 0 ||
                strcmp(mygetenv(argv[arg_offs + 1]), argv[arg_offs + 2]) != 0) {
                fprintf(stderr, "error in setenv of \"%s\" to \"%s\"\n",
                        argv[arg_offs + 1], argv[arg_offs + 2]);
                fprintf(stderr, "setenv returned %d\n", rc);
                fprintf(stderr, "env var \"%s\" is now \"%s\"\n", argv[arg_offs + 1],
                        mygetenv(argv[arg_offs + 1]));
                exit(1);
            }
            arg_offs += 3;
        } else if (strcmp(argv[arg_offs], "-out") == 0) {
            if (argc <= arg_offs + 1)
                return usage(argv[0]);
            outfile = argv[arg_offs + 1];
            arg_offs += 2;
        } else if (strcmp(argv[arg_offs], "-pid") == 0) {
            if (argc <= arg_offs + 1)
                return usage(argv[0]);
            pidfile = argv[arg_offs + 1];
            arg_offs += 2;
        } else {
            return usage(argv[0]);
        }
        if (argc - arg_offs < 1)
            return usage(argv[0]);
    }

#ifdef UNIX
    child = fork();
    if (child < 0) {
        perror("ERROR on fork");
    } else if (child == 0) {
        /* redirect std{out,err} */
        redirect_stdouterr(outfile);
        execv(argv[arg_offs], argv + arg_offs /*include app*/);
        fprintf(stderr, "execv of %s FAILED", argv[arg_offs]);
        exit(1);
    }
    /* else, parent, and we continue below */
    if (pidfile == NULL)
        printf("%d\n", child);
#else
    /* redirect std{out,err} */
    redirect_stdouterr(outfile);
    /* Do we want _P_DETACH instead of _P_NOWAIT?  _P_DETACH doesn't return the
     * child handle though.
     */
    hchild = (HANDLE)_spawnv(_P_NOWAIT, argv[arg_offs], argv + arg_offs /*include app*/);
    if (hchild == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "_spawnv of %s FAILED", argv[arg_offs]);
        exit(1);
    }
    child = process_id_from_handle(hchild);
#endif
    if (pidfile != NULL) {
        FILE *f = fopen(pidfile, "w");
        if (f == NULL) {
            perror("open pidfile failed");
            exit(1);
        }
        fprintf(f, "%d\n", child);
        fclose(f);
    }
    return 0;
}