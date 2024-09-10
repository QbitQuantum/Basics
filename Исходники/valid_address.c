static int valid_ipv6(char *str)
{
	unsigned int prefix_len;
	struct in6_addr addr; /* net order */
	char *slash, *endp;

	slash = strchr(str, '/');
	if (!slash) {
		fprintf(stderr, "Missing network prefix\n");
		return 0;
	}

	*slash++ = 0;
	prefix_len = strtoul(slash, &endp, 10);
	if (*slash == '\0' || *endp != '\0')
		fprintf(stderr, "Non-digit in prefix length\n");

	else if (prefix_len <= 1 || prefix_len > 128)
		fprintf(stderr,
			"Invalid prefix len %d for IPv6\n", prefix_len);

	else if (inet_pton(AF_INET6, str, &addr) <= 0)
		fprintf(stderr, "Invalid IPv6 address\n");

	else if (IN6_IS_ADDR_LINKLOCAL(&addr))
		fprintf(stderr,
			"Can not assign an address reserved for IPv6 link local\n");
	else if (IN6_IS_ADDR_MULTICAST(&addr))
		fprintf(stderr,
			"Can not assign an address reserved for IPv6 multicast\n");
	else if (IN6_IS_ADDR_UNSPECIFIED(&addr))
		fprintf(stderr,
			"Can not assign IPv6 reserved for IPv6 unspecified address\n");
	else 
		return 1;	/* is valid address and prefix */

	return 0;	/* Invalid address */
}