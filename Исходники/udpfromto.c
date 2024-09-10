int sendfromto(int s, void *buf, size_t len, int flags,
	       struct sockaddr *from, socklen_t fromlen,
	       struct sockaddr *to, socklen_t tolen)
{
	struct msghdr msgh;
	struct cmsghdr *cmsg;
	struct iovec iov;
	char cbuf[256];

#ifdef __FreeBSD__
	/*
	 *	FreeBSD is extra pedantic about the use of IP_SENDSRCADDR,
	 *	and sendmsg will fail with EINVAL if IP_SENDSRCADDR is used
	 *	with a socket which is bound to something other than
	 *	INADDR_ANY
	 */
	struct sockaddr bound;
	socklen_t bound_len = sizeof(bound);

	if (getsockname(s, &bound, &bound_len) < 0) {
		return -1;
	}

	switch (bound.sa_family) {
	case AF_INET:
		if (((struct sockaddr_in *) &bound)->sin_addr.s_addr != INADDR_ANY) {
			from = NULL;
		}
		break;

	case AF_INET6:
		if (!IN6_IS_ADDR_UNSPECIFIED(&((struct sockaddr_in6 *) &bound)->sin6_addr)) {
			from = NULL;
		}
		break;
	}
#else
#  if !defined(IP_PKTINFO) && !defined(IP_SENDSRCADDR) && !defined(IPV6_PKTINFO)
	/*
	 *	If the sendmsg() flags aren't defined, fall back to
	 *	using sendto().
	 */
	from = NULL;
#  endif
#endif

	/*
	 *	Catch the case where the caller passes invalid arguments.
	 */
	if (!from || (fromlen == 0) || (from->sa_family == AF_UNSPEC)) {
		return sendto(s, buf, len, flags, to, tolen);
	}

	/* Set up control buffer iov and msgh structures. */
	memset(&cbuf, 0, sizeof(cbuf));
	memset(&msgh, 0, sizeof(msgh));
	memset(&iov, 0, sizeof(iov));
	iov.iov_base = buf;
	iov.iov_len = len;
	msgh.msg_iov = &iov;
	msgh.msg_iovlen = 1;
	msgh.msg_name = to;
	msgh.msg_namelen = tolen;

	if (from->sa_family == AF_INET) {
#if !defined(IP_PKTINFO) && !defined(IP_SENDSRCADDR)
		return sendto(s, buf, len, flags, to, tolen);
#else
		struct sockaddr_in *s4 = (struct sockaddr_in *) from;

#  ifdef IP_PKTINFO
		struct in_pktinfo *pkt;

		msgh.msg_control = cbuf;
		msgh.msg_controllen = CMSG_SPACE(sizeof(*pkt));

		cmsg = CMSG_FIRSTHDR(&msgh);
		cmsg->cmsg_level = SOL_IP;
		cmsg->cmsg_type = IP_PKTINFO;
		cmsg->cmsg_len = CMSG_LEN(sizeof(*pkt));

		pkt = (struct in_pktinfo *) CMSG_DATA(cmsg);
		memset(pkt, 0, sizeof(*pkt));
		pkt->ipi_spec_dst = s4->sin_addr;
#  endif

#  ifdef IP_SENDSRCADDR
		struct in_addr *in;

		msgh.msg_control = cbuf;
		msgh.msg_controllen = CMSG_SPACE(sizeof(*in));

		cmsg = CMSG_FIRSTHDR(&msgh);
		cmsg->cmsg_level = IPPROTO_IP;
		cmsg->cmsg_type = IP_SENDSRCADDR;
		cmsg->cmsg_len = CMSG_LEN(sizeof(*in));

		in = (struct in_addr *) CMSG_DATA(cmsg);
		*in = s4->sin_addr;
#  endif
#endif	/* IP_PKTINFO or IP_SENDSRCADDR */
	}

#ifdef AF_INET6
	else if (from->sa_family == AF_INET6) {
#  if !defined(IPV6_PKTINFO)
		return sendto(s, buf, len, flags, to, tolen);
#  else
		struct sockaddr_in6 *s6 = (struct sockaddr_in6 *) from;

		struct in6_pktinfo *pkt;

		msgh.msg_control = cbuf;
		msgh.msg_controllen = CMSG_SPACE(sizeof(*pkt));

		cmsg = CMSG_FIRSTHDR(&msgh);
		cmsg->cmsg_level = IPPROTO_IPV6;
		cmsg->cmsg_type = IPV6_PKTINFO;
		cmsg->cmsg_len = CMSG_LEN(sizeof(*pkt));

		pkt = (struct in6_pktinfo *) CMSG_DATA(cmsg);
		memset(pkt, 0, sizeof(*pkt));
		pkt->ipi6_addr = s6->sin6_addr;
#  endif	/* IPV6_PKTINFO */
	}
#endif

	/*
	 *	Unknown address family.
	 */
	else {
		errno = EINVAL;
		return -1;
	}

	return sendmsg(s, &msgh, flags);
}