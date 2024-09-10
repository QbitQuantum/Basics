int
main(int argc, char **argv)
#endif	/* WIN32 */
{
#ifdef	WIN32
	struct arg_param *p = (struct arg_param *)pv;
	int      		argc;
	char			**argv;
	SERVICE_STATUS          ss;
#endif	/* WIN32 */
	char *name = NULL;
	struct tpp_config conf;
	int rpp_fd;
	char *pc;
	int numthreads;
	char lockfile[MAXPATHLEN + 1];
	char path_log[MAXPATHLEN + 1];
	char svr_home[MAXPATHLEN + 1];
	char *log_file = 0;
	char *host;
	int port;
	char *routers = NULL;
	int c, i, rc;
	extern char *optarg;
	int	are_primary;
	int	num_var_env;
#ifndef WIN32
	struct sigaction act;
	struct sigaction oact;
#endif

#ifndef WIN32
	/*the real deal or just pbs_version and exit*/

	execution_mode(argc, argv);
#endif

	/* As a security measure and to make sure all file descriptors	*/
	/* are available to us,  close all above stderr			*/
#ifdef WIN32
	_fcloseall();
#else
	i = sysconf(_SC_OPEN_MAX);
	while (--i > 2)
		(void)close(i); /* close any file desc left open by parent */
#endif

	/* If we are not run with real and effective uid of 0, forget it */
#ifdef WIN32
	argc = p->argc;
	argv = p->argv;

	ZeroMemory(&ss, sizeof(ss));
	ss.dwCheckPoint = 0;
	ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState = g_dwCurrentState;
	ss.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	ss.dwWaitHint = 6000;

	if (g_ssHandle != 0)
		SetServiceStatus(g_ssHandle, &ss);

	if (!isAdminPrivilege(getlogin())) {
		fprintf(stderr, "%s: Must be run by root\n", argv[0]);
		return (2);
	}

#else
	if ((getuid() != 0) || (geteuid() != 0)) {
		fprintf(stderr, "%s: Must be run by root\n", argv[0]);
		return (2);
	}
#endif	/* WIN32 */

	/* set standard umask */
#ifndef WIN32
	umask(022);
#endif

	/* load the pbs conf file */
	if (pbs_loadconf(0) == 0) {
		fprintf(stderr, "%s: Configuration error\n", argv[0]);
		return (1);
	}

	umask(022);

#ifdef	WIN32
	save_env();
#endif
	/* The following is code to reduce security risks                */
	/* start out with standard umask, system resource limit infinite */
	if ((num_var_env = setup_env(pbs_conf.pbs_environment)) == -1) {
#ifdef	WIN32
		g_dwCurrentState = SERVICE_STOPPED;
		ss.dwCurrentState = g_dwCurrentState;
		ss.dwWin32ExitCode = ERROR_INVALID_ENVIRONMENT;
		if (g_ssHandle != 0) SetServiceStatus(g_ssHandle, &ss);
		return (1);
#else
		exit(1);
#endif	/* WIN32 */
	}

#ifndef WIN32
	i = getgid();
	(void)setgroups(1, (gid_t *)&i);	/* secure suppl. groups */
#endif

	log_event_mask = &pbs_conf.pbs_comm_log_events;
	tpp_set_logmask(*log_event_mask);

#ifdef WIN32
	winsock_init();
#endif

	routers = pbs_conf.pbs_comm_routers;
	numthreads = pbs_conf.pbs_comm_threads;

	server_host[0] = '\0';
	if (pbs_conf.pbs_comm_name) {
		name = pbs_conf.pbs_comm_name;
		host = tpp_parse_hostname(name, &port);
		if (host)
			snprintf(server_host, sizeof(server_host), "%s", host);
		free(host);
		host = NULL;
	} else if (pbs_conf.pbs_leaf_name) {
		char *endp;

		snprintf(server_host, sizeof(server_host), "%s", pbs_conf.pbs_leaf_name);
		endp = strchr(server_host, ','); /* find the first name */
		if (endp)
			*endp = '\0';
		endp = strchr(server_host, ':'); /* cut out the port */
		if (endp)
			*endp = '\0';
		name = server_host;
	} else {
		if (gethostname(server_host, (sizeof(server_host) - 1)) == -1) {
#ifndef WIN32
			sprintf(log_buffer, "Could not determine my hostname, errno=%d", errno);
#else
			sprintf(log_buffer, "Could not determine my hostname, errno=%d", WSAGetLastError());
#endif
			fprintf(stderr, "%s\n", log_buffer);
			return (1);
		}
		if ((get_fullhostname(server_host, server_host, (sizeof(server_host) - 1)) == -1)) {
			sprintf(log_buffer, "Could not determine my hostname");
			fprintf(stderr, "%s\n", log_buffer);
			return (1);
		}
		name = server_host;
	}
	if (server_host[0] == '\0') {
		sprintf(log_buffer, "Could not determine server host");
		fprintf(stderr, "%s\n", log_buffer);
		return (1);
	}

	while ((c = getopt(argc, argv, "r:t:e:N")) != -1) {
		switch (c) {
			case 'e': *log_event_mask = strtol(optarg, NULL, 0);
				break;
			case 'r':
				routers = optarg;
				break;
			case 't':
				numthreads = atol(optarg);
				if (numthreads == -1) {
					usage(argv[0]);
					return (1);
				}
				break;
			case 'N':
				stalone = 1;
				break;
			default:
				usage(argv[0]);
				return (1);
		}
	}

	(void)strcpy(daemonname, "Comm@");
	(void)strcat(daemonname, name);
	if ((pc = strchr(daemonname, (int)'.')) != NULL)
		*pc = '\0';

	if(set_msgdaemonname(daemonname)) {
		fprintf(stderr, "Out of memory\n");
		return 1;
	}

	(void) snprintf(path_log, sizeof(path_log), "%s/%s", pbs_conf.pbs_home_path, PBS_COMM_LOGDIR);
#ifdef WIN32
	/*
	 * let SCM wait 10 seconds for log_open() to complete
	 * as it does network interface query which can take time
	 */

	ss.dwCheckPoint++;
	ss.dwWaitHint = 60000;
	if (g_ssHandle != 0) SetServiceStatus(g_ssHandle, &ss);
#endif
	(void) log_open(log_file, path_log);

	/* set pbs_comm's process limits */
	set_limits(); /* set_limits can call log_record, so call only after opening log file */

	/* set tcp function pointers */
	set_tpp_funcs(log_tppmsg);

	(void) snprintf(svr_home, sizeof(svr_home), "%s/%s", pbs_conf.pbs_home_path, PBS_SVR_PRIVATE);
	if (chdir(svr_home) != 0) {
		(void) sprintf(log_buffer, msg_init_chdir, svr_home);
		log_err(-1, __func__, log_buffer);
		return (1);
	}

	(void) sprintf(lockfile, "%s/%s/comm.lock", pbs_conf.pbs_home_path, PBS_SVR_PRIVATE);
	if ((are_primary = are_we_primary()) == FAILOVER_SECONDARY) {
		strcat(lockfile, ".secondary");
	} else if (are_primary == FAILOVER_CONFIG_ERROR) {
		sprintf(log_buffer, "Failover configuration error");
		log_err(-1, __func__, log_buffer);
#ifdef WIN32
		g_dwCurrentState = SERVICE_STOPPED;
		ss.dwCurrentState = g_dwCurrentState;
		ss.dwWin32ExitCode = ERROR_SERVICE_NOT_ACTIVE;
		if (g_ssHandle != 0) SetServiceStatus(g_ssHandle, &ss);
#endif
		return (3);
	}

	if ((lockfds = open(lockfile, O_CREAT | O_WRONLY, 0600)) < 0) {
		(void) sprintf(log_buffer, "pbs_comm: unable to open lock file");
		log_err(errno, __func__, log_buffer);
		return (1);
	}

	if ((host = tpp_parse_hostname(name, &port)) == NULL) {
		sprintf(log_buffer, "Out of memory parsing leaf name");
		log_err(errno, __func__, log_buffer);
		return (1);
	}

	rc = 0;
	if (pbs_conf.auth_method == AUTH_RESV_PORT) {
		rc = set_tpp_config(&pbs_conf, &conf, host, port, routers, pbs_conf.pbs_use_compression,
				TPP_AUTH_RESV_PORT, NULL, NULL);
	} else {
		/* for all non-resv-port based authentication use a callback from TPP */
		rc = set_tpp_config(&pbs_conf, &conf, host, port, routers, pbs_conf.pbs_use_compression,
				TPP_AUTH_EXTERNAL, get_ext_auth_data, validate_ext_auth_data);
	}
	if (rc == -1) {
		(void) sprintf(log_buffer, "Error setting TPP config");
		log_err(-1, __func__, log_buffer);
		return (1);
	}
	free(host);

	i = 0;
	if (conf.routers) {
		while (conf.routers[i]) {
			sprintf(log_buffer, "Router[%d]:%s", i, conf.routers[i]);
			fprintf(stdout, "%s\n", log_buffer);
			log_event(PBSEVENT_SYSTEM | PBSEVENT_FORCE, PBS_EVENTCLASS_SERVER, LOG_INFO, msg_daemonname, log_buffer);
			i++;
		}
	}

#ifndef DEBUG
#ifndef WIN32
	if (stalone != 1)
		go_to_background();
#endif
#endif


#ifdef WIN32
	ss.dwCheckPoint = 0;
	g_dwCurrentState = SERVICE_RUNNING;
	ss.dwCurrentState = g_dwCurrentState;
	if (g_ssHandle != 0) SetServiceStatus(g_ssHandle, &ss);
#endif

	if (already_forked == 0)
		lock_out(lockfds, F_WRLCK);

	/* go_to_backgroud call creates a forked process,
	 * thus print/log pid only after go_to_background()
	 * has been called
	 */
	sprintf(log_buffer, "%s ready (pid=%d), Proxy Name:%s, Threads:%d", argv[0], getpid(), conf.node_name, numthreads);
	fprintf(stdout, "%s\n", log_buffer);
	log_event(PBSEVENT_SYSTEM | PBSEVENT_FORCE, PBS_EVENTCLASS_SERVER, LOG_INFO, msg_daemonname, log_buffer);

#ifndef DEBUG
	pbs_close_stdfiles();
#endif

#ifdef WIN32
	signal(SIGINT, stop_me);
	signal(SIGTERM, stop_me);
#else
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = hup_me;
	if (sigaction(SIGHUP, &act, &oact) != 0) {
		log_err(errno, __func__, "sigaction for HUP");
		return (2);
	}
	act.sa_handler = stop_me;
	if (sigaction(SIGINT, &act, &oact) != 0) {
		log_err(errno, __func__, "sigaction for INT");
		return (2);
	}
	if (sigaction(SIGTERM, &act, &oact) != 0) {
		log_err(errno, __func__, "sigactin for TERM");
		return (2);
	}
	if (sigaction(SIGQUIT, &act, &oact) != 0) {
		log_err(errno, __func__, "sigactin for QUIT");
		return (2);
	}
#ifdef SIGSHUTDN
	if (sigaction(SIGSHUTDN, &act, &oact) != 0) {
		log_err(errno, __func__, "sigactin for SHUTDN");
		return (2);
	}
#endif	/* SIGSHUTDN */

	act.sa_handler = SIG_IGN;
	if (sigaction(SIGPIPE, &act, &oact) != 0) {
		log_err(errno, __func__, "sigaction for PIPE");
		return (2);
	}
	if (sigaction(SIGUSR1, &act, &oact) != 0) {
		log_err(errno, __func__, "sigaction for USR1");
		return (2);
	}
	if (sigaction(SIGUSR2, &act, &oact) != 0) {
		log_err(errno, __func__, "sigaction for USR2");
		return (2);
	}
#endif 	/* WIN32 */

	conf.node_type = TPP_ROUTER_NODE;
	conf.numthreads = numthreads;

	if ((rpp_fd = tpp_init_router(&conf)) == -1) {
		log_err(-1, __func__, "tpp init failed\n");
		return 1;
	}

	/* Protect from being killed by kernel */
	daemon_protect(0, PBS_DAEMON_PROTECT_ON);

	/* go in a while loop */
	while (get_out == 0) {

		if (hupped == 1) {
			struct pbs_config pbs_conf_bak;
			int new_logevent;

			hupped = 0; /* reset back */
			memcpy(&pbs_conf_bak, &pbs_conf, sizeof(struct pbs_config));

			if (pbs_loadconf(1) == 0) {
				log_tppmsg(LOG_CRIT, NULL, "Configuration error, ignoring");
				memcpy(&pbs_conf, &pbs_conf_bak, sizeof(struct pbs_config));
			} else {
				/* restore old pbs.conf */
				new_logevent = pbs_conf.pbs_comm_log_events;
				memcpy(&pbs_conf, &pbs_conf_bak, sizeof(struct pbs_config));
				pbs_conf.pbs_comm_log_events = new_logevent;
				log_tppmsg(LOG_INFO, NULL, "Processed SIGHUP");

				log_event_mask = &pbs_conf.pbs_comm_log_events;
				tpp_set_logmask(*log_event_mask);
			}
		}

		sleep(3);
	}

	tpp_router_shutdown();

	log_event(PBSEVENT_SYSTEM | PBSEVENT_FORCE, PBS_EVENTCLASS_SERVER, LOG_NOTICE, msg_daemonname, "Exiting");
	log_close(1);

	lock_out(lockfds, F_UNLCK);	/* unlock  */
	(void)close(lockfds);
	(void)unlink(lockfile);

	return 0;
}