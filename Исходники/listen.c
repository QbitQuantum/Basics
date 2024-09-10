int
main(int argc, char **argv)
{
	struct stat buf;
	int ret;
	char scratch[BUFSIZ];
	char log[BUFSIZ];
	char olog[BUFSIZ];
	char *scratch_p = scratch;
	char *mytag_p;
	FILE *fp;
	extern char *getenv();
	char *parse();
	int	c;
	extern	char *optarg;
	extern	int optind;
	int i;
	char	*Mytag_p = Mytag;

	/* Get my port monitor tag out of the environment		*/
	if ((mytag_p = getenv("PMTAG")) == NULL) {
		/* no place to write */
		exit(1);
	}
	strcpy(Mytag, mytag_p);

	/* open log file */
	sprintf(log, "%s/%s/%s", ALTDIR, Mytag_p, LOGNAME);
	sprintf(olog, "%s/%s/%s", ALTDIR, Mytag_p, OLOGNAME);
	if (stat(log, &buf) == 0) {
		/* file exists, try and save it but if we can't don't worry */
		unlink(olog);
		rename(log, olog);
	}
	if ((i = open(log, O_WRONLY|O_CREAT|O_APPEND, 0444)) < 0)
		logexit(1, nologfile);
	/* as stated above, the log file should be file descriptor 5 */
	if ((ret = fcntl(i, F_DUPFD, 5)) != 5)
		logexit(1, nologfile);
	Logfp = fdopen(ret, "a+");

	/* Get my port monitor tag out of the environment		*/
	if ((mytag_p = getenv("PMTAG")) == NULL) {
		logexit(1, nopmtag);
	}
	strcpy(Mytag, mytag_p);

	(void) umask(022);
	Readdb = FALSE;

	if (geteuid() != (uid_t) 0) {
		logmessage("Must be root to start listener");
		logexit(1, badstart);
	}

	while ((c = getopt(argc, argv, "m:")) != EOF) 
		switch (c) {
		case 'm':
			Minor_prefix = optarg;
			break;
		default:
			logexit(1, usage);
			break;
		}

	if ((Netspec = argv[optind]) == NULL) {
		logexit(1, usage);
	}
	if ((Netconf = getnetconfigent(Netspec)) == NULL) {
		sprintf(scratch, "no netconfig entry for <%s>", Netspec);
		logmessage(scratch);
		logexit(1, badstart);
	}
	if (!Minor_prefix)
		Minor_prefix = argv[optind];

	if ((int) strlen(Netspec) > PATHSIZE)  {
		logmessage(badnspmsg);
		logexit(1, badstart);
	}

	/* 
	 * SAC will start the listener in the correct directory, so we
	 * don't need to chdir there, as we did in older versions
	 */

	strcpy(Provbuf, "/dev/");
	strcat(Provbuf, Netspec);

	(void) umask(0);

	init_files();		/* open Accept, Sac, Pm, Pass files	*/
	pid_open();		/* create pid file			*/

#ifdef	DEBUGMODE
	sprintf(scratch, "%s/%s/%s", ALTDIR, Mytag, DBGNAME);
	Debugfp = fopen(scratch, "w");
#endif


#ifdef	DEBUGMODE
	if ((!Logfp) || (!Debugfp)) 
#else
	if (!Logfp)
#endif
		logexit(1, badstart);

/*
 * In case we started with no environment, find out what timezone we're
 * in.  This will get passed to children, so only need to do once.
 */

	if (getenv("TZ") == NULL) {
		fp = fopen(TIMEZONE, "r");
		if (fp) {
			while (fgets(tzenv, BUFSIZ, fp)) {
				if (tzenv[strlen(tzenv) - 1] == '\n')
					tzenv[strlen(tzenv) - 1] = '\0';
				if (!strncmp(TZSTR, tzenv, strlen(TZSTR))) {
					putenv(parse(tzenv));
					break;
				}
			}
			fclose(fp);
		}
		else {
			sprintf(scratch, "couldn't open %s, default to GMT", TIMEZONE);
			logmessage(scratch);
		}
	}

	logmessage("@(#)listen:listen.c	1.19.9.1");

#ifdef	DEBUGMODE
	logmessage("Listener process with DEBUG capability");
#endif

	sprintf(scratch, "Listener port monitor tag: %s", Mytag_p);
	logmessage(scratch);
	DEBUG((9, "Minor prefix: %s  Netspec %s", Minor_prefix, Netspec));

	/* fill in Pmmesg fields that always stay the same */

	Pmmsg.pm_maxclass = MAXCLASS;
	strcpy(Pmmsg.pm_tag, Mytag_p);
	Pmmsg.pm_size = 0;

	/* Find out what state to start in.  If not in env, exit */
	if ((scratch_p = getenv("ISTATE")) == NULL)
		logexit(1, "ERROR: ISTATE variable not set in environment");
	
	if (!strcmp(scratch_p, "enabled")) {
		State = PM_ENABLED;
		logmessage("Starting state: ENABLED");
	}
	else {
		State = PM_DISABLED;
		logmessage("Starting state: DISABLED");
	}

	/* try to get my "basename"		*/
	Progname = strrchr(argv[0], '/');
	if (Progname && Progname[1])
		++Progname;
	else
		Progname = argv[0];

	catch_signals();

	/* 
	 * Allocate memory for private address and file descriptor table 
	 * Here we are assuming that no matter how many private addresses
	 * exist in the system if the system limit is 20 then we will only
	 * get 20 file descriptors
	 */

	Ndesc = ulimit(4,0L);		/* get num of file des on system */

	read_dbf(DB_INIT);
	net_open();			/* init, open, bind names 	*/

	for (i = 3; i < Ndesc; i++)  {	/* leave stdout, stderr open	*/
		fcntl(i, F_SETFD, 1);	/* set close on exec flag*/
	}

	logmessage("Initialization Complete");

	listen();
	return (0);
}