int telnet_main(int argc, char **argv)
{
	char *host;
	int port;
	int len;
#ifdef USE_POLL
	struct pollfd ufds[2];
#else
	fd_set readfds;
	int maxfd;
#endif

	INIT_G();

#if ENABLE_FEATURE_AUTOWIDTH
	get_terminal_width_height(0, &G.win_width, &G.win_height);
#endif

#if ENABLE_FEATURE_TELNET_TTYPE
	G.ttype = getenv("TERM");
#endif

	if (tcgetattr(0, &G.termios_def) >= 0) {
		G.do_termios = 1;
		G.termios_raw = G.termios_def;
		cfmakeraw(&G.termios_raw);
	}

	if (argc < 2)
		bb_show_usage();

#if ENABLE_FEATURE_TELNET_AUTOLOGIN
	if (1 & getopt32(argv, "al:", &G.autologin))
		G.autologin = getenv("USER");
	argv += optind;
#else
	argv++;
#endif
	if (!*argv)
		bb_show_usage();
	host = *argv++;
	port = bb_lookup_port(*argv ? *argv++ : "telnet", "tcp", 23);
	if (*argv) /* extra params?? */
		bb_show_usage();

	G.netfd = create_and_connect_stream_or_die(host, port);

	setsockopt(G.netfd, SOL_SOCKET, SO_KEEPALIVE, &const_int_1, sizeof(const_int_1));

	signal(SIGINT, fgotsig);

#ifdef USE_POLL
	ufds[0].fd = 0; ufds[1].fd = G.netfd;
	ufds[0].events = ufds[1].events = POLLIN;
#else
	FD_ZERO(&readfds);
	FD_SET(0, &readfds);
	FD_SET(G.netfd, &readfds);
	maxfd = G.netfd + 1;
#endif

	while (1) {
#ifndef USE_POLL
		fd_set rfds = readfds;

		switch (select(maxfd, &rfds, NULL, NULL, NULL))
#else
		switch (poll(ufds, 2, -1))
#endif
		{
		case 0:
			/* timeout */
		case -1:
			/* error, ignore and/or log something, bay go to loop */
			if (G.gotsig)
				conescape();
			else
				sleep(1);
			break;
		default:

#ifdef USE_POLL
			if (ufds[0].revents) /* well, should check POLLIN, but ... */
#else
			if (FD_ISSET(0, &rfds))
#endif
			{
				len = read(0, G.buf, DATABUFSIZE);
				if (len <= 0)
					doexit(0);
				TRACE(0, ("Read con: %d\n", len));
				handlenetoutput(len);
			}

#ifdef USE_POLL
			if (ufds[1].revents) /* well, should check POLLIN, but ... */
#else
			if (FD_ISSET(G.netfd, &rfds))
#endif
			{
				len = read(G.netfd, G.buf, DATABUFSIZE);
				if (len <= 0) {
					write_str(1, "Connection closed by foreign host\r\n");
					doexit(1);
				}
				TRACE(0, ("Read netfd (%d): %d\n", G.netfd, len));
				handlenetinput(len);
			}
		}
	}
}