static void ping(const char *host)
{
	char packet[datalen + MAXIPLEN + MAXICMPLEN];
	char buf[INET6_ADDRSTRLEN];
	int sockopt;
	struct msghdr msg;
	struct sockaddr_in6 from;
	struct iovec iov;
	char control_buf[CMSG_SPACE(36)];

	pingsock = create_icmp6_socket();

	memset(&pingaddr, 0, sizeof(struct sockaddr_in));

	pingaddr.sin6_family = AF_INET6;
	hostent = xgethostbyname2(host, AF_INET6);
	if (hostent->h_addrtype != AF_INET6)
		bb_error_msg_and_die("unknown address type; only AF_INET6 is currently supported.");

	memcpy(&pingaddr.sin6_addr, hostent->h_addr, sizeof(pingaddr.sin6_addr));

#ifdef ICMP6_FILTER
	{
		struct icmp6_filter filt;
		if (!(options & O_VERBOSE)) {
			ICMP6_FILTER_SETBLOCKALL(&filt);
#if 0
			if ((options & F_FQDN) || (options & F_FQDNOLD) ||
				(options & F_NODEADDR) || (options & F_SUPTYPES))
				ICMP6_FILTER_SETPASS(ICMP6_NI_REPLY, &filt);
			else
#endif
				ICMP6_FILTER_SETPASS(ICMP6_ECHO_REPLY, &filt);
		} else {
			ICMP6_FILTER_SETPASSALL(&filt);
		}
		if (setsockopt(pingsock, IPPROTO_ICMPV6, ICMP6_FILTER, &filt,
					   sizeof(filt)) < 0)
			bb_error_msg_and_die("setsockopt(ICMP6_FILTER)");
	}
#endif /*ICMP6_FILTER*/

	/* enable broadcast pings */
	sockopt = 1;
	setsockopt(pingsock, SOL_SOCKET, SO_BROADCAST, (char *) &sockopt,
			   sizeof(sockopt));

	/* set recv buf for broadcast pings */
	sockopt = 48 * 1024;
	setsockopt(pingsock, SOL_SOCKET, SO_RCVBUF, (char *) &sockopt,
			   sizeof(sockopt));

	sockopt = offsetof(struct icmp6_hdr, icmp6_cksum);
	setsockopt(pingsock, SOL_RAW, IPV6_CHECKSUM, (char *) &sockopt,
			   sizeof(sockopt));

	sockopt = 1;
	setsockopt(pingsock, SOL_IPV6, IPV6_HOPLIMIT, (char *) &sockopt,
			   sizeof(sockopt));

	if (ifname) {
		if ((pingaddr.sin6_scope_id = if_nametoindex(ifname)) == 0)
			bb_error_msg_and_die("%s: invalid interface name", ifname);
	}

	printf("PING %s (%s): %d data bytes\n",
	           hostent->h_name,
			   inet_ntop(AF_INET6, (struct in_addr6 *) &pingaddr.sin6_addr,
						 buf, sizeof(buf)),
		   datalen);

	signal(SIGINT, pingstats);

	/* start the ping's going ... */
	sendping(0);

	/* listen for replies */
	msg.msg_name=&from;
	msg.msg_namelen=sizeof(from);
	msg.msg_iov=&iov;
	msg.msg_iovlen=1;
	msg.msg_control=control_buf;
	iov.iov_base=packet;
	iov.iov_len=sizeof(packet);
	while (1) {
		int c;
		struct cmsghdr *cmsgptr = NULL;
		int hoplimit=-1;
		msg.msg_controllen=sizeof(control_buf);

		if ((c = recvmsg(pingsock, &msg, 0)) < 0) {
			if (errno == EINTR)
				continue;
			bb_perror_msg("recvfrom");
			continue;
		}
		for (cmsgptr = CMSG_FIRSTHDR(&msg); cmsgptr != NULL;
			 cmsgptr = CMSG_NXTHDR(&msg, cmsgptr)) {
			if (cmsgptr->cmsg_level == SOL_IPV6 &&
				cmsgptr->cmsg_type == IPV6_HOPLIMIT ) {
				hoplimit=*(int*)CMSG_DATA(cmsgptr);
			}
		}
		unpack(packet, c, &from, hoplimit);
		if (pingcount > 0 && nreceived >= pingcount)
			break;
	}
	pingstats(0);
}