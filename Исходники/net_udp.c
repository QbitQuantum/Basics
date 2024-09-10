static const char *udp_host_addr6(socket_udp *s)
{
#ifdef HAVE_IPv6
	static char		 hname[MAXHOSTNAMELEN];
	int 			 gai_err, newsock;
	struct addrinfo 	 hints, *ai;
	struct sockaddr_in6 	 local, addr6;
	int len = sizeof(local), result = 0;

	newsock=socket(AF_INET6, SOCK_DGRAM,0);
    memset ((char *)&addr6, 0, len);
    addr6.sin6_family = AF_INET6;
#ifdef HAVE_SIN6_LEN
    addr6.sin6_len    = len;
#endif
    bind (newsock, (struct sockaddr *) &addr6, len);
    addr6.sin6_addr = s->addr6;
    addr6.sin6_port = htons (s->rx_port);
    connect (newsock, (struct sockaddr *) &addr6, len);

    memset ((char *)&local, 0, len);
	if ((result = getsockname(newsock,(struct sockaddr *)&local, &len)) < 0){
		local.sin6_addr = in6addr_any;
		local.sin6_port = 0;
		debug_msg("getsockname failed\n");
	}

	close (newsock);

	if (IN6_IS_ADDR_UNSPECIFIED(&local.sin6_addr) || IN6_IS_ADDR_MULTICAST(&local.sin6_addr)) {
		if (gethostname(hname, MAXHOSTNAMELEN) != 0) {
			debug_msg("gethostname failed\n");
			abort();
		}
		
		hints.ai_protocol  = 0;
		hints.ai_flags     = 0;
		hints.ai_family    = AF_INET6;
		hints.ai_socktype  = SOCK_DGRAM;
		hints.ai_addrlen   = 0;
		hints.ai_canonname = NULL;
		hints.ai_addr      = NULL;
		hints.ai_next      = NULL;

		if ((gai_err = getaddrinfo(hname, NULL, &hints, &ai))) {
			debug_msg("getaddrinfo: %s: %s\n", hname, gai_strerror(gai_err));
			abort();
		}
		
		if (inet_ntopxp(AF_INET6, &(((struct sockaddr_in6 *)(ai->ai_addr))->sin6_addr), hname, MAXHOSTNAMELEN) == NULL) {
			debug_msg("inet_ntop: %s: \n", hname);
			abort();
		}
		freeaddrinfo(ai);
		return (const char*)hname;
	}
	if (inet_ntopxp(AF_INET6, &local.sin6_addr, hname, MAXHOSTNAMELEN) == NULL) {
		debug_msg("inet_ntop: %s: \n", hname);
		abort();
	}
	return (const char*)hname;
#else  /* HAVE_IPv6 */
	UNUSED(s);
	return "::";	/* The unspecified address... */
#endif /* HAVE_IPv6 */
}