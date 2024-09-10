static int iptunnel_parse_opt(struct link_util *lu, int argc, char **argv,
			      struct nlmsghdr *n)
{
	struct {
		struct nlmsghdr n;
		struct ifinfomsg i;
		char buf[2048];
	} req;
	struct ifinfomsg *ifi = (struct ifinfomsg *)(n + 1);
	struct rtattr *tb[IFLA_MAX + 1];
	struct rtattr *linkinfo[IFLA_INFO_MAX+1];
	struct rtattr *iptuninfo[IFLA_IPTUN_MAX + 1];
	int len;
	__u32 link = 0;
	__u32 laddr = 0;
	__u32 raddr = 0;
	__u8 ttl = 0;
	__u8 tos = 0;
	__u8 pmtudisc = 1;
	__u16 iflags = 0;
	__u8 proto = 0;
	struct in6_addr ip6rdprefix;
	__u16 ip6rdprefixlen = 0;
	__u32 ip6rdrelayprefix = 0;
	__u16 ip6rdrelayprefixlen = 0;

	memset(&ip6rdprefix, 0, sizeof(ip6rdprefix));

	if (!(n->nlmsg_flags & NLM_F_CREATE)) {
		memset(&req, 0, sizeof(req));

		req.n.nlmsg_len = NLMSG_LENGTH(sizeof(*ifi));
		req.n.nlmsg_flags = NLM_F_REQUEST;
		req.n.nlmsg_type = RTM_GETLINK;
		req.i.ifi_family = preferred_family;
		req.i.ifi_index = ifi->ifi_index;

		if (rtnl_talk(&rth, &req.n, 0, 0, &req.n) < 0) {
get_failed:
			fprintf(stderr,
				"Failed to get existing tunnel info.\n");
			return -1;
		}

		len = req.n.nlmsg_len;
		len -= NLMSG_LENGTH(sizeof(*ifi));
		if (len < 0)
			goto get_failed;

		parse_rtattr(tb, IFLA_MAX, IFLA_RTA(&req.i), len);

		if (!tb[IFLA_LINKINFO])
			goto get_failed;

		parse_rtattr_nested(linkinfo, IFLA_INFO_MAX, tb[IFLA_LINKINFO]);

		if (!linkinfo[IFLA_INFO_DATA])
			goto get_failed;

		parse_rtattr_nested(iptuninfo, IFLA_IPTUN_MAX,
				    linkinfo[IFLA_INFO_DATA]);

		if (iptuninfo[IFLA_IPTUN_LOCAL])
			laddr = rta_getattr_u32(iptuninfo[IFLA_IPTUN_LOCAL]);

		if (iptuninfo[IFLA_IPTUN_REMOTE])
			raddr = rta_getattr_u32(iptuninfo[IFLA_IPTUN_REMOTE]);

		if (iptuninfo[IFLA_IPTUN_TTL])
			ttl = rta_getattr_u8(iptuninfo[IFLA_IPTUN_TTL]);

		if (iptuninfo[IFLA_IPTUN_TOS])
			tos = rta_getattr_u8(iptuninfo[IFLA_IPTUN_TOS]);

		if (iptuninfo[IFLA_IPTUN_PMTUDISC])
			pmtudisc =
				rta_getattr_u8(iptuninfo[IFLA_IPTUN_PMTUDISC]);

		if (iptuninfo[IFLA_IPTUN_FLAGS])
			iflags = rta_getattr_u16(iptuninfo[IFLA_IPTUN_FLAGS]);

		if (iptuninfo[IFLA_IPTUN_LINK])
			link = rta_getattr_u32(iptuninfo[IFLA_IPTUN_LINK]);

		if (iptuninfo[IFLA_IPTUN_PROTO])
			proto = rta_getattr_u8(iptuninfo[IFLA_IPTUN_PROTO]);

		if (iptuninfo[IFLA_IPTUN_6RD_PREFIX])
			memcpy(&ip6rdprefix,
			       RTA_DATA(iptuninfo[IFLA_IPTUN_6RD_PREFIX]),
			       sizeof(laddr));

		if (iptuninfo[IFLA_IPTUN_6RD_PREFIXLEN])
			ip6rdprefixlen =
				rta_getattr_u16(iptuninfo[IFLA_IPTUN_6RD_PREFIXLEN]);

		if (iptuninfo[IFLA_IPTUN_6RD_RELAY_PREFIX])
			ip6rdrelayprefix =
				rta_getattr_u32(iptuninfo[IFLA_IPTUN_6RD_RELAY_PREFIX]);

		if (iptuninfo[IFLA_IPTUN_6RD_RELAY_PREFIXLEN])
			ip6rdrelayprefixlen =
				rta_getattr_u16(iptuninfo[IFLA_IPTUN_6RD_RELAY_PREFIXLEN]);
	}

	while (argc > 0) {
		if (strcmp(*argv, "remote") == 0) {
			NEXT_ARG();
			if (strcmp(*argv, "any"))
				raddr = get_addr32(*argv);
			else
				raddr = 0;
		} else if (strcmp(*argv, "local") == 0) {
			NEXT_ARG();
			if (strcmp(*argv, "any"))
				laddr = get_addr32(*argv);
			else
				laddr = 0;
		} else if (matches(*argv, "dev") == 0) {
			NEXT_ARG();
			link = if_nametoindex(*argv);
			if (link == 0)
				invarg("\"dev\" is invalid", *argv);
		} else if (strcmp(*argv, "ttl") == 0 ||
			   strcmp(*argv, "hoplimit") == 0) {
			NEXT_ARG();
			if (strcmp(*argv, "inherit") != 0) {
				if (get_u8(&ttl, *argv, 0))
					invarg("invalid TTL\n", *argv);
			} else
				ttl = 0;
		} else if (strcmp(*argv, "tos") == 0 ||
			   strcmp(*argv, "tclass") == 0 ||
			   matches(*argv, "dsfield") == 0) {
			__u32 uval;
			NEXT_ARG();
			if (strcmp(*argv, "inherit") != 0) {
				if (rtnl_dsfield_a2n(&uval, *argv))
					invarg("bad TOS value", *argv);
				tos = uval;
			} else
				tos = 1;
		} else if (strcmp(*argv, "nopmtudisc") == 0) {
			pmtudisc = 0;
		} else if (strcmp(*argv, "pmtudisc") == 0) {
			pmtudisc = 1;
		} else if (strcmp(lu->id, "sit") == 0 &&
			   strcmp(*argv, "isatap") == 0) {
			iflags |= SIT_ISATAP;
		} else if (strcmp(lu->id, "sit") == 0 &&
			   strcmp(*argv, "mode") == 0) {
			NEXT_ARG();
			if (strcmp(*argv, "ipv6/ipv4") == 0 ||
			    strcmp(*argv, "ip6ip") == 0)
				proto = IPPROTO_IPV6;
			else if (strcmp(*argv, "ipv4/ipv4") == 0 ||
				 strcmp(*argv, "ipip") == 0 ||
				 strcmp(*argv, "ip4ip4") == 0)
				proto = IPPROTO_IPIP;
			else if (strcmp(*argv, "any/ipv4") == 0 ||
				 strcmp(*argv, "any") == 0)
				proto = 0;
			else
				invarg("Cannot guess tunnel mode.", *argv);
		} else if (strcmp(*argv, "6rd-prefix") == 0) {
			inet_prefix prefix;
			NEXT_ARG();
			if (get_prefix(&prefix, *argv, AF_INET6))
				invarg("invalid 6rd_prefix\n", *argv);
			memcpy(&ip6rdprefix, prefix.data, 16);
			ip6rdprefixlen = prefix.bitlen;
		} else if (strcmp(*argv, "6rd-relay_prefix") == 0) {
			inet_prefix prefix;
			NEXT_ARG();
			if (get_prefix(&prefix, *argv, AF_INET))
				invarg("invalid 6rd-relay_prefix\n", *argv);
			memcpy(&ip6rdrelayprefix, prefix.data, 4);
			ip6rdrelayprefixlen = prefix.bitlen;
		} else if (strcmp(*argv, "6rd-reset") == 0) {
			inet_prefix prefix;
			get_prefix(&prefix, "2002::", AF_INET6);
			memcpy(&ip6rdprefix, prefix.data, 16);
			ip6rdprefixlen = 16;
			ip6rdrelayprefix = 0;
			ip6rdrelayprefixlen = 0;
		} else
			usage(strcmp(lu->id, "sit") == 0);
		argc--, argv++;
	}

	if (ttl && pmtudisc == 0) {
		fprintf(stderr, "ttl != 0 and noptmudisc are incompatible\n");
		exit(-1);
	}

	addattr32(n, 1024, IFLA_IPTUN_LINK, link);
	addattr32(n, 1024, IFLA_IPTUN_LOCAL, laddr);
	addattr32(n, 1024, IFLA_IPTUN_REMOTE, raddr);
	addattr8(n, 1024, IFLA_IPTUN_TTL, ttl);
	addattr8(n, 1024, IFLA_IPTUN_TOS, tos);
	addattr8(n, 1024, IFLA_IPTUN_PMTUDISC, pmtudisc);
	if (strcmp(lu->id, "sit") == 0) {
		addattr16(n, 1024, IFLA_IPTUN_FLAGS, iflags);
		addattr8(n, 1024, IFLA_IPTUN_PROTO, proto);
		if (ip6rdprefixlen) {
			addattr_l(n, 1024, IFLA_IPTUN_6RD_PREFIX,
				  &ip6rdprefix, sizeof(ip6rdprefix));
			addattr16(n, 1024, IFLA_IPTUN_6RD_PREFIXLEN,
				  ip6rdprefixlen);
			addattr32(n, 1024, IFLA_IPTUN_6RD_RELAY_PREFIX,
				  ip6rdrelayprefix);
			addattr16(n, 1024, IFLA_IPTUN_6RD_RELAY_PREFIXLEN,
				  ip6rdrelayprefixlen);
		}
	}

	return 0;
}