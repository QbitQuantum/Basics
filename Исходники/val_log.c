const char    *
val_get_ns_string(struct sockaddr *serv, char *dst, size_t size)
{
    struct sockaddr_in *sin;
#ifdef VAL_IPV6
    struct sockaddr_in6 *sin6;
#endif
    struct sockaddr_storage *server;
    const char *addr = NULL;

    if ((serv == NULL) || (dst == NULL))
        return NULL;

    server = (struct sockaddr_storage *) serv;

    switch (server->ss_family) {
    case AF_INET:
        sin = (struct sockaddr_in *) server;
        INET_NTOP(AF_INET, ((struct sockaddr *)sin), 
            sizeof(struct sockaddr_in), dst, size, addr);
        return addr;
#ifdef VAL_IPV6
    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) server;
        INET_NTOP(AF_INET6, ((struct sockaddr *)sin6), 
            sizeof(struct sockaddr_in), dst, size, addr);
        return addr;
#endif
    }
    return NULL;
}