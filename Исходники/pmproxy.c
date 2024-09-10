int
main(int argc, char *argv[])
{
    int		sts;
    int		nport = 0;
    int		localhost = 0;
    int		maxpending = MAXPENDING;
    char	*envstr;

    umask(022);
    __pmGetUsername(&username);
    __pmSetInternalState(PM_STATE_PMCS);
    __pmServerSetFeature(PM_SERVER_FEATURE_DISCOVERY);

    if ((envstr = getenv("PMPROXY_PORT")) != NULL)
        nport = __pmServerAddPorts(envstr);
    if ((envstr = getenv("PMPROXY_LOCAL")) != NULL)
        if ((localhost = atoi(envstr)) != 0)
            __pmServerSetFeature(PM_SERVER_FEATURE_LOCAL);
    if ((envstr = getenv("PMPROXY_MAXPENDING")) != NULL)
        maxpending = atoi(envstr);
    ParseOptions(argc, argv, &nport);
    if (localhost)
        __pmServerAddInterface("INADDR_LOOPBACK");
    if (nport == 0)
        __pmServerAddPorts(TO_STRING(PROXY_PORT));
    GetProxyHostname();

    __pmServerSetServiceSpec(PM_SERVER_PROXY_SPEC);
    if (run_daemon) {
        fflush(stderr);
        StartDaemon(argc, argv);
        __pmServerCreatePIDFile(PM_SERVER_PROXY_SPEC, 0);
    }

    __pmSetSignalHandler(SIGHUP, SIG_IGN);
    __pmSetSignalHandler(SIGINT, SigIntProc);
    __pmSetSignalHandler(SIGTERM, SigIntProc);
    __pmSetSignalHandler(SIGBUS, SigBad);
    __pmSetSignalHandler(SIGSEGV, SigBad);

    /* Open request ports for client connections */
    if ((sts = __pmServerOpenRequestPorts(&sockFds, maxpending)) < 0)
        DontStart();
    maxReqPortFd = maxSockFd = sts;

    __pmOpenLog(pmProgname, logfile, stderr, &sts);
    /* close old stdout, and force stdout into same stream as stderr */
    fflush(stdout);
    close(fileno(stdout));
    if (dup(fileno(stderr)) == -1) {
        fprintf(stderr, "Warning: dup() failed: %s\n", pmErrStr(-oserror()));
    }

    fprintf(stderr, "pmproxy: PID = %" FMT_PID, getpid());
    fprintf(stderr, ", PDU version = %u\n", PDU_VERSION);
    __pmServerDumpRequestPorts(stderr);
    fflush(stderr);

    /* lose root privileges if we have them */
    __pmSetProcessIdentity(username);

    if (__pmSecureServerSetup(certdb, dbpassfile) < 0)
        DontStart();

    /* all the work is done here */
    ClientLoop();

    Shutdown();
    exit(0);
}