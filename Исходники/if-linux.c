static int
link_route(struct nlmsghdr *nlm)
{
	int len, idx, metric;
	struct rtattr *rta;
	struct rtmsg *rtm;
	struct rt rt;
	char ifn[IF_NAMESIZE + 1];

	if (nlm->nlmsg_type != RTM_DELROUTE)
		return 0;

	len = nlm->nlmsg_len - sizeof(*nlm);
	if ((size_t)len < sizeof(*rtm)) {
		errno = EBADMSG;
		return -1;
	}
	rtm = NLMSG_DATA(nlm);
	if (rtm->rtm_type != RTN_UNICAST ||
	    rtm->rtm_table != RT_TABLE_MAIN ||
	    rtm->rtm_family != AF_INET ||
	    nlm->nlmsg_pid == (uint32_t)getpid())
		return 1;
	rta = (struct rtattr *)(void *)((char *)rtm +NLMSG_ALIGN(sizeof(*rtm)));
	len = NLMSG_PAYLOAD(nlm, sizeof(*rtm));
	memset(&rt, 0, sizeof(rt));
	rt.dest.s_addr = INADDR_ANY;
	rt.net.s_addr = INADDR_ANY;
	rt.gate.s_addr = INADDR_ANY;
	metric = 0;
	while (RTA_OK(rta, len)) {
		switch (rta->rta_type) {
		case RTA_DST:
			memcpy(&rt.dest.s_addr, RTA_DATA(rta),
			    sizeof(rt.dest.s_addr));
			break;
		case RTA_GATEWAY:
			memcpy(&rt.gate.s_addr, RTA_DATA(rta),
			    sizeof(rt.gate.s_addr));
			break;
		case RTA_OIF:
			idx = *(int *)RTA_DATA(rta);
			if (if_indextoname(idx, ifn))
				rt.iface = find_interface(ifn);
			break;
		case RTA_PRIORITY:
			metric = *(int *)RTA_DATA(rta);
			break;
		}
		rta = RTA_NEXT(rta, len);
	}
	if (rt.iface != NULL) {
		if (metric == rt.iface->metric) {
#ifdef INET
			inet_cidrtoaddr(rtm->rtm_dst_len, &rt.net);
			ipv4_routedeleted(&rt);
#endif
		}
	}
	return 1;
}