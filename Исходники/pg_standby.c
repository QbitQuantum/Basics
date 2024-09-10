/*------------ MAIN ----------------------------------------*/
int
main(int argc, char **argv)
{
	int			c;

	progname = get_progname(argv[0]);

	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0)
		{
			usage();
			exit(0);
		}
		if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0)
		{
			puts("pg_standby (PostgreSQL) " PG_VERSION);
			exit(0);
		}
	}

#ifndef WIN32
	/*
	 * You can send SIGUSR1 to trigger failover.
	 *
	 * Postmaster uses SIGQUIT to request immediate shutdown. The default
	 * action is to core dump, but we don't want that, so trap it and commit
	 * suicide without core dump.
	 *
	 * We used to use SIGINT and SIGQUIT to trigger failover, but that turned
	 * out to be a bad idea because postmaster uses SIGQUIT to request
	 * immediate shutdown. We still trap SIGINT, but that may change in a
	 * future release.
	 *
	 * There's no way to trigger failover via signal on Windows.
	 */
	(void) signal(SIGUSR1, sighandler);
	(void) signal(SIGINT, sighandler);	/* deprecated, use SIGUSR1 */
	(void) signal(SIGQUIT, sigquit_handler);
#endif

	while ((c = getopt(argc, argv, "cdk:lr:s:t:w:")) != -1)
	{
		switch (c)
		{
			case 'c':			/* Use copy */
				restoreCommandType = RESTORE_COMMAND_COPY;
				break;
			case 'd':			/* Debug mode */
				debug = true;
				break;
			case 'k':			/* keepfiles */
				keepfiles = atoi(optarg);
				if (keepfiles < 0)
				{
					fprintf(stderr, "%s: -k keepfiles must be >= 0\n", progname);
					exit(2);
				}
				break;
			case 'l':			/* Use link */
				/*
				 * Link feature disabled, possibly permanently. Linking
				 * causes a problem after recovery ends that is not currently
				 * resolved by PostgreSQL. 25 Jun 2009
				 */
#ifdef NOT_USED
				restoreCommandType = RESTORE_COMMAND_LINK;
#endif
				break;
			case 'r':			/* Retries */
				maxretries = atoi(optarg);
				if (maxretries < 0)
				{
					fprintf(stderr, "%s: -r maxretries must be >= 0\n", progname);
					exit(2);
				}
				break;
			case 's':			/* Sleep time */
				sleeptime = atoi(optarg);
				if (sleeptime <= 0 || sleeptime > 60)
				{
					fprintf(stderr, "%s: -s sleeptime incorrectly set\n", progname);
					exit(2);
				}
				break;
			case 't':			/* Trigger file */
				triggerPath = optarg;
				break;
			case 'w':			/* Max wait time */
				maxwaittime = atoi(optarg);
				if (maxwaittime < 0)
				{
					fprintf(stderr, "%s: -w maxwaittime incorrectly set\n", progname);
					exit(2);
				}
				break;
			default:
				fprintf(stderr, "Try \"%s --help\" for more information.\n", progname);
				exit(2);
				break;
		}
	}

	/*
	 * Parameter checking - after checking to see if trigger file present
	 */
	if (argc == 1)
	{
		fprintf(stderr, "%s: not enough command-line arguments\n", progname);
		exit(2);
	}

	/*
	 * We will go to the archiveLocation to get nextWALFileName.
	 * nextWALFileName may not exist yet, which would not be an error, so we
	 * separate the archiveLocation and nextWALFileName so we can check
	 * separately whether archiveLocation exists, if not that is an error
	 */
	if (optind < argc)
	{
		archiveLocation = argv[optind];
		optind++;
	}
	else
	{
		fprintf(stderr, "%s: must specify archive location\n", progname);
		fprintf(stderr, "Try \"%s --help\" for more information.\n", progname);
		exit(2);
	}

	if (optind < argc)
	{
		nextWALFileName = argv[optind];
		optind++;
	}
	else
	{
		fprintf(stderr, "%s: use %%f to specify nextWALFileName\n", progname);
		fprintf(stderr, "Try \"%s --help\" for more information.\n", progname);
		exit(2);
	}

	if (optind < argc)
	{
		xlogFilePath = argv[optind];
		optind++;
	}
	else
	{
		fprintf(stderr, "%s: use %%p to specify xlogFilePath\n", progname);
		fprintf(stderr, "Try \"%s --help\" for more information.\n", progname);
		exit(2);
	}

	if (optind < argc)
	{
		restartWALFileName = argv[optind];
		optind++;
	}

	CustomizableInitialize();

	need_cleanup = SetWALFileNameForCleanup();

	if (debug)
	{
		fprintf(stderr, "Trigger file 		: %s\n", triggerPath ? triggerPath : "<not set>");
		fprintf(stderr, "Waiting for WAL file	: %s\n", nextWALFileName);
		fprintf(stderr, "WAL file path		: %s\n", WALFilePath);
		fprintf(stderr, "Restoring to		: %s\n", xlogFilePath);
		fprintf(stderr, "Sleep interval		: %d second%s\n",
				sleeptime, (sleeptime > 1 ? "s" : " "));
		fprintf(stderr, "Max wait interval	: %d %s\n",
				maxwaittime, (maxwaittime > 0 ? "seconds" : "forever"));
		fprintf(stderr, "Command for restore	: %s\n", restoreCommand);
		fprintf(stderr, "Keep archive history	: ");
		if (need_cleanup)
			fprintf(stderr, "%s and later\n", exclusiveCleanupFileName);
		else
			fprintf(stderr, "No cleanup required\n");
		fflush(stderr);
	}

	/*
	 * Check for initial history file: always the first file to be requested
	 * It's OK if the file isn't there - all other files need to wait
	 */
	if (strlen(nextWALFileName) > 8 &&
		strspn(nextWALFileName, "0123456789ABCDEF") == 8 &&
		strcmp(nextWALFileName + strlen(nextWALFileName) - strlen(".history"),
			   ".history") == 0)
	{
		nextWALFileType = XLOG_HISTORY;
		if (RestoreWALFileForRecovery())
			exit(0);
		else
		{
			if (debug)
			{
				fprintf(stderr, "history file not found\n");
				fflush(stderr);
			}
			exit(1);
		}
	}

	/*
	 * Main wait loop
	 */
	for (;;)
	{
		/* Check for trigger file or signal first */
		CheckForExternalTrigger();
#ifndef WIN32
		if (signaled)
		{
			Failover = FastFailover;
			if (debug)
			{
				fprintf(stderr, "signaled to exit: fast failover\n");
				fflush(stderr);
			}
		}
#endif

		/*
		 * Check for fast failover immediately, before checking if the
		 * requested WAL file is available
		 */
		if (Failover == FastFailover)
			exit(1);

		if (CustomizableNextWALFileReady())
		{
			/*
			 * Once we have restored this file successfully we can remove some
			 * prior WAL files. If this restore fails we musn't remove any
			 * file because some of them will be requested again immediately
			 * after the failed restore, or when we restart recovery.
			 */
			if (RestoreWALFileForRecovery())
			{
				if (need_cleanup)
					CustomizableCleanupPriorWALFiles();

				exit(0);
			}
			else
			{
				/* Something went wrong in copying the file */
				exit(1);
			}
		}

		/* Check for smart failover if the next WAL file was not available */
		if (Failover == SmartFailover)
			exit(1);

		if (sleeptime <= 60)
			pg_usleep(sleeptime * 1000000L);

		waittime += sleeptime;
		if (waittime >= maxwaittime && maxwaittime > 0)
		{
			Failover = FastFailover;
			if (debug)
			{
				fprintf(stderr, "Timed out after %d seconds: fast failover\n",
						waittime);
				fflush(stderr);
			}
		}
		if (debug)
		{
			fprintf(stderr, "WAL file not present yet.");
			if (triggerPath)
				fprintf(stderr, " Checking for trigger file...");
			fprintf(stderr, "\n");
			fflush(stderr);
		}
	}
}