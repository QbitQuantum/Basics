static int really_send(int sock, struct in6_addr const *dest, struct properties const *props, struct safe_buffer const *sb)
{
	struct sockaddr_in6 addr;
	memset((void *)&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(IPPROTO_ICMPV6);
	memcpy(&addr.sin6_addr, dest, sizeof(struct in6_addr));

	struct iovec iov;
	iov.iov_len = sb->used;
	iov.iov_base = (caddr_t)sb->buffer;

	char __attribute__ ((aligned(8))) chdr[CMSG_SPACE(sizeof(struct in6_pktinfo))];
	memset(chdr, 0, sizeof(chdr));
	struct cmsghdr *cmsg = (struct cmsghdr *)chdr;

	cmsg->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));
	cmsg->cmsg_level = IPPROTO_IPV6;
	cmsg->cmsg_type = IPV6_PKTINFO;

	struct in6_pktinfo *pkt_info = (struct in6_pktinfo *)CMSG_DATA(cmsg);
	pkt_info->ipi6_ifindex = props->if_index;
	memcpy(&pkt_info->ipi6_addr, &props->if_addr, sizeof(struct in6_addr));

#ifdef HAVE_SIN6_SCOPE_ID
	if (IN6_IS_ADDR_LINKLOCAL(&addr.sin6_addr) || IN6_IS_ADDR_MC_LINKLOCAL(&addr.sin6_addr))
		addr.sin6_scope_id = props->if_index;
#endif

	struct msghdr mhdr;
	memset(&mhdr, 0, sizeof(mhdr));
	mhdr.msg_name = (caddr_t) & addr;
	mhdr.msg_namelen = sizeof(struct sockaddr_in6);
	mhdr.msg_iov = &iov;
	mhdr.msg_iovlen = 1;
	mhdr.msg_control = (void *)cmsg;
	mhdr.msg_controllen = sizeof(chdr);

	return sendmsg(sock, &mhdr, 0);
}