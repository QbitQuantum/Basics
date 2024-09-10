int
main(int argc, char *argv[])
{
    const struct cmd *c;

    fcntl(3, F_CLOSEM);
    openlog("timedc", 0, LOG_AUTH);

    /*
     * security dictates!
     */
    if (priv_resources() < 0)
        errx(EXIT_FAILURE, "Could not get privileged resources");
    if (drop_privileges() < 0)
        errx(EXIT_FAILURE, "Could not drop privileges");

    if (--argc > 0) {
        c = getcmd(*++argv);
        if (c == (struct cmd *)-1) {
            printf("?Ambiguous command\n");
            exit(EXIT_FAILURE);
        }
        if (c == 0) {
            printf("?Invalid command\n");
            exit(EXIT_FAILURE);
        }
        (*c->c_handler)(argc, argv);
        exit(EXIT_SUCCESS);
    }

    fromatty = isatty(fileno(stdin));
    if (setjmp(toplevel))
        putchar('\n');
    (void) signal(SIGINT, intr);
    for (;;) {
        if (fromatty) {
            printf("timedc> ");
            (void) fflush(stdout);
        }
        if (fgets(cmdline, sizeof(cmdline), stdin) == NULL)
            quit(0, NULL);
        if (cmdline[0] == 0)
            break;
        if (makeargv()) {
            printf("?Too many arguments\n");
            continue;
        }
        if (margv[0] == 0)
            continue;
        c = getcmd(margv[0]);
        if (c == (struct cmd *)-1) {
            printf("?Ambiguous command\n");
            continue;
        }
        if (c == 0) {
            printf("?Invalid command\n");
            continue;
        }
        (*c->c_handler)(margc, margv);
    }
    return 0;
}