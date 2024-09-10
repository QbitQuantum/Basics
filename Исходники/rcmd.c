int
rcmd_af(char **ahost, int rport, const char *locuser, const char *remuser,
	const char *cmd, int *fd2p, int af)
{
	struct addrinfo hints, *res, *ai;
	struct sockaddr_storage from;
	fd_set reads;
	sigset_t oldmask, newmask;
	pid_t pid;
	int s, aport, lport, timo, error;
	char c, *p;
	int refused, nres;
	char num[8];
	static char canonnamebuf[MAXDNAME];	/* is it proper here? */

	/* call rcmdsh() with specified remote shell if appropriate. */
	if (!issetugid() && (p = getenv("RSH"))) {
		struct servent *sp = getservbyname("shell", "tcp");

		if (sp && sp->s_port == rport)
			return (rcmdsh(ahost, rport, locuser, remuser,
			    cmd, p));
	}

	/* use rsh(1) if non-root and remote port is shell. */
	if (geteuid()) {
		struct servent *sp = getservbyname("shell", "tcp");

		if (sp && sp->s_port == rport)
			return (rcmdsh(ahost, rport, locuser, remuser,
			    cmd, NULL));
	}

	pid = getpid();

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = af;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	snprintf(num, sizeof(num), "%d", ntohs(rport));
	error = getaddrinfo(*ahost, num, &hints, &res);
	if (error) {
		fprintf(stderr, "rcmd: getaddrinfo: %s\n",
			gai_strerror(error));
		if (error == EAI_SYSTEM)
			fprintf(stderr, "rcmd: getaddrinfo: %s\n",
				strerror(errno));
		return (-1);
	}

	if (res->ai_canonname &&
	    strlen(res->ai_canonname) + 1 < sizeof(canonnamebuf)) {
		strncpy(canonnamebuf, res->ai_canonname, sizeof(canonnamebuf));
		*ahost = canonnamebuf;
	}
	nres = 0;
	for (ai = res; ai; ai = ai->ai_next)
		nres++;
	ai = res;
	refused = 0;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGURG);
	_sigprocmask(SIG_BLOCK, (const sigset_t *)&newmask, &oldmask);
	for (timo = 1, lport = IPPORT_RESERVED - 1;;) {
		s = rresvport_af(&lport, ai->ai_family);
		if (s < 0) {
			if (errno != EAGAIN && ai->ai_next) {
				ai = ai->ai_next;
				continue;
			}
			if (errno == EAGAIN)
				fprintf(stderr,
				    "rcmd: socket: All ports in use\n");
			else
				fprintf(stderr, "rcmd: socket: %s\n",
				    strerror(errno));
			freeaddrinfo(res);
			_sigprocmask(SIG_SETMASK, (const sigset_t *)&oldmask,
			    NULL);
			return (-1);
		}
		_fcntl(s, F_SETOWN, pid);
		if (_connect(s, ai->ai_addr, ai->ai_addrlen) >= 0)
			break;
		_close(s);
		if (errno == EADDRINUSE) {
			lport--;
			continue;
		}
		if (errno == ECONNREFUSED)
			refused = 1;
		if (ai->ai_next == NULL && (!refused || timo > 16)) {
			fprintf(stderr, "%s: %s\n", *ahost, strerror(errno));
			freeaddrinfo(res);
			_sigprocmask(SIG_SETMASK, (const sigset_t *)&oldmask,
			    NULL);
			return (-1);
		}
		if (nres > 1) {
			int oerrno = errno;

			getnameinfo(ai->ai_addr, ai->ai_addrlen, paddr,
			    sizeof(paddr), NULL, 0, NI_NUMERICHOST);
			fprintf(stderr, "connect to address %s: ", paddr);
			errno = oerrno;
			perror(0);
		}
		if ((ai = ai->ai_next) == NULL) {
			/* refused && timo <= 16 */
			struct timespec time_to_sleep, time_remaining;

			time_to_sleep.tv_sec = timo;
			time_to_sleep.tv_nsec = 0;
			_nanosleep(&time_to_sleep, &time_remaining);
			timo *= 2;
			ai = res;
			refused = 0;
		}
		if (nres > 1) {
			getnameinfo(ai->ai_addr, ai->ai_addrlen, paddr,
			    sizeof(paddr), NULL, 0, NI_NUMERICHOST);
			fprintf(stderr, "Trying %s...\n", paddr);
		}
	}
	lport--;
	if (fd2p == 0) {
		_write(s, "", 1);
		lport = 0;
	} else {
		int s2 = rresvport_af(&lport, ai->ai_family), s3;
		socklen_t len = ai->ai_addrlen;
		int nfds;

		if (s2 < 0)
			goto bad;
		_listen(s2, 1);
		snprintf(num, sizeof(num), "%d", lport);
		if (_write(s, num, strlen(num)+1) != strlen(num)+1) {
			fprintf(stderr,
			    "rcmd: write (setting up stderr): %s\n",
			    strerror(errno));
			_close(s2);
			goto bad;
		}
		nfds = max(s, s2)+1;
		if(nfds > FD_SETSIZE) {
			fprintf(stderr, "rcmd: too many files\n");
			_close(s2);
			goto bad;
		}
again:
		FD_ZERO(&reads);
		FD_SET(s, &reads);
		FD_SET(s2, &reads);
		errno = 0;
		if (_select(nfds, &reads, 0, 0, 0) < 1 || !FD_ISSET(s2, &reads)){
			if (errno != 0)
				fprintf(stderr,
				    "rcmd: select (setting up stderr): %s\n",
				    strerror(errno));
			else
				fprintf(stderr,
				"select: protocol failure in circuit setup\n");
			_close(s2);
			goto bad;
		}
		s3 = _accept(s2, (struct sockaddr *)&from, &len);
		switch (from.ss_family) {
		case AF_INET:
			aport = ntohs(((struct sockaddr_in *)&from)->sin_port);
			break;
#ifdef INET6
		case AF_INET6:
			aport = ntohs(((struct sockaddr_in6 *)&from)->sin6_port);
			break;
#endif
		default:
			aport = 0;	/* error */
			break;
		}
		/*
		 * XXX careful for ftp bounce attacks. If discovered, shut them
		 * down and check for the real auxiliary channel to connect.
		 */
		if (aport == 20) {
			_close(s3);
			goto again;
		}
		_close(s2);
		if (s3 < 0) {
			fprintf(stderr,
			    "rcmd: accept: %s\n", strerror(errno));
			lport = 0;
			goto bad;
		}
		*fd2p = s3;
		if (aport >= IPPORT_RESERVED || aport < IPPORT_RESERVED / 2) {
			fprintf(stderr,
			    "socket: protocol failure in circuit setup.\n");
			goto bad2;
		}
	}
	_write(s, locuser, strlen(locuser)+1);
	_write(s, remuser, strlen(remuser)+1);
	_write(s, cmd, strlen(cmd)+1);
	if (_read(s, &c, 1) != 1) {
		fprintf(stderr,
		    "rcmd: %s: %s\n", *ahost, strerror(errno));
		goto bad2;
	}
	if (c != 0) {
		while (_read(s, &c, 1) == 1) {
			_write(STDERR_FILENO, &c, 1);
			if (c == '\n')
				break;
		}
		goto bad2;
	}
	_sigprocmask(SIG_SETMASK, (const sigset_t *)&oldmask, NULL);
	freeaddrinfo(res);
	return (s);
bad2:
	if (lport)
		_close(*fd2p);
bad:
	_close(s);
	_sigprocmask(SIG_SETMASK, (const sigset_t *)&oldmask, NULL);
	freeaddrinfo(res);
	return (-1);
}