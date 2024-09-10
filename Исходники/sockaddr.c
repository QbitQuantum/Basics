static apr_status_t parse_ip(apr_ipsubnet_t *ipsub, const char *ipstr, int network_allowed)
{
    /* supported flavors of IP:
     *
     * . IPv6 numeric address string (e.g., "fe80::1")
     * 
     *   IMPORTANT: Don't store IPv4-mapped IPv6 address as an IPv6 address.
     *
     * . IPv4 numeric address string (e.g., "127.0.0.1")
     *
     * . IPv4 network string (e.g., "9.67")
     *
     *   IMPORTANT: This network form is only allowed if network_allowed is on.
     */
    int rc;

#if APR_HAVE_IPV6
    rc = apr_inet_pton(AF_INET6, ipstr, ipsub->sub);
    if (rc == 1) {
        if (IN6_IS_ADDR_V4MAPPED((struct in6_addr *)ipsub->sub)) {
            /* apr_ipsubnet_test() assumes that we don't create IPv4-mapped IPv6
             * addresses; this of course forces the user to specify IPv4 addresses
             * in a.b.c.d style instead of ::ffff:a.b.c.d style.
             */
            return APR_EBADIP;
        }
        ipsub->family = AF_INET6;
    }
    else
#endif
    {
        rc = apr_inet_pton(AF_INET, ipstr, ipsub->sub);
        if (rc == 1) {
            ipsub->family = AF_INET;
        }
    }
    if (rc != 1) {
        if (network_allowed) {
            return parse_network(ipsub, ipstr);
        }
        else {
            return APR_EBADIP;
        }
    }
    return APR_SUCCESS;
}