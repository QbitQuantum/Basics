int
main(int argc, char *argv[])
{
	/* Scratch variables... */
	int c;
	pid_t	oldpid;
	size_t i;
	struct sigaction action;
#ifdef HAVE_GETPWNAM
	struct passwd *pwd = NULL;
#endif /* HAVE_GETPWNAM */

	/* For initialising the address info structures */
	/* static so it can get very big without overflowing the stack */
	static struct addrinfo hints[MAX_INTERFACES];
	static const char *nodes[MAX_INTERFACES];
	const char *udp_port = 0;
	const char *tcp_port = 0;

	const char *configfile = CONFIGFILE;

	char* argv0 = (argv0 = strrchr(argv[0], '/')) ? argv0 + 1 : argv[0];

	log_init(argv0);

	/* Initialize the server handler... */
	memset(&nsd, 0, sizeof(struct nsd));
	nsd.region      = region_create(xalloc, free);
	nsd.dbfile	= 0;
	nsd.pidfile	= 0;
	nsd.server_kind = NSD_SERVER_MAIN;

	for (i = 0; i < MAX_INTERFACES; i++) {
		memset(&hints[i], 0, sizeof(hints[i]));
		hints[i].ai_family = DEFAULT_AI_FAMILY;
		hints[i].ai_flags = AI_PASSIVE;
		nodes[i] = NULL;
	}

	nsd.identity	= 0;
	nsd.version	= VERSION;
	nsd.username	= 0;
	nsd.chrootdir	= 0;
	nsd.nsid 	= NULL;
	nsd.nsid_len 	= 0;

	nsd.child_count = 0;
	nsd.maximum_tcp_count = 0;
	nsd.current_tcp_count = 0;
	nsd.grab_ip6_optional = 0;
	nsd.file_rotation_ok = 0;

	/* Set up our default identity to gethostname(2) */
	if (gethostname(hostname, MAXHOSTNAMELEN) == 0) {
		nsd.identity = hostname;
	} else {
		log_msg(LOG_ERR,
			"failed to get the host name: %s - using default identity",
			strerror(errno));
		nsd.identity = IDENTITY;
	}


	/* Parse the command line... */
	while ((c = getopt(argc, argv, "46a:c:df:hi:I:l:N:n:P:p:s:u:t:X:V:v"
#ifndef NDEBUG /* <mattthijs> only when configured with --enable-checking */
		"F:L:"
#endif /* NDEBUG */
		)) != -1) {
		switch (c) {
		case '4':
			for (i = 0; i < MAX_INTERFACES; ++i) {
				hints[i].ai_family = AF_INET;
			}
			break;
		case '6':
#ifdef INET6
			for (i = 0; i < MAX_INTERFACES; ++i) {
				hints[i].ai_family = AF_INET6;
			}
#else /* !INET6 */
			error("IPv6 support not enabled.");
#endif /* INET6 */
			break;
		case 'a':
			if (nsd.ifs < MAX_INTERFACES) {
				nodes[nsd.ifs] = optarg;
				++nsd.ifs;
			} else {
				error("too many interfaces ('-a') specified.");
			}
			break;
		case 'c':
			configfile = optarg;
			break;
		case 'd':
			nsd.debug = 1;
			break;
		case 'f':
			nsd.dbfile = optarg;
			break;
		case 'h':
			usage();
			exit(0);
		case 'i':
			nsd.identity = optarg;
			break;
		case 'I':
			if (nsd.nsid_len != 0) {
				/* can only be given once */
				break;
			}
			if (strncasecmp(optarg, "ascii_", 6) == 0) {
				nsd.nsid = xalloc(strlen(optarg+6));
				nsd.nsid_len = strlen(optarg+6);
				memmove(nsd.nsid, optarg+6, nsd.nsid_len);
			} else {
				if (strlen(optarg) % 2 != 0) {
					error("the NSID must be a hex string of an even length.");
				}
				nsd.nsid = xalloc(strlen(optarg) / 2);
				nsd.nsid_len = strlen(optarg) / 2;
				if (hex_pton(optarg, nsd.nsid, nsd.nsid_len) == -1) {
					error("hex string cannot be parsed '%s' in NSID.", optarg);
				}
			}
			break;
		case 'l':
			nsd.log_filename = optarg;
			break;
		case 'N':
			i = atoi(optarg);
			if (i <= 0) {
				error("number of child servers must be greater than zero.");
			} else {
				nsd.child_count = i;
			}
			break;
		case 'n':
			i = atoi(optarg);
			if (i <= 0) {
				error("number of concurrent TCP connections must greater than zero.");
			} else {
				nsd.maximum_tcp_count = i;
			}
			break;
		case 'P':
			nsd.pidfile = optarg;
			break;
		case 'p':
			if (atoi(optarg) == 0) {
				error("port argument must be numeric.");
			}
			tcp_port = optarg;
			udp_port = optarg;
			break;
		case 's':
#ifdef BIND8_STATS
			nsd.st.period = atoi(optarg);
#else /* !BIND8_STATS */
			error("BIND 8 statistics not enabled.");
#endif /* BIND8_STATS */
			break;
		case 't':
#ifdef HAVE_CHROOT
			nsd.chrootdir = optarg;
#else /* !HAVE_CHROOT */
			error("chroot not supported on this platform.");
#endif /* HAVE_CHROOT */
			break;
		case 'u':
			nsd.username = optarg;
			break;
		case 'V':
			verbosity = atoi(optarg);
			break;
		case 'v':
			version();
			/* version exits */
#ifndef NDEBUG
		case 'F':
			sscanf(optarg, "%x", &nsd_debug_facilities);
			break;
		case 'L':
			sscanf(optarg, "%d", &nsd_debug_level);
			break;
#endif /* NDEBUG */
		case '?':
		default:
			usage();
			exit(1);
		}
	}
	argc -= optind;
	argv += optind;

	/* Commandline parse error */
	if (argc != 0) {
		usage();
		exit(1);
	}

	if (strlen(nsd.identity) > UCHAR_MAX) {
		error("server identity too long (%u characters)",
		      (unsigned) strlen(nsd.identity));
	}
	if(!tsig_init(nsd.region))
		error("init tsig failed");

	/* Read options */
	nsd.options = nsd_options_create(region_create_custom(xalloc, free,
		DEFAULT_CHUNK_SIZE, DEFAULT_LARGE_OBJECT_SIZE,
		DEFAULT_INITIAL_CLEANUP_SIZE, 1));
	if(!parse_options_file(nsd.options, configfile, NULL, NULL)) {
		error("could not read config: %s\n", configfile);
	}
	if(!parse_zone_list_file(nsd.options)) {
		error("could not read zonelist file %s\n",
			nsd.options->zonelistfile);
	}
	if(nsd.options->do_ip4 && !nsd.options->do_ip6) {
		for (i = 0; i < MAX_INTERFACES; ++i) {
			hints[i].ai_family = AF_INET;
		}
	}
#ifdef INET6
	if(nsd.options->do_ip6 && !nsd.options->do_ip4) {
		for (i = 0; i < MAX_INTERFACES; ++i) {
			hints[i].ai_family = AF_INET6;
		}
	}
#endif /* INET6 */
	if(nsd.options->ip_addresses)
	{
		ip_address_option_t* ip = nsd.options->ip_addresses;
		while(ip) {
			if (nsd.ifs < MAX_INTERFACES) {
				nodes[nsd.ifs] = ip->address;
				++nsd.ifs;
			} else {
				error("too many interfaces ('-a' + "
				      "'ip-address:') specified.");
				break;
			}
			ip = ip->next;
		}
	}
	if (verbosity == 0)
		verbosity = nsd.options->verbosity;
#ifndef NDEBUG
	if (nsd_debug_level > 0 && verbosity == 0)
		verbosity = nsd_debug_level;
#endif /* NDEBUG */
	if(nsd.options->debug_mode) nsd.debug=1;
	if(!nsd.dbfile)
	{
		if(nsd.options->database)
			nsd.dbfile = nsd.options->database;
		else
			nsd.dbfile = DBFILE;
	}
	if(!nsd.pidfile)
	{
		if(nsd.options->pidfile)
			nsd.pidfile = nsd.options->pidfile;
		else
			nsd.pidfile = PIDFILE;
	}
	if(strcmp(nsd.identity, hostname)==0 || strcmp(nsd.identity,IDENTITY)==0)
	{
		if(nsd.options->identity)
			nsd.identity = nsd.options->identity;
	}
	if (nsd.options->logfile && !nsd.log_filename) {
		nsd.log_filename = nsd.options->logfile;
	}
	if(nsd.child_count == 0) {
		nsd.child_count = nsd.options->server_count;
	}
	if(nsd.maximum_tcp_count == 0) {
		nsd.maximum_tcp_count = nsd.options->tcp_count;
	}
	nsd.tcp_timeout = nsd.options->tcp_timeout;
	nsd.tcp_query_count = nsd.options->tcp_query_count;
	nsd.ipv4_edns_size = nsd.options->ipv4_edns_size;
	nsd.ipv6_edns_size = nsd.options->ipv6_edns_size;

	if(udp_port == 0)
	{
		if(nsd.options->port != 0) {
			udp_port = nsd.options->port;
			tcp_port = nsd.options->port;
		} else {
			udp_port = UDP_PORT;
			tcp_port = TCP_PORT;
		}
	}
#ifdef BIND8_STATS
	if(nsd.st.period == 0) {
		nsd.st.period = nsd.options->statistics;
	}
#endif /* BIND8_STATS */
#ifdef HAVE_CHROOT
	if(nsd.chrootdir == 0) nsd.chrootdir = nsd.options->chroot;
#ifdef CHROOTDIR
	/* if still no chrootdir, fallback to default */
	if(nsd.chrootdir == 0) nsd.chrootdir = CHROOTDIR;
#endif /* CHROOTDIR */
#endif /* HAVE_CHROOT */
	if(nsd.username == 0) {
		if(nsd.options->username) nsd.username = nsd.options->username;
		else nsd.username = USER;
	}
	if(nsd.options->zonesdir && nsd.options->zonesdir[0]) {
		if(chdir(nsd.options->zonesdir)) {
			error("cannot chdir to '%s': %s",
				nsd.options->zonesdir, strerror(errno));
		}
		DEBUG(DEBUG_IPC,1, (LOG_INFO, "changed directory to %s",
			nsd.options->zonesdir));
	}

	/* EDNS0 */
	edns_init_data(&nsd.edns_ipv4, nsd.options->ipv4_edns_size);
#if defined(INET6)
#if defined(IPV6_USE_MIN_MTU) || defined(IPV6_MTU)
	edns_init_data(&nsd.edns_ipv6, nsd.options->ipv6_edns_size);
#else /* no way to set IPV6 MTU, send no bigger than that. */
	if (nsd.options->ipv6_edns_size < IPV6_MIN_MTU)
		edns_init_data(&nsd.edns_ipv6, nsd.options->ipv6_edns_size);
	else
		edns_init_data(&nsd.edns_ipv6, IPV6_MIN_MTU);
#endif /* IPV6 MTU) */
#endif /* defined(INET6) */

	if (nsd.nsid_len == 0 && nsd.options->nsid) {
		if (strlen(nsd.options->nsid) % 2 != 0) {
			error("the NSID must be a hex string of an even length.");
		}
		nsd.nsid = xalloc(strlen(nsd.options->nsid) / 2);
		nsd.nsid_len = strlen(nsd.options->nsid) / 2;
		if (hex_pton(nsd.options->nsid, nsd.nsid, nsd.nsid_len) == -1) {
			error("hex string cannot be parsed '%s' in NSID.", nsd.options->nsid);
		}
	}
	edns_init_nsid(&nsd.edns_ipv4, nsd.nsid_len);
#if defined(INET6)
	edns_init_nsid(&nsd.edns_ipv6, nsd.nsid_len);
#endif /* defined(INET6) */

	/* Number of child servers to fork.  */
	nsd.children = (struct nsd_child *) region_alloc_array(
		nsd.region, nsd.child_count, sizeof(struct nsd_child));
	for (i = 0; i < nsd.child_count; ++i) {
		nsd.children[i].kind = NSD_SERVER_BOTH;
		nsd.children[i].pid = -1;
		nsd.children[i].child_fd = -1;
		nsd.children[i].parent_fd = -1;
		nsd.children[i].handler = NULL;
		nsd.children[i].need_to_send_STATS = 0;
		nsd.children[i].need_to_send_QUIT = 0;
		nsd.children[i].need_to_exit = 0;
		nsd.children[i].has_exited = 0;
	}

	nsd.this_child = NULL;

	/* We need at least one active interface */
	if (nsd.ifs == 0) {
		nsd.ifs = 1;

		/*
		 * With IPv6 we'd like to open two separate sockets,
		 * one for IPv4 and one for IPv6, both listening to
		 * the wildcard address (unless the -4 or -6 flags are
		 * specified).
		 *
		 * However, this is only supported on platforms where
		 * we can turn the socket option IPV6_V6ONLY _on_.
		 * Otherwise we just listen to a single IPv6 socket
		 * and any incoming IPv4 connections will be
		 * automatically mapped to our IPv6 socket.
		 */
#ifdef INET6
		if (hints[0].ai_family == AF_UNSPEC) {
#ifdef IPV6_V6ONLY
			hints[0].ai_family = AF_INET6;
			hints[1].ai_family = AF_INET;
			nsd.ifs = 2;
			nsd.grab_ip6_optional = 1;
#else /* !IPV6_V6ONLY */
			hints[0].ai_family = AF_INET6;
#endif	/* IPV6_V6ONLY */
		}
#endif /* INET6 */
	}

	/* Set up the address info structures with real interface/port data */
	for (i = 0; i < nsd.ifs; ++i) {
		int r;
		const char* node = NULL;
		const char* service = NULL;

		/* We don't perform name-lookups */
		if (nodes[i] != NULL)
			hints[i].ai_flags |= AI_NUMERICHOST;
		get_ip_port_frm_str(nodes[i], &node, &service);

		hints[i].ai_socktype = SOCK_DGRAM;
		if ((r=getaddrinfo(node, (service?service:udp_port), &hints[i], &nsd.udp[i].addr)) != 0) {
#ifdef INET6
			if(nsd.grab_ip6_optional && hints[0].ai_family == AF_INET6) {
				log_msg(LOG_WARNING, "No IPv6, fallback to IPv4. getaddrinfo: %s",
				r==EAI_SYSTEM?strerror(errno):gai_strerror(r));
				continue;
			}
#endif
			error("cannot parse address '%s': getaddrinfo: %s %s",
				nodes[i]?nodes[i]:"(null)",
				gai_strerror(r),
				r==EAI_SYSTEM?strerror(errno):"");
		}

		hints[i].ai_socktype = SOCK_STREAM;
		if ((r=getaddrinfo(node, (service?service:tcp_port), &hints[i], &nsd.tcp[i].addr)) != 0) {
			error("cannot parse address '%s': getaddrinfo: %s %s",
				nodes[i]?nodes[i]:"(null)",
				gai_strerror(r),
				r==EAI_SYSTEM?strerror(errno):"");
		}
	}

	/* Parse the username into uid and gid */
	nsd.gid = getgid();
	nsd.uid = getuid();
#ifdef HAVE_GETPWNAM
	/* Parse the username into uid and gid */
	if (*nsd.username) {
		if (isdigit((unsigned char)*nsd.username)) {
			char *t;
			nsd.uid = strtol(nsd.username, &t, 10);
			if (*t != 0) {
				if (*t != '.' || !isdigit((unsigned char)*++t)) {
					error("-u user or -u uid or -u uid.gid");
				}
				nsd.gid = strtol(t, &t, 10);
			} else {
				/* Lookup the group id in /etc/passwd */
				if ((pwd = getpwuid(nsd.uid)) == NULL) {
					error("user id %u does not exist.", (unsigned) nsd.uid);
				} else {
					nsd.gid = pwd->pw_gid;
				}
			}
		} else {
			/* Lookup the user id in /etc/passwd */
			if ((pwd = getpwnam(nsd.username)) == NULL) {
				error("user '%s' does not exist.", nsd.username);
			} else {
				nsd.uid = pwd->pw_uid;
				nsd.gid = pwd->pw_gid;
			}
		}
	}
	/* endpwent(); */
#endif /* HAVE_GETPWNAM */

#if defined(HAVE_SSL)
	key_options_tsig_add(nsd.options);
#endif

	append_trailing_slash(&nsd.options->xfrdir, nsd.options->region);
	/* Check relativity of pathnames to chroot */
	if (nsd.chrootdir && nsd.chrootdir[0]) {
		/* existing chrootdir: append trailing slash for strncmp checking */
		append_trailing_slash(&nsd.chrootdir, nsd.region);
		append_trailing_slash(&nsd.options->zonesdir, nsd.options->region);

		/* zonesdir must be absolute and within chroot,
		 * all other pathnames may be relative to zonesdir */
		if (strncmp(nsd.options->zonesdir, nsd.chrootdir, strlen(nsd.chrootdir)) != 0) {
			error("zonesdir %s has to be an absolute path that starts with the chroot path %s",
				nsd.options->zonesdir, nsd.chrootdir);
		} else if (!file_inside_chroot(nsd.pidfile, nsd.chrootdir)) {
			error("pidfile %s is not relative to %s: chroot not possible",
				nsd.pidfile, nsd.chrootdir);
		} else if (!file_inside_chroot(nsd.dbfile, nsd.chrootdir)) {
			error("database %s is not relative to %s: chroot not possible",
				nsd.dbfile, nsd.chrootdir);
		} else if (!file_inside_chroot(nsd.options->xfrdfile, nsd.chrootdir)) {
			error("xfrdfile %s is not relative to %s: chroot not possible",
				nsd.options->xfrdfile, nsd.chrootdir);
		} else if (!file_inside_chroot(nsd.options->zonelistfile, nsd.chrootdir)) {
			error("zonelistfile %s is not relative to %s: chroot not possible",
				nsd.options->zonelistfile, nsd.chrootdir);
		} else if (!file_inside_chroot(nsd.options->xfrdir, nsd.chrootdir)) {
			error("xfrdir %s is not relative to %s: chroot not possible",
				nsd.options->xfrdir, nsd.chrootdir);
		}
	}

	/* Set up the logging */
	log_open(LOG_PID, FACILITY, nsd.log_filename);
	if (!nsd.log_filename)
		log_set_log_function(log_syslog);
	else if (nsd.uid && nsd.gid) {
		if(chown(nsd.log_filename, nsd.uid, nsd.gid) != 0)
			VERBOSITY(2, (LOG_WARNING, "chown %s failed: %s",
				nsd.log_filename, strerror(errno)));
	}

	/* Do we have a running nsd? */
	if ((oldpid = readpid(nsd.pidfile)) == -1) {
		if (errno != ENOENT) {
			log_msg(LOG_ERR, "can't read pidfile %s: %s",
				nsd.pidfile, strerror(errno));
		}
	} else {
		if (kill(oldpid, 0) == 0 || errno == EPERM) {
			log_msg(LOG_WARNING,
				"%s is already running as %u, continuing",
				argv0, (unsigned) oldpid);
		} else {
			log_msg(LOG_ERR,
				"...stale pid file from process %u",
				(unsigned) oldpid);
		}
	}

	/* Setup the signal handling... */
	action.sa_handler = sig_handler;
	sigfillset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGHUP, &action, NULL);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGILL, &action, NULL);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGALRM, &action, NULL);
	sigaction(SIGCHLD, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &action, NULL);

	/* Initialize... */
	nsd.mode = NSD_RUN;
	nsd.signal_hint_child = 0;
	nsd.signal_hint_reload = 0;
	nsd.signal_hint_reload_hup = 0;
	nsd.signal_hint_quit = 0;
	nsd.signal_hint_shutdown = 0;
	nsd.signal_hint_stats = 0;
	nsd.signal_hint_statsusr = 0;
	nsd.quit_sync_done = 0;

	/* Initialize the server... */
	if (server_init(&nsd) != 0) {
		error("server initialization failed, %s could "
			"not be started", argv0);
	}
#if defined(HAVE_SSL)
	if(nsd.options->control_enable) {
		/* read ssl keys while superuser and outside chroot */
		if(!(nsd.rc = daemon_remote_create(nsd.options)))
			error("could not perform remote control setup");
	}
#endif /* HAVE_SSL */

	/* Unless we're debugging, fork... */
	if (!nsd.debug) {
		int fd;

		/* Take off... */
		switch ((nsd.pid = fork())) {
		case 0:
			/* Child */
			break;
		case -1:
			error("fork() failed: %s", strerror(errno));
		default:
			/* Parent is done */
			server_close_all_sockets(nsd.udp, nsd.ifs);
			server_close_all_sockets(nsd.tcp, nsd.ifs);
			exit(0);
		}

		/* Detach ourselves... */
		if (setsid() == -1) {
			error("setsid() failed: %s", strerror(errno));
		}

		if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
			(void)dup2(fd, STDIN_FILENO);
			(void)dup2(fd, STDOUT_FILENO);
			(void)dup2(fd, STDERR_FILENO);
			if (fd > 2)
				(void)close(fd);
		}
	}

	/* Get our process id */
	nsd.pid = getpid();

	/* Set user context */
#ifdef HAVE_GETPWNAM
	if (*nsd.username) {
#ifdef HAVE_SETUSERCONTEXT
		/* setusercontext does initgroups, setuid, setgid, and
		 * also resource limits from login config, but we
		 * still call setresuid, setresgid to be sure to set all uid */
		if (setusercontext(NULL, pwd, nsd.uid,
			LOGIN_SETALL & ~LOGIN_SETUSER & ~LOGIN_SETGROUP) != 0)
			log_msg(LOG_WARNING, "unable to setusercontext %s: %s",
				nsd.username, strerror(errno));
#endif /* HAVE_SETUSERCONTEXT */
	}
#endif /* HAVE_GETPWNAM */

	/* Chroot */
#ifdef HAVE_CHROOT
	if (nsd.chrootdir && nsd.chrootdir[0]) {
		int l = strlen(nsd.chrootdir)-1; /* ends in trailing slash */

		if (file_inside_chroot(nsd.log_filename, nsd.chrootdir))
			nsd.file_rotation_ok = 1;

		/* strip chroot from pathnames if they're absolute */
		nsd.options->zonesdir += l;
		if (nsd.log_filename){
			if (nsd.log_filename[0] == '/')
				nsd.log_filename += l;
		}
		if (nsd.pidfile[0] == '/')
			nsd.pidfile += l;
		if (nsd.dbfile[0] == '/')
			nsd.dbfile += l;
		if (nsd.options->xfrdfile[0] == '/')
			nsd.options->xfrdfile += l;
		if (nsd.options->zonelistfile[0] == '/')
			nsd.options->zonelistfile += l;
		if (nsd.options->xfrdir[0] == '/')
			nsd.options->xfrdir += l;

		/* strip chroot from pathnames of "include:" statements
		 * on subsequent repattern commands */
		cfg_parser->chroot = nsd.chrootdir;

#ifdef HAVE_TZSET
		/* set timezone whilst not yet in chroot */
		tzset();
#endif
		if (chroot(nsd.chrootdir)) {
			error("unable to chroot: %s", strerror(errno));
		}
		if (chdir("/")) {
			error("unable to chdir to chroot: %s", strerror(errno));
		}
		DEBUG(DEBUG_IPC,1, (LOG_INFO, "changed root directory to %s",
			nsd.chrootdir));
		/* chdir to zonesdir again after chroot */
		if(nsd.options->zonesdir && nsd.options->zonesdir[0]) {
			if(chdir(nsd.options->zonesdir)) {
				error("unable to chdir to '%s': %s",
					nsd.options->zonesdir, strerror(errno));
			}
			DEBUG(DEBUG_IPC,1, (LOG_INFO, "changed directory to %s",
				nsd.options->zonesdir));
		}
	}
	else
#endif /* HAVE_CHROOT */
		nsd.file_rotation_ok = 1;

	DEBUG(DEBUG_IPC,1, (LOG_INFO, "file rotation on %s %sabled",
		nsd.log_filename, nsd.file_rotation_ok?"en":"dis"));

	/* Write pidfile */
	if (writepid(&nsd) == -1) {
		log_msg(LOG_ERR, "cannot overwrite the pidfile %s: %s",
			nsd.pidfile, strerror(errno));
	}

	/* Drop the permissions */
#ifdef HAVE_GETPWNAM
	if (*nsd.username) {
#ifdef HAVE_INITGROUPS
		if(initgroups(nsd.username, nsd.gid) != 0)
			log_msg(LOG_WARNING, "unable to initgroups %s: %s",
				nsd.username, strerror(errno));
#endif /* HAVE_INITGROUPS */
		endpwent();

#ifdef HAVE_SETRESGID
		if(setresgid(nsd.gid,nsd.gid,nsd.gid) != 0)
#elif defined(HAVE_SETREGID) && !defined(DARWIN_BROKEN_SETREUID)
			if(setregid(nsd.gid,nsd.gid) != 0)
#else /* use setgid */
				if(setgid(nsd.gid) != 0)
#endif /* HAVE_SETRESGID */
					error("unable to set group id of %s: %s",
						nsd.username, strerror(errno));

#ifdef HAVE_SETRESUID
		if(setresuid(nsd.uid,nsd.uid,nsd.uid) != 0)
#elif defined(HAVE_SETREUID) && !defined(DARWIN_BROKEN_SETREUID)
			if(setreuid(nsd.uid,nsd.uid) != 0)
#else /* use setuid */
				if(setuid(nsd.uid) != 0)
#endif /* HAVE_SETRESUID */
					error("unable to set user id of %s: %s",
						nsd.username, strerror(errno));

		DEBUG(DEBUG_IPC,1, (LOG_INFO, "dropped user privileges, run as %s",
			nsd.username));
	}
#endif /* HAVE_GETPWNAM */
	xfrd_make_tempdir(&nsd);
#ifdef USE_ZONE_STATS
	options_zonestatnames_create(nsd.options);
	server_zonestat_alloc(&nsd);
#endif /* USE_ZONE_STATS */

	if(nsd.server_kind == NSD_SERVER_MAIN) {
		server_prepare_xfrd(&nsd);
		/* xfrd forks this before reading database, so it does not get
		 * the memory size of the database */
		server_start_xfrd(&nsd, 0, 0);
	}
	if (server_prepare(&nsd) != 0) {
		unlinkpid(nsd.pidfile);
		error("server preparation failed, %s could "
			"not be started", argv0);
	}
	if(nsd.server_kind == NSD_SERVER_MAIN) {
		server_send_soa_xfrd(&nsd, 0);
	}

	/* Really take off */
	log_msg(LOG_NOTICE, "%s started (%s), pid %d",
		argv0, PACKAGE_STRING, (int) nsd.pid);

	if (nsd.server_kind == NSD_SERVER_MAIN) {
		server_main(&nsd);
	} else {
		server_child(&nsd);
	}

	/* NOTREACH */
	exit(0);
}