/*
 * Input a Neighbor Solicitation Message.
 *
 * Based on RFC 2461
 * Based on RFC 2462 (duplicate address detection)
 */
void
nd6_ns_input(struct mbuf *m, int off, int icmp6len)
{
	struct ifnet *ifp = m->m_pkthdr.rcvif;
	struct ip6_hdr *ip6 = mtod(m, struct ip6_hdr *);
	struct nd_neighbor_solicit *nd_ns;
	struct in6_addr saddr6 = ip6->ip6_src;
	struct in6_addr daddr6 = ip6->ip6_dst;
	struct in6_addr taddr6;
	struct in6_addr myaddr6;
	char *lladdr = NULL;
	struct ifaddr *ifa = NULL;
	int lladdrlen = 0;
	int anycast = 0, proxy = 0, tentative = 0;
	int tlladdr;
	union nd_opts ndopts;
	struct sockaddr_dl *proxydl = NULL;
	char ip6bufs[INET6_ADDRSTRLEN], ip6bufd[INET6_ADDRSTRLEN];

#ifndef PULLDOWN_TEST
	IP6_EXTHDR_CHECK(m, off, icmp6len,);
	nd_ns = (struct nd_neighbor_solicit *)((caddr_t)ip6 + off);
#else
	IP6_EXTHDR_GET(nd_ns, struct nd_neighbor_solicit *, m, off, icmp6len);
	if (nd_ns == NULL) {
		ICMP6STAT_INC(icp6s_tooshort);
		return;
	}
#endif
	ip6 = mtod(m, struct ip6_hdr *); /* adjust pointer for safety */
	taddr6 = nd_ns->nd_ns_target;
	if (in6_setscope(&taddr6, ifp, NULL) != 0)
		goto bad;

	if (ip6->ip6_hlim != 255) {
		nd6log((LOG_ERR,
		    "nd6_ns_input: invalid hlim (%d) from %s to %s on %s\n",
		    ip6->ip6_hlim, ip6_sprintf(ip6bufs, &ip6->ip6_src),
		    ip6_sprintf(ip6bufd, &ip6->ip6_dst), if_name(ifp)));
		goto bad;
	}

	if (IN6_IS_ADDR_UNSPECIFIED(&saddr6)) {
		/* dst has to be a solicited node multicast address. */
		if (daddr6.s6_addr16[0] == IPV6_ADDR_INT16_MLL &&
		    /* don't check ifindex portion */
		    daddr6.s6_addr32[1] == 0 &&
		    daddr6.s6_addr32[2] == IPV6_ADDR_INT32_ONE &&
		    daddr6.s6_addr8[12] == 0xff) {
			; /* good */
		} else {
			nd6log((LOG_INFO, "nd6_ns_input: bad DAD packet "
			    "(wrong ip6 dst)\n"));
			goto bad;
		}
	} else if (!V_nd6_onlink_ns_rfc4861) {
		struct sockaddr_in6 src_sa6;

		/*
		 * According to recent IETF discussions, it is not a good idea
		 * to accept a NS from an address which would not be deemed
		 * to be a neighbor otherwise.  This point is expected to be
		 * clarified in future revisions of the specification.
		 */
		bzero(&src_sa6, sizeof(src_sa6));
		src_sa6.sin6_family = AF_INET6;
		src_sa6.sin6_len = sizeof(src_sa6);
		src_sa6.sin6_addr = saddr6;
		if (nd6_is_addr_neighbor(&src_sa6, ifp) == 0) {
			nd6log((LOG_INFO, "nd6_ns_input: "
				"NS packet from non-neighbor\n"));
			goto bad;
		}
	}

	if (IN6_IS_ADDR_MULTICAST(&taddr6)) {
		nd6log((LOG_INFO, "nd6_ns_input: bad NS target (multicast)\n"));
		goto bad;
	}

	icmp6len -= sizeof(*nd_ns);
	nd6_option_init(nd_ns + 1, icmp6len, &ndopts);
	if (nd6_options(&ndopts) < 0) {
		nd6log((LOG_INFO,
		    "nd6_ns_input: invalid ND option, ignored\n"));
		/* nd6_options have incremented stats */
		goto freeit;
	}

	if (ndopts.nd_opts_src_lladdr) {
		lladdr = (char *)(ndopts.nd_opts_src_lladdr + 1);
		lladdrlen = ndopts.nd_opts_src_lladdr->nd_opt_len << 3;
	}

	if (IN6_IS_ADDR_UNSPECIFIED(&ip6->ip6_src) && lladdr) {
		nd6log((LOG_INFO, "nd6_ns_input: bad DAD packet "
		    "(link-layer address option)\n"));
		goto bad;
	}

	/*
	 * Attaching target link-layer address to the NA?
	 * (RFC 2461 7.2.4)
	 *
	 * NS IP dst is unicast/anycast			MUST NOT add
	 * NS IP dst is solicited-node multicast	MUST add
	 *
	 * In implementation, we add target link-layer address by default.
	 * We do not add one in MUST NOT cases.
	 */
	if (!IN6_IS_ADDR_MULTICAST(&daddr6))
		tlladdr = 0;
	else
		tlladdr = 1;

	/*
	 * Target address (taddr6) must be either:
	 * (1) Valid unicast/anycast address for my receiving interface,
	 * (2) Unicast address for which I'm offering proxy service, or
	 * (3) "tentative" address on which DAD is being performed.
	 */
	/* (1) and (3) check. */
	if (ifp->if_carp)
		ifa = (*carp_iamatch6_p)(ifp, &taddr6);
	if (ifa == NULL)
		ifa = (struct ifaddr *)in6ifa_ifpwithaddr(ifp, &taddr6);

	/* (2) check. */
	if (ifa == NULL) {
		struct rtentry *rt;
		struct sockaddr_in6 tsin6;
		int need_proxy;
#ifdef RADIX_MPATH
		struct route_in6 ro;
#endif

		bzero(&tsin6, sizeof tsin6);
		tsin6.sin6_len = sizeof(struct sockaddr_in6);
		tsin6.sin6_family = AF_INET6;
		tsin6.sin6_addr = taddr6;

#ifdef RADIX_MPATH
		bzero(&ro, sizeof(ro));
		ro.ro_dst = tsin6;
		rtalloc_mpath((struct route *)&ro, RTF_ANNOUNCE);
		rt = ro.ro_rt;
#else
		rt = rtalloc1((struct sockaddr *)&tsin6, 0, 0);
#endif
		need_proxy = (rt && (rt->rt_flags & RTF_ANNOUNCE) != 0 &&
		    rt->rt_gateway->sa_family == AF_LINK);
		if (rt)
			RTFREE_LOCKED(rt);
		if (need_proxy) {
			/*
			 * proxy NDP for single entry
			 */
			ifa = (struct ifaddr *)in6ifa_ifpforlinklocal(ifp,
				IN6_IFF_NOTREADY|IN6_IFF_ANYCAST);
			if (ifa) {
				proxy = 1;
				proxydl = SDL(rt->rt_gateway);
			}
		}
	}
	if (ifa == NULL) {
		/*
		 * We've got an NS packet, and we don't have that adddress
		 * assigned for us.  We MUST silently ignore it.
		 * See RFC2461 7.2.3.
		 */
		goto freeit;
	}
	myaddr6 = *IFA_IN6(ifa);
	anycast = ((struct in6_ifaddr *)ifa)->ia6_flags & IN6_IFF_ANYCAST;
	tentative = ((struct in6_ifaddr *)ifa)->ia6_flags & IN6_IFF_TENTATIVE;
	if (((struct in6_ifaddr *)ifa)->ia6_flags & IN6_IFF_DUPLICATED)
		goto freeit;

	if (lladdr && ((ifp->if_addrlen + 2 + 7) & ~7) != lladdrlen) {
		nd6log((LOG_INFO, "nd6_ns_input: lladdrlen mismatch for %s "
		    "(if %d, NS packet %d)\n",
		    ip6_sprintf(ip6bufs, &taddr6),
		    ifp->if_addrlen, lladdrlen - 2));
		goto bad;
	}

	if (IN6_ARE_ADDR_EQUAL(&myaddr6, &saddr6)) {
		nd6log((LOG_INFO, "nd6_ns_input: duplicate IP6 address %s\n",
		    ip6_sprintf(ip6bufs, &saddr6)));
		goto freeit;
	}

	/*
	 * We have neighbor solicitation packet, with target address equals to
	 * one of my tentative address.
	 *
	 * src addr	how to process?
	 * ---		---
	 * multicast	of course, invalid (rejected in ip6_input)
	 * unicast	somebody is doing address resolution -> ignore
	 * unspec	dup address detection
	 *
	 * The processing is defined in RFC 2462.
	 */
	if (tentative) {
		/*
		 * If source address is unspecified address, it is for
		 * duplicate address detection.
		 *
		 * If not, the packet is for addess resolution;
		 * silently ignore it.
		 */
		if (IN6_IS_ADDR_UNSPECIFIED(&saddr6))
			nd6_dad_ns_input(ifa);

		goto freeit;
	}

	/*
	 * If the source address is unspecified address, entries must not
	 * be created or updated.
	 * It looks that sender is performing DAD.  Output NA toward
	 * all-node multicast address, to tell the sender that I'm using
	 * the address.
	 * S bit ("solicited") must be zero.
	 */
	if (IN6_IS_ADDR_UNSPECIFIED(&saddr6)) {
		struct in6_addr in6_all;

		in6_all = in6addr_linklocal_allnodes;
		if (in6_setscope(&in6_all, ifp, NULL) != 0)
			goto bad;
		nd6_na_output(ifp, &in6_all, &taddr6,
		    ((anycast || proxy || !tlladdr) ? 0 : ND_NA_FLAG_OVERRIDE) |
		    (V_ip6_forwarding ? ND_NA_FLAG_ROUTER : 0),
		    tlladdr, (struct sockaddr *)proxydl);
		goto freeit;
	}

	nd6_cache_lladdr(ifp, &saddr6, lladdr, lladdrlen,
	    ND_NEIGHBOR_SOLICIT, 0);

	nd6_na_output(ifp, &saddr6, &taddr6,
	    ((anycast || proxy || !tlladdr) ? 0 : ND_NA_FLAG_OVERRIDE) |
	    (V_ip6_forwarding ? ND_NA_FLAG_ROUTER : 0) | ND_NA_FLAG_SOLICITED,
	    tlladdr, (struct sockaddr *)proxydl);
 freeit:
	if (ifa != NULL)
		ifa_free(ifa);
	m_freem(m);
	return;

 bad:
	nd6log((LOG_ERR, "nd6_ns_input: src=%s\n",
		ip6_sprintf(ip6bufs, &saddr6)));
	nd6log((LOG_ERR, "nd6_ns_input: dst=%s\n",
		ip6_sprintf(ip6bufs, &daddr6)));
	nd6log((LOG_ERR, "nd6_ns_input: tgt=%s\n",
		ip6_sprintf(ip6bufs, &taddr6)));
	ICMP6STAT_INC(icp6s_badns);
	if (ifa != NULL)
		ifa_free(ifa);
	m_freem(m);
}