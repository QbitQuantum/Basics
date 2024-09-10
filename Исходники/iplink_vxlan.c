static int vxlan_parse_opt(struct link_util *lu, int argc, char **argv,
			  struct nlmsghdr *n)
{
	__u32 vni = 0;
	__u32 gaddr = 0;
	__u32 daddr = 0;
	struct in6_addr gaddr6 = IN6ADDR_ANY_INIT;
	struct in6_addr daddr6 = IN6ADDR_ANY_INIT;
	__u8 learning = 1;
	__u16 dstport = 0;
	__u8 metadata = 0;
	__u64 attrs = 0;
	bool set_op = (n->nlmsg_type == RTM_NEWLINK &&
		       !(n->nlmsg_flags & NLM_F_CREATE));

	while (argc > 0) {
		if (!matches(*argv, "id") ||
		    !matches(*argv, "vni")) {
			/* We will add ID attribute outside of the loop since we
			 * need to consider metadata information as well.
			 */
			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_ID, "id", *argv);
			if (get_u32(&vni, *argv, 0) ||
			    vni >= 1u << 24)
				invarg("invalid id", *argv);
		} else if (!matches(*argv, "group")) {
			if (daddr || !IN6_IS_ADDR_UNSPECIFIED(&daddr6)) {
				fprintf(stderr, "vxlan: both group and remote");
				fprintf(stderr, " cannot be specified\n");
				return -1;
			}
			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_GROUP, "group", *argv);
			if (!inet_get_addr(*argv, &gaddr, &gaddr6)) {
				fprintf(stderr, "Invalid address \"%s\"\n", *argv);
				return -1;
			}
			if (!IN6_IS_ADDR_MULTICAST(&gaddr6) && !IN_MULTICAST(ntohl(gaddr)))
				invarg("invalid group address", *argv);
		} else if (!matches(*argv, "remote")) {
			if (gaddr || !IN6_IS_ADDR_UNSPECIFIED(&gaddr6)) {
				fprintf(stderr, "vxlan: both group and remote");
				fprintf(stderr, " cannot be specified\n");
				return -1;
			}
			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_GROUP, "remote", *argv);
			if (!inet_get_addr(*argv, &daddr, &daddr6)) {
				fprintf(stderr, "Invalid address \"%s\"\n", *argv);
				return -1;
			}
			if (IN6_IS_ADDR_MULTICAST(&daddr6) || IN_MULTICAST(ntohl(daddr)))
				invarg("invalid remote address", *argv);
		} else if (!matches(*argv, "local")) {
			__u32 saddr = 0;
			struct in6_addr saddr6 = IN6ADDR_ANY_INIT;

			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_LOCAL, "local", *argv);
			if (strcmp(*argv, "any")) {
				if (!inet_get_addr(*argv, &saddr, &saddr6)) {
					fprintf(stderr, "Invalid address \"%s\"\n", *argv);
					return -1;
				}
			}

			if (IN_MULTICAST(ntohl(saddr)) || IN6_IS_ADDR_MULTICAST(&saddr6))
				invarg("invalid local address", *argv);

			if (saddr)
				addattr_l(n, 1024, IFLA_VXLAN_LOCAL, &saddr, 4);
			else if (!IN6_IS_ADDR_UNSPECIFIED(&saddr6))
				addattr_l(n, 1024, IFLA_VXLAN_LOCAL6, &saddr6,
					  sizeof(struct in6_addr));
		} else if (!matches(*argv, "dev")) {
			unsigned int link;

			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_LINK, "dev", *argv);
			link = if_nametoindex(*argv);
			if (link == 0) {
				fprintf(stderr, "Cannot find device \"%s\"\n",
					*argv);
				exit(-1);
			}
			addattr32(n, 1024, IFLA_VXLAN_LINK, link);
		} else if (!matches(*argv, "ttl") ||
			   !matches(*argv, "hoplimit")) {
			unsigned int uval;
			__u8 ttl = 0;

			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_TTL, "ttl", *argv);
			if (strcmp(*argv, "inherit") != 0) {
				if (get_unsigned(&uval, *argv, 0))
					invarg("invalid TTL", *argv);
				if (uval > 255)
					invarg("TTL must be <= 255", *argv);
				ttl = uval;
			}
			addattr8(n, 1024, IFLA_VXLAN_TTL, ttl);
		} else if (!matches(*argv, "tos") ||
			   !matches(*argv, "dsfield")) {
			__u32 uval;
			__u8 tos;

			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_TOS, "tos", *argv);
			if (strcmp(*argv, "inherit") != 0) {
				if (rtnl_dsfield_a2n(&uval, *argv))
					invarg("bad TOS value", *argv);
				tos = uval;
			} else
				tos = 1;
			addattr8(n, 1024, IFLA_VXLAN_TOS, tos);
		} else if (!matches(*argv, "label") ||
			   !matches(*argv, "flowlabel")) {
			__u32 uval;

			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_LABEL, "flowlabel",
				     *argv);
			if (get_u32(&uval, *argv, 0) ||
			    (uval & ~LABEL_MAX_MASK))
				invarg("invalid flowlabel", *argv);
			addattr32(n, 1024, IFLA_VXLAN_LABEL, htonl(uval));
		} else if (!matches(*argv, "ageing")) {
			__u32 age;

			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_AGEING, "ageing",
				     *argv);
			if (strcmp(*argv, "none") == 0)
				age = 0;
			else if (get_u32(&age, *argv, 0))
				invarg("ageing timer", *argv);
			addattr32(n, 1024, IFLA_VXLAN_AGEING, age);
		} else if (!matches(*argv, "maxaddress")) {
			__u32 maxaddr;

			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_LIMIT,
				     "maxaddress", *argv);
			if (strcmp(*argv, "unlimited") == 0)
				maxaddr = 0;
			else if (get_u32(&maxaddr, *argv, 0))
				invarg("max addresses", *argv);
			addattr32(n, 1024, IFLA_VXLAN_LIMIT, maxaddr);
		} else if (!matches(*argv, "port") ||
			   !matches(*argv, "srcport")) {
			struct ifla_vxlan_port_range range = { 0, 0 };

			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_PORT_RANGE, "srcport",
				     *argv);
			if (get_be16(&range.low, *argv, 0))
				invarg("min port", *argv);
			NEXT_ARG();
			if (get_be16(&range.high, *argv, 0))
				invarg("max port", *argv);
			if (range.low || range.high) {
				addattr_l(n, 1024, IFLA_VXLAN_PORT_RANGE,
					  &range, sizeof(range));
			}
		} else if (!matches(*argv, "dstport")) {
			NEXT_ARG();
			check_duparg(&attrs, IFLA_VXLAN_PORT, "dstport", *argv);
			if (get_u16(&dstport, *argv, 0))
				invarg("dst port", *argv);
		} else if (!matches(*argv, "nolearning")) {
			check_duparg(&attrs, IFLA_VXLAN_LEARNING, *argv, *argv);
			learning = 0;
		} else if (!matches(*argv, "learning")) {
			check_duparg(&attrs, IFLA_VXLAN_LEARNING, *argv, *argv);
			learning = 1;
		} else if (!matches(*argv, "noproxy")) {
			check_duparg(&attrs, IFLA_VXLAN_PROXY, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_PROXY, 0);
		} else if (!matches(*argv, "proxy")) {
			check_duparg(&attrs, IFLA_VXLAN_PROXY, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_PROXY, 1);
		} else if (!matches(*argv, "norsc")) {
			check_duparg(&attrs, IFLA_VXLAN_RSC, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_RSC, 0);
		} else if (!matches(*argv, "rsc")) {
			check_duparg(&attrs, IFLA_VXLAN_RSC, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_RSC, 1);
		} else if (!matches(*argv, "nol2miss")) {
			check_duparg(&attrs, IFLA_VXLAN_L2MISS, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_L2MISS, 0);
		} else if (!matches(*argv, "l2miss")) {
			check_duparg(&attrs, IFLA_VXLAN_L2MISS, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_L2MISS, 1);
		} else if (!matches(*argv, "nol3miss")) {
			check_duparg(&attrs, IFLA_VXLAN_L3MISS, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_L3MISS, 0);
		} else if (!matches(*argv, "l3miss")) {
			check_duparg(&attrs, IFLA_VXLAN_L3MISS, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_L3MISS, 1);
		} else if (!matches(*argv, "udpcsum")) {
			check_duparg(&attrs, IFLA_VXLAN_UDP_CSUM, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_UDP_CSUM, 1);
		} else if (!matches(*argv, "noudpcsum")) {
			check_duparg(&attrs, IFLA_VXLAN_UDP_CSUM, *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_UDP_CSUM, 0);
		} else if (!matches(*argv, "udp6zerocsumtx")) {
			check_duparg(&attrs, IFLA_VXLAN_UDP_ZERO_CSUM6_TX,
				     *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_UDP_ZERO_CSUM6_TX, 1);
		} else if (!matches(*argv, "noudp6zerocsumtx")) {
			check_duparg(&attrs, IFLA_VXLAN_UDP_ZERO_CSUM6_TX,
				     *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_UDP_ZERO_CSUM6_TX, 0);
		} else if (!matches(*argv, "udp6zerocsumrx")) {
			check_duparg(&attrs, IFLA_VXLAN_UDP_ZERO_CSUM6_RX,
				     *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_UDP_ZERO_CSUM6_RX, 1);
		} else if (!matches(*argv, "noudp6zerocsumrx")) {
			check_duparg(&attrs, IFLA_VXLAN_UDP_ZERO_CSUM6_RX,
				     *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_UDP_ZERO_CSUM6_RX, 0);
		} else if (!matches(*argv, "remcsumtx")) {
			check_duparg(&attrs, IFLA_VXLAN_REMCSUM_TX,
				     *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_REMCSUM_TX, 1);
		} else if (!matches(*argv, "noremcsumtx")) {
			check_duparg(&attrs, IFLA_VXLAN_REMCSUM_TX,
				     *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_REMCSUM_TX, 0);
		} else if (!matches(*argv, "remcsumrx")) {
			check_duparg(&attrs, IFLA_VXLAN_REMCSUM_RX,
				     *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_REMCSUM_RX, 1);
		} else if (!matches(*argv, "noremcsumrx")) {
			check_duparg(&attrs, IFLA_VXLAN_REMCSUM_RX,
				     *argv, *argv);
			addattr8(n, 1024, IFLA_VXLAN_REMCSUM_RX, 0);
		} else if (!matches(*argv, "external")) {
			check_duparg(&attrs, IFLA_VXLAN_COLLECT_METADATA,
				     *argv, *argv);
			metadata = 1;
			learning = 0;
			/* we will add LEARNING attribute outside of the loop */
			addattr8(n, 1024, IFLA_VXLAN_COLLECT_METADATA,
				 metadata);
		} else if (!matches(*argv, "noexternal")) {
			check_duparg(&attrs, IFLA_VXLAN_COLLECT_METADATA,
				     *argv, *argv);
			metadata = 0;
			addattr8(n, 1024, IFLA_VXLAN_COLLECT_METADATA,
				 metadata);
		} else if (!matches(*argv, "gbp")) {
			check_duparg(&attrs, IFLA_VXLAN_GBP, *argv, *argv);
			addattr_l(n, 1024, IFLA_VXLAN_GBP, NULL, 0);
		} else if (!matches(*argv, "gpe")) {
			check_duparg(&attrs, IFLA_VXLAN_GPE, *argv, *argv);
			addattr_l(n, 1024, IFLA_VXLAN_GPE, NULL, 0);
		} else if (matches(*argv, "help") == 0) {
			explain();
			return -1;
		} else {
			fprintf(stderr, "vxlan: unknown command \"%s\"?\n", *argv);
			explain();
			return -1;
		}
		argc--, argv++;
	}

	if (metadata && VXLAN_ATTRSET(attrs, IFLA_VXLAN_ID)) {
		fprintf(stderr, "vxlan: both 'external' and vni cannot be specified\n");
		return -1;
	}

	if (!metadata && !VXLAN_ATTRSET(attrs, IFLA_VXLAN_ID)) {
		fprintf(stderr, "vxlan: missing virtual network identifier\n");
		return -1;
	}

	if ((gaddr || !IN6_IS_ADDR_UNSPECIFIED(&gaddr6)) &&
	    !VXLAN_ATTRSET(attrs, IFLA_VXLAN_LINK)) {
		fprintf(stderr, "vxlan: 'group' requires 'dev' to be specified\n");
		return -1;
	}

	if (!VXLAN_ATTRSET(attrs, IFLA_VXLAN_PORT) &&
	    VXLAN_ATTRSET(attrs, IFLA_VXLAN_GPE)) {
		dstport = 4790;
	} else if (!VXLAN_ATTRSET(attrs, IFLA_VXLAN_PORT) && !set_op) {
		fprintf(stderr, "vxlan: destination port not specified\n"
			"Will use Linux kernel default (non-standard value)\n");
		fprintf(stderr,
			"Use 'dstport 4789' to get the IANA assigned value\n"
			"Use 'dstport 0' to get default and quiet this message\n");
	}

	addattr32(n, 1024, IFLA_VXLAN_ID, vni);
	if (gaddr)
		addattr_l(n, 1024, IFLA_VXLAN_GROUP, &gaddr, 4);
	else if (daddr)
		addattr_l(n, 1024, IFLA_VXLAN_GROUP, &daddr, 4);
	else if (!IN6_IS_ADDR_UNSPECIFIED(&gaddr6))
		addattr_l(n, 1024, IFLA_VXLAN_GROUP6, &gaddr6, sizeof(struct in6_addr));
	else if (!IN6_IS_ADDR_UNSPECIFIED(&daddr6))
		addattr_l(n, 1024, IFLA_VXLAN_GROUP6, &daddr6, sizeof(struct in6_addr));
	else if (preferred_family == AF_INET)
		addattr_l(n, 1024, IFLA_VXLAN_GROUP, &daddr, 4);
	else if (preferred_family == AF_INET6)
		addattr_l(n, 1024, IFLA_VXLAN_GROUP6, &daddr6, sizeof(struct in6_addr));

	if (!set_op || VXLAN_ATTRSET(attrs, IFLA_VXLAN_LEARNING))
		addattr8(n, 1024, IFLA_VXLAN_LEARNING, learning);

	if (dstport)
		addattr16(n, 1024, IFLA_VXLAN_PORT, htons(dstport));

	return 0;
}