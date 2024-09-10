int
main(int argc, char **argv)
{
    struct CmdLine cmdline;
    struct cmd_syndesc *ts;
    int err = 0;

#ifdef	AFS_AIX32_ENV
    /*
     * The following signal action for AIX is necessary so that in case of a
     * crash (i.e. core is generated) we can include the user's data section
     * in the core dump. Unfortunately, by default, only a partial core is
     * generated which, in many cases, isn't too useful.
     */
    struct sigaction nsa;

    sigemptyset(&nsa.sa_mask);
    nsa.sa_handler = SIG_DFL;
    nsa.sa_flags = SA_FULLDUMP;
    sigaction(SIGABRT, &nsa, NULL);
    sigaction(SIGSEGV, &nsa, NULL);
#endif

    /* Initialize directory paths */
    if (!(initAFSDirPath() & AFSDIR_SERVER_PATHS_OK)) {
#ifdef AFS_NT40_ENV
	ReportErrorEventAlt(AFSEVT_SVR_NO_INSTALL_DIR, 0, argv[0], 0);
#endif
	fprintf(stderr, "%s: Unable to obtain AFS server directory.\n",
		argv[0]);
	exit(2);
    }
#ifdef AFS_NT40_ENV
    /* Default to binary mode for fopen() */
    _set_fmode(_O_BINARY);

    main_thread = pthread_self();
    if (spawnDatap && spawnDataLen) {
	/* This is a child per partition salvager. Don't setup log or
	 * try to lock the salvager lock.
	 */
	if (nt_SetupPartitionSalvage(spawnDatap, spawnDataLen) < 0)
	    exit(3);
    } else {
#endif

#ifndef AFS_NT40_ENV
	if (geteuid() != 0) {
	    printf("Salvager must be run as root.\n");
	    fflush(stdout);
	    Exit(0);
	}
#endif

	/* Get and hold a lock for the duration of the salvage to make sure
	 * that no other salvage runs at the same time.  The routine
	 * VInitVolumePackage2 (called below) makes sure that a file server or
	 * other volume utilities don't interfere with the salvage.
	 */
	get_salvage_lock = 1;
#ifdef AFS_NT40_ENV
    }
#endif

    cmdline.argc = argc;
    cmdline.argv = argv;
    ts = cmd_CreateSyntax("initcmd", handleit, &cmdline, 0, "initialize the program");
    cmd_AddParm(ts, "-partition", CMD_SINGLE, CMD_OPTIONAL,
		"Name of partition to salvage");
    cmd_AddParm(ts, "-volumeid", CMD_SINGLE, CMD_OPTIONAL,
		"Volume Id to salvage");
    cmd_AddParm(ts, "-debug", CMD_FLAG, CMD_OPTIONAL,
		"Run in Debugging mode");
    cmd_AddParm(ts, "-nowrite", CMD_FLAG, CMD_OPTIONAL,
		"Run readonly/test mode");
    cmd_AddParm(ts, "-inodes", CMD_FLAG, CMD_OPTIONAL,
		"Just list affected afs inodes - debugging flag");
    cmd_AddParm(ts, "-force", CMD_FLAG, CMD_OPTIONAL, "Force full salvaging");
    cmd_AddParm(ts, "-oktozap", CMD_FLAG, CMD_OPTIONAL,
		"Give permission to destroy bogus inodes/volumes - debugging flag");
    cmd_AddParm(ts, "-rootinodes", CMD_FLAG, CMD_OPTIONAL,
		"Show inodes owned by root - debugging flag");
    cmd_AddParm(ts, "-salvagedirs", CMD_FLAG, CMD_OPTIONAL,
		"Force rebuild/salvage of all directories");
    cmd_AddParm(ts, "-blockreads", CMD_FLAG, CMD_OPTIONAL,
		"Read smaller blocks to handle IO/bad blocks");
    cmd_AddParm(ts, "-parallel", CMD_SINGLE, CMD_OPTIONAL,
		"# of max parallel partition salvaging");
    cmd_AddParm(ts, "-tmpdir", CMD_SINGLE, CMD_OPTIONAL,
		"Name of dir to place tmp files ");
    cmd_AddParm(ts, "-showlog", CMD_FLAG, CMD_OPTIONAL,
		"Show log file upon completion");
    cmd_AddParm(ts, "-showsuid", CMD_FLAG, CMD_OPTIONAL,
		"Report on suid/sgid files");
    cmd_AddParm(ts, "-showmounts", CMD_FLAG, CMD_OPTIONAL,
		"Report on mountpoints");
    cmd_AddParm(ts, "-orphans", CMD_SINGLE, CMD_OPTIONAL,
		"ignore | remove | attach");

    /* note - syslog isn't avail on NT, but if we make it conditional, have
     * to deal with screwy offsets for cmd params */
    cmd_AddParm(ts, "-syslog", CMD_FLAG, CMD_OPTIONAL,
		"Write salvage log to syslogs");
    cmd_AddParm(ts, "-syslogfacility", CMD_SINGLE, CMD_OPTIONAL,
		"Syslog facility number to use");
    cmd_AddParm(ts, "-datelogs", CMD_FLAG, CMD_OPTIONAL,
		"Include timestamp in logfile filename");
#ifdef FAST_RESTART
    cmd_AddParm(ts, "-DontSalvage", CMD_FLAG, CMD_OPTIONAL,
		"Don't salvage. This my be set in BosConfig to let the fileserver restart immediately after a crash. Bad volumes will be taken offline");
#elif defined(AFS_DEMAND_ATTACH_FS)
    cmd_Seek(ts, 20); /* skip DontSalvage */
    cmd_AddParm(ts, "-forceDAFS", CMD_FLAG, CMD_OPTIONAL,
		"For Demand Attach Fileserver, permit a manual volume salvage outside of the salvageserver");
#endif /* FAST_RESTART */
    cmd_Seek(ts, 21); /* skip DontSalvage and forceDAFS if needed */
    cmd_AddParm(ts, "-f", CMD_FLAG, CMD_OPTIONAL, "Alias for -force");
    err = cmd_Dispatch(argc, argv);
    Exit(err);
    return 0; /* not reached */
}