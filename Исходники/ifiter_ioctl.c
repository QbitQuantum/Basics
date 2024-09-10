static isc_result_t
internal_current6(isc_interfaceiter_t *iter) {
	struct LIFREQ *ifrp;
	struct LIFREQ lifreq;
	int family;
	char strbuf[BUFSIZ];
	int fd;

	REQUIRE(VALID_IFITER(iter));
	if (iter->result6 != ISC_R_SUCCESS)
		return (iter->result6);
	REQUIRE(iter->pos6 < (unsigned int) iter->lifc.lifc_len);

	ifrp = (void *)((char *)iter->lifc.lifc_req + iter->pos6);

	memset(&lifreq, 0, sizeof(lifreq));
	memcpy(&lifreq, ifrp, sizeof(lifreq));

	family = lifreq.lifr_addr.ss_family;
	if (family != AF_INET && family != AF_INET6)
		return (ISC_R_IGNORE);

	memset(&iter->current, 0, sizeof(iter->current));
	iter->current.af = family;

	INSIST(sizeof(lifreq.lifr_name) <= sizeof(iter->current.name));
	memset(iter->current.name, 0, sizeof(iter->current.name));
	memcpy(iter->current.name, lifreq.lifr_name, sizeof(lifreq.lifr_name));

	get_addr(family, &iter->current.address,
		 (struct sockaddr *)&lifreq.lifr_addr, lifreq.lifr_name);

	if (isc_netaddr_islinklocal(&iter->current.address))
		isc_netaddr_setzone(&iter->current.address, 
				    (uint32_t)lifreq.lifr_index);

	/*
	 * If the interface does not have a address ignore it.
	 */
	switch (family) {
	case AF_INET:
		if (iter->current.address.type.in.s_addr == htonl(INADDR_ANY))
			return (ISC_R_IGNORE);
		break;
	case AF_INET6:
		if (memcmp(&iter->current.address.type.in6, &in6addr_any,
			   sizeof(in6addr_any)) == 0)
			return (ISC_R_IGNORE);
		break;
	}

	/*
	 * Get interface flags.
	 */

	iter->current.flags = 0;

	if (family == AF_INET6)
		fd = iter->socket6;
	else
		fd = iter->socket;

	/*
	 * Ignore the HP/UX warning about "integer overflow during
	 * conversion.  It comes from its own macro definition,
	 * and is really hard to shut up.
	 */
	if (isc_ioctl(fd, SIOCGLIFFLAGS, (char *) &lifreq) < 0) {
		strerror_r(errno, strbuf, sizeof(strbuf));
		UNEXPECTED_ERROR(__FILE__, __LINE__,
				 "%s: getting interface flags: %s",
				 lifreq.lifr_name, strbuf);
		return (ISC_R_IGNORE);
	}

	if ((lifreq.lifr_flags & IFF_UP) != 0)
		iter->current.flags |= INTERFACE_F_UP;

#ifdef IFF_POINTOPOINT
	if ((lifreq.lifr_flags & IFF_POINTOPOINT) != 0)
		iter->current.flags |= INTERFACE_F_POINTTOPOINT;
#endif

	if ((lifreq.lifr_flags & IFF_LOOPBACK) != 0)
		iter->current.flags |= INTERFACE_F_LOOPBACK;

	if ((lifreq.lifr_flags & IFF_BROADCAST) != 0) {
		iter->current.flags |= INTERFACE_F_BROADCAST;
	}

#ifdef IFF_MULTICAST
	if ((lifreq.lifr_flags & IFF_MULTICAST) != 0) {
		iter->current.flags |= INTERFACE_F_MULTICAST;
	}
#endif

#ifdef IFF_POINTOPOINT
	/*
	 * If the interface is point-to-point, get the destination address.
	 */
	if ((iter->current.flags & INTERFACE_F_POINTTOPOINT) != 0) {
		/*
		 * Ignore the HP/UX warning about "integer overflow during
		 * conversion.  It comes from its own macro definition,
		 * and is really hard to shut up.
		 */
		if (isc_ioctl(fd, SIOCGLIFDSTADDR, (char *)&lifreq)
		    < 0) {
			strerror_r(errno, strbuf, sizeof(strbuf));
			UNEXPECTED_ERROR(__FILE__, __LINE__,
					 "%s: getting destination address: %s",
					 lifreq.lifr_name, strbuf);
			return (ISC_R_IGNORE);
		}
		get_addr(family, &iter->current.dstaddress,
			 (struct sockaddr *)&lifreq.lifr_dstaddr,
			 lifreq.lifr_name);
	}
#endif

#ifdef SIOCGLIFBRDADDR
	if ((iter->current.flags & INTERFACE_F_BROADCAST) != 0) {
		/*
		 * Ignore the HP/UX warning about "integer overflow during
		 * conversion.  It comes from its own macro definition,
		 * and is really hard to shut up.
		 */
		if (isc_ioctl(iter->socket, SIOCGLIFBRDADDR, (char *)&lifreq)
		    < 0) {
			strerror_r(errno, strbuf, sizeof(strbuf));
			UNEXPECTED_ERROR(__FILE__, __LINE__,
					 "%s: getting broadcast address: %s",
					 lifreq.lifr_name, strbuf);
			return (ISC_R_IGNORE);
		}
		get_addr(family, &iter->current.broadcast,
			 (struct sockaddr *)&lifreq.lifr_broadaddr,
			 lifreq.lifr_name);
	}
#endif	/* SIOCGLIFBRDADDR */

	/*
	 * Get the network mask.  Netmask already zeroed.
	 */
	memset(&lifreq, 0, sizeof(lifreq));
	memcpy(&lifreq, ifrp, sizeof(lifreq));

#ifdef lifr_addrlen
	/*
	 * Special case: if the system provides lifr_addrlen member, the
	 * netmask of an IPv6 address can be derived from the length, since
	 * an IPv6 address always has a contiguous mask.
	 */
	if (family == AF_INET6) {
		int i, bits;

		iter->current.netmask.family = family;
		for (i = 0; i < lifreq.lifr_addrlen; i += 8) {
			bits = lifreq.lifr_addrlen - i;
			bits = (bits < 8) ? (8 - bits) : 0;
			iter->current.netmask.type.in6.s6_addr[i / 8] =
				(~0 << bits) & 0xff;
		}
		iter->current.ifindex = if_nametoindex(iter->current.name);
		return (ISC_R_SUCCESS);
	}
#endif

	/*
	 * Ignore the HP/UX warning about "integer overflow during
	 * conversion.  It comes from its own macro definition,
	 * and is really hard to shut up.
	 */
	if (isc_ioctl(fd, SIOCGLIFNETMASK, (char *)&lifreq) < 0) {
		strerror_r(errno, strbuf, sizeof(strbuf));
		UNEXPECTED_ERROR(__FILE__, __LINE__,
				 "%s: getting netmask: %s",
				 lifreq.lifr_name, strbuf);
		return (ISC_R_IGNORE);
	}
	get_addr(family, &iter->current.netmask,
		 (struct sockaddr *)&lifreq.lifr_addr, lifreq.lifr_name);

	iter->current.ifindex = if_nametoindex(iter->current.name);
	return (ISC_R_SUCCESS);
}