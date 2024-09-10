static bool parse_ipv6(const char *s, const char *ifaces, unsigned port, ctdb_sock_addr *saddr)
{
	saddr->ip6.sin6_family   = AF_INET6;
	saddr->ip6.sin6_port     = htons(port);
	saddr->ip6.sin6_flowinfo = 0;
	saddr->ip6.sin6_scope_id = 0;

	if (inet_pton(AF_INET6, s, &saddr->ip6.sin6_addr) != 1) {
		DEBUG(DEBUG_ERR, (__location__ " Failed to translate %s into sin6_addr\n", s));
		return false;
	}

	if (ifaces && IN6_IS_ADDR_LINKLOCAL(&saddr->ip6.sin6_addr)) {
		if (strchr(ifaces, ',')) {
			DEBUG(DEBUG_ERR, (__location__ " Link local address %s "
					  "is specified for multiple ifaces %s\n",
					  s, ifaces));
			return false;
		}
		saddr->ip6.sin6_scope_id = if_nametoindex(ifaces);
	}

	return true;
}