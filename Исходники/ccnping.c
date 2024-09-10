int main(int argc, char *argv[])
{
    const char *progname = argv[0];
    struct ccn_ping_client client = {.identifier = 0, .interval = 1, .sent = 0,
        .received = 0, .total = -1, .number = -1, .print_timestamp = 0, .allow_caching = 0};
    struct ccn_closure in_content = {.p = &incoming_content};
    struct hashtb_param param = {0};
    int res;

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handle_interrupt;
    sigaction(SIGINT, &sa, &osa);

    memset(&sta, 0, sizeof(sta));
    gettimeofday(&sta.start, 0);
    sta.min = INT_MAX;

    while ((res = getopt(argc, argv, "htai:c:n:p:")) != -1) {
        switch (res) {
            case 'c':
                client.total = atol(optarg);
                if (client.total <= 0)
                    usage(progname);
                break;
            case 'i':
                client.interval = atof(optarg);
                if (client.interval < PING_MIN_INTERVAL)
                    usage(progname);
                break;
            case 'n':
                client.number = atol(optarg);
                if (client.number < 0)
                    usage(progname);
                break;
            case 'p':
                client.identifier = optarg;
                if (!is_valid_identifier(client.identifier))
                    usage(progname);
                break;
            case 't':
                client.print_timestamp = 1;
                break;
            case 'a':
                client.allow_caching = 1;
                break;
            case 'h':
            default:
                usage(progname);
                break;
        }
    }

    if (client.number < 0)
        srandom(time(NULL)  * getpid());

    argc -= optind;
    argv += optind;

    if (argv[0] == NULL)
        usage(progname);

    sta.prefix = argv[0];

    client.original_prefix = argv[0];
    client.prefix = ccn_charbuf_create();
    res = ccn_name_from_uri(client.prefix, argv[0]);
    if (res < 0) {
        fprintf(stderr, "%s: bad ccn URI: %s\n", progname, argv[0]);
        exit(1);
    }
    if (argv[1] != NULL)
        fprintf(stderr, "%s warning: extra arguments ignored\n", progname);

    //append "/ping" to the given name prefix
    res = ccn_name_append_str(client.prefix, PING_COMPONENT);
    if (res < 0) {
        fprintf(stderr, "%s: error constructing ccn URI: %s/%s\n", progname, argv[0], PING_COMPONENT);
        exit(1);
    }

    //append identifier if not empty
    if (client.identifier) {
        res = ccn_name_append_str(client.prefix, client.identifier);
        if (res < 0) {
            fprintf(stderr, "%s: error constructing ccn URI: %s/%s/%s\n",
                    progname, argv[0], PING_COMPONENT, client.identifier);
            exit(1);
        }
    }

    /* Connect to ccnd */
    client.h = ccn_create();
    if (ccn_connect(client.h, NULL) == -1) {
        perror("Could not connect to ccnd");
        exit(1);
    }

    client.closure = &in_content;
    in_content.data = &client;

    client.ccn_ping_table = hashtb_create(sizeof(struct ccn_ping_entry), &param);

    client.sched = ccn_schedule_create(&client, &ccn_ping_ticker);
    client.event = ccn_schedule_event(client.sched, 0, &do_ping, NULL, 0);

    if (client.print_timestamp) {
        printf("%ld.%06u: ", (long)sta.start.tv_sec, (unsigned)sta.start.tv_usec);
    }
    printf("CCNPING %s\n", client.original_prefix);

    res = 0;

    while (res >= 0 && (client.total <= 0 || client.sent < client.total || hashtb_n(client.ccn_ping_table) > 0))
    {
        if (client.total <= 0 || client.sent < client.total)
            ccn_schedule_run(client.sched);
        res = ccn_run(client.h, 10);
    }

    ccn_schedule_destroy(&client.sched);
    ccn_destroy(&client.h);
    ccn_charbuf_destroy(&client.prefix);

    print_statistics();

    return 0;
}