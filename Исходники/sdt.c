int
main(int argc, char *argv[])
{
    SDT_STATE *ss = NULL;
    pid_t pid = 0;
    int nd = 0;
    int ch = 0;
    int di = 0;

    IS_NULL(ss = calloc(1, sizeof(SDT_STATE)));

    ss->rand = sdt_rand_init();
    (void)sdt_dns_init();

    ss->sess.o.id = (u_int16_t)sdt_arc4random(ss->rand);
    ss->backoff = 1;
    ss->maxbackoff = MAXBACKOFF;
    ss->sleep = SLEEP_TXT;
    ss->bufsz = 110;
    ss->delay = 1000000/2; /* 2/second */
    ss->faststart = 3;
    ss->maxpollfail = MAXPOLLFAIL;
    ss->type = ns_t_txt;
    ss->verbose_lines = 100;
    ss->protocol = PROTO_STATIC_FWD;
    ss->target_port = 22;

    ss->dname_next = &sdt_dns_dn_roundrobin;

    ss->fd_in = fileno(stdin);
    ss->fd_out = fileno(stdout);

    while ( (ch = getopt(argc, argv, "A:B:b:D:dF:hM:m:n:p:R:r:S:s:T:t:V:vx:")) != -1) {
        switch (ch) {
        case 'A':	/* alarm, delay buf */
            ss->delay = (u_int32_t)atoi(optarg);
            break;
        case 'B':   /* send buf size */
            ss->bufsz = (size_t)atoi(optarg);
            break;
        case 'b':   /* max backoff */
            ss->maxbackoff = (u_int16_t)atoi(optarg);
            break;
        case 'D': { /* Dynamic forward */
            char *hostname = NULL;

            IS_NULL(hostname = strdup(optarg));
            sdt_parse_forward(ss, hostname);
            free(hostname);
        }
        break;
        case 'd':   /* Debug DNS */
            sdt_dns_setopt(SDT_RES_DEBUG, 1);
            break;
        case 'F':   /* fast start */
            ss->faststart = (int32_t)atoi(optarg);
            break;
        case 'M':
            ss->maxpollfail = (int32_t)atoi(optarg);
            break;
        case 'm':
            ss->sleep = (u_int32_t)atoi(optarg);
            break;
        case 'n':   /* strategy for shuffling domain name list */
            if (strcasecmp(optarg, "roundrobin") == 0)
                ss->dname_next = &sdt_dns_dn_roundrobin;
            else if (strcasecmp(optarg, "random") == 0)
                ss->dname_next = &sdt_dns_dn_random;
            else
                usage(ss);
            break;
        case 'p':   /* Proxy mode */
            ss->proxy_port = (in_port_t)atoi(optarg);
            break;
        case 'R':   /* Retry lookup */
            sdt_dns_setopt(SDT_RES_RETRY, (u_int32_t)atoi(optarg));
            break;
        case 'r':
            if (sdt_dns_parsens(ss, optarg) < 0)
                errx(EXIT_FAILURE, "Invalid NS address");

            nsauto = 1;
            break;
        case 'S':   /* Resolver strategies */
            if (strcasecmp(optarg, "blast") == 0)
                sdt_dns_setopt(SDT_RES_BLAST, 0);
            else if (strcasecmp(optarg, "rotate") == 0)
                sdt_dns_setopt(SDT_RES_ROTATE, 0);
            else
                usage(ss);
            break;
        case 's':   /* forwarded session */
            ss->sess.o.fwd = (u_int8_t)atoi(optarg);
            break;
        case 'T':
            sdt_dns_setopt(SDT_RES_USEVC, (int32_t)atoi(optarg));
            break;
        case 't':   /* DNS message type */
            if (strcasecmp(optarg, "TXT") == 0)
                ss->type = ns_t_txt;
            else if (strcasecmp(optarg, "CNAME") == 0)
                ss->type = ns_t_cname;
            else if (strcasecmp(optarg, "NULL") == 0)
                ss->type = ns_t_null;
            else
                usage(ss);
            break;
        case 'V':
            ss->verbose_lines = atoi(optarg);
            break;
        case 'v':
            ss->verbose++;
            break;
        case 'x':   /* Transmit lookup timeout */
            sdt_dns_setopt(SDT_RES_RETRANS, (int32_t)atoi(optarg));
            break;

        case 'h':
        default:
            usage(ss);
        }
    }

    argc -= optind;
    argv += optind;

    if ( (argc == 0) || (argc >= MAXDNAMELIST))
        usage(ss);

    ss->dname_max = argc;
    IS_NULL(ss->dname = calloc(argc, sizeof(char *)));
    for ( di = 0; di < argc; di++) {
        if (strlen(argv[di]) > NS_MAXCDNAME - 1)
            usage(ss);
        IS_NULL(ss->dname[di] = strdup(argv[di]));
    }

    if (ss->proxy_port > 0)
        IS_ERR(ss->fd_out = ss->fd_in = sdt_proxy_open(ss));

    IS_ERR(nd = open("/dev/null", O_RDWR, 0));

    VERBOSE(1, "session id = %u, opt = %u, session = %d\n", ss->sess.o.id,
            ss->sess.o.opt, ss->sess.o.fwd);

    (void)signal(SIGPIPE, SIG_IGN);

    switch (pid = fork()) {
    case -1:
        err(EXIT_FAILURE, "fork");
    case 0:
        if (ss->proxy_port > 0)
            IS_ERR(dup2(fileno(stdout), nd));
        IS_ERR(dup2(fileno(stdin), nd));
        (void)signal(SIGUSR1,wakeup);
        sdt_loop_poll(ss);
        break;
    default:
        if (ss->proxy_port > 0)
            IS_ERR(dup2(fileno(stdin), nd));
        IS_ERR(dup2(fileno(stdout), nd));
        (void)signal(SIGHUP,wakeup);
        (void)signal(SIGTERM,wakeup);
        (void)signal(SIGALRM,wakeup);
        (void)signal(SIGCHLD,wakeup);
        ss->child = pid;
        sdt_loop_A(ss);

        if (woken == 1) {
            (void)kill(pid, SIGHUP);
            (void)wait(NULL);
        }

        break;
    }

    free(ss->dname);
    free(ss);
    IS_ERR(close(nd));

    exit(EXIT_SUCCESS);
}