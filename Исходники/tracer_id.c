enum ip_addr_type get_ipv6_addr_type(const struct sockaddr_in6 *ip)
{
    if (IN6_IS_ADDR_LOOPBACK(ip)) {
        return ADDR_TYPE_IPV6_LOOPBACK;
    } else if (IN6_IS_ADDR_SITELOCAL(ip)) {
        return ADDR_TYPE_IPV6_SITE_LOCAL;
    } else {
        return ADDR_TYPE_IPV6_OTHER;
    }
}