/*
 * Start up the process with the given args
 */
INTERNAL int
start_agent(AGENT_REQ *areq, char *cmd, char *args, int *retpid) {
	int   argc;
	char *argv[MAX_ARGS];
	char  hostname[AGENTD_NAMELEN];
	int   childpid;
	int   pid, exitstat;
	int   pipeout[2], pipeerr[2];
	int   rc;
	EVENT_AGENTD_STAT estat;
	EVENT_AGENTD_LOG  elogout, elogerr;
	char  msg[200];
	char  cmdpath[PATHLEN];

	if (WorkDir) make_path(cmdpath, ExecPath, cmd);
	else         strcpy(cmdpath, cmd);

	argv[0] = cmd;
	argc    = 1;

	if (Verbose) printf("0: %s (%s)\n", argv[0], cmdpath);
	rc = parse_args(args, argv, 1);
	if (rc < 0) {
		return(0);
	}
	argc = rc;

/**************************/
/****** START DEBUG *******/
#ifdef FAKE_THIS_FOR_DEBUGGING
printf("start_agent: sleeping\n");
	if (areq) {
		areq->status = AGENTD_AGENT_RUNNING;
		areq->pid    = 9999999;

		estat.reqseq  = EventSeq(areq->ereq);
		estat.tag     = areq->ereq.tag;
		estat.reqtype = AGENTD_CTL_START;
		estat.result  = 9999999;
		estat.rstatus = AGENTD_STATUS_OK;
		SEND(EventFrom(areq->ereq), AGENTD_STAT, estat);
	}
sleep(10);
	if (areq) {
		areq->status = AGENTD_AGENT_EXIT;

		estat.result  = 0;
		estat.rstatus = AGENTD_AGENT_EXIT;
		SEND(EventFrom(areq->ereq), AGENTD_STAT, estat);
	}
printf("start_agent: exiting\n");
return(AGENTD_STATUS_OK);
#endif
/******** END DEBUG *******/
/**************************/

	if (pipe(pipeout) != SYS_OK) {
		fprintf(stderr, "start_agent: couldn't create stdout pipe\n");
		perror("start_agent");
		return(AGENTD_STATUS_RUNERR);
	}
	if (pipe(pipeerr) != SYS_OK) {
		fprintf(stderr, "start_agent: couldn't create stderr pipe\n");
		perror("start_agent");
		return(AGENTD_STATUS_RUNERR);
	}

	childpid = fork();
	if (childpid < 0) {        /* Error occurred */
		fprintf(stderr, "start_agent: fork failed\n");
		perror("start_agent");

		close(pipeout[0]);
		close(pipeout[1]);
		close(pipeerr[0]);
		close(pipeerr[1]);

		return(AGENTD_STATUS_RUNERR);
	}

	/*
	 * Exec command from newly forked process
	 */
	if (childpid == 0) {       /* Child process */
		int   fdin;
		int   argc;
		int   rc;

	   /****
		event_exit_();
	    ****/

		if (WorkDir) chdir(WorkPath);

		/* stdin */
		fdin = open("/dev/null", O_RDONLY);
		dup2(fdin, 0);
		close(fdin);

		/* stdout */
		rc = dup2(pipeout[1], 1);
		close(pipeout[0]);
		close(pipeout[1]);
		if (rc < 0) printf("start_agent: couldn't dup pipe as stdout");

		/* stderr */
		rc = dup2(pipeerr[1], 2);
		close(pipeerr[0]);
		close(pipeerr[1]);
		if (rc < 0) printf("start_agent: couldn't dup pipe as stderr");

		/* Create a new process group */
		setpgrp();

		fprintf(stderr,
			"agentd: child proc %d, pgrp %d execing %s\n",
			 getpid(), getpgrp(), cmd);

		execv(cmdpath, argv);

		/* If exec returns it means an error occurred */
		close(0);
		close(1);
		close(2);

		exit(AGENTD_STATUS_RUNERR);
	}

	signal(SIGABRT, SIG_IGN);

	if (Verbose) printf("start_agent: created child process %d\n", childpid);

	/* Report startup status to requester */
	if (areq) {
		areq->status = AGENTD_AGENT_RUNNING;
		areq->pid    = childpid;

		estat.reqseq  = EventSeq(areq->ereq);
		estat.tag     = areq->ereq.tag;
		estat.reqtype = AGENTD_CTL_START;
		estat.result  = childpid;
		estat.rstatus = AGENTD_STATUS_OK;
		SEND(EventFrom(areq->ereq), AGENTD_STAT, estat);
	}

	gethostname(hostname, sizeof(hostname));

	/* Set up stderr */
	elogerr.head.to = EVENT_BCAST_NOTME;
	elogerr.type    = AGENTD_LOG_STDERR;
	elogerr.flags   = pipeerr[0];
	elogerr.pid     = childpid;
	strcpy(elogerr.hostname, hostname);
	strcpy(elogerr.program,  cmd);

	/* Start reader thread and wait for it to initialize */
	if (Verbose) printf("start_agent: starting reader thread for stderr\n");
	mp_task(reader, &elogerr, 0);
	mp_decsema(ReadInit);

	/* Broadcast a message */
	sprintf(elogerr.msg, "agentd: agent started as pid %d\n", childpid);
	SEND(EVENT_BCAST_NOTME, AGENTD_LOG, elogerr);

	/* Now do the same for stdout */
	elogout.head.to = EVENT_BCAST_NOTME;
	elogout.type    = AGENTD_LOG_STDOUT;
	elogout.flags   = pipeout[0];
	elogout.pid     = childpid;
	strcpy(elogout.hostname, hostname);
	strcpy(elogout.program,  cmd);

	if (Verbose) printf("start_agent: starting reader thread for stdout\n");
	mp_task(reader, &elogout, 0);
	mp_decsema(ReadInit);

	/* Wait for child (agent) process to exit */
	if (Verbose) printf("start_agent: waiting for agent proc %d\n", childpid);
	pid = waitpid(childpid, &exitstat, 0);
	if (pid <= 0) {
		perror("start_agent: waitpid");
	}

	if (WIFSIGNALED(exitstat))
	   sprintf(msg, "agent %d exited on signal %s with rc %d",
		childpid,
		signame(WTERMSIG(exitstat)),
		WEXITSTATUS(exitstat));
	else
	   sprintf(msg, "agent %d exited normally with rc %d",
		childpid, WEXITSTATUS(exitstat));

	if (Verbose) printf("start_agent: %s\n", msg);

	/* Set exit and write to pipe to wake up readers */
	mp_lock(Exitlock);

	Exit = childpid;

	sleep(5); /* delay to let things quiesce */

	write(pipeout[1], EofStr, strlen(EofStr)+1);
	write(pipeerr[1], EofStr, strlen(EofStr)+1);

	if (Verbose) printf("start_agent: %d.%d waiting for 2 %d.readers to exit\n", getpid(), mp_gettid(), childpid);
	mp_decsema(Exitwait);
	if (Verbose) printf("start_agent: %d.%d waiting for 1 %d.reader to exit\n", getpid(), mp_gettid(), childpid);
	mp_decsema(Exitwait);
	if (Verbose) printf("start_agent: %d.%d all %d.readers exited\n", getpid(), mp_gettid(), childpid);

	Exit = 0;
	mp_unlock(Exitlock);

	/* Broadcast a message */
	sprintf(elogerr.msg, "agentd: %s\n", msg);
	SEND(EVENT_BCAST_NOTME, AGENTD_LOG, elogerr);

	close(pipeout[0]);
	close(pipeout[1]);
	close(pipeerr[0]);
	close(pipeerr[1]);

	/*
	 * Report exit status back to requester
	 */
	if (areq) {
		areq->status = AGENTD_AGENT_EXIT;

		estat.result  = exitstat;
		estat.rstatus = AGENTD_AGENT_EXIT;
		SEND(EventFrom(areq->ereq), AGENTD_STAT, estat);
	}

	if (retpid) *retpid = childpid;

	return(AGENTD_STATUS_OK);
}