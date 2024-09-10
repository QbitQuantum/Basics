bool is_linklocal_addr(const struct sockaddr_storage *pss)
{
#ifdef HAVE_IPV6
	if (pss->ss_family == AF_INET6) {
		const struct in6_addr *pin6 =
			&((const struct sockaddr_in6 *)pss)->sin6_addr;
		return IN6_IS_ADDR_LINKLOCAL(pin6);
	}
#endif
	if (pss->ss_family == AF_INET) {
		const struct in_addr *pin =
			&((const struct sockaddr_in *)pss)->sin_addr;
		struct in_addr ll_addr;
		struct in_addr mask_addr;

		/* 169.254.0.0/16, is link local, see RFC 3927 */
		ll_addr.s_addr = 0xa9fe0000;
		mask_addr.s_addr = 0xffff0000;
		return same_net_v4(*pin, ll_addr, mask_addr);
	}
	return false;
}