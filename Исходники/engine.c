/**
 * Set up engine.
 *
 */
static ods_status
engine_setup(engine_type* engine)
{
    ods_status status = ODS_STATUS_OK;
    struct sigaction action;
    int result = 0;
    int sockets[2] = {0,0};

    ods_log_debug("[%s] setup signer engine", engine_str);
    if (!engine || !engine->config) {
        return ODS_STATUS_ASSERT_ERR;
    }
    /* set edns */
    edns_init(&engine->edns, EDNS_MAX_MESSAGE_LEN);

    /* create command handler (before chowning socket file) */
    engine->cmdhandler = cmdhandler_create(engine->allocator,
        engine->config->clisock_filename);
    if (!engine->cmdhandler) {
        return ODS_STATUS_CMDHANDLER_ERR;
    }
    engine->dnshandler = dnshandler_create(engine->allocator,
        engine->config->interfaces);
    engine->xfrhandler = xfrhandler_create(engine->allocator);
    if (!engine->xfrhandler) {
        return ODS_STATUS_XFRHANDLER_ERR;
    }
    if (engine->dnshandler) {
        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sockets) == -1) {
            return ODS_STATUS_XFRHANDLER_ERR;
        }
        engine->xfrhandler->dnshandler.fd = sockets[0];
        engine->dnshandler->xfrhandler.fd = sockets[1];
        status = dnshandler_listen(engine->dnshandler);
        if (status != ODS_STATUS_OK) {
            ods_log_error("[%s] setup: unable to listen to sockets (%s)",
                engine_str, ods_status2str(status));
        }
    }
    /* privdrop */
    engine->uid = privuid(engine->config->username);
    engine->gid = privgid(engine->config->group);
    /* TODO: does piddir exists? */
    /* remove the chown stuff: piddir? */
    ods_chown(engine->config->pid_filename, engine->uid, engine->gid, 1);
    ods_chown(engine->config->clisock_filename, engine->uid, engine->gid, 0);
    ods_chown(engine->config->working_dir, engine->uid, engine->gid, 0);
    if (engine->config->log_filename && !engine->config->use_syslog) {
        ods_chown(engine->config->log_filename, engine->uid, engine->gid, 0);
    }
    if (engine->config->working_dir &&
        chdir(engine->config->working_dir) != 0) {
        ods_log_error("[%s] setup: unable to chdir to %s (%s)", engine_str,
            engine->config->working_dir, strerror(errno));
        return ODS_STATUS_CHDIR_ERR;
    }
    if (engine_privdrop(engine) != ODS_STATUS_OK) {
        return ODS_STATUS_PRIVDROP_ERR;
    }
    /* set up hsm */ /* LEAK */
    result = lhsm_open(engine->config->repositories);
    if (result != HSM_OK) {
        fprintf(stderr, "Fail to open hsm\n");
        return ODS_STATUS_HSM_ERR;
    }
    /* daemonize */
    if (engine->daemonize) {
        switch ((engine->pid = fork())) {
            case -1: /* error */
                ods_log_error("[%s] setup: unable to fork daemon (%s)",
                    engine_str, strerror(errno));
                return ODS_STATUS_FORK_ERR;
            case 0: /* child */
                break;
            default: /* parent */
                engine_cleanup(engine);
                engine = NULL;
                xmlCleanupParser();
                xmlCleanupGlobals();
                xmlCleanupThreads();
                exit(0);
        }
        if (setsid() == -1) {
            hsm_close();
            ods_log_error("[%s] setup: unable to setsid daemon (%s)",
                engine_str, strerror(errno));
            return ODS_STATUS_SETSID_ERR;
        }
    }
    engine->pid = getpid();
    /* write pidfile */
    if (util_write_pidfile(engine->config->pid_filename, engine->pid) == -1) {
        hsm_close();
        return ODS_STATUS_WRITE_PIDFILE_ERR;
    }
    /* setup done */
    ods_log_verbose("[%s] running as pid %lu", engine_str,
        (unsigned long) engine->pid);
    /* catch signals */
    signal_set_engine(engine);
    action.sa_handler = signal_handler;
    sigfillset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGHUP, &action, NULL);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGILL, &action, NULL);
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGALRM, &action, NULL);
    sigaction(SIGCHLD, &action, NULL);
    action.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &action, NULL);
    /* create workers/drudgers */
    engine_create_workers(engine);
    engine_create_drudgers(engine);
    /* start cmd/dns/xfr handlers */
    engine_start_cmdhandler(engine);
    engine_start_dnshandler(engine);
    engine_start_xfrhandler(engine);
    tsig_handler_init(engine->allocator);
    return ODS_STATUS_OK;
}