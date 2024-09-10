/* function for IPv4/IPv6 address */
static void format_addr(char *buff, char *data) {
	lnf_ip_t *addr = (lnf_ip_t *)data;

	if (IN6_IS_ADDR_V4COMPAT((struct in6_addr *)addr)) {
		inet_ntop(AF_INET, (char *)&(addr->data[3]), buff, MAX_STR);
	} else {
		inet_ntop(AF_INET6, addr, buff, MAX_STR);
	}
}