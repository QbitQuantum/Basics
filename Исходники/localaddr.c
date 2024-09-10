static int
is_loopback_address(struct sockaddr *sa)
{
    switch (sa->sa_family) {
    case AF_INET: {
        struct sockaddr_in *s4 = sa2sin(sa);
        return s4->sin_addr.s_addr == htonl(INADDR_LOOPBACK);
    }
    case AF_INET6: {
        struct sockaddr_in6 *s6 = sa2sin6(sa);
        return IN6_IS_ADDR_LOOPBACK(&s6->sin6_addr);
    }
    default:
        return 0;
    }
}