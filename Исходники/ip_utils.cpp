bool
IpAddr::isLoopback() const
{
    switch (addr.addr.sa_family) {
    case AF_INET: {
        uint8_t b1 = (uint8_t)(addr.ipv4.sin_addr.s_addr >> 24);
        return b1 == 127;
    }
    case AF_INET6:
        return IN6_IS_ADDR_LOOPBACK(reinterpret_cast<const in6_addr*>(&addr.ipv6.sin6_addr));
    default:
        return false;
    }
}