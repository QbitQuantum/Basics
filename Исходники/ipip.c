static int ipip_tunnel_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ip_tunnel *tunnel = (struct ip_tunnel*)dev->priv;
	struct net_device_stats *stats = &tunnel->stat;
	struct iphdr  *tiph = &tunnel->parms.iph;
	u8     tos = tunnel->parms.iph.tos;
	u16    df = tiph->frag_off;
	struct rtable *rt;     			/* Route to the other host */
	struct net_device *tdev;			/* Device to other host */
	struct iphdr  *old_iph = skb->nh.iph;
#ifdef CONFIG_NET_IPIP_IPV6
	struct ipv6hdr *iph6 = skb->nh.ipv6h;
#endif
	struct iphdr  *iph;			/* Our new IP header */
	int    max_headroom;			/* The extra header space needed */
	u32    dst = tiph->daddr;
	int    mtu;
	u8 protocol = 0; 

	switch (skb->protocol) {
	case __constant_htons(ETH_P_IP):
		protocol = IPPROTO_IPIP;
		break;
#ifdef CONFIG_NET_IPIP_IPV6
	case __constant_htons(ETH_P_IPV6):
		protocol = IPPROTO_IPV6;
		break;
#endif
	}

	if (tunnel->recursion++) {
		tunnel->stat.collisions++;
		goto tx_error;
	}

	switch(skb->protocol) {
	case __constant_htons(ETH_P_IP):
		if (tunnel->parms.iph.protocol &&
		    tunnel->parms.iph.protocol != IPPROTO_IPIP)
			goto tx_error;
		if (tos&1)
			tos = old_iph->tos;
		break;
#ifdef CONFIG_NET_IPIP_IPV6
	case __constant_htons(ETH_P_IPV6):
		if (tunnel->parms.iph.protocol &&
		    tunnel->parms.iph.protocol != IPPROTO_IPV6)
			goto tx_error;
		break;
#endif
	default:
		goto tx_error;
	}

	if (!dst) {
		switch(skb->protocol){
		case __constant_htons(ETH_P_IP):
			/* NBMA tunnel */
			if ((rt = (struct rtable*)skb->dst) == NULL) {
				tunnel->stat.tx_fifo_errors++;
				goto tx_error;
			}
			dst = rt->rt_gateway;
			break;
#ifdef CONFIG_NET_IPIP_IPV6
		case __constant_htons(ETH_P_IPV6):
		    {
			struct in6_addr *addr6 = &iph6->daddr;
			if (addr6->s6_addr16[0] == htons(0x2002)) {
				memcpy(&dst, &addr6->s6_addr16[1], 4);
			} else {
				/* dst is zero */
				struct neighbour *neigh = NULL;
				if (skb->dst)
					neigh = skb->dst->neighbour;
				if (neigh == NULL) {
					printk(KERN_DEBUG "tunl: nexthop == NULL\n");
					goto tx_error;
				}
				addr6 = (struct in6_addr*)&neigh->primary_key;
				if (IN6_IS_ADDR_UNSPECIFIED(addr6))
					addr6 = &skb->nh.ipv6h->daddr;
				if (IN6_IS_ADDR_V4COMPAT(addr6))
					dst = addr6->s6_addr32[3];
#ifdef CONFIG_IPV6_6TO4_NEXTHOP
				else if (addr6->s6_addr16[0] == htons(0x2002)) 
					memcpy(&dst, &addr6->s6_addr16[1], 4);
#endif
				else
					goto tx_error_icmp;
			}
			break;
		    }
#endif
		}
		if (!dst)
			goto tx_error_icmp;
	}

	if (ip_route_output(&rt, dst, tiph->saddr, RT_TOS(tos), tunnel->parms.link)) {
		tunnel->stat.tx_carrier_errors++;
		goto tx_error_icmp;
	}
	tdev = rt->u.dst.dev;

	if (tdev == dev) {
		ip_rt_put(rt);
		tunnel->stat.collisions++;
		goto tx_error;
	}

	if (tiph->frag_off)
		mtu = rt->u.dst.pmtu - sizeof(struct iphdr);
	else
		mtu = skb->dst ? skb->dst->pmtu : dev->mtu;

	if (mtu < 68) {
		tunnel->stat.collisions++;
		ip_rt_put(rt);
		goto tx_error;
	}

	switch(skb->protocol){
	case __constant_htons(ETH_P_IP):
		if (skb->dst && mtu < skb->dst->pmtu)
			skb->dst->pmtu = mtu;

		df |= (old_iph->frag_off&htons(IP_DF));

		if ((old_iph->frag_off&htons(IP_DF)) && mtu < ntohs(old_iph->tot_len)) {
			icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED, htonl(mtu));
			ip_rt_put(rt);
			goto tx_error;
		}
		break;

#ifdef CONFIG_NET_IPIP_IPV6
	case __constant_htons(ETH_P_IPV6):
#if 0
		if (mtu < IPV6_MIN_MTU) {
			/* XXX: too small; we should fragment this packet? */
			tunnel->stat.tx_carrier_errors++;
			goto tx_error_icmp;
		}
#endif
		if (skb->len > mtu && mtu > IPV6_MIN_MTU) {
			icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu, dev);
			ip_rt_put(rt);
			goto tx_error;
		}
		df = mtu > IPV6_MIN_MTU ? htons(IP_DF) : 0;
		break;
#endif
	}
	if (tunnel->err_count > 0) {
		if (jiffies - tunnel->err_time < IPTUNNEL_ERR_TIMEO) {
			tunnel->err_count--;
			dst_link_failure(skb);
		} else
			tunnel->err_count = 0;
	}

	/*
	 * Okay, now see if we can stuff it in the buffer as-is.
	 */
	max_headroom = (((tdev->hard_header_len+15)&~15)+sizeof(struct iphdr));
	if (skb_headroom(skb) < max_headroom || skb_cloned(skb) || skb_shared(skb)) {
		struct sk_buff *new_skb = skb_realloc_headroom(skb, max_headroom);
		if (!new_skb) {
			ip_rt_put(rt);
  			stats->tx_dropped++;
			dev_kfree_skb(skb);
			tunnel->recursion--;
			return 0;
		}
		if (skb->sk)
			skb_set_owner_w(new_skb, skb->sk);
		dev_kfree_skb(skb);
		skb = new_skb;
		old_iph = skb->nh.iph;
	}

	skb->h.raw = skb->nh.raw;
	skb->nh.raw = skb_push(skb, sizeof(struct iphdr));
	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
	dst_release(skb->dst);
	skb->dst = &rt->u.dst;

	/*
	 *	Push down and install the IPIP header.
	 */

	iph 			=	skb->nh.iph;
	iph->version		=	4;
	iph->ihl		=	sizeof(struct iphdr)>>2;
	iph->daddr		=	rt->rt_dst;
	iph->saddr		=	rt->rt_src;

	iph->ttl		=	tiph->ttl;
	iph->frag_off		=	df;

	switch(skb->protocol){
	case __constant_htons(ETH_P_IP):
		iph->protocol	=	protocol;
		iph->tos	=	INET_ECN_encapsulate(tos, old_iph->tos);
		if (iph->ttl == 0)
			iph->ttl =	old_iph->ttl;
		break;
#ifdef CONFIG_NET_IPIP_IPV6
	case __constant_htons(ETH_P_IPV6):
		iph->protocol	=	protocol;
		iph->tos	=	INET_ECN_encapsulate(tos, ip6_get_dsfield(iph6));
		if (iph->ttl == 0)
			iph->ttl =	iph6->hop_limit;
		break;
#endif
	}

	nf_reset(skb);

	IPTUNNEL_XMIT();
	tunnel->recursion--;
	return 0;

tx_error_icmp:
	dst_link_failure(skb);
tx_error:
	stats->tx_errors++;
	dev_kfree_skb(skb);
	tunnel->recursion--;
	return 0;
}