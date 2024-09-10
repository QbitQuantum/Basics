static int
filter_addresses(struct nlmsghdr *nh, void *data)
{
    int rc;
    int maxroutes = 0;
    struct kernel_route *routes = NULL;
    struct in6_addr addr;
    int *found = NULL;
    int len;
    struct ifaddrmsg *ifa;
    char ifname[IFNAMSIZ];
    int ifindex = 0;
    int ll = 0;

    if (data) {
        void **args = (void **)data;
        maxroutes = *(int *)args[0];
        routes = (struct kernel_route*)args[1];
        found = (int *)args[2];
        ifindex = args[3] ? *(int*)args[3] : 0;
        ll = args[4] ? !!*(int*)args[4] : 0;
    }

    len = nh->nlmsg_len;

    if (data && *found >= maxroutes)
        return 0;

    if (nh->nlmsg_type != RTM_NEWADDR &&
            (data || nh->nlmsg_type != RTM_DELADDR))
        return 0;

    ifa = (struct ifaddrmsg *)NLMSG_DATA(nh);
    len -= NLMSG_LENGTH(0);

    rc = parse_addr_rta(ifa, len, &addr);
    if (rc < 0)
        return 0;

    if (ll == !IN6_IS_ADDR_LINKLOCAL(&addr))
        return 0;

    if (ifindex && ifa->ifa_index != ifindex)
        return 0;

    kdebugf("found address on interface %s(%d): %s\n",
            if_indextoname(ifa->ifa_index, ifname), ifa->ifa_index,
            format_address(addr.s6_addr));

    if (data) {
        struct kernel_route *route = &routes[*found];
        memcpy(route->prefix, addr.s6_addr, 16);
        route->plen = 128;
        route->metric = 0;
        route->ifindex = ifa->ifa_index;
        route->proto = RTPROT_BABEL_LOCAL;
        memset(route->gw, 0, 16);
        *found = (*found)+1;
    }

    return 1;
}