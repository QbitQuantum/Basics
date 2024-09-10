char *
inet6name(const unsigned char *in6)
{
	char *cp;
	static char line[NI_MAXHOST];
	static char domain[MAXHOSTNAMELEN];
	static int first = 1;
#ifdef NETSNMP_ENABLE_IPV6
	struct hostent *hp;
	char hbuf[NI_MAXHOST];
	const int niflag = NI_NUMERICHOST;
	struct sockaddr_in6 sin6;
	const struct in6_addr *in6p = (const struct in6_addr *)in6;
#endif

	if (first && !nflag) {
		first = 0;
		if (gethostname(line, sizeof(line)) == 0 &&
		    (cp = strchr(line, '.')))
			(void) strlcpy(domain, cp + 1, sizeof domain);
		else
			domain[0] = '\0';
	}
#ifdef NETSNMP_ENABLE_IPV6
	cp = NULL;
	if (!nflag && !IN6_IS_ADDR_UNSPECIFIED(in6p)) {
		hp = netsnmp_gethostbyaddr((const char *)in6p, sizeof(*in6p),
                                           AF_INET6);
		if (hp) {
			if ((cp = strchr(hp->h_name, '.')) &&
			    !strcmp(cp + 1, domain))
				*cp = 0;
			cp = hp->h_name;
		}
	}
	if (IN6_IS_ADDR_UNSPECIFIED(in6p))
		strlcpy(line, "*", sizeof(line));
	else if (cp)
		strlcpy(line, cp, sizeof(line));
	else {
		memset(&sin6, 0, sizeof(sin6));
/*		sin6.sin6_len = sizeof(sin6);   */
		sin6.sin6_family = AF_INET6;
		sin6.sin6_addr = *in6p;
#ifdef __KAME__
		if (IN6_IS_ADDR_LINKLOCAL(in6p) ||
		    IN6_IS_ADDR_MC_LINKLOCAL(in6p)) {
			sin6.sin6_scope_id =
			    ntohs(*(const uint16_t *)&in6p->s6_addr[2]);
			sin6.sin6_addr.s6_addr[2] = 0;
			sin6.sin6_addr.s6_addr[3] = 0;
		}
#endif
		if (getnameinfo((struct sockaddr *)&sin6, sizeof(sin6),
		    hbuf, sizeof(hbuf), NULL, 0, niflag) != 0)
			strlcpy(hbuf, "?", sizeof hbuf);
		strlcpy(line, hbuf, sizeof(line));
	}
#else
	strlcpy(line, "[[XXX - inet6 address]]", sizeof(line));
#endif
	return (line);
}