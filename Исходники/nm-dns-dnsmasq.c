static char *
ip6_addr_to_string (const struct in6_addr *addr, const char *iface)
{
	char *buf;

	if (IN6_IS_ADDR_V4MAPPED (addr)) {
		buf = g_malloc (INET_ADDRSTRLEN);
		nm_utils_inet4_ntop (addr->s6_addr32[3], buf);
	} else if (!iface || !iface[0] || !IN6_IS_ADDR_LINKLOCAL (addr)) {
		buf = g_malloc (INET6_ADDRSTRLEN);
		nm_utils_inet6_ntop (addr, buf);
	} else {
		/* Need to scope the address with %<zone-id>. Before dnsmasq 2.58,
		 * only '@' was supported as delimiter. Since 2.58, '@' and '%'
		 * are supported. Due to a bug, since 2.73 only '%' works properly
		 * as "server" address.
		 */
		buf = g_strconcat (nm_utils_inet6_ntop (addr, NULL), "%", iface, NULL);
	}
	return buf;
}