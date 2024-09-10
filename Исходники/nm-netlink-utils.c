static void
foreach_route_cb (struct nl_object *object, void *user_data)
{
	ForeachRouteInfo *info = user_data;
	struct rtnl_route *route = (struct rtnl_route *) object;
	struct nl_addr *dst;

	if (info->out_route)
		return;

	if (nm_logging_level_enabled (LOGL_DEBUG))
		dump_route (route);

	if (   info->ifindex > 0
	    && rtnl_route_get_oif (route) != info->ifindex)
		return;

	if (   info->scope != RT_SCOPE_UNIVERSE
	    && rtnl_route_get_scope (route) != info->scope)
		return;

	if (   info->family != AF_UNSPEC
	    && rtnl_route_get_family (route) != info->family)
		return;

	dst = rtnl_route_get_dst (route);

	/* Check for IPv6 LL and MC routes that might need to be ignored */
	if (   (info->family == AF_INET6 || info->family == AF_UNSPEC)
	    && (rtnl_route_get_family (route) == AF_INET6)) {
		struct in6_addr *addr = NULL;

		if (dst)
			addr = nl_addr_get_binary_addr (dst);
		if (addr) {
			if (   IN6_IS_ADDR_LINKLOCAL (addr)
			    || IN6_IS_ADDR_MC_LINKLOCAL (addr)
			    || (IN6_IS_ADDR_MULTICAST (addr) && (nl_addr_get_prefixlen (dst) == 8)))
				return;
		}
	}

	info->out_route = info->callback (route, dst, info->iface, info->user_data);
	if (info->out_route) {
		/* Ref the route so it sticks around after the cache is cleared */
		rtnl_route_get (info->out_route);
	}
}