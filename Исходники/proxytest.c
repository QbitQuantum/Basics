/**
 * Create a socket for outbound connection to dst_addr:dst_port.
 *
 * The socket is non-blocking and TCP sockets has SIGPIPE disabled if
 * possible.  On Linux it's not possible and should be disabled for
 * each send(2) individually.
 */
SOCKET
proxy_connected_socket(int sdom, int stype,
                       ipX_addr_t *dst_addr, u16_t dst_port)
{
    struct sockaddr_in6 dst_sin6;
    struct sockaddr_in dst_sin;
    struct sockaddr *pdst_sa;
    socklen_t dst_sa_len;
    void *pdst_addr;
    const struct sockaddr *psrc_sa;
    socklen_t src_sa_len;
    int status;
    SOCKET s;

    LWIP_ASSERT1(sdom == PF_INET || sdom == PF_INET6);
    LWIP_ASSERT1(stype == SOCK_STREAM || stype == SOCK_DGRAM);

    if (sdom == PF_INET6) {
        pdst_sa = (struct sockaddr *)&dst_sin6;
        pdst_addr = (void *)&dst_sin6.sin6_addr;

        memset(&dst_sin6, 0, sizeof(dst_sin6));
#if HAVE_SA_LEN
        dst_sin6.sin6_len =
#endif
            dst_sa_len = sizeof(dst_sin6);
        dst_sin6.sin6_family = AF_INET6;
        memcpy(&dst_sin6.sin6_addr, &dst_addr->ip6, sizeof(ip6_addr_t));
        dst_sin6.sin6_port = htons(dst_port);
    }
    else { /* sdom = PF_INET */
        pdst_sa = (struct sockaddr *)&dst_sin;
        pdst_addr = (void *)&dst_sin.sin_addr;

        memset(&dst_sin, 0, sizeof(dst_sin));
#if HAVE_SA_LEN
        dst_sin.sin_len =
#endif
            dst_sa_len = sizeof(dst_sin);
        dst_sin.sin_family = AF_INET;
        dst_sin.sin_addr.s_addr = dst_addr->ip4.addr; /* byte-order? */
        dst_sin.sin_port = htons(dst_port);
    }

#if LWIP_PROXY_DEBUG && !RT_OS_WINDOWS
    {
        char addrbuf[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255"];
        const char *addrstr;

        addrstr = inet_ntop(sdom, pdst_addr, addrbuf, sizeof(addrbuf));
        DPRINTF(("---> %s %s%s%s:%d ",
                 stype == SOCK_STREAM ? "TCP" : "UDP",
                 sdom == PF_INET6 ? "[" : "",
                 addrstr,
                 sdom == PF_INET6 ? "]" : "",
                 dst_port));
    }
#endif

    s = proxy_create_socket(sdom, stype);
    if (s == INVALID_SOCKET) {
        return INVALID_SOCKET;
    }
    DPRINTF(("socket %d\n", s));

    /* TODO: needs locking if dynamic modifyvm is allowed */
    if (sdom == PF_INET6) {
        psrc_sa = (const struct sockaddr *)g_proxy_options->src6;
        src_sa_len = sizeof(struct sockaddr_in6);
    }
    else {
        psrc_sa = (const struct sockaddr *)g_proxy_options->src4;
        src_sa_len = sizeof(struct sockaddr_in);
    }
    if (psrc_sa != NULL) {
        status = bind(s, psrc_sa, src_sa_len);
        if (status == SOCKET_ERROR) {
            DPRINTF(("socket %d: bind: %s\n", s, strerror(errno)));
            closesocket(s);
            return INVALID_SOCKET;
        }
    }

    status = connect(s, pdst_sa, dst_sa_len);
    if (status == SOCKET_ERROR && errno != EINPROGRESS) {
        DPRINTF(("socket %d: connect: %s\n", s, strerror(errno)));
        closesocket(s);
        return INVALID_SOCKET;
    }

    return s;
}