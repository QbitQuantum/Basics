/*
 * Allocate and fill in the interfaces global variable with the
 * machine's ip addresses and netmasks.
 */
void
load_interfaces()
{
    struct ifconf *ifconf;
    struct ifreq *ifr, ifr_tmp;
    struct sockaddr_in *sin;
    int sock, n, i;
    size_t len = sizeof(struct ifconf) + BUFSIZ;
    char *previfname = "", *ifconf_buf = NULL;
#ifdef _ISC
    struct strioctl strioctl;
#endif /* _ISC */

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
	error(1, "cannot open socket");

    /*
     * Get interface configuration or return (leaving num_interfaces == 0)
     */
    for (;;) {
	ifconf_buf = erealloc(ifconf_buf, len);
	ifconf = (struct ifconf *) ifconf_buf;
	ifconf->ifc_len = len - sizeof(struct ifconf);
	ifconf->ifc_buf = (caddr_t) (ifconf_buf + sizeof(struct ifconf));

#ifdef _ISC
	STRSET(SIOCGIFCONF, (caddr_t) ifconf, len);
	if (ioctl(sock, I_STR, (caddr_t) &strioctl) < 0) {
#else
	/* Note that some kernels return EINVAL if the buffer is too small */
	if (ioctl(sock, SIOCGIFCONF, (caddr_t) ifconf) < 0 && errno != EINVAL) {
#endif /* _ISC */
	    efree(ifconf_buf);
	    (void) close(sock);
	    return;
	}

	/* Break out of loop if we have a big enough buffer. */
	if (ifconf->ifc_len + sizeof(struct ifreq) < len)
	    break;
	len += BUFSIZ;
    }

    /* Allocate space for the maximum number of interfaces that could exist. */
    if ((n = ifconf->ifc_len / sizeof(struct ifreq)) == 0)
	return;
    interfaces = (struct interface *) emalloc2(n, sizeof(struct interface));

    /* For each interface, store the ip address and netmask. */
    for (i = 0; i < ifconf->ifc_len; ) {
	/* Get a pointer to the current interface. */
	ifr = (struct ifreq *) &ifconf->ifc_buf[i];

	/* Set i to the subscript of the next interface. */
	i += sizeof(struct ifreq);
#ifdef HAVE_SA_LEN
	if (ifr->ifr_addr.sa_len > sizeof(ifr->ifr_addr))
	    i += ifr->ifr_addr.sa_len - sizeof(struct sockaddr);
#endif /* HAVE_SA_LEN */

	/* Skip duplicates and interfaces with NULL addresses. */
	sin = (struct sockaddr_in *) &ifr->ifr_addr;
	if (sin->sin_addr.s_addr == 0 ||
	    strncmp(previfname, ifr->ifr_name, sizeof(ifr->ifr_name) - 1) == 0)
	    continue;

	if (ifr->ifr_addr.sa_family != AF_INET)
		continue;

#ifdef SIOCGIFFLAGS
	zero_bytes(&ifr_tmp, sizeof(ifr_tmp));
	strncpy(ifr_tmp.ifr_name, ifr->ifr_name, sizeof(ifr_tmp.ifr_name) - 1);
	if (ioctl(sock, SIOCGIFFLAGS, (caddr_t) &ifr_tmp) < 0)
#endif
	    ifr_tmp = *ifr;
	
	/* Skip interfaces marked "down" and "loopback". */
	if (!ISSET(ifr_tmp.ifr_flags, IFF_UP) ||
	    ISSET(ifr_tmp.ifr_flags, IFF_LOOPBACK))
		continue;

	sin = (struct sockaddr_in *) &ifr->ifr_addr;
	interfaces[num_interfaces].addr.ip4.s_addr = sin->sin_addr.s_addr;

	/* Stash the name of the interface we saved. */
	previfname = ifr->ifr_name;

	/* Get the netmask. */
	zero_bytes(&ifr_tmp, sizeof(ifr_tmp));
	strncpy(ifr_tmp.ifr_name, ifr->ifr_name, sizeof(ifr_tmp.ifr_name) - 1);
#ifdef SIOCGIFNETMASK
#ifdef _ISC
	STRSET(SIOCGIFNETMASK, (caddr_t) &ifr_tmp, sizeof(ifr_tmp));
	if (ioctl(sock, I_STR, (caddr_t) &strioctl) == 0) {
#else
	if (ioctl(sock, SIOCGIFNETMASK, (caddr_t) &ifr_tmp) == 0) {
#endif /* _ISC */
	    sin = (struct sockaddr_in *) &ifr_tmp.ifr_addr;

	    interfaces[num_interfaces].netmask.ip4.s_addr = sin->sin_addr.s_addr;
	} else {
#else
	{
#endif /* SIOCGIFNETMASK */
	    if (IN_CLASSC(interfaces[num_interfaces].addr.ip4.s_addr))
		interfaces[num_interfaces].netmask.ip4.s_addr = htonl(IN_CLASSC_NET);
	    else if (IN_CLASSB(interfaces[num_interfaces].addr.ip4.s_addr))
		interfaces[num_interfaces].netmask.ip4.s_addr = htonl(IN_CLASSB_NET);
	    else
		interfaces[num_interfaces].netmask.ip4.s_addr = htonl(IN_CLASSA_NET);
	}

	/* Only now can we be sure it was a good/interesting interface. */
	interfaces[num_interfaces].family = AF_INET;
	num_interfaces++;
    }

    /* If the expected size < real size, realloc the array. */
    if (n != num_interfaces) {
	if (num_interfaces != 0)
	    interfaces = (struct interface *) erealloc3(interfaces,
		num_interfaces, sizeof(struct interface));
	else
	    efree(interfaces);
    }
    efree(ifconf_buf);
    (void) close(sock);
}

#else /* !SIOCGIFCONF || STUB_LOAD_INTERFACES */

/*
 * Stub function for those without SIOCGIFCONF
 */
void
load_interfaces()
{
    return;
}

#endif /* SIOCGIFCONF && !STUB_LOAD_INTERFACES */

void
dump_interfaces()
{
    int i;
#ifdef HAVE_IN6_ADDR
    char addrbuf[INET6_ADDRSTRLEN], maskbuf[INET6_ADDRSTRLEN];
#endif

    puts("Local IP address and netmask pairs:");
    for (i = 0; i < num_interfaces; i++) {
	switch(interfaces[i].family) {
	    case AF_INET:
		printf("\t%s / ", inet_ntoa(interfaces[i].addr.ip4));
		puts(inet_ntoa(interfaces[i].netmask.ip4));
		break;
#ifdef HAVE_IN6_ADDR
	    case AF_INET6:
		inet_ntop(AF_INET6, &interfaces[i].addr.ip6,
		    addrbuf, sizeof(addrbuf));
		inet_ntop(AF_INET6, &interfaces[i].netmask.ip6,
		    maskbuf, sizeof(maskbuf));
		printf("\t%s / %s\n", addrbuf, maskbuf);
		break;
#endif /* HAVE_IN6_ADDR */
	}
    }
}