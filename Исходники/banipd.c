int main(int argc, char **argv)
{
    gid_t gid;
    addr_t addr;
    struct sigaction sa;
    int c, dFlag, vFlag;
    unsigned long max_message_size;
    const char *queuename, *tablename;

    ctxt = NULL;
    gid = (gid_t) -1;
    vFlag = dFlag = 0;
    tablename = queuename = NULL;
    if (NULL == (queue = queue_init())) {
        errx("queue_init failed"); // TODO: better
    }
    atexit(cleanup);
    sa.sa_handler = &on_signal;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);
    if (NULL == (engine = get_default_engine())) {
        errx("no engine available for your system");
    }
    while (-1 != (c = getopt_long(argc, argv, optstr, long_options, NULL))) {
        switch (c) {
            case 'b':
            {
                unsigned long val;

                if (parse_ulong(optarg, &val)) {
                    queue_set_attribute(queue, QUEUE_ATTR_MAX_MESSAGE_SIZE, val); // TODO: check returned value
                }
                break;
            }
            case 'd':
                dFlag = 1;
                break;
            case 'e':
            {
                if (NULL == (engine = get_engine_by_name(optarg))) {
                    errx("unknown engine '%s'", optarg);
                }
                break;
            }
            case 'g':
            {
                struct group *grp;

                if (NULL == (grp = getgrnam(optarg))) {
                    errc("getgrnam failed");
                }
                gid = grp->gr_gid;
                break;
            }
            case 'l':
            {
                logfilename = optarg;
                if (NULL == (err_file = fopen(logfilename, "a"))) {
                    err_file = NULL;
                    warnc("fopen '%s' failed, falling back to stderr", logfilename);
                }
                break;
            }
            case 'p':
                pidfilename = optarg;
                break;
            case 'q':
                queuename = optarg;
                break;
            case 's':
            {
                unsigned long val;

                if (parse_ulong(optarg, &val)) {
                    queue_set_attribute(queue, QUEUE_ATTR_MAX_MESSAGE_IN_QUEUE, val); // TODO: check returned value
                }
                break;
            }
            case 't':
                tablename = optarg;
                break;
            case 'v':
                vFlag++;
                break;
            case 'h':
            default:
                usage();
        }
    }
    argc -= optind;
    argv += optind;

    if (0 != argc || NULL == queuename || NULL == tablename) {
        usage();
    }

    if (dFlag) {
        if (0 != daemon(0, !vFlag)) {
            errc("daemon failed");
        }
    }
    if (NULL != pidfilename) {
        FILE *fp;

        if (NULL == (fp = fopen(pidfilename, "w"))) {
            warnc("can't create pid file '%s'", pidfilename);
        } else {
            fprintf(fp, "%ld\n", (long) getpid());
            fclose(fp);
        }
    }

    if (((gid_t) -1) != gid) {
        if (0 != setgid(gid)) {
            errc("setgid failed");
        }
        if (0 != setgroups(1, &gid)) {
            errc("setgroups failed");
        }
    }
    CAP_RIGHTS_LIMIT(STDOUT_FILENO, CAP_WRITE);
    CAP_RIGHTS_LIMIT(STDERR_FILENO, CAP_WRITE);
    if (NULL != err_file/* && fileno(err_file) > 2*/) {
        CAP_RIGHTS_LIMIT(fileno(err_file), CAP_WRITE);
    }
    if (QUEUE_ERR_OK != queue_open(queue, queuename, QUEUE_FL_OWNER)) {
        errx("queue_open failed"); // TODO: better
    }
    if (QUEUE_ERR_OK != queue_get_attribute(queue, QUEUE_ATTR_MAX_MESSAGE_SIZE, &max_message_size)) {
        errx("queue_get_attribute failed"); // TODO: better
    }
    if (NULL == (buffer = calloc(++max_message_size, sizeof(*buffer)))) {
        errx("calloc failed");
    }
    if (NULL != engine->open) {
        ctxt = engine->open(tablename);
    }
    if (0 == getuid() && engine->drop_privileges) {
        struct passwd *pwd;

        if (NULL == (pwd = getpwnam("nobody"))) {
            if (NULL == (pwd = getpwnam("daemon"))) {
                errx("no nobody or daemon user accounts found on this system");
            }
        }
        if (0 != setuid(pwd->pw_uid)) {
            errc("setuid failed");
        }
    }
    CAP_ENTER();
    while (1) {
        ssize_t read;

        if (-1 == (read = queue_receive(queue, buffer, max_message_size))) {
            errc("queue_receive failed"); // TODO: better
        } else {
            if (!parse_addr(buffer, &addr)) {
                errx("parsing of '%s' failed", buffer); // TODO: better
            } else {
                engine->handle(ctxt, tablename, addr);
            }
        }
    }
    /* not reached */

    return BANIPD_EXIT_SUCCESS;
}