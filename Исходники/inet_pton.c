/**
 * int inet_pton(int af, const char *src, void *dst);
 *
 * Compatible with inet_pton just replace inet_pton with xp_inet_pton
 * and you are good to go. Uses WSAStringToAddressA instead of
 * inet_pton, compatible with Windows 2000 +
 */
static int xp_inet_pton(int family, const char *src, void *dst)
{
    int rc;
    struct sockaddr_storage addr;
    int addr_len = sizeof(addr);

    addr.ss_family = family;

    rc = WSAStringToAddressA((char *) src, family, NULL,
        (struct sockaddr*) &addr, &addr_len);
    if (rc != 0) {
        return -1;
    }

    if (family == AF_INET) {
        memcpy(dst, &((struct sockaddr_in *) &addr)->sin_addr,
            sizeof(struct in_addr));
    } else if (family == AF_INET6) {
        memcpy(dst, &((struct sockaddr_in6 *)&addr)->sin6_addr,
            sizeof(struct in6_addr));
    }

    return 1;
}