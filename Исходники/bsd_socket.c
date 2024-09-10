/*
 * ::getaddrinfo
 */
int getaddrinfo(const char *nodename, const char *servname,
                const struct addrinfo *hints,
                struct addrinfo **res)
{
    unsigned long ip_addr;
    uint8_t domain;

    *res = malloc(sizeof(struct addrinfo));
    if (*res == NULL)
    {
        return EAI_MEMORY;
    }
    memset(*res, 0, sizeof(struct addrinfo));

    (*res)->ai_addr = malloc(sizeof(struct sockaddr));
    if ((*res)->ai_addr == NULL)
    {
        free(*res);
        return EAI_MEMORY;
    }
    memset((*res)->ai_addr, 0, sizeof(struct addrinfo));

    switch (hints->ai_family)
    {
        case AF_INET:
            domain = SL_AF_INET;
            break;
        case AF_INET6:
            domain = SL_AF_INET6;
            break;
        case AF_PACKET:
            domain = SL_AF_PACKET;
            break;
        default:
            errno = EAFNOSUPPORT;
            free((*res)->ai_addr);
            free(*res);
            return -1;
    }

    int result = sl_NetAppDnsGetHostByName((int8_t*)nodename, strlen(nodename),
                                           &ip_addr, domain);

    if (result != 0)
    {
        free((*res)->ai_addr);
        free(*res);
        switch (result)
        {
            default:
            case SL_POOL_IS_EMPTY:
                return EAI_AGAIN;
            case SL_NET_APP_DNS_QUERY_NO_RESPONSE:
            case SL_NET_APP_DNS_NO_SERVER:
            case SL_NET_APP_DNS_QUERY_FAILED:
            case SL_NET_APP_DNS_MALFORMED_PACKET:
            case SL_NET_APP_DNS_MISMATCHED_RESPONSE:
                return EAI_FAIL;
        }
    }

    switch (hints->ai_family)
    {
        case AF_INET:
        {
            struct sockaddr_in *addr_in = (struct sockaddr_in*)(*res)->ai_addr;
            (*res)->ai_flags = 0;
            (*res)->ai_family = hints->ai_family;
            (*res)->ai_socktype = hints->ai_socktype;
            (*res)->ai_protocol = hints->ai_protocol;
            (*res)->ai_addrlen = sizeof(struct sockaddr_in);
            addr_in->sin_family = hints->ai_family;
            addr_in->sin_port = htons((uint16_t)strtol(servname, NULL, 0));
            addr_in->sin_addr.s_addr = htonl(ip_addr);
            break;
        }
        case AF_INET6:
        case AF_PACKET:
        default:
            errno = EAFNOSUPPORT;
            free((*res)->ai_addr);
            free(*res);
            return -1;
    }

    return 0;
}