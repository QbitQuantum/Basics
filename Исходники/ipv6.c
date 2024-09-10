bool fe_ipv6_peer_from_host(fe_ipv6_peer *p, const char host[FE_IPV6_HOSTMAXLEN], uint16_t port, 
                            bool udp) {
    struct addrinfo hints = {0};
    hints.ai_family = AF_INET6;
    hints.ai_socktype = udp ? SOCK_DGRAM : SOCK_STREAM;
    hints.ai_protocol = udp ? IPPROTO_UDP : IPPROTO_TCP;
/* Maybe my MinGW is buggy, but I need this : */
#ifndef AI_NUMERICSERV
#define AI_NUMERICSERV 0x0008
#endif
#ifndef AI_ALL
#define AI_ALL         0x0100
#endif
#ifndef AI_V4MAPPED
#define AI_V4MAPPED    0x0800
#endif
    hints.ai_flags = AI_V4MAPPED | AI_ALL | AI_NUMERICSERV;
    char service[6];
    snprintf(service, 6, "%hu", port);
    struct addrinfo *info;
    int err = getaddrinfo(host, service, &hints, &info);
    if(err) {
#ifdef FE_TARGET_WINDOWS
        WCHAR* errstr_w = gai_strerrorW(err);
        char* errstr = fe_utf8_from_win32unicode(errstr_w);
        fe_logv(TAG, "%s\n", errstr);
        fe_mem_heapfree(errstr);
#else
        fe_logv(TAG, "%s\n", gai_strerror(err));
#endif
        return false;
    }
    /* const struct addrinfo *cur;
       for(cur=info ; cur ; cur=cur->ai_next) ... */
    *p = *(fe_ipv6_peer*)info->ai_addr;
    freeaddrinfo(info);
    return true;
}