static RPC_STATUS rpcrt4_ncacn_ip_tcp_parse_top_of_tower(const unsigned char *tower_data,
                                                         size_t tower_size,
                                                         char **networkaddr,
                                                         char **endpoint)
{
    const twr_tcp_floor_t *tcp_floor = (const twr_tcp_floor_t *)tower_data;
    const twr_ipv4_floor_t *ipv4_floor;
    struct in_addr in_addr;

    TRACE("(%p, %d, %p, %p)\n", tower_data, (int)tower_size, networkaddr, endpoint);

    if (tower_size < sizeof(*tcp_floor))
        return EPT_S_NOT_REGISTERED;

    tower_data += sizeof(*tcp_floor);
    tower_size -= sizeof(*tcp_floor);

    if (tower_size < sizeof(*ipv4_floor))
        return EPT_S_NOT_REGISTERED;

    ipv4_floor = (const twr_ipv4_floor_t *)tower_data;

    if ((tcp_floor->count_lhs != sizeof(tcp_floor->protid)) ||
        (tcp_floor->protid != EPM_PROTOCOL_TCP) ||
        (tcp_floor->count_rhs != sizeof(tcp_floor->port)) ||
        (ipv4_floor->count_lhs != sizeof(ipv4_floor->protid)) ||
        (ipv4_floor->protid != EPM_PROTOCOL_IP) ||
        (ipv4_floor->count_rhs != sizeof(ipv4_floor->ipv4addr)))
        return EPT_S_NOT_REGISTERED;

    if (endpoint)
    {
        *endpoint = I_RpcAllocate(6 /* sizeof("65535") + 1 */);
        if (!*endpoint)
            return RPC_S_OUT_OF_RESOURCES;
        sprintf(*endpoint, "%u", ntohs(tcp_floor->port));
    }

    if (networkaddr)
    {
        *networkaddr = I_RpcAllocate(INET_ADDRSTRLEN);
        if (!*networkaddr)
        {
            if (endpoint)
            {
                I_RpcFree(*endpoint);
                *endpoint = NULL;
            }
            return RPC_S_OUT_OF_RESOURCES;
        }
        in_addr.s_addr = ipv4_floor->ipv4addr;
        if (!inet_ntop(AF_INET, &in_addr, *networkaddr, INET_ADDRSTRLEN))
        {
            ERR("inet_ntop: %s\n", strerror(errno));
            I_RpcFree(*networkaddr);
            *networkaddr = NULL;
            if (endpoint)
            {
                I_RpcFree(*endpoint);
                *endpoint = NULL;
            }
            return EPT_S_NOT_REGISTERED;
        }
    }

    return RPC_S_OK;
}