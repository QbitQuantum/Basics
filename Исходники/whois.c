static void
whois(const char *query, const char *hostname, int flags)
{
	FILE *fp;
	struct addrinfo *hostres, *res;
	char *buf, *host, *nhost, *p;
	int s = -1, f;
	nfds_t i, j;
	size_t len, count;
	struct pollfd *fds;
	int timeout = 180;

	hostres = gethostinfo(hostname, 1);
	for (res = hostres, count = 0; res; res = res->ai_next)
		count++;
	fds = calloc(count, sizeof(*fds));
	if (fds == NULL)
		err(EX_OSERR, "calloc()");

	/*
	 * Traverse the result list elements and make non-block
	 * connection attempts.
	 */
	count = i = 0;
	for (res = hostres; res != NULL; res = res->ai_next) {
		s = socket(res->ai_family, res->ai_socktype | SOCK_NONBLOCK,
		    res->ai_protocol);
		if (s < 0)
			continue;
		if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
			if (errno == EINPROGRESS) {
				/* Add the socket to poll list */
				fds[i].fd = s;
				fds[i].events = POLLERR | POLLHUP |
						POLLIN | POLLOUT;
				count++;
				i++;
			} else {
				close(s);
				s = -1;

				/*
				 * Poll only if we have something to poll,
				 * otherwise just go ahead and try next
				 * address
				 */
				if (count == 0)
					continue;
			}
		} else
			goto done;

		/*
		 * If we are at the last address, poll until a connection is
		 * established or we failed all connection attempts.
		 */
		if (res->ai_next == NULL)
			timeout = INFTIM;

		/*
		 * Poll the watched descriptors for successful connections:
		 * if we still have more untried resolved addresses, poll only
		 * once; otherwise, poll until all descriptors have errors,
		 * which will be considered as ETIMEDOUT later.
		 */
		do {
			int n;

			n = poll(fds, i, timeout);
			if (n == 0) {
				/*
				 * No event reported in time.  Try with a
				 * smaller timeout (but cap at 2-3ms)
				 * after a new host have been added.
				 */
				if (timeout >= 3)
					timeout <<= 1;

				break;
			} else if (n < 0) {
				/*
				 * errno here can only be EINTR which we would
				 * want to clean up and bail out.
				 */
				s = -1;
				goto done;
			}

			/*
			 * Check for the event(s) we have seen.
			 */
			for (j = 0; j < i; j++) {
				if (fds[j].fd == -1 || fds[j].events == 0 ||
				    fds[j].revents == 0)
					continue;
				if (fds[j].revents & ~(POLLIN | POLLOUT)) {
					close(s);
					fds[j].fd = -1;
					fds[j].events = 0;
					count--;
					continue;
				} else if (fds[j].revents & (POLLIN | POLLOUT)) {
					/* Connect succeeded. */
					s = fds[j].fd;

					goto done;
				}

			}
		} while (timeout == INFTIM && count != 0);
	}

	/* All attempts were failed */
	s = -1;
	if (count == 0)
		errno = ETIMEDOUT;
done:
	if (s == -1)
		err(EX_OSERR, "connect()");

	/* Close all watched fds except the succeeded one */
	for (j = 0; j < i; j++)
		if (fds[j].fd != s && fds[j].fd != -1)
			close(fds[j].fd);
	free(fds);

	/* Restore default blocking behavior.  */
	if ((f = fcntl(s, F_GETFL)) == -1)
		err(EX_OSERR, "fcntl()");
	f &= ~O_NONBLOCK;
	if (fcntl(s, F_SETFL, f) == -1)
		err(EX_OSERR, "fcntl()");

	fp = fdopen(s, "r+");
	if (fp == NULL)
		err(EX_OSERR, "fdopen()");

	if (!(flags & WHOIS_SPAM_ME) &&
	    (strcasecmp(hostname, DENICHOST) == 0 ||
	     strcasecmp(hostname, "de" QNICHOST_TAIL) == 0)) {
		const char *q;
		int idn = 0;
		for (q = query; *q != '\0'; q++)
			if (!isascii(*q))
				idn = 1;
		fprintf(fp, "-T dn%s %s\r\n", idn ? "" : ",ace", query);
	} else if (!(flags & WHOIS_SPAM_ME) &&
		   (strcasecmp(hostname, DKNICHOST) == 0 ||
		    strcasecmp(hostname, "dk" QNICHOST_TAIL) == 0))
		fprintf(fp, "--show-handles %s\r\n", query);
	else if ((flags & WHOIS_SPAM_ME) ||
		 strchr(query, ' ') != NULL)
		fprintf(fp, "%s\r\n", query);
	else if (strcasecmp(hostname, ANICHOST) == 0) {
		if (strncasecmp(query, "AS", 2) == 0 &&
		    strspn(query+2, "0123456789") == strlen(query+2))
			fprintf(fp, "+ a %s\r\n", query+2);
		else
			fprintf(fp, "+ %s\r\n", query);
	} else if (strcasecmp(hostres->ai_canonname, VNICHOST) == 0)
		fprintf(fp, "domain %s\r\n", query);
	else
		fprintf(fp, "%s\r\n", query);
	fflush(fp);

	nhost = NULL;
	while ((buf = fgetln(fp, &len)) != NULL) {
		/* Nominet */
		if (!(flags & WHOIS_SPAM_ME) &&
		    len == 5 && strncmp(buf, "-- \r\n", 5) == 0)
			break;

		printf("%.*s", (int)len, buf);

		if ((flags & WHOIS_RECURSE) && nhost == NULL) {
			for (i = 0; whois_referral[i].prefix != NULL; i++) {
				p = buf;
				SCAN(p, buf+len, *p == ' ');
				if (strncasecmp(p, whois_referral[i].prefix,
					           whois_referral[i].len) != 0)
					continue;
				p += whois_referral[i].len;
				SCAN(p, buf+len, *p == ' ');
				host = p;
				SCAN(p, buf+len, ishost(*p));
				/* avoid loops */
				if (strncmp(hostname, host, p - host) != 0)
					s_asprintf(&nhost, "%.*s",
						   (int)(p - host), host);
				break;
			}
			for (i = 0; actually_arin[i] != NULL; i++) {
				if (strncmp(buf, actually_arin[i], len) == 0) {
					s_asprintf(&nhost, "%s", ANICHOST);
					break;
				}
			}
		}
		/* Verisign etc. */
		if (!(flags & WHOIS_SPAM_ME) &&
		    len >= sizeof(CHOPSPAM)-1 &&
		    (strncasecmp(buf, CHOPSPAM, sizeof(CHOPSPAM)-1) == 0 ||
		     strncasecmp(buf, CHOPSPAM+4, sizeof(CHOPSPAM)-5) == 0)) {
			printf("\n");
			break;
		}
	}
	fclose(fp);
	freeaddrinfo(hostres);
	if (nhost != NULL) {
		whois(query, nhost, flags);
		free(nhost);
	}
}