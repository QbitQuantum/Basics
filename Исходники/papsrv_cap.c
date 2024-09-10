/*
** This is the daemon's main loop where we accept incoming connections.
** This loop never ends.
*/
void appletalk_dependent_daemon_main_loop(void)
	{
	int rquantum=1;				/* too bad the other end does not tell use */
	int x;						/* used to look thru names */
	int papfd;					/* server endpoint handle */
	int sesfd;					/* session handle */
	pid_t pid;					/* process id of our child */
	int err;
	AddrBlock remote;			/* Address of remote */

	/* Run GetNextJob() on each endpoint in the array created by add_name(). */
	for(x=0; x < name_count; x++)
		{
		if((err = GetNextJob(endpoints[x].fd, &endpoints[x].sesfd, &endpoints[x].gcomp)) != 0)
			fatal(1, "GetNextJob() returned %d", err);
		}

	/* Change the status from `starting up' to `receiving'. */
	strcpy(status.StatusStr, "xThe PPR spooler is receiving your job.");
	status.StatusStr[0] = (unsigned char)strlen(&status.StatusStr[1]);

	while(TRUE)									/* loop until killed */
		{
		DODEBUG_LOOP(("waiting for connexion"));

		/* Give the AppleTalk stack time to work. */
		abSleep(10,TRUE);

		/* Try the file descriptor representing each name in turn. */
		for(x=0; x < name_count; x++)
			{
			DODEBUG_LOOP(("checking endpoint %d, gcomp=%d", x, endpoints[x].gcomp));

			if(endpoints[x].gcomp > 0)		/* If command not completed, */
				continue;					/* try the next one. */

			if(endpoints[x].gcomp < 0)		/* if error, */
				fatal(1, "GetNextJob() completed with error %d on \"%s\"", endpoints[x].gcomp, adv[x].PAPname);

			DODEBUG_LOOP(("connexion found, sesfd=%d", endpoints[x].sesfd));

			/* Note this session number and get ready to accept another. */
			papfd = endpoints[x].fd;			/* name fd */
			sesfd = endpoints[x].sesfd;			/* session fd */
			if((err = GetNextJob(endpoints[x].fd, &endpoints[x].sesfd, &endpoints[x].gcomp)) != 0)
				fatal(1, "GetNextJob() returned %d",err);

			/* Fork so that one copy of this process can continue
			** to be the daemon while the other goes off and
			** talks with the client.
			*/
			while( (pid=fork()) == -1 )		/* If we can't fork(), */
				{							/* then wait and try again. */
				debug("out of processes");	/* (Of course, forking for ppr */
				sleep(60);					/* may fail later.) */
				}

			if(pid==0)					/* if we are the child */
				{
				DODEBUG_LOOP(("Hello, I am the child"));

				i_am_master = FALSE;

				SLClose(papfd);			/* close server's listening socket */

				/* reset termination signal handlers */
				signal(SIGHUP, SIG_DFL);
				signal(SIGINT, SIG_DFL);
				signal(SIGTERM, SIG_DFL);

				/* change SIGCHLD handler */
				signal(SIGCHLD, printjob_reapchild);

				/*
				** Set up a handler for SIGPIPE which may occur
				** if PPR exits suddenly.
				*/
				signal(SIGPIPE,sigpipe_handler);

				/* compute usable size of write buffer */
				write_unit = (rquantum<=MAX_REMOTE_QUANTUM?rquantum:MAX_REMOTE_QUANTUM) * 512;

				/*
				** In CAP we must make a seperate call in order
				** to find the address of the client.  This address
				** is passed to child_main_loop().  It eventually finds
				** its way into the ppr -r switch.
				*/
				PAPGetNetworkInfo(sesfd, &remote);

				/*
				** Call child_main_loop() which accepts all the
				** queries and jobs.
				*/
				child_main_loop(sesfd, x, (int)ntohs(remote.net), (int)remote.node);

				/*
				** Since child_main_loop() has returned,
				** we are done, the child can exit.
				*/
				PAPClose(sesfd);		/* don't test return code */
				exit(0);				/* sucessful exit */
				}

			else						/* if parent */
				{
				children++;				/* add to count of children */
				PAPShutdown(sesfd);		/* close server's copy of connection */
				}

			} /* end of for loop which tries each endpoint */

		} /* end of outside loop which never ends */
	} /* end of appletalk_dependent_main_loop() */