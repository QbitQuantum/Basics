u_int32_t
scope6_addr2default(struct in6_addr *addr)
{

	/*
	 * special case: The loopback address should be considered as
	 * link-local, but there's no ambiguity in the syntax.
	 */
	if (IN6_IS_ADDR_LOOPBACK(addr))
		return (0);

	return (sid_default.s6id_list[in6_addrscope(addr)]);
}