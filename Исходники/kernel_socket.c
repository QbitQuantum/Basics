static int
parse_kernel_route(const struct rt_msghdr *rtm, struct kernel_route *route)
{

    void *rta = (void*)rtm + sizeof(struct rt_msghdr);
    struct sockaddr_in6 *sin6;
    char addr[INET6_ADDRSTRLEN];

    memset(route, 0, sizeof(*route));
    route->metric = 0;
    route->ifindex = rtm->rtm_index;

    if(!(rtm->rtm_addrs & RTA_DST))
        return -1;
    sin6 = (struct sockaddr_in6 *)rta;
    if(IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr) 
       || IN6_IS_ADDR_MC_LINKLOCAL(&sin6->sin6_addr))
        return -1;
    if((rtm->rtm_flags & RTF_PROTO2) != 0)
        return -1;
    memcpy(&route->prefix, &sin6->sin6_addr, 16);
    rta += ROUNDUP(sizeof(struct sockaddr_in6));
   
    if(!(rtm->rtm_addrs & RTA_GATEWAY))
        return -1;

    sin6 = (struct sockaddr_in6 *)rta;
    if(IN6_IS_ADDR_LINKLOCAL (&sin6->sin6_addr)) {
        route->ifindex = IN6_LINKLOCAL_IFINDEX(sin6->sin6_addr);
        SET_IN6_LINKLOCAL_IFINDEX(sin6->sin6_addr, 0);
    }
    memcpy(&route->gw, &sin6->sin6_addr, 16);
    rta += ROUNDUP(sizeof(struct sockaddr_in6));

    if(!(rtm->rtm_addrs & RTA_NETMASK)) {
        route->plen = 0;
    } else {
        sin6 = (struct sockaddr_in6 *)rta;        
        route->plen = mask2len(&sin6->sin6_addr);
        inet_ntop(AF_INET6, &sin6->sin6_addr, addr, sizeof(addr));
        rta += ROUNDUP(sizeof(struct sockaddr_in6));
    }
    if (rtm->rtm_flags & RTF_HOST)
        route->plen = 128;

    if(ifindex_lo < 0) {
        ifindex_lo = if_nametoindex("lo0");
        if(ifindex_lo <= 0)
            return -1;
    }

    if(route->ifindex == ifindex_lo)
        return -1;

    return 0;

}