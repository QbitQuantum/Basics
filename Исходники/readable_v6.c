int
readable_v6(void)
{
#ifdef	IPV6
	int					i, hlen1, hlen2, icmp6len, sport;
	char				buf[MAXLINE];
	char				srcstr[INET6_ADDRSTRLEN], dststr[INET6_ADDRSTRLEN];
	ssize_t				n;
	socklen_t			len;
	struct ip6_hdr		*ip6, *hip6;
	struct icmp6_hdr	*icmp6;
	struct udphdr		*udp;
	struct sockaddr_in6	from, dest;
	struct icmpd_err	icmpd_err;

	len = sizeof(from);
	n = Recvfrom(fd6, buf, MAXLINE, 0, (SA *) &from, &len);

	printf("%d bytes ICMPv6 from %s:",
		   n, Sock_ntop_host((SA *) &from, len));

	ip6 = (struct ip6_hdr *) buf;		/* start of IPv6 header */
	hlen1 = sizeof(struct ip6_hdr);
	if (ip6->ip6_nxt != IPPROTO_ICMPV6)
		err_quit("next header not IPPROTO_ICMPV6");

	icmp6 = (struct icmp6_hdr *) (buf + hlen1);
	if ( (icmp6len = n - hlen1) < 8)
		err_quit("icmp6len (%d) < 8", icmp6len);

	printf(" type = %d, code = %d\n", icmp6->icmp6_type, icmp6->icmp6_code);
/* end readable_v61 */

/* include readable_v62 */
	if (icmp6->icmp6_type == ICMP6_DST_UNREACH ||
		icmp6->icmp6_type == ICMP6_PACKET_TOO_BIG ||
		icmp6->icmp6_type == ICMP6_TIME_EXCEEDED) {
		if (icmp6len < 8 + 40 + 8)
			err_quit("icmp6len (%d) < 8 + 40 + 8", icmp6len);

		hip6 = (struct ip6_hdr *) (buf + hlen1 + 8);
		hlen2 = sizeof(struct ip6_hdr);
		printf("\tsrcip = %s, dstip = %s, next hdr = %d\n",
			   Inet_ntop(AF_INET6, &hip6->ip6_src, srcstr, sizeof(srcstr)),
			   Inet_ntop(AF_INET6, &hip6->ip6_dst, dststr, sizeof(dststr)),
			   hip6->ip6_nxt);
 		if (hip6->ip6_nxt == IPPROTO_UDP) {
			udp = (struct udphdr *) (buf + hlen1 + 8 + hlen2);
			sport = udp->uh_sport;

				/* 4find client's Unix domain socket, send headers */
			for (i = 0; i <= maxi; i++) {
				if (client[i].connfd >= 0 &&
					client[i].family == AF_INET6 &&
					client[i].lport == sport) {

					bzero(&dest, sizeof(dest));
					dest.sin6_family = AF_INET6;
#ifdef	HAVE_SOCKADDR_SA_LEN
					dest.sin6_len = sizeof(dest);
#endif
					memcpy(&dest.sin6_addr, &hip6->ip6_dst,
						   sizeof(struct in6_addr));
					dest.sin6_port = udp->uh_dport;

					icmpd_err.icmpd_type = icmp6->icmp6_type;
					icmpd_err.icmpd_code = icmp6->icmp6_code;
					icmpd_err.icmpd_len = sizeof(struct sockaddr_in6);
					memcpy(&icmpd_err.icmpd_dest, &dest, sizeof(dest));

						/* 4convert type & code to reasonable errno value */
					icmpd_err.icmpd_errno = EHOSTUNREACH;	/* default */
					if (icmp6->icmp6_type == ICMP6_DST_UNREACH) {
						if (icmp6->icmp6_code == ICMP_UNREACH_PORT)
							icmpd_err.icmpd_errno = ECONNREFUSED;
						else if (icmp6->icmp6_code == ICMP_UNREACH_NEEDFRAG)
							icmpd_err.icmpd_errno = EMSGSIZE;
					}
					Write(client[i].connfd, &icmpd_err, sizeof(icmpd_err));
				}
			}
		}
	}
	return(--nready);
#endif
}