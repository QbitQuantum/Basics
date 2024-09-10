/* main -- dnsproxy main function
 */
int
main(int argc, char *argv[])
{
    int ch;
    struct passwd *pw = NULL;
    struct sockaddr_in addr;
    struct event evq, eva;
    const char *config = "/etc/dnsproxy.conf";
    int daemonize = 0;

    /* Process commandline arguments */
    while ((ch = getopt(argc, argv, "c:dhV")) != -1) {
        switch (ch) {
        case 'c':
            config = optarg;
            break;
        case 'd':
            daemonize = 1;
            break;
        case 'V':
            fprintf(stderr, PACKAGE_STRING "\n");
            exit(0);
        /* FALLTHROUGH */
        case 'h':
        default:
            fprintf(stderr,
            "usage: dnsproxy [-c file] [-dhV]\n"        \
            "\t-c file  Read configuration from file\n" \
            "\t-d       Detach and run as a daemon\n"   \
            "\t-h       This help text\n"           \
            "\t-V       Show version information\n");
            exit(1);
        }
    }

    /* Parse configuration and check required parameters */
    if (!parse(config))
        fatal("unable to parse configuration");

    if (!authoritative || !recursive)
        fatal("No authoritative or recursive server defined");

    if (!listenat)
        listenat = strdup("0.0.0.0");

    /* Create and bind query socket */
    if ((sock_query = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        fatal("unable to create socket: %s", strerror(errno));

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_addr.s_addr = inet_addr(listenat);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    if (bind(sock_query, (struct sockaddr *)&addr, sizeof(addr)) != 0)
        fatal("unable to bind socket: %s", strerror(errno));

    /* Create and bind answer socket */
    if ((sock_answer = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        fatal("unable to create socket: %s", strerror(errno));

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;

    if (bind(sock_answer, (struct sockaddr *)&addr, sizeof(addr)) != 0)
        fatal("unable to bind socket: %s", strerror(errno));

    /* Fill sockaddr_in structs for both servers */
    memset(&authoritative_addr, 0, sizeof(struct sockaddr_in));
    authoritative_addr.sin_addr.s_addr = inet_addr(authoritative);
    authoritative_addr.sin_port = htons(authoritative_port);
    authoritative_addr.sin_family = AF_INET;

    memset(&recursive_addr, 0, sizeof(struct sockaddr_in));
    recursive_addr.sin_addr.s_addr = inet_addr(recursive);
    recursive_addr.sin_port = htons(recursive_port);
    recursive_addr.sin_family = AF_INET;

    /* Daemonize if requested and switch to syslog */
    if (daemonize) {
        if (daemon(0, 0) == -1)
            fatal("unable to daemonize");
        log_syslog("dnsproxy");
    }

    /* Find less privileged user */
    if (user) {
        pw = getpwnam(user);
        if (!pw)
            fatal("unable to find user %s", user);
    }

    /* Do a chroot if requested */
    if (chrootdir) {
        if (chdir(chrootdir) || chroot(chrootdir))
            fatal("unable to chroot to %s", chrootdir);
        chdir("/");
    }

    /* Drop privileges */
    if (user) {
        if (setgroups(1, &pw->pw_gid) < 0)
            fatal("setgroups: %s", strerror(errno));
#if defined(HAVE_SETRESGID)
        if (setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) < 0)
            fatal("setresgid: %s", strerror(errno));
#elif defined(HAVE_SETREGID)
        if (setregid(pw->pw_gid, pw->pw_gid) < 0)
            fatal("setregid: %s", strerror(errno));
#else
        if (setegid(pw->pw_gid) < 0)
            fatal("setegid: %s", strerror(errno));
        if (setgid(pw->pw_gid) < 0)
            fatal("setgid: %s", strerror(errno));
#endif
#if defined(HAVE_SETRESUID)
        if (setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid) < 0)
            fatal("setresuid: %s", strerror(errno));
#elif defined(HAVE_SETREUID)
        if (setreuid(pw->pw_uid, pw->pw_uid) < 0)
            fatal("setreuid: %s", strerror(errno));
#else
        if (seteuid(pw->pw_uid) < 0)
            fatal("seteuid: %s", strerror(errno));
        if (setuid(pw->pw_uid) < 0)
            fatal("setuid: %s", strerror(errno));
#endif
    }

    /* Init event handling */
    event_init();

    event_set(&evq, sock_query, EV_READ, do_query, &evq);
    event_add(&evq, NULL);

    event_set(&eva, sock_answer, EV_READ, do_answer, &eva);
    event_add(&eva, NULL);

    /* Zero counters and start statistics timer */
    statistics_start();

    /* Take care of signals */
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        fatal("unable to mask signal SIGINT: %s", strerror(errno));

    if (signal(SIGTERM, signal_handler) == SIG_ERR)
        fatal("unable to mask signal SIGTERM: %s", strerror(errno));

    if (signal(SIGHUP, SIG_IGN) == SIG_ERR)
        fatal("unable to mask signal SIGHUP: %s", strerror(errno));

    event_sigcb = signal_event;

    /* Start libevent main loop */
    event_dispatch();

    return 0;

}