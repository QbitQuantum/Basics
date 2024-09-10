int
main(int argc, char *argv[])
{
#ifdef __FreeBSD__
	FILE *fpid = NULL;
#endif	
	fd_set *fdsr = NULL, *fdsw = NULL;
	struct sockaddr_in sin;
	struct sockaddr_in lin;
	int ch, s, s2, conflisten = 0, syncfd = 0, i, omax = 0, one = 1;
	socklen_t sinlen;
	u_short port;
	struct servent *ent;
	struct rlimit rlp;
	char *bind_address = NULL;
	const char *errstr;
	char *sync_iface = NULL;
	char *sync_baddr = NULL;

	tzset();
	openlog_r("spamd", LOG_PID | LOG_NDELAY, LOG_DAEMON, &sdata);

	if ((ent = getservbyname("spamd", "tcp")) == NULL)
		errx(1, "Can't find service \"spamd\" in /etc/services");
	port = ntohs(ent->s_port);
	if ((ent = getservbyname("spamd-cfg", "tcp")) == NULL)
		errx(1, "Can't find service \"spamd-cfg\" in /etc/services");
	cfg_port = ntohs(ent->s_port);
	if ((ent = getservbyname("spamd-sync", "udp")) == NULL)
		errx(1, "Can't find service \"spamd-sync\" in /etc/services");
	sync_port = ntohs(ent->s_port);

	if (gethostname(hostname, sizeof hostname) == -1)
		err(1, "gethostname");
	maxfiles = get_maxfiles();
	if (maxcon > maxfiles)
		maxcon = maxfiles;
	if (maxblack > maxfiles)
		maxblack = maxfiles;
	while ((ch =
#ifndef __FreeBSD__
	    getopt(argc, argv, "45l:c:B:p:bdG:h:s:S:M:n:vw:y:Y:")) != -1) {
#else
	    getopt(argc, argv, "45l:c:B:p:bdG:h:s:S:M:n:vw:y:Y:t:m:")) != -1) {
#endif
		switch (ch) {
		case '4':
			nreply = "450";
			break;
		case '5':
			nreply = "550";
			break;
		case 'l':
			bind_address = optarg;
			break;
		case 'B':
			i = atoi(optarg);
			maxblack = i;
			break;
		case 'c':
			i = atoi(optarg);
			if (i > maxfiles) {
				fprintf(stderr,
				    "%d > system max of %d connections\n",
				    i, maxfiles);
				usage();
			}
			maxcon = i;
			break;
		case 'p':
			i = atoi(optarg);
			port = i;
			break;
		case 'd':
			debug = 1;
			break;
		case 'b':
			greylist = 0;
			break;
		case 'G':
			if (sscanf(optarg, "%d:%d:%d", &passtime, &greyexp,
			    &whiteexp) != 3)
				usage();
			/* convert to seconds from minutes */
			passtime *= 60;
			/* convert to seconds from hours */
			whiteexp *= (60 * 60);
			/* convert to seconds from hours */
			greyexp *= (60 * 60);
			break;
		case 'h':
			bzero(&hostname, sizeof(hostname));
			if (strlcpy(hostname, optarg, sizeof(hostname)) >=
			    sizeof(hostname))
				errx(1, "-h arg too long");
			break;
		case 's':
			i = atoi(optarg);
			if (i < 0 || i > 10)
				usage();
			stutter = i;
			break;
		case 'S':
			/* 
			 * strtonum is aviable with FreeBSD 6.1,
			 * for older versions we have to fallback
			 */

			i = strtonum(optarg, 0, 90, &errstr);
			if (errstr)
				usage();
			grey_stutter = i;
			break;
		case 'M':
			low_prio_mx_ip = optarg;
			break;
		case 'n':
			spamd = optarg;
			break;
		case 'v':
			verbose = 1;
			break;
		case 'w':
			window = atoi(optarg);
			if (window <= 0)
				usage();
			break;
		case 'Y':
			if (sync_addhost(optarg, sync_port) != 0)
				sync_iface = optarg;
			syncsend++;
			break;
		case 'y':
			sync_baddr = optarg;
			syncrecv++;
			break;
#ifdef __FreeBSD__
		case 't':
			ipfw_tabno = atoi(optarg);
			break;
		case 'm':
			if (strcmp(optarg, "ipfw") == 0)
				use_pf=0;
			break;
#endif
		default:
			usage();
			break;
		}
	}

	setproctitle("[priv]%s%s",
	    greylist ? " (greylist)" : "",
	    (syncrecv || syncsend) ? " (sync)" : "");

	if (!greylist)
		maxblack = maxcon;
	else if (maxblack > maxcon)
		usage();

	rlp.rlim_cur = rlp.rlim_max = maxcon + 15;
	if (setrlimit(RLIMIT_NOFILE, &rlp) == -1)
		err(1, "setrlimit");

	con = calloc(maxcon, sizeof(*con));
	if (con == NULL)
		err(1, "calloc");

	con->obuf = malloc(8192);

	if (con->obuf == NULL)
		err(1, "malloc");
	con->osize = 8192;

	for (i = 0; i < maxcon; i++)
		con[i].fd = -1;

	signal(SIGPIPE, SIG_IGN);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1)
		err(1, "socket");

	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one,
	    sizeof(one)) == -1)
		return (-1);

	conflisten = socket(AF_INET, SOCK_STREAM, 0);
	if (conflisten == -1)
		err(1, "socket");

	if (setsockopt(conflisten, SOL_SOCKET, SO_REUSEADDR, &one,
	    sizeof(one)) == -1)
		return (-1);

	memset(&sin, 0, sizeof sin);
	sin.sin_len = sizeof(sin);
	if (bind_address) {
		if (inet_pton(AF_INET, bind_address, &sin.sin_addr) != 1)
			err(1, "inet_pton");
	} else
		sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	if (bind(s, (struct sockaddr *)&sin, sizeof sin) == -1)
		err(1, "bind");

	memset(&lin, 0, sizeof sin);
	lin.sin_len = sizeof(sin);
	lin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	lin.sin_family = AF_INET;
	lin.sin_port = htons(cfg_port);

	if (bind(conflisten, (struct sockaddr *)&lin, sizeof lin) == -1)
		err(1, "bind local");

	if (syncsend || syncrecv) {
		syncfd = sync_init(sync_iface, sync_baddr, sync_port);
		if (syncfd == -1)
			err(1, "sync init");
	}

	pw = getpwnam("_spamd");
	if (!pw)
		pw = getpwnam("nobody");

#ifdef __FreeBSD__
	/* open the pid file just before daemon */
	fpid = fopen(pid_file, "w");
	if (fpid == NULL) {
		syslog(LOG_ERR, "exiting (couldn't create pid file %s)", 
			pid_file);
		err(1, "couldn't create pid file \"%s\"", pid_file);
	}
#endif	

	if (debug == 0) {
		if (daemon(1, 1) == -1)
			err(1, "daemon");
	}

	if (greylist) {
#ifdef __FreeBSD__
		if(use_pf){
#endif			
			pfdev = open("/dev/pf", O_RDWR);
			if (pfdev == -1) {
				syslog_r(LOG_ERR, &sdata, "open /dev/pf: %m");
				exit(1);
			}
#ifdef __FreeBSD__
		} 	
#endif

		maxblack = (maxblack >= maxcon) ? maxcon - 100 : maxblack;
		if (maxblack < 0)
			maxblack = 0;

		/* open pipe to talk to greylister */
		if (pipe(greypipe) == -1) {
			syslog(LOG_ERR, "pipe (%m)");
			exit(1);
		}
		/* open pipe to recieve spamtrap configs */
		if (pipe(trappipe) == -1) {
			syslog(LOG_ERR, "pipe (%m)");
			exit(1);
		}
		jail_pid = fork();
		switch (jail_pid) {
		case -1:
			syslog(LOG_ERR, "fork (%m)");
			exit(1);
		case 0:
			/* child - continue */
			signal(SIGPIPE, SIG_IGN);
			grey = fdopen(greypipe[1], "w");
			if (grey == NULL) {
				syslog(LOG_ERR, "fdopen (%m)");
				_exit(1);
			}
			close(greypipe[0]);
			trapfd = trappipe[0];
			trapcfg = fdopen(trappipe[0], "r");
			if (trapcfg == NULL) {
				syslog(LOG_ERR, "fdopen (%m)");
				_exit(1);
			}
			close(trappipe[1]);
			goto jail;
		}
		/* parent - run greylister */
		grey = fdopen(greypipe[0], "r");
		if (grey == NULL) {
			syslog(LOG_ERR, "fdopen (%m)");
			exit(1);
		}
		close(greypipe[1]);
		trapcfg = fdopen(trappipe[1], "w");
		if (trapcfg == NULL) {
			syslog(LOG_ERR, "fdopen (%m)");
			exit(1);
		}
		close(trappipe[0]);
		return (greywatcher());
		/* NOTREACHED */
	}

jail:
#ifdef __FreeBSD__
	/* after switch user and daemon write and close the pid file */
	if (fpid) {
		fprintf(fpid, "%ld\n", (long) getpid());
		if (fclose(fpid) == EOF) {
			syslog(LOG_ERR, "exiting (couldn't close pid file %s)", 
				pid_file);
			exit(1);
		}
	}
#endif	

	if (chroot("/var/empty") == -1 || chdir("/") == -1) {
		syslog(LOG_ERR, "cannot chdir to /var/empty.");
		exit(1);
	}

	if (pw)
		if (setgroups(1, &pw->pw_gid) ||
		    setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) ||
		    setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid))
			err(1, "failed to drop privs");

	if (listen(s, 10) == -1)
		err(1, "listen");

	if (listen(conflisten, 10) == -1)
		err(1, "listen");

	if (debug != 0)
		printf("listening for incoming connections.\n");
	syslog_r(LOG_WARNING, &sdata, "listening for incoming connections.");

	while (1) {
		struct timeval tv, *tvp;
		int max, n;
		int writers;

		max = MAX(s, conflisten);
		if (syncrecv)
			max = MAX(max, syncfd);
		max = MAX(max, conffd);
		max = MAX(max, trapfd);

		time(&t);
		for (i = 0; i < maxcon; i++)
			if (con[i].fd != -1)
				max = MAX(max, con[i].fd);

		if (max > omax) {
			free(fdsr);
			fdsr = NULL;
			free(fdsw);
			fdsw = NULL;
			fdsr = (fd_set *)calloc(howmany(max+1, NFDBITS),
			    sizeof(fd_mask));
			if (fdsr == NULL)
				err(1, "calloc");
			fdsw = (fd_set *)calloc(howmany(max+1, NFDBITS),
			    sizeof(fd_mask));
			if (fdsw == NULL)
				err(1, "calloc");
			omax = max;
		} else {
			memset(fdsr, 0, howmany(max+1, NFDBITS) *
			    sizeof(fd_mask));
			memset(fdsw, 0, howmany(max+1, NFDBITS) *
			    sizeof(fd_mask));
		}

		writers = 0;
		for (i = 0; i < maxcon; i++) {
			if (con[i].fd != -1 && con[i].r) {
				if (con[i].r + MAXTIME <= t) {
					closecon(&con[i]);
					continue;
				}
				FD_SET(con[i].fd, fdsr);
			}
			if (con[i].fd != -1 && con[i].w) {
				if (con[i].w + MAXTIME <= t) {
					closecon(&con[i]);
					continue;
				}
				if (con[i].w <= t)
					FD_SET(con[i].fd, fdsw);
				writers = 1;
			}
		}
		FD_SET(s, fdsr);

		/* only one active config conn at a time */
		if (conffd == -1)
			FD_SET(conflisten, fdsr);
		else
			FD_SET(conffd, fdsr);
		if (trapfd != -1)
			FD_SET(trapfd, fdsr);
		if (syncrecv)
			FD_SET(syncfd, fdsr);

		if (writers == 0) {
			tvp = NULL;
		} else {
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			tvp = &tv;
		}

		n = select(max+1, fdsr, fdsw, NULL, tvp);
		if (n == -1) {
			if (errno != EINTR)
				err(1, "select");
			continue;
		}
		if (n == 0)
			continue;

		for (i = 0; i < maxcon; i++) {
			if (con[i].fd != -1 && FD_ISSET(con[i].fd, fdsr))
				handler(&con[i]);
			if (con[i].fd != -1 && FD_ISSET(con[i].fd, fdsw))
				handlew(&con[i], clients + 5 < maxcon);
		}
		if (FD_ISSET(s, fdsr)) {
			sinlen = sizeof(sin);
			s2 = accept(s, (struct sockaddr *)&sin, &sinlen);
			if (s2 == -1)
				/* accept failed, they may try again */
				continue;
			for (i = 0; i < maxcon; i++)
				if (con[i].fd == -1)
					break;
			if (i == maxcon)
				close(s2);
			else {
				initcon(&con[i], s2, (struct sockaddr *)&sin);
				syslog_r(LOG_INFO, &sdata,
				    "%s: connected (%d/%d)%s%s",
				    con[i].addr, clients, blackcount,
				    ((con[i].lists == NULL) ? "" :
				    ", lists:"),
				    ((con[i].lists == NULL) ? "":
				    con[i].lists));
			}
		}
		if (FD_ISSET(conflisten, fdsr)) {
			sinlen = sizeof(lin);
			conffd = accept(conflisten, (struct sockaddr *)&lin,
			    &sinlen);
			if (conffd == -1)
				/* accept failed, they may try again */
				continue;
			else if (ntohs(lin.sin_port) >= IPPORT_RESERVED) {
				close(conffd);
				conffd = -1;
			}
		}
		if (conffd != -1 && FD_ISSET(conffd, fdsr))
			do_config();
		if (trapfd != -1 && FD_ISSET(trapfd, fdsr))
			read_configline(trapcfg);
		if (syncrecv && FD_ISSET(syncfd, fdsr))
			sync_recv();
	}
	exit(1);
}