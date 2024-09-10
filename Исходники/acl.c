static isc_boolean_t
is_loopback(dns_aclipprefix_t *p) {
	switch (p->address.family) {
	case AF_INET:
		if (p->prefixlen == 32 &&
		    htonl(p->address.type.in.s_addr) == INADDR_LOOPBACK)
			return (ISC_TRUE);
		break;
	case AF_INET6:
		if (p->prefixlen == 128 &&
		    IN6_IS_ADDR_LOOPBACK(&p->address.type.in6))
			return (ISC_TRUE);
		break;
	default:
		break;
	}
	return (ISC_FALSE);
}