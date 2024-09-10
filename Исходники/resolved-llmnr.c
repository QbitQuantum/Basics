int manager_llmnr_ipv4_tcp_fd(Manager *m) {
        union sockaddr_union sa = {
                .in.sin_family = AF_INET,
                .in.sin_port = htobe16(LLMNR_PORT),
        };
        static const int one = 1, pmtu = IP_PMTUDISC_DONT;
        int r;

        assert(m);

        if (m->llmnr_ipv4_tcp_fd >= 0)
                return m->llmnr_ipv4_tcp_fd;

        m->llmnr_ipv4_tcp_fd = socket(AF_INET, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0);
        if (m->llmnr_ipv4_tcp_fd < 0)
                return -errno;

        /* RFC 4795, section 2.5. requires setting the TTL of TCP streams to 1 */
        r = setsockopt(m->llmnr_ipv4_tcp_fd, IPPROTO_IP, IP_TTL, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = setsockopt(m->llmnr_ipv4_tcp_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = setsockopt(m->llmnr_ipv4_tcp_fd, IPPROTO_IP, IP_PKTINFO, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = setsockopt(m->llmnr_ipv4_tcp_fd, IPPROTO_IP, IP_RECVTTL, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        /* Disable Don't-Fragment bit in the IP header */
        r = setsockopt(m->llmnr_ipv4_tcp_fd, IPPROTO_IP, IP_MTU_DISCOVER, &pmtu, sizeof(pmtu));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = bind(m->llmnr_ipv4_tcp_fd, &sa.sa, sizeof(sa.in));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = listen(m->llmnr_ipv4_tcp_fd, SOMAXCONN);
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = sd_event_add_io(m->event, &m->llmnr_ipv4_tcp_event_source, m->llmnr_ipv4_tcp_fd, EPOLLIN, on_llmnr_stream, m);
        if (r < 0)
                goto fail;

        return m->llmnr_ipv4_tcp_fd;

fail:
        m->llmnr_ipv4_tcp_fd = safe_close(m->llmnr_ipv4_tcp_fd);
        return r;
}

int manager_llmnr_ipv6_tcp_fd(Manager *m) {
        union sockaddr_union sa = {
                .in6.sin6_family = AF_INET6,
                .in6.sin6_port = htobe16(LLMNR_PORT),
        };
        static const int one = 1;
        int r;

        assert(m);

        if (m->llmnr_ipv6_tcp_fd >= 0)
                return m->llmnr_ipv6_tcp_fd;

        m->llmnr_ipv6_tcp_fd = socket(AF_INET6, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0);
        if (m->llmnr_ipv6_tcp_fd < 0)
                return -errno;

        /* RFC 4795, section 2.5. requires setting the TTL of TCP streams to 1 */
        r = setsockopt(m->llmnr_ipv6_tcp_fd, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = setsockopt(m->llmnr_ipv6_tcp_fd, IPPROTO_IPV6, IPV6_V6ONLY, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = setsockopt(m->llmnr_ipv6_tcp_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = setsockopt(m->llmnr_ipv6_tcp_fd, IPPROTO_IPV6, IPV6_RECVPKTINFO, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = setsockopt(m->llmnr_ipv6_tcp_fd, IPPROTO_IPV6, IPV6_RECVHOPLIMIT, &one, sizeof(one));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = bind(m->llmnr_ipv6_tcp_fd, &sa.sa, sizeof(sa.in6));
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = listen(m->llmnr_ipv6_tcp_fd, SOMAXCONN);
        if (r < 0) {
                r = -errno;
                goto fail;
        }

        r = sd_event_add_io(m->event, &m->llmnr_ipv6_tcp_event_source, m->llmnr_ipv6_tcp_fd, EPOLLIN, on_llmnr_stream, m);
        if (r < 0)
                goto fail;

        return m->llmnr_ipv6_tcp_fd;

fail:
        m->llmnr_ipv6_tcp_fd = safe_close(m->llmnr_ipv6_tcp_fd);
        return r;
}