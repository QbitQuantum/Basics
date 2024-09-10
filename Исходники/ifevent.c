static int
__ni_rtevent_process_rdnss_info(ni_netdev_t *dev, const struct nd_opt_hdr *opt,
				size_t len)
{
	const struct ni_nd_opt_rdnss_info_p *ropt;
	char buf[INET6_ADDRSTRLEN+1] = {'\0'};
	const struct in6_addr* addr;
	ni_ipv6_devinfo_t *ipv6;
	unsigned int lifetime;
	struct timeval acquired;
	ni_bool_t emit = FALSE;
	const char *server;

	if (opt == NULL || len < (sizeof(*ropt) + sizeof(*addr))) {
		ni_error("%s: unable to parse ipv6 rdnss info event data -- too short",
				dev->name);
		return -1;
	}

	ipv6 = ni_netdev_get_ipv6(dev);
	if (!ipv6) {
		ni_error("%s: unable to allocate device ipv6 structure: %m",
				dev->name);
		return -1;
	}

	ropt = (const struct ni_nd_opt_rdnss_info_p *)opt;

	ni_timer_get_time(&acquired);
	lifetime = ntohl(ropt->nd_opt_rdnss_lifetime);
	len -= sizeof(*ropt);
	addr = &ropt->nd_opt_rdnss_addr[0];
	for ( ; len >= sizeof(*addr); len -= sizeof(*addr), ++addr) {
		if (IN6_IS_ADDR_LOOPBACK(addr) || IN6_IS_ADDR_UNSPECIFIED(addr)) {
			server = inet_ntop(AF_INET6, addr, buf, sizeof(buf));
			ni_debug_verbose(NI_LOG_DEBUG2, NI_TRACE_IPV6|NI_TRACE_EVENTS,
					"%s: ignoring invalid rdnss server address %s",
					dev->name, server);
			continue;
		}

		if (!ni_ipv6_ra_rdnss_list_update(&ipv6->radv.rdnss, addr,
					lifetime, &acquired)) {
			server = inet_ntop(AF_INET6, addr, buf, sizeof(buf));
			ni_debug_verbose(NI_LOG_DEBUG, NI_TRACE_IPV6|NI_TRACE_EVENTS,
					"%s: failed to track ipv6 rnssl server %s",
					dev->name, server);
			continue;
		}

		emit = TRUE;
	}

	if (emit)
		__ni_netdev_nduseropt_event(dev, NI_EVENT_RDNSS_UPDATE);
	return 0;
}