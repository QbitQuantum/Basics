/*
 * Type0 routing header processing
 *
 * RFC2292 backward compatibility warning: no support for strict/loose bitmap,
 * as it was dropped between RFC1883 and RFC2460.
 */
static int
ip6_rthdr0(struct mbuf *m, struct ip6_hdr *ip6, 
	struct ip6_rthdr0 *rh0)
{
	int addrs, index;
	struct in6_addr *nextaddr, tmpaddr;
	const struct ip6aux *ip6a;

	if (rh0->ip6r0_segleft == 0)
		return (0);

	if (rh0->ip6r0_len % 2
#ifdef COMPAT_RFC1883
	    || rh0->ip6r0_len > 46
#endif
		) {
		/*
		 * Type 0 routing header can't contain more than 23 addresses.
		 * RFC 2462: this limitation was removed since strict/loose
		 * bitmap field was deleted.
		 */
		IP6_STATINC(IP6_STAT_BADOPTIONS);
		icmp6_error(m, ICMP6_PARAM_PROB, ICMP6_PARAMPROB_HEADER,
			    (char *)&rh0->ip6r0_len - (char *)ip6);
		return (-1);
	}

	if ((addrs = rh0->ip6r0_len / 2) < rh0->ip6r0_segleft) {
		IP6_STATINC(IP6_STAT_BADOPTIONS);
		icmp6_error(m, ICMP6_PARAM_PROB, ICMP6_PARAMPROB_HEADER,
			    (char *)&rh0->ip6r0_segleft - (char *)ip6);
		return (-1);
	}

	index = addrs - rh0->ip6r0_segleft;
	rh0->ip6r0_segleft--;
	nextaddr = ((struct in6_addr *)(rh0 + 1)) + index;

	/*
	 * reject invalid addresses.  be proactive about malicious use of
	 * IPv4 mapped/compat address.
	 * XXX need more checks?
	 */
	if (IN6_IS_ADDR_MULTICAST(nextaddr) ||
	    IN6_IS_ADDR_UNSPECIFIED(nextaddr) ||
	    IN6_IS_ADDR_V4MAPPED(nextaddr) ||
	    IN6_IS_ADDR_V4COMPAT(nextaddr)) {
		p6stat[IP6_STAT_BADOPTIONS]++;
		goto bad;
	}
	if (IN6_IS_ADDR_MULTICAST(&ip6->ip6_dst) ||
	    IN6_IS_ADDR_UNSPECIFIED(&ip6->ip6_dst) ||
	    IN6_IS_ADDR_V4MAPPED(&ip6->ip6_dst) ||
	    IN6_IS_ADDR_V4COMPAT(&ip6->ip6_dst)) {
		IP6_STATINC(IP6_STAT_BADOPTIONS);
		goto bad;
	}

	/*
	 * Determine the scope zone of the next hop, based on the interface
	 * of the current hop. [RFC4007, Section 9]
	 * Then disambiguate the scope zone for the next hop (if necessary). 
	 */
	if ((ip6a = ip6_getdstifaddr(m)) == NULL)
		goto bad;
	if (in6_setzoneid(nextaddr, ip6a->ip6a_scope_id) != 0) {
		IP6_STATINC(IP6_STAT_BADSCOPE);
		goto bad;
	}

	/*
	 * Swap the IPv6 destination address and nextaddr. Forward the packet.
	 */
	tmpaddr = *nextaddr;
	*nextaddr = ip6->ip6_dst;
	in6_clearscope(nextaddr); /* XXX */
	ip6->ip6_dst = tmpaddr;

#ifdef COMPAT_RFC1883
	if (rh0->ip6r0_slmap[index / 8] & (1 << (7 - (index % 8))))
		ip6_forward(m, IPV6_SRCRT_NEIGHBOR);
	else
		ip6_forward(m, IPV6_SRCRT_NOTNEIGHBOR);
#else
	ip6_forward(m, 1);
#endif

	return (-1);			/* m would be freed in ip6_forward() */

  bad:
	m_freem(m);
	return (-1);
}