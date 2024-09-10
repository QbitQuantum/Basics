uint32_t addrConvert(struct sockaddr *pAddr)
{
    uint32_t ipv4;
    if (AF_INET6 == pAddr->sa_family)
    {
        if (IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *)pAddr)->sin6_addr))
            ipv4 = ((Addr6 *) & ((struct sockaddr_in6 *)pAddr)->sin6_addr)->m_addrs[3];
        else
        {
            Addr6 *a6 = (Addr6 *) & ((struct sockaddr_in6 *)pAddr)->sin6_addr;
            ipv4 = a6->m_addrs[0] ^ a6->m_addrs[1] ^ a6->m_addrs[2] ^ a6->m_addrs[3];
        }
    }
    else
        ipv4 = ((struct sockaddr_in *)pAddr)->sin_addr.s_addr;
    return ipv4;
}