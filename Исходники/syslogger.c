/*
 * Main entry point for syslogger process
 * argc/argv parameters are valid only in EXEC_BACKEND case.
 */
NON_EXEC_STATIC void
SysLoggerMain(int argc, char *argv[])
{
#ifndef WIN32
	char		logbuffer[READ_BUF_SIZE];
	int			bytes_in_logbuffer = 0;
#endif
	char	   *currentLogDir;
	char	   *currentLogFilename;
	int			currentLogRotationAge;

	IsUnderPostmaster = true;	/* we are a postmaster subprocess now */

	MyProcPid = getpid();		/* reset MyProcPid */

#ifdef EXEC_BACKEND
	syslogger_parseArgs(argc, argv);
#endif   /* EXEC_BACKEND */

	am_syslogger = true;

	init_ps_display("logger process", "", "", "");

	/*
	 * If we restarted, our stderr is already redirected into our own input
	 * pipe.  This is of course pretty useless, not to mention that it
	 * interferes with detecting pipe EOF.	Point stderr to /dev/null. This
	 * assumes that all interesting messages generated in the syslogger will
	 * come through elog.c and will be sent to write_syslogger_file.
	 */
	if (redirection_done)
	{
		int			fd = open(DEVNULL, O_WRONLY, 0);

		/*
		 * The closes might look redundant, but they are not: we want to be
		 * darn sure the pipe gets closed even if the open failed.	We can
		 * survive running with stderr pointing nowhere, but we can't afford
		 * to have extra pipe input descriptors hanging around.
		 */
		close(fileno(stdout));
		close(fileno(stderr));
		if (fd != -1)
		{
			dup2(fd, fileno(stdout));
			dup2(fd, fileno(stderr));
			close(fd);
		}
	}

	/* Syslogger's own stderr can't be the syslogPipe, so set it back to
	 * text mode if we didn't just close it. 
	 * (It was set to binary in SubPostmasterMain).
	 */
#ifdef WIN32
	else
		_setmode(_fileno(stderr),_O_TEXT);
#endif

	/*
	 * Also close our copy of the write end of the pipe.  This is needed to
	 * ensure we can detect pipe EOF correctly.  (But note that in the restart
	 * case, the postmaster already did this.)
	 */
#ifndef WIN32
	if (syslogPipe[1] >= 0)
		close(syslogPipe[1]);
	syslogPipe[1] = -1;
#else
	if (syslogPipe[1])
		CloseHandle(syslogPipe[1]);
	syslogPipe[1] = 0;
#endif

	/*
	 * If possible, make this process a group leader, so that the postmaster
	 * can signal any child processes too.  (syslogger probably never has
	 * any child processes, but for consistency we make all postmaster
	 * child processes do this.)
	 */
#ifdef HAVE_SETSID
	if (setsid() < 0)
		elog(FATAL, "setsid() failed: %m");
#endif

	/*
	 * Properly accept or ignore signals the postmaster might send us
	 *
	 * Note: we ignore all termination signals, and instead exit only when all
	 * upstream processes are gone, to ensure we don't miss any dying gasps of
	 * broken backends...
	 */

	pqsignal(SIGHUP, sigHupHandler);	/* set flag to read config file */
	pqsignal(SIGINT, SIG_IGN);
	pqsignal(SIGTERM, SIG_IGN);
	pqsignal(SIGQUIT, SIG_IGN);
	pqsignal(SIGALRM, SIG_IGN);
	pqsignal(SIGPIPE, SIG_IGN);
	pqsignal(SIGUSR1, sigUsr1Handler);	/* request log rotation */
	pqsignal(SIGUSR2, SIG_IGN);

	/*
	 * Reset some signals that are accepted by postmaster but not here
	 */
	pqsignal(SIGCHLD, SIG_DFL);
	pqsignal(SIGTTIN, SIG_DFL);
	pqsignal(SIGTTOU, SIG_DFL);
	pqsignal(SIGCONT, SIG_DFL);
	pqsignal(SIGWINCH, SIG_DFL);

	PG_SETMASK(&UnBlockSig);

#ifdef WIN32
	/* Fire up separate data transfer thread */
	InitializeCriticalSection(&sysloggerSection);
	EnterCriticalSection(&sysloggerSection);

	{
		unsigned int tid;

		threadHandle = (HANDLE) _beginthreadex(0, 0, pipeThread, 0, 0, &tid);
	}
#endif   /* WIN32 */

	/* remember active logfile parameters */
	currentLogDir = pstrdup(Log_directory);
	currentLogFilename = pstrdup(Log_filename);
	currentLogRotationAge = Log_RotationAge;
	/* set next planned rotation time */
	set_next_rotation_time();

	/* main worker loop */
	for (;;)
	{
		bool		time_based_rotation = false;

#ifndef WIN32
		int			bytesRead;
		int			rc;
		fd_set		rfds;
		struct timeval timeout;
#endif

		if (got_SIGHUP)
		{
			got_SIGHUP = false;
			ProcessConfigFile(PGC_SIGHUP);

			/*
			 * Check if the log directory or filename pattern changed in
			 * postgresql.conf. If so, force rotation to make sure we're
			 * writing the logfiles in the right place.
			 */
			if (strcmp(Log_directory, currentLogDir) != 0)
			{
				pfree(currentLogDir);
				currentLogDir = pstrdup(Log_directory);
				rotation_requested = true;
			}
			if (strcmp(Log_filename, currentLogFilename) != 0)
			{
				pfree(currentLogFilename);
				currentLogFilename = pstrdup(Log_filename);
				rotation_requested = true;
			}

			/*
			 * If rotation time parameter changed, reset next rotation time,
			 * but don't immediately force a rotation.
			 */
			if (currentLogRotationAge != Log_RotationAge)
			{
				currentLogRotationAge = Log_RotationAge;
				set_next_rotation_time();
			}
		}

		if (!rotation_requested && Log_RotationAge > 0)
		{
			/* Do a logfile rotation if it's time */
			pg_time_t	now = time(NULL);

			if (now >= next_rotation_time)
				rotation_requested = time_based_rotation = true;
		}

		if (!rotation_requested && Log_RotationSize > 0)
		{
			/* Do a rotation if file is too big */
			if (ftell(syslogFile) >= Log_RotationSize * 1024L)
				rotation_requested = true;
		}

		if (rotation_requested)
			logfile_rotate(time_based_rotation);

#ifndef WIN32

		/*
		 * Wait for some data, timing out after 1 second
		 */
		FD_ZERO(&rfds);
		FD_SET(syslogPipe[0], &rfds);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		rc = select(syslogPipe[0] + 1, &rfds, NULL, NULL, &timeout);

		if (rc < 0)
		{
			if (errno != EINTR)
				ereport(LOG,
						(errcode_for_socket_access(),
						 errmsg("select() failed in logger process: %m")));
		}
		else if (rc > 0 && FD_ISSET(syslogPipe[0], &rfds))
		{
			bytesRead = piperead(syslogPipe[0],
								 logbuffer + bytes_in_logbuffer,
								 sizeof(logbuffer) - bytes_in_logbuffer);
			if (bytesRead < 0)
			{
				if (errno != EINTR)
					ereport(LOG,
							(errcode_for_socket_access(),
							 errmsg("could not read from logger pipe: %m")));
			}
			else if (bytesRead > 0)
			{
				bytes_in_logbuffer += bytesRead;
				process_pipe_input(logbuffer, &bytes_in_logbuffer);
				continue;
			}
			else
			{
				/*
				 * Zero bytes read when select() is saying read-ready means
				 * EOF on the pipe: that is, there are no longer any processes
				 * with the pipe write end open.  Therefore, the postmaster
				 * and all backends are shut down, and we are done.
				 */
				pipe_eof_seen = true;

				/* if there's any data left then force it out now */
				flush_pipe_input(logbuffer, &bytes_in_logbuffer);
			}
		}
#else							/* WIN32 */

		/*
		 * On Windows we leave it to a separate thread to transfer data and
		 * detect pipe EOF.  The main thread just wakes up once a second to
		 * check for SIGHUP and rotation conditions.
		 *
		 * Server code isn't generally thread-safe, so we ensure that only
		 * one of the threads is active at a time by entering the critical
		 * section whenever we're not sleeping.
		 */
		LeaveCriticalSection(&sysloggerSection);

		pg_usleep(1000000L);

		EnterCriticalSection(&sysloggerSection);
#endif   /* WIN32 */

		if (pipe_eof_seen)
		{
			ereport(LOG,
					(errmsg("logger shutting down")));

			/*
			 * Normal exit from the syslogger is here.	Note that we
			 * deliberately do not close syslogFile before exiting; this is to
			 * allow for the possibility of elog messages being generated
			 * inside proc_exit.  Regular exit() will take care of flushing
			 * and closing stdio channels.
			 */
			proc_exit(0);
		}
	}
}