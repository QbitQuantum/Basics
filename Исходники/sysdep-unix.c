int
isns_portal_to_sockaddr(const isns_portal_info_t *portal,
		struct sockaddr_storage *addr)
{
	const struct sockaddr_in6 *six = &portal->addr;
	struct sockaddr_in *sin;

	/* Check if this is really a v4 address is disguise.
	 * If so, explicitly use an AF_INET socket - the
	 * stack may not support IPv6.
	 */
	if (IN6_IS_ADDR_V4MAPPED(&six->sin6_addr)
	 || IN6_IS_ADDR_V4COMPAT(&six->sin6_addr)) {
		sin = (struct sockaddr_in *) addr;

		memset(sin, 0, sizeof(*sin));
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = six->sin6_addr.s6_addr32[3];
		sin->sin_port = six->sin6_port;

		return sizeof(*sin);
	}
	
	/* This is the genuine article */
	memcpy(addr, six, sizeof(*six));
	return sizeof(*six);
}