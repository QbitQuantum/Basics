/*
 * Return a socket bound to an appropriate port number/address. Exits
 * the program on failure.
 */
static int
get_socket(int **sa, int *nsa)
{
    char	host[NI_MAXHOST], serv[NI_MAXHOST];
    struct addrinfo hint, *res, *rp;
    u_long inaddr;
    int		ecode,
		flag,
		kalive = 1,
		s;

    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    hint.ai_flags = AI_PASSIVE;
#ifdef AI_ADDRCONFIG
    hint.ai_flags |= AI_ADDRCONFIG;
#endif
    if (bind_address)
	ecode = getaddrinfo(bind_address, portstr, &hint, &res);
    else
	ecode = getaddrinfo(NULL, portstr, &hint, &res);
    if (ecode != 0) {
	report(LOG_ERR, "getaddrinfo: %s\n", gai_strerror(ecode));
	    tac_exit(1);
	}

    *sa = NULL;
    *nsa = 0;
    for (rp = res; rp != NULL; rp = rp->ai_next) {
	s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	if (s == -1)
	    continue;

	if (1 || debug & DEBUG_PACKET_FLAG)
	    report(LOG_DEBUG, "socket FD %d AF %d", s, rp->ai_family);
	flag = 1;
	if (rp->ai_family == AF_INET6)
	    setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &flag, sizeof(flag));
#ifdef SO_REUSEADDR
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&flag,
		       sizeof(flag)) < 0)
	perror("setsockopt - SO_REUSEADDR");
#endif
    if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (void *)&kalive,
		   sizeof(kalive)) < 0)
	    perror("setsockopt - SO_KEEPALIVE");
	flag = 0;
	if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char *)&flag,
		       sizeof(flag)) < 0)
	    perror("setsockopt - SO_NODELAY");

	if (bind(s, rp->ai_addr, rp->ai_addrlen) < 0) {
	    console = 1;
	    ecode = errno;
	    if (lookup_peer)
		flag = 0;
	    else
		flag = NI_NUMERICHOST | NI_NUMERICSERV;
	    if (getnameinfo(rp->ai_addr, rp->ai_addrlen, host, NI_MAXHOST,
			    serv, NI_MAXHOST, flag)) {
		strncpy(host, "unknown", NI_MAXHOST - 1);
		host[NI_MAXHOST - 1] = '\0';
		strncpy(serv, "unknown", NI_MAXHOST - 1);
		serv[NI_MAXHOST - 1] = '\0';
	    }
	    report(LOG_ERR, "get_socket: bind %s:%s %s", host, serv,
		   strerror(ecode));
	    console = 0;
	    close(s);
	    s = -1;
	    continue;
	}
	if (*sa == NULL)
	    *sa = malloc(sizeof(int) * ++(*nsa));
	else
	    *sa = realloc(*sa, sizeof(int) * ++(*nsa));
	if (*sa == NULL) {
	    report(LOG_ERR, "malloc failure: %s", strerror(errno));
	tac_exit(1);
    }
	(*sa)[*nsa - 1] = s;
    }
    freeaddrinfo(res);

    if (*nsa < 1) {
	console = 1;
	report(LOG_ERR, "get_socket: could not bind a listening socket");
	tac_exit(1);
    }
    return(0);
}