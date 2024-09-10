/*
 * route_get_exact_prefix: it dumps the routing table and search for a route
 * which has the prefix equal to `prefix', if it is found its destination
 * address is stored in `dst' and its interface name in `dev_name' (which must
 * be IFNAMSIZ big).
 */
int
route_get_exact_prefix_dst(inet_prefix prefix, inet_prefix * dst,
						   char *dev_name)
{
	int do_ipv6 = AF_UNSPEC;
	struct rtnl_handle rth;
	char dst_data[sizeof(inet_prefix) + IFNAMSIZ];

	route_reset_filter();
	filter.tb = RT_TABLE_MAIN;

	filter.mdst = prefix;
	filter.rdst = filter.mdst;

	if (do_ipv6 == AF_UNSPEC && filter.tb)
		do_ipv6 = AF_INET;

	if (rtnl_open(&rth, 0) < 0)
		return -1;

	ll_init_map(&rth);

	if (rtnl_wilddump_request(&rth, do_ipv6, RTM_GETROUTE) < 0) {
		error(ERROR_MSG "Cannot send dump request" ERROR_POS);
		return -1;
	}

	setzero(dst_data, sizeof(dst_data));
	if (rtnl_dump_filter(&rth, route_get_gw, dst_data, NULL, NULL) < 0) {
		debug(DBG_NORMAL, ERROR_MSG "Dump terminated" ERROR_POS);
		return -1;
	}
	inet_copy(dst, (inet_prefix *) dst_data);
	memcpy(dev_name, dst_data + sizeof(inet_prefix), IFNAMSIZ);

	rtnl_close(&rth);

	return 0;
}