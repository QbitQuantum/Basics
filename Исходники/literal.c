static int nn_inet_pton(int family, const char *src, void *dst)
{
    int rc;
    struct sockaddr_storage addr;
    int addr_len = sizeof(addr);

    if (nn_slow (family != AF_INET && family != AF_INET6)) {
        errno = EAFNOSUPPORT;
        return -1;
    }

    addr.ss_family = family;
    rc = WSAStringToAddressA ((char*) src, family, NULL,
        (struct sockaddr*) &addr, &addr_len);
    if (rc != 0)
        return 0;

    if (family == AF_INET) {
        memcpy(dst, &((struct sockaddr_in *) &addr)->sin_addr,
            sizeof(struct in_addr));
    } else if (family == AF_INET6) {
        memcpy(dst, &((struct sockaddr_in6 *)&addr)->sin6_addr,
            sizeof(struct in6_addr));
    }

    return 1;
}