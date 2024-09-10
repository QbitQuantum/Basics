int
main(int argc, char **argv)
{
	int ch, np, ret, Xflag = 0;
	pcap_handler phandler = dump_packet;
	const char *errstr = NULL;
	char *pidf = NULL;

	ret = 0;

	closefrom(STDERR_FILENO + 1);

	while ((ch = getopt(argc, argv, "Dxd:f:i:p:s:")) != -1) {
		switch (ch) {
		case 'D':
			Debug = 1;
			break;
		case 'd':
			delay = strtonum(optarg, 5, 60*60, &errstr);
			if (errstr)
				usage();
			break;
		case 'f':
			filename = optarg;
			break;
		case 'i':
			interface = optarg;
			break;
		case 'p':
			pidf = optarg;
			break;
		case 's':
			snaplen = strtonum(optarg, 0, PFLOGD_MAXSNAPLEN,
			    &errstr);
			if (snaplen <= 0)
				snaplen = DEF_SNAPLEN;
			if (errstr)
				snaplen = PFLOGD_MAXSNAPLEN;
			break;
		case 'x':
			Xflag++;
			break;
		default:
			usage();
		}

	}

	log_debug = Debug;
	argc -= optind;
	argv += optind;

	/* does interface exist */
	if (!if_exists(interface)) {
		warn("Failed to initialize: %s", interface);
		logmsg(LOG_ERR, "Failed to initialize: %s", interface);
		logmsg(LOG_ERR, "Exiting, init failure");
		exit(1);
	}

	if (!Debug) {
		openlog("pflogd", LOG_PID | LOG_CONS, LOG_DAEMON);
		if (daemon(0, 0)) {
			logmsg(LOG_WARNING, "Failed to become daemon: %s",
			    strerror(errno));
		}
		pidfile(pidf);
	}

	tzset();
	(void)umask(S_IRWXG | S_IRWXO);

	/* filter will be used by the privileged process */
	if (argc) {
		filter = copy_argv(argv);
		if (filter == NULL)
			logmsg(LOG_NOTICE, "Failed to form filter expression");
	}

	/* initialize pcap before dropping privileges */
	if (init_pcap()) {
		logmsg(LOG_ERR, "Exiting, init failure");
		exit(1);
	}

	/* Privilege separation begins here */
	if (priv_init()) {
		logmsg(LOG_ERR, "unable to privsep");
		exit(1);
	}

	setproctitle("[initializing]");
	/* Process is now unprivileged and inside a chroot */
	signal(SIGTERM, sig_close);
	signal(SIGINT, sig_close);
	signal(SIGQUIT, sig_close);
	signal(SIGALRM, sig_alrm);
	signal(SIGUSR1, sig_usr1);
	signal(SIGHUP, sig_hup);
	alarm(delay);

	buffer = malloc(PFLOGD_BUFSIZE);

	if (buffer == NULL) {
		logmsg(LOG_WARNING, "Failed to allocate output buffer");
		phandler = dump_packet_nobuf;
	} else {
		bufleft = buflen = PFLOGD_BUFSIZE;
		bufpos = buffer;
		bufpkt = 0;
	}

	if (reset_dump(Xflag) < 0) {
		if (Xflag)
			return (1);

		logmsg(LOG_ERR, "Logging suspended: open error");
		set_suspended(1);
	} else if (Xflag)
		return (0);

	while (1) {
		np = pcap_dispatch(hpcap, PCAP_NUM_PKTS,
		    phandler, (u_char *)dpcap);
		if (np < 0) {
			if (!if_exists(interface) == -1) {
				logmsg(LOG_NOTICE, "interface %s went away",
				    interface);
				ret = -1;
				break;
			}
			logmsg(LOG_NOTICE, "%s", pcap_geterr(hpcap));
		}

		if (gotsig_close)
			break;
		if (gotsig_hup) {
			if (reset_dump(0)) {
				logmsg(LOG_ERR,
				    "Logging suspended: open error");
				set_suspended(1);
			}
			gotsig_hup = 0;
		}

		if (gotsig_alrm) {
			if (dpcap)
				flush_buffer(dpcap);
			else 
				gotsig_hup = 1;
			gotsig_alrm = 0;
			alarm(delay);
		}

		if (gotsig_usr1) {
			log_pcap_stats();
			gotsig_usr1 = 0;
		}
	}

	logmsg(LOG_NOTICE, "Exiting");
	if (dpcap) {
		flush_buffer(dpcap);
		fclose(dpcap);
	}
	purge_buffer();

	log_pcap_stats();
	pcap_close(hpcap);
	if (!Debug)
		closelog();
	return (ret);
}