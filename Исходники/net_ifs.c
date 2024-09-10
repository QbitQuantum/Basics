/*
 * Allocate and fill in the interfaces global variable with the
 * machine's ip addresses and netmasks.
 */
int
get_net_ifs(char **addrinfo)
{
    struct ifconf *ifconf;
    struct ifreq *ifr, ifr_tmp;
    struct sockaddr_in *sin;
    int ailen, i, len, n, sock, num_interfaces = 0;
    size_t buflen = sizeof(struct ifconf) + BUFSIZ;
    char *cp, *previfname = "", *ifconf_buf = NULL;
#ifdef _ISC
    struct strioctl strioctl;
#endif /* _ISC */
    debug_decl(get_net_ifs, SUDO_DEBUG_NETIF)

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
	error(1, _("unable to open socket"));

    /*
     * Get interface configuration or return.
     */
    for (;;) {
	ifconf_buf = emalloc(buflen);
	ifconf = (struct ifconf *) ifconf_buf;
	ifconf->ifc_len = buflen - sizeof(struct ifconf);
	ifconf->ifc_buf = (caddr_t) (ifconf_buf + sizeof(struct ifconf));

#ifdef _ISC
	STRSET(SIOCGIFCONF, (caddr_t) ifconf, buflen);
	if (ioctl(sock, I_STR, (caddr_t) &strioctl) < 0)
#else
	/* Note that some kernels return EINVAL if the buffer is too small */
	if (ioctl(sock, SIOCGIFCONF, (caddr_t) ifconf) < 0 && errno != EINVAL)
#endif /* _ISC */
	    goto done;

	/* Break out of loop if we have a big enough buffer. */
	if (ifconf->ifc_len + sizeof(struct ifreq) < buflen)
	    break;
	buflen += BUFSIZ;
	efree(ifconf_buf);
    }

    /* Allocate space for the maximum number of interfaces that could exist. */
    if ((n = ifconf->ifc_len / sizeof(struct ifreq)) == 0)
	debug_return_int(0);
    ailen = n * 2 * INET6_ADDRSTRLEN;
    *addrinfo = cp = emalloc(ailen);

    /* For each interface, store the ip address and netmask. */
    for (i = 0; i < ifconf->ifc_len; ) {
	/* Get a pointer to the current interface. */
	ifr = (struct ifreq *) &ifconf->ifc_buf[i];

	/* Set i to the subscript of the next interface. */
	i += sizeof(struct ifreq);
#ifdef HAVE_STRUCT_SOCKADDR_SA_LEN
	if (ifr->ifr_addr.sa_len > sizeof(ifr->ifr_addr))
	    i += ifr->ifr_addr.sa_len - sizeof(struct sockaddr);
#endif /* HAVE_STRUCT_SOCKADDR_SA_LEN */

	/* Skip duplicates and interfaces with NULL addresses. */
	sin = (struct sockaddr_in *) &ifr->ifr_addr;
	if (sin->sin_addr.s_addr == 0 ||
	    strncmp(previfname, ifr->ifr_name, sizeof(ifr->ifr_name) - 1) == 0)
	    continue;

	if (ifr->ifr_addr.sa_family != AF_INET)
		continue;

#ifdef SIOCGIFFLAGS
	memset(&ifr_tmp, 0, sizeof(ifr_tmp));
	strncpy(ifr_tmp.ifr_name, ifr->ifr_name, sizeof(ifr_tmp.ifr_name) - 1);
	if (ioctl(sock, SIOCGIFFLAGS, (caddr_t) &ifr_tmp) < 0)
#endif
	    ifr_tmp = *ifr;
	
	/* Skip interfaces marked "down" and "loopback". */
	if (!ISSET(ifr_tmp.ifr_flags, IFF_UP) ||
	    ISSET(ifr_tmp.ifr_flags, IFF_LOOPBACK))
		continue;

	sin = (struct sockaddr_in *) &ifr->ifr_addr;
	len = snprintf(cp, ailen - (*addrinfo - cp),
	    "%s%s/", cp == *addrinfo ? "" : " ",
	    inet_ntoa(sin->sin_addr));
	if (len <= 0 || len >= ailen - (*addrinfo - cp)) {
	    warningx(_("load_interfaces: overflow detected"));
	    goto done;
	}
	cp += len;

	/* Stash the name of the interface we saved. */
	previfname = ifr->ifr_name;

	/* Get the netmask. */
	memset(&ifr_tmp, 0, sizeof(ifr_tmp));
	strncpy(ifr_tmp.ifr_name, ifr->ifr_name, sizeof(ifr_tmp.ifr_name) - 1);
#ifdef _ISC
	STRSET(SIOCGIFNETMASK, (caddr_t) &ifr_tmp, sizeof(ifr_tmp));
	if (ioctl(sock, I_STR, (caddr_t) &strioctl) < 0) {
#else
	if (ioctl(sock, SIOCGIFNETMASK, (caddr_t) &ifr_tmp) < 0) {
#endif /* _ISC */
	    sin = (struct sockaddr_in *) &ifr_tmp.ifr_addr;
	    sin->sin_addr.s_addr = htonl(IN_CLASSC_NET);
	}
	sin = (struct sockaddr_in *) &ifr_tmp.ifr_addr;
	len = snprintf(cp, ailen - (*addrinfo - cp),
	    "%s", inet_ntoa(sin->sin_addr));
	if (len <= 0 || len >= ailen - (*addrinfo - cp)) {
	    warningx(_("load_interfaces: overflow detected"));
	    goto done;
	}
	cp += len;
	num_interfaces++;
    }

done:
    efree(ifconf_buf);
    (void) close(sock);

    debug_return_int(num_interfaces);
}

#else /* !SIOCGIFCONF || STUB_LOAD_INTERFACES */

/*
 * Stub function for those without SIOCGIFCONF or getifaddrs()
 */
int
get_net_ifs(char **addrinfo)
{
    debug_decl(get_net_ifs, SUDO_DEBUG_NETIF)
    debug_return_int(0);
}