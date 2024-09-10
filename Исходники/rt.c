/* Parse one route */
static int rt_parse(const struct nlmsghdr *nlhdr, struct net_rt *rt)
{
	struct rtmsg *rtmsg;
	struct rtattr *rtattr;
	int len;

	rtmsg = (struct rtmsg *)NLMSG_DATA(nlhdr);

	/* If the route does not belong to main routing table then return. */
	if (RT_TABLE_MAIN != rtmsg->rtm_table)
		return EINVAL;

	sa_init(&rt->dst, rtmsg->rtm_family);
	rt->dstlen = rtmsg->rtm_dst_len;

	/* get the rtattr field */
	rtattr = (struct rtattr *)RTM_RTA(rtmsg);
	len = RTM_PAYLOAD(nlhdr);
	for (;RTA_OK(rtattr, len); rtattr = RTA_NEXT(rtattr, len)) {

		switch (rtattr->rta_type) {

		case RTA_OIF:
			if_indextoname(*(int *)RTA_DATA(rtattr), rt->ifname);
			break;

		case RTA_GATEWAY:
			switch (rtmsg->rtm_family) {

			case AF_INET:
				sa_init(&rt->gw, AF_INET);
				rt->gw.u.in.sin_addr.s_addr
					= *(uint32_t *)RTA_DATA(rtattr);
				break;

#ifdef HAVE_INET6
			case AF_INET6:
				sa_set_in6(&rt->gw, RTA_DATA(rtattr), 0);
				break;
#endif

			default:
				DEBUG_WARNING("RTA_DST: unknown family %d\n",
					      rtmsg->rtm_family);
				break;
			}
			break;

#if 0
		case RTA_PREFSRC:
			rt->srcaddr = *(uint32_t *)RTA_DATA(rtattr);
			break;
#endif

		case RTA_DST:
			switch (rtmsg->rtm_family) {

			case AF_INET:
				sa_init(&rt->dst, AF_INET);
				rt->dst.u.in.sin_addr.s_addr
					= *(uint32_t *)RTA_DATA(rtattr);
				break;

#ifdef HAVE_INET6
			case AF_INET6:
				sa_set_in6(&rt->dst, RTA_DATA(rtattr), 0);
				break;
#endif

			default:
				DEBUG_WARNING("RTA_DST: unknown family %d\n",
					      rtmsg->rtm_family);
				break;
			}
			break;
		}
	}

	return 0;
}