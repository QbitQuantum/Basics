int main(int argc,  char *argv[])
{
	struct sockaddr_in sockname, client;
	struct sigaction sa;
	struct tm* time_struct;
	FILE * logfile;
	socklen_t clientlen;
        int sd;
	char timec[80];
	char dircopy[80];
	char *ep;
	time_t rawtime;
	u_short port;
	pid_t pid;
	u_long p;


	/*
	 * first, figure out what port we will listen on - it should
	 * be our first parameter.
	 */

	if (argc != 4) {
		usage();
		errno = 0;
	}
        p = strtoul(argv[1], &ep, 10);
        if (*argv[1] == '\0' || *ep != '\0') {
		/* parameter wasn't a number, or was empty */
		fprintf(stderr, "%s - not a number\n", argv[1]);
		usage();
	}
        if ((errno == ERANGE && p == ULONG_MAX) || (p > USHRT_MAX)) {
		/* It's a number, but it either can't fit in an unsigned
		 * long, or is too big for an unsigned short
		 */
		fprintf(stderr, "%s - value out of range\n", argv[1]);
		usage();
	}
	
	strncpy(dircopy, argv[2], sizeof(dircopy));
	
	/* Checking if the directory exists.
	 * adapted from
	 * http://stackoverflow.com/a/12510903
	 */
	if (opendir(dircopy) == NULL) {
		fprintf(stderr, "Directory does not exist.\n");
		usage();
	}

	/* 
	 * Check to make sure logfile can open and does exist 
	 */
	logfile = fopen(argv[3], "a");

	if (logfile == NULL) {
		fprintf(stderr, "Error opening logfile.\n");
		usage();
	}
	fclose(logfile);

	/* used strncpy as I found out assignment is not possible */

	strncpy(docdir, argv[2], sizeof(docdir));
	strncpy(logdir, argv[3], sizeof(logdir));

	/* now safe to do this */

	if (daemon(1, 0) == -1) {
		fprintf(stderr, "Could not daemonize.\n");
		usage();
	}

	port = p;

	memset(&sockname, 0, sizeof(sockname));
	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(port);
	sockname.sin_addr.s_addr = htonl(INADDR_ANY);
	sd=socket(AF_INET,SOCK_STREAM,0);
	if ( sd == -1)
		err(1, "socket failed");

	if (bind(sd, (struct sockaddr *) &sockname, sizeof(sockname)) == -1)
		err(1, "bind failed");

	if (listen(sd,3) == -1)
		err(1, "listen failed");

	/*
	 * we're now bound, and listening for connections on "sd" -
	 * each call to "accept" will return us a descriptor talking to
	 * a connected client
	 */


	/*
	 * first, let's make sure we can have children without leaving
	 * zombies around when they die - we can do this by catching
	 * SIGCHLD.
	 */
	sa.sa_handler = kidhandler;
        sigemptyset(&sa.sa_mask);
	/*
	 * we want to allow system calls like accept to be restarted if they
	 * get interrupted by a SIGCHLD
	 */
        sa.sa_flags = SA_RESTART;
        if (sigaction(SIGCHLD, &sa, NULL) == -1)
                err(1, "sigaction failed");

	/*
	 * finally - the main loop.  accept connections and deal with 'em
	 */
	for(;;) {
		int clientsd;
		clientlen = sizeof(&client);
		clientsd = accept(sd, (struct sockaddr *)&client, &clientlen);
		if (clientsd == -1)
			err(1, "accept failed");
		/*
		 * We fork child to deal with each connection, this way more
		 * than one client can connect to us and get served at any one
		 * time.
		 */

		pid = fork();
		if (pid == -1)
		     err(1, "fork failed");

		if(pid == 0) 
		{
			/* 
			 * Using INET to determine client ip 
			 * code adapted from
			 * http://stackoverflow.com/a/3060988
			 */
			char clientip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(client.sin_addr), clientip, INET_ADDRSTRLEN);

			/*
			 * Getting current time using time library
			 * code adapted from
			 * http://stackoverflow.com/a/10332099
			 */
			time(&rawtime);
			time_struct = localtime(&rawtime);
			strftime(timec, 80, "%a, %d %b %Y %X %Z", time_struct);
			client_request(clientsd, timec, clientip);
			exit(0);
		}
		close(clientsd);
	}
}