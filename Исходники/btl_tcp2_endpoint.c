static void mca_btl_tcp2_endpoint_dump(mca_btl_base_endpoint_t* btl_endpoint, const char* msg)
{
    char src[64];
    char dst[64];
    int sndbuf,rcvbuf,nodelay,flags;
#if OPAL_ENABLE_IPV6
    struct sockaddr_storage inaddr;
#else
    struct sockaddr_in inaddr;
#endif
    opal_socklen_t obtlen;
    opal_socklen_t addrlen = sizeof(inaddr);

    getsockname(btl_endpoint->endpoint_sd, (struct sockaddr*)&inaddr, &addrlen);
#if OPAL_ENABLE_IPV6
    {
        char *address;
        address = (char *) opal_net_get_hostname((struct sockaddr*) &inaddr);
        if (NULL != address) {
            sprintf(src, "%s", address);
        }
    }
#else
    sprintf(src, "%s", inet_ntoa(inaddr.sin_addr));
#endif
    getpeername(btl_endpoint->endpoint_sd, (struct sockaddr*)&inaddr, &addrlen);
#if OPAL_ENABLE_IPV6
    {
        char *address;
        address = (char *) opal_net_get_hostname ((struct sockaddr*) &inaddr);
        if (NULL != address) {
            sprintf(dst, "%s", address);
        }
    }
#else
    sprintf(dst, "%s", inet_ntoa(inaddr.sin_addr));
#endif

    if((flags = fcntl(btl_endpoint->endpoint_sd, F_GETFL, 0)) < 0) {
        BTL_ERROR(("fcntl(F_GETFL) failed: %s (%d)", 
                   strerror(opal_socket_errno), opal_socket_errno));
    }

#if defined(SO_SNDBUF)
    obtlen = sizeof(sndbuf);
    if(getsockopt(btl_endpoint->endpoint_sd, SOL_SOCKET, SO_SNDBUF, (char *)&sndbuf, &obtlen) < 0) {
        BTL_ERROR(("SO_SNDBUF option: %s (%d)",
                   strerror(opal_socket_errno), opal_socket_errno));
    }
#else
    sndbuf = -1;
#endif
#if defined(SO_RCVBUF)
    obtlen = sizeof(rcvbuf);
    if(getsockopt(btl_endpoint->endpoint_sd, SOL_SOCKET, SO_RCVBUF, (char *)&rcvbuf, &obtlen) < 0) {
        BTL_ERROR(("SO_RCVBUF option: %s (%d)", 
                   strerror(opal_socket_errno), opal_socket_errno));
    }
#else
    rcvbuf = -1;
#endif
#if defined(TCP_NODELAY)
    obtlen = sizeof(nodelay);
    if(getsockopt(btl_endpoint->endpoint_sd, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, &obtlen) < 0) {
        BTL_ERROR(("TCP_NODELAY option: %s (%d)", 
                   strerror(opal_socket_errno), opal_socket_errno));
    }
#else
    nodelay = 0;
#endif

    BTL_VERBOSE(("%s: %s - %s nodelay %d sndbuf %d rcvbuf %d flags %08x", 
        msg, src, dst, nodelay, sndbuf, rcvbuf, flags));
}