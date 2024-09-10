// Forwards a packet on a specific interface
ssize_t relayd_forward_packet(int socket, struct sockaddr_in6 *dest,
		struct iovec *iov, size_t iov_len,
		const struct relayd_interface *iface)
{
	// Construct headers
	uint8_t cmsg_buf[CMSG_SPACE(sizeof(struct in6_pktinfo))] = {0};
	struct msghdr msg = {(void*)dest, sizeof(*dest), iov, iov_len,
				cmsg_buf, sizeof(cmsg_buf), 0};

	// Set control data (define destination interface)
	struct cmsghdr *chdr = CMSG_FIRSTHDR(&msg);
	chdr->cmsg_level = IPPROTO_IPV6;
	chdr->cmsg_type = IPV6_PKTINFO;
	chdr->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));
	struct in6_pktinfo *pktinfo = (struct in6_pktinfo*)CMSG_DATA(chdr);
	pktinfo->ipi6_ifindex = iface->ifindex;

	// Also set scope ID if link-local
	if (IN6_IS_ADDR_LINKLOCAL(&dest->sin6_addr)
			|| IN6_IS_ADDR_MC_LINKLOCAL(&dest->sin6_addr))
		dest->sin6_scope_id = iface->ifindex;

	// IPV6_PKTINFO doesn't really work for IPv6-raw sockets (bug?)
	if (dest->sin6_port == 0) {
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
	}

	char ipbuf[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &dest->sin6_addr, ipbuf, sizeof(ipbuf));

	ssize_t sent = sendmsg(socket, &msg, MSG_DONTWAIT);
	if (sent < 0)
		syslog(LOG_WARNING, "Failed to relay to %s%%%s (%s)",
				ipbuf, iface->ifname, strerror(errno));
	else
		syslog(LOG_NOTICE, "Relayed %li bytes to %s%%%s",
				(long)sent, ipbuf, iface->ifname);
	return sent;
}