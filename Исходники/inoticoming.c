int main(int argc, char * const argv[]) {
	int notifd;
	int dirwatchid;
	const char *directory;
	char *logfilename = NULL;
	int timeout, e, opt;
	struct inotify_event *event;
	FILE *pidfile;
	DIR *dir;
	bool initialsearch = false;
	static const struct option global_long_options[] = {
		{ "version",	no_argument,		NULL, 1},
		{ "help",	no_argument,		NULL, 'h'},
		{ "logfile",	required_argument,	NULL, 'l'},
		{ "foreground",	no_argument,		NULL, 'F'},
		{ "initialsearch",no_argument,		NULL, 'i'},
		{ "pid-file",	required_argument,	NULL, 'p'},
		{ NULL,	0, NULL, 0}
	};

	program = argv[0];
	if (argc < 2) {
		logerror("Not enough arguments.\n");
		syntax(stderr, EXIT_FAILURE);
	}
	opterr = 0;
	while ((opt = getopt_long(argc, argv, "+h?p:l:Ffi",
					global_long_options, NULL)) >= 0) {
		switch (opt) {
			case 1:
				puts(PACKAGE " " VERSION);
				exit(EXIT_SUCCESS);
				break;
			case 'h':
				syntax(stdout, EXIT_SUCCESS);
				break;
			case 'l':
				if (logfile != NULL)
					logerror_die(
"Multiple --logfile options are not supported.\n");
				logfilename = xstrdup(optarg);
				break;
			case 'p':
				if (pidfilename != NULL)
					logerror_die(
"Multiple --pid-file options are not supported.\n");
				pidfilename = xstrdup(optarg);
				break;
			case 'f':
			case 'F':
				foreground = true;
				break;
			case 'i':
				initialsearch = true;
				break;
			case '?':
				if (optopt == '\0')
					logerror_die(
"Unknown/ambiguous global option '%s'!\n", argv[optind-1]);
				else if (optopt == 'p' || optopt == 'l')
					logerror_die(
"Global option '%s' needs an argument!\n", argv[optind-1]);
				else
					logerror_die(
"Unknown global option '%c'!\n", (char)optopt);
				break;
		}
	}
	if (optind >= argc)
		logerror_die("Not enough arguments!\n");
	directory = argv[optind];
	optind++;
	while (optind < argc)
		parseaction(argc, argv, logfilename != NULL);
	if (lookfor == NULL)
		logerror_die("Nothing to do specified!\n");

	notifd = inotify_init();
	if (notifd < 0) {
		e = errno;
		fprintf(stderr, "%s: Could not initialize inotify: %s(%d)\n",
				program, strerror(e), e);
		return EXIT_FAILURE;
	}

	dirwatchid = inotify_add_watch(notifd, directory,
			IN_MOVED_TO|IN_CLOSE_WRITE|IN_ONLYDIR|IN_DELETE_SELF);
	if (dirwatchid < 0) {
		e = errno;
		fprintf(stderr, "%s: Error adding watch for %s: %s(%d)\n",
				program, directory, strerror(e), e);
		close(notifd);
		return EXIT_FAILURE;
	}

	if (initialsearch) {
		dir = opendir(directory);
		if (dir == NULL) {
			e = errno;
			fprintf(stderr, "%s: Error opening directory %s:"
					" %s(%d)\n", program, directory,
					strerror(e), e);
			close(notifd);
			return EXIT_FAILURE;
		}
	} else
		dir = NULL;

	if (pidfilename != NULL) {
		pidfile = fopen(pidfilename, "w");
		if (pidfile == NULL) {
			e = errno;
			logerror_die("Could not create/open pidfile '%s': "
					"%s(%d)\n",
					pidfilename, strerror(e), e);
		}
	} else
		pidfile = NULL;
	if (!foreground) {
		if (logfilename != NULL) {
			logfile = fopen(logfilename, "a");
			if (logfile == NULL) {
				e = errno;
				logerror_die("Error opening logfile '%s': "
						"%s(%d)\n",
						logfilename, strerror(e), e);
			}
			free(logfilename); logfilename = NULL;
			setlinebuf(logfile);
		} else
			openlog("queueprocessor", LOG_PID, LOG_DAEMON);
		if (daemon(false, false) < 0) {
			e = errno;
			logerror_die("Failed to daemonize: %s(%d)\n",
					strerror(e), e);
		}
		amdaemon = true;
	} else {
		setlinebuf(stdout);
		setlinebuf(stderr);
	}
	if (pidfile != NULL) {
		fprintf(pidfile, "%llu", (unsigned long long)getpid());
		fclose(pidfile);
	}
	{
		const int exceptions[6] = { 0, 1, 2, notifd,
			(logfile==NULL)?-1:fileno(logfile),
			(dir==NULL)?-1:dirfd(dir) };
		closeallopenfds(exceptions, 6);
		errno = 0;
	}
	signal(SIGTERM, termsignal);
	signal(SIGABRT, termsignal);

	if (dir != NULL) {
		process_directory(dir);
		closedir(dir);
	}

	timeout = -1;
	while (!termsignaled) {
		if (waitforevent(notifd, timeout)) {
			bool doread = true;
			if (termsignaled)
				break;
			while ((event = getevent(notifd, &doread)) != NULL) {
				processevent(event);
				free(event);
			}
		} else {
			timeout = -1;
		}
	}
	close(notifd);
	return EXIT_SUCCESS;
}