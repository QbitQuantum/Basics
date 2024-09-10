void mh_send_be(struct in6_addr *dst, struct in6_addr *hoa,
		struct in6_addr *src, uint8_t status, int iif)
{
	struct ip6_mh_binding_error *be;
	struct iovec iov;
	struct in6_addr_bundle out;

	if (IN6_IS_ADDR_UNSPECIFIED(dst) ||
	    IN6_IS_ADDR_LOOPBACK(dst) ||
	    IN6_IS_ADDR_MULTICAST(dst)) {
		MDBG("Omit BE for non-unicast "
		     "%x:%x:%x:%x:%x:%x:%x:%x\n", NIP6ADDR(dst));
		return;
	}

	out.remote_coa = NULL;
	out.local_coa = NULL;
	be = mh_create(&iov, IP6_MH_TYPE_BERROR);
	if (!be)
		return;
	be->ip6mhbe_status = status;
	out.src = src;
	out.dst = dst;
	if (hoa)
		be->ip6mhbe_homeaddr = *hoa;
	out.dst = dst;

	mh_send(&out, &iov, 1, NULL, iif);
	free_iov_data(&iov, 1);
}