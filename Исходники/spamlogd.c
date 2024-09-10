int
main(int argc, char **argv)
{
#ifdef __FreeBSD__
	FILE		*fpid = NULL;
#endif	
	int		 ch;
	struct passwd	*pw;
	pcap_handler	 phandler = logpkt_handler;
	int syncfd = 0;
	struct servent *ent;
	char *sync_iface = NULL;
	char *sync_baddr = NULL;

	if ((ent = getservbyname("spamd-sync", "udp")) == NULL)
		errx(1, "Can't find service \"spamd-sync\" in /etc/services");
	sync_port = ntohs(ent->s_port);
#ifndef __FreeBSD__
	while ((ch = getopt(argc, argv, "DIi:l:Y:")) != -1) {
#else
	while ((ch = getopt(argc, argv, "DIi:l:Y:m:")) != -1) {
#endif
		switch (ch) {
		case 'D':
			flag_debug = 1;
			break;
		case 'I':
			flag_inbound = 1;
			break;
		case 'i':
			networkif = optarg;
			break;
		case 'l':
			pflogif = optarg;
			break;
		case 'Y':
			if (sync_addhost(optarg, sync_port) != 0)
				sync_iface = optarg;
			syncsend++;
			break;
#ifdef __FreeBSD__
		case 'm':
			if (strcmp(optarg, "ipfw") == 0)
				use_pf=0;
			break;
#endif
			
		default:
			usage();
			/* NOTREACHED */
		}
	}

	signal(SIGINT , sighandler_close);
	signal(SIGQUIT, sighandler_close);
	signal(SIGTERM, sighandler_close);

	logmsg(LOG_DEBUG, "Listening on %s for %s %s", pflogif,
	    (networkif == NULL) ? "all interfaces." : networkif,
	    (flag_inbound) ? "Inbound direction only." : "");

	if (init_pcap() == -1)
		err(1, "couldn't initialize pcap");

	if (syncsend) {
		syncfd = sync_init(sync_iface, sync_baddr, sync_port);
		if (syncfd == -1)
			err(1, "sync init");
	}
	
#ifdef __FreeBSD__
	/* open the pid file just before switch the user */
	fpid = fopen(pid_file, "w");
	if (fpid == NULL) {
		syslog(LOG_ERR, "exiting (couldn't create pid file %s)", 
				pid_file);
		 err(1, "couldn't create pid file \"%s\"", pid_file);
	}
#endif	

	/* privdrop */
	pw = getpwnam("_spamd");
	if (pw == NULL)
		errx(1, "User '_spamd' not found! ");

	if (setgroups(1, &pw->pw_gid) ||
	    setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) ||
	    setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid))
		err(1, "failed to drop privs");

	if (!flag_debug) {
		if (daemon(0, 0) == -1)
			err(1, "daemon");
		tzset();
		openlog_r("spamlogd", LOG_PID | LOG_NDELAY, LOG_DAEMON, &sdata);
	}

#ifdef __FreeBSD__
	/* after switch user and daemon write and close the pid file */
	if (fpid) {
		fprintf(fpid, "%ld\n", (long) getpid());
		if (fclose(fpid) == EOF) {
			syslog(LOG_ERR, "exiting (couldn't close pid file %s)", 
				pid_file);
			exit (1);
		}
	}
#endif	

	pcap_loop(hpcap, -1, phandler, NULL);

	logmsg(LOG_NOTICE, "exiting");
	if (!flag_debug)
		closelog_r(&sdata);

	exit(0);
}