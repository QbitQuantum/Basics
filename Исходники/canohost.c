static char *
get_remote_hostname(int sock, int use_dns)
{
	struct sockaddr_storage from;
	int i;
	socklen_t fromlen;
	struct addrinfo hints, *ai, *aitop;
	char name[NI_MAXHOST], ntop[NI_MAXHOST], ntop2[NI_MAXHOST];

	/* Get IP address of client. */
	fromlen = sizeof(from);
	memset(&from, 0, sizeof(from));
	if (getpeername(sock, (struct sockaddr *)&from, &fromlen) < 0) {
		debug("getpeername failed: %.100s", strerror(errno));
		cleanup_exit(255);
	}

	if (from.ss_family == AF_INET)
		check_ip_options(sock, ntop);

	ipv64_normalise_mapped(&from, &fromlen);

	if (from.ss_family == AF_INET6)
		fromlen = sizeof(struct sockaddr_in6);

	if (getnameinfo((struct sockaddr *)&from, fromlen, ntop, sizeof(ntop),
	    NULL, 0, NI_NUMERICHOST) != 0)
		fatal("get_remote_hostname: getnameinfo NI_NUMERICHOST failed");

	if (!use_dns)
		return xstrdup(ntop);

	debug3("Trying to reverse map address %.100s.", ntop);
	/* Map the IP address to a host name. */
	if (getnameinfo((struct sockaddr *)&from, fromlen, name, sizeof(name),
	    NULL, 0, NI_NAMEREQD) != 0) {
		/* Host name not found.  Use ip address. */
		return xstrdup(ntop);
	}

	/*
	 * if reverse lookup result looks like a numeric hostname,
	 * someone is trying to trick us by PTR record like following:
	 *	1.1.1.10.in-addr.arpa.	IN PTR	2.3.4.5
	 */
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_DGRAM;	/*dummy*/
	hints.ai_flags = AI_NUMERICHOST;
	if (getaddrinfo(name, NULL, &hints, &ai) == 0) {
		logit("Nasty PTR record \"%s\" is set up for %s, ignoring",
		    name, ntop);
		freeaddrinfo(ai);
		return xstrdup(ntop);
	}

	/*
	 * Convert it to all lowercase (which is expected by the rest
	 * of this software).
	 */
	for (i = 0; name[i]; i++)
		if (isupper(name[i]))
			name[i] = (char)tolower(name[i]);
	/*
	 * Map it back to an IP address and check that the given
	 * address actually is an address of this host.  This is
	 * necessary because anyone with access to a name server can
	 * define arbitrary names for an IP address. Mapping from
	 * name to IP address can be trusted better (but can still be
	 * fooled if the intruder has access to the name server of
	 * the domain).
	 */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = from.ss_family;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(name, NULL, &hints, &aitop) != 0) {
		logit("reverse mapping checking getaddrinfo for %.700s "
		    "[%s] failed - POSSIBLE BREAK-IN ATTEMPT!", name, ntop);
		return xstrdup(ntop);
	}
	/* Look for the address from the list of addresses. */
	for (ai = aitop; ai; ai = ai->ai_next) {
		if (getnameinfo(ai->ai_addr, ai->ai_addrlen, ntop2,
		    sizeof(ntop2), NULL, 0, NI_NUMERICHOST) == 0 &&
		    (strcmp(ntop, ntop2) == 0))
				break;
	}
	freeaddrinfo(aitop);
	/* If we reached the end of the list, the address was not there. */
	if (!ai) {
		/* Address not found for the host name. */
		logit("Address %.100s maps to %.600s, but this does not "
		    "map back to the address - POSSIBLE BREAK-IN ATTEMPT!",
		    ntop, name);
		return xstrdup(ntop);
	}
	return xstrdup(name);
}