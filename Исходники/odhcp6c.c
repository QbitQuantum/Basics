int main(_unused int argc, char* const argv[])
{
	// Allocate ressources
	const char *pidfile = NULL;
	const char *script = "/usr/sbin/odhcp6c-update";
	ssize_t l;
	uint8_t buf[134];
	char *optpos;
	uint16_t opttype;
	enum odhcp6c_ia_mode ia_na_mode = IA_MODE_TRY;
	enum odhcp6c_ia_mode ia_pd_mode = IA_MODE_TRY;
	static struct in6_addr ifid = IN6ADDR_ANY_INIT;
	int sol_timeout = DHCPV6_SOL_MAX_RT;

#ifdef EXT_BFD_PING
	int bfd_interval = 0, bfd_loss = 3;
#endif

	bool help = false, daemonize = false;
	int logopt = LOG_PID;
	int c, request_pd = 0;
	while ((c = getopt(argc, argv, "S::N:P:FB:c:i:r:s:kt:hedp:")) != -1) {
		switch (c) {
		case 'S':
			allow_slaac_only = (optarg) ? atoi(optarg) : -1;
			break;

		case 'N':
			if (!strcmp(optarg, "force")) {
				ia_na_mode = IA_MODE_FORCE;
				allow_slaac_only = -1;
			} else if (!strcmp(optarg, "none")) {
				ia_na_mode = IA_MODE_NONE;
			} else if (!strcmp(optarg, "try")) {
				ia_na_mode = IA_MODE_TRY;
			} else{
				help = true;
			}
			break;

		case 'P':
			if (allow_slaac_only >= 0 && allow_slaac_only < 10)
				allow_slaac_only = 10;

			request_pd = strtoul(optarg, NULL, 10);
			if (request_pd == 0)
				request_pd = -1;

			break;

		case 'F':
			allow_slaac_only = -1;
			ia_pd_mode = IA_MODE_FORCE;
			break;

#ifdef EXT_BFD_PING
		case 'B':
			bfd_interval = atoi(optarg);
			break;
#endif

		case 'c':
			l = script_unhexlify(&buf[4], sizeof(buf) - 4, optarg);
			if (l > 0) {
				buf[0] = 0;
				buf[1] = DHCPV6_OPT_CLIENTID;
				buf[2] = 0;
				buf[3] = l;
				odhcp6c_add_state(STATE_CLIENT_ID, buf, l + 4);
			} else {
				help = true;
			}
			break;

		case 'i':
			if (inet_pton(AF_INET6, optarg, &ifid) != 1)
				help = true;
			break;

		case 'r':
			optpos = optarg;
			while (optpos[0]) {
				opttype = htons(strtoul(optarg, &optpos, 10));
				if (optpos == optarg)
					break;
				else if (optpos[0])
					optarg = &optpos[1];
				odhcp6c_add_state(STATE_ORO, &opttype, 2);
			}
			break;

		case 's':
			script = optarg;
			break;

		case 'k':
			release = false;
			break;

		case 't':
			sol_timeout = atoi(optarg);
			break;

		case 'e':
			logopt |= LOG_PERROR;
			break;

		case 'd':
			daemonize = true;
			break;

		case 'p':
			pidfile = optarg;
			break;

		default:
			help = true;
			break;
		}
	}

	openlog("odhcp6c", logopt, LOG_DAEMON);
	const char *ifname = argv[optind];

	if (help || !ifname)
		return usage();

	signal(SIGIO, sighandler);
	signal(SIGHUP, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGCHLD, sighandler);
	signal(SIGTERM, sighandler);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);

	if ((urandom_fd = open("/dev/urandom", O_CLOEXEC | O_RDONLY)) < 0 ||
			init_dhcpv6(ifname, request_pd, sol_timeout) ||
			ra_init(ifname, &ifid) || script_init(script, ifname)) {
		syslog(LOG_ERR, "failed to initialize: %s", strerror(errno));
		return 3;
	}

	if (daemonize) {
		openlog("odhcp6c", LOG_PID, LOG_DAEMON); // Disable LOG_PERROR
		if (daemon(0, 0)) {
			syslog(LOG_ERR, "Failed to daemonize: %s",
					strerror(errno));
			return 4;
		}

		char pidbuf[128];
		if (!pidfile) {
			snprintf(pidbuf, sizeof(pidbuf),
					"/var/run/odhcp6c.%s.pid", ifname);
			pidfile = pidbuf;
		}

		int fd = open(pidfile, O_WRONLY | O_CREAT);
		if (fd >= 0) {
			char buf[8];
			int len = snprintf(buf, sizeof(buf), "%i\n", getpid());
			write(fd, buf, len);
			close(fd);
		}
	}

	script_call("started");

	while (do_signal != SIGTERM) { // Main logic
		odhcp6c_clear_state(STATE_SERVER_ID);
		odhcp6c_clear_state(STATE_IA_NA);
		odhcp6c_clear_state(STATE_IA_PD);
		odhcp6c_clear_state(STATE_SNTP_IP);
		odhcp6c_clear_state(STATE_SNTP_FQDN);
		odhcp6c_clear_state(STATE_SIP_IP);
		odhcp6c_clear_state(STATE_SIP_FQDN);
		dhcpv6_set_ia_mode(ia_na_mode, ia_pd_mode);
		bound = false;

		syslog(LOG_NOTICE, "(re)starting transaction on %s", ifname);

		do_signal = 0;
		int mode = dhcpv6_request(DHCPV6_MSG_SOLICIT);
		odhcp6c_signal_process();

		if (mode < 0)
			continue;

		do {
			int res = dhcpv6_request(mode == DHCPV6_STATELESS ?
					DHCPV6_MSG_INFO_REQ : DHCPV6_MSG_REQUEST);

			odhcp6c_signal_process();
			if (res > 0)
				break;
			else if (do_signal > 0) {
				mode = -1;
				break;
			}

			mode = dhcpv6_promote_server_cand();
		} while (mode > DHCPV6_UNKNOWN);

		if (mode < 0)
			continue;

		switch (mode) {
		case DHCPV6_STATELESS:
			bound = true;
			syslog(LOG_NOTICE, "entering stateless-mode on %s", ifname);

			while (do_signal == 0 || do_signal == SIGUSR1) {
				do_signal = 0;
				script_call("informed");					

				int res = dhcpv6_poll_reconfigure();
				odhcp6c_signal_process();

				if (res > 0)
					continue;

				if (do_signal == SIGUSR1) {
					do_signal = 0; // Acknowledged
					continue;
				} else if (do_signal > 0)
					break;

				res = dhcpv6_request(DHCPV6_MSG_INFO_REQ);
				odhcp6c_signal_process();
				if (do_signal == SIGUSR1)
					continue;
				else if (res < 0)
					break;
			}
			break;

		case DHCPV6_STATEFUL:
			script_call("bound");
			bound = true;
			syslog(LOG_NOTICE, "entering stateful-mode on %s", ifname);
#ifdef EXT_BFD_PING
			if (bfd_interval > 0)
				bfd_start(ifname, bfd_loss, bfd_interval);
#endif

			while (do_signal == 0 || do_signal == SIGUSR1) {
				// Renew Cycle
				// Wait for T1 to expire or until we get a reconfigure
				int res = dhcpv6_poll_reconfigure();
				odhcp6c_signal_process();
				if (res > 0) {
					script_call("updated");
					continue;
				}

				// Handle signal, if necessary
				if (do_signal == SIGUSR1)
					do_signal = 0; // Acknowledged
				else if (do_signal > 0)
					break; // Other signal type

				// Send renew as T1 expired
				size_t ia_pd_len, ia_na_len;
				odhcp6c_get_state(STATE_IA_PD, &ia_pd_len);
				odhcp6c_get_state(STATE_IA_NA, &ia_na_len);

				// If we have any IAs, send renew, otherwise request
				if (ia_pd_len == 0 && ia_na_len == 0)
					res = dhcpv6_request(DHCPV6_MSG_REQUEST);
				else
					res = dhcpv6_request(DHCPV6_MSG_RENEW);

				odhcp6c_signal_process();
				if (res > 0) { // Renew was succesfull
					// Publish updates
					script_call("updated");
					continue; // Renew was successful
				}
				
				odhcp6c_clear_state(STATE_SERVER_ID); // Remove binding

				// If we have IAs, try rebind otherwise restart
				res = dhcpv6_request(DHCPV6_MSG_REBIND);
				odhcp6c_signal_process();

				if (res > 0)
					script_call("rebound");
				else {
#ifdef EXT_BFD_PING
					bfd_stop();
#endif
					break;
				}
			}
			break;

		default:
			break;
		}

		size_t ia_pd_len, ia_na_len, server_id_len;
		odhcp6c_get_state(STATE_IA_PD, &ia_pd_len);
		odhcp6c_get_state(STATE_IA_NA, &ia_na_len);
		odhcp6c_get_state(STATE_SERVER_ID, &server_id_len);

		// Add all prefixes to lost prefixes
		bound = false;
		script_call("unbound");

		if (server_id_len > 0 && (ia_pd_len > 0 || ia_na_len > 0) && release)
			dhcpv6_request(DHCPV6_MSG_RELEASE);

		odhcp6c_clear_state(STATE_IA_NA);
		odhcp6c_clear_state(STATE_IA_PD);
	}

	script_call("stopped");
	return 0;
}