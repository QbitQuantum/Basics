int
main(int argc, char *argv[])
{
    int		sts;
    int		nport = 0;
    char	*envstr;
#ifdef HAVE_SA_SIGINFO
    static struct sigaction act;
#endif

    umask(022);
    __pmProcessDataSize(NULL);
    __pmGetUsername(&username);
    __pmSetInternalState(PM_STATE_PMCS);
    __pmServerSetFeature(PM_SERVER_FEATURE_DISCOVERY);
    __pmServerSetFeature(PM_SERVER_FEATURE_CONTAINERS);

    if ((envstr = getenv("PMCD_PORT")) != NULL)
	nport = __pmServerAddPorts(envstr);
    ParseOptions(argc, argv, &nport);
    if (nport == 0)
	__pmServerAddPorts(TO_STRING(SERVER_PORT));

    /* Set the local socket path. A message will be generated into the log
     * if this fails, but it is not fatal, since other connection options
     * may exist. 
     */
    __pmServerSetLocalSocket(sockpath);

    /* Set the service spec. This will cause our service to be advertised on
     * the network if that is supported.
     */
    __pmServerSetServiceSpec(PM_SERVER_SERVICE_SPEC);

    if (run_daemon) {
	fflush(stderr);
	StartDaemon(argc, argv);
    }

#ifdef HAVE_SA_SIGINFO
    act.sa_sigaction = SigIntProc;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
#else
    __pmSetSignalHandler(SIGINT, SigIntProc);
    __pmSetSignalHandler(SIGTERM, SigIntProc);
#endif
    __pmSetSignalHandler(SIGHUP, SigHupProc);
    __pmSetSignalHandler(SIGBUS, SigBad);
    __pmSetSignalHandler(SIGSEGV, SigBad);

    if ((sts = __pmServerOpenRequestPorts(&clientFds, MAXPENDING)) < 0)
	DontStart();
    maxReqPortFd = maxClientFd = sts;

    __pmOpenLog(pmProgname, logfile, stderr, &sts);
    /* close old stdout, and force stdout into same stream as stderr */
    fflush(stdout);
    close(fileno(stdout));
    sts = dup(fileno(stderr));
    /* if this fails beware of the sky falling in */
    assert(sts >= 0);

    sts = pmLoadASCIINameSpace(pmnsfile, dupok);
    if (sts < 0) {
	fprintf(stderr, "Error: pmLoadASCIINameSpace(%s, %d): %s\n",
	    (pmnsfile == PM_NS_DEFAULT) ? "DEFAULT" : pmnsfile, dupok, pmErrStr(sts));
	DontStart();
    }

    if (ParseInitAgents(configFileName) < 0) {
	/* error already reported in ParseInitAgents() */
	DontStart();
    }

    if (nAgents <= 0) {
	fprintf(stderr, "Error: No PMDAs found in the configuration file \"%s\"\n",
		configFileName);
	DontStart();
    }

    if (run_daemon) {
	if (__pmServerCreatePIDFile(PM_SERVER_SERVICE_SPEC, PM_FATAL_ERR) < 0)
	    DontStart();
	if (__pmSetProcessIdentity(username) < 0)
	    DontStart();
    }

    if (__pmSecureServerSetup(certdb, dbpassfile) < 0)
	DontStart();

    PrintAgentInfo(stderr);
    __pmAccDumpLists(stderr);
    fprintf(stderr, "\npmcd: PID = %" FMT_PID, getpid());
    fprintf(stderr, ", PDU version = %u\n", PDU_VERSION);
    __pmServerDumpRequestPorts(stderr);
    fflush(stderr);

    /* all the work is done here */
    ClientLoop();

    Shutdown();
    exit(0);
}