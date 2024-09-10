bool sockaddr_isAddrSiteLocal(const struct sockaddr * sa)
{
    if (sa->sa_family == AF_INET) {
        return false;
    }else if (sa->sa_family == AF_INET6) {
        return IN6_IS_ADDR_SITELOCAL(&((struct sockaddr_in6*)sa)->sin6_addr);
    }
    return false;
}