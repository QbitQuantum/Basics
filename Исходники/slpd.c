int
main(int argc, char *const *argv)
{
	struct sockaddr_in bindaddr;
	socklen_t addrlen;
	const char *isDA;
	const char *proxyReg;
	int connfd;
	int lfd;
	const int on = 1;

	detachfromtty();

	openlog("slpd", LOG_PID, LOG_DAEMON);

	do_args(argc, argv);

	/* If slpd has been configured to run as a DA, start it and exit */
	isDA = SLPGetProperty("net.slp.isDA");
	proxyReg = SLPGetProperty("net.slp.serializedRegURL");
	if ((isDA && (strcasecmp(isDA, "true") == 0)) || proxyReg) {
		run_slpd();
		return (1);
	}

	if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		syslog(LOG_ERR, "socket failed: %s", strerror(errno));
		cleanup_and_exit(1);
	}

	(void) setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on));

	(void) memset((void *)&bindaddr, 0, sizeof (bindaddr));
	bindaddr.sin_family = AF_INET;
	bindaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	bindaddr.sin_port = htons(427);

	if (bind(lfd, (const struct sockaddr *)&bindaddr, sizeof (bindaddr))
	    < 0) {
		syslog(LOG_ERR, "bind failed: %s", strerror(errno));
		cleanup_and_exit(1);
	}

	if (listen(lfd, 1) < 0) {
		syslog(LOG_ERR, "listen failed: %s", strerror(errno));
		cleanup_and_exit(1);
	}

	addrlen = sizeof (bindaddr);
	if ((connfd = accept(lfd, (struct sockaddr *)&bindaddr, &addrlen))
	    < 0) {
		syslog(LOG_ERR, "accept failed: %s", strerror(errno));
		cleanup_and_exit(1);
	}

	(void) close(lfd);

	(void) dup2(connfd, 0);
	(void) close(connfd);
	(void) dup2(0, 1);
	(void) dup2(0, 2);

	run_slpd();

	return (1);
}