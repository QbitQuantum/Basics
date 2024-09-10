static ngx_int_t
ngx_limit_tcp_find(ngx_connection_t *c)
{
    struct sockaddr_in    *sin;
    ngx_limit_tcp_conf_t  *ltcf;
#if (NGX_HAVE_INET6)
    u_char                *p;
    in_addr_t              addr;
    struct sockaddr_in6   *sin6;
#endif

    ltcf = (ngx_limit_tcp_conf_t *) ngx_get_conf(ngx_cycle->conf_ctx,
                                                 ngx_limit_tcp_module);
    switch (c->sockaddr->sa_family) {

    case AF_INET:
        if (ltcf->rules) {
            sin = (struct sockaddr_in *) c->sockaddr;
            return ngx_limit_tcp_inet(c, ltcf, sin->sin_addr.s_addr);
        }
        break;

#if (NGX_HAVE_INET6)

    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) c->sockaddr;
        p = sin6->sin6_addr.s6_addr;

        if (ltcf->rules && IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr)) {
            addr = p[12] << 24;
            addr += p[13] << 16;
            addr += p[14] << 8;
            addr += p[15];
            return ngx_limit_tcp_inet(c, ltcf, htonl(addr));
        }

        if (ltcf->rules6) {
            return ngx_limit_tcp_inet6(c, ltcf, p);
        }

#endif
    }

    return NGX_OK;
}