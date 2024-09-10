static void
print_addrinfo(int type, void *ainfo)
{
    struct sockaddr_in *s_inaddr = NULL;
    struct sockaddr_in6 *s_in6addr = NULL;
    struct addrinfo *a = (struct addrinfo *) ainfo;
    char            buf[INET6_ADDRSTRLEN];
    size_t          buflen = INET6_ADDRSTRLEN;

    while (a != NULL) {
        printf("{\n");
        printf("\tFlags:     %d [", a->ai_flags);
        if (a->ai_flags & AI_PASSIVE)
            printf("AI_PASSIVE ");
        if (a->ai_flags & AI_CANONNAME)
            printf("AI_CANONNAME ");
        if (a->ai_flags & AI_NUMERICHOST)
            printf("AI_NUMERICHOST ");
#ifdef AI_V4MAPPED
        if (a->ai_flags & AI_V4MAPPED)
            printf("AI_V4MAPPED ");
#endif
#ifdef AI_ALL
        if (a->ai_flags & AI_ALL)
            printf("AI_ALL ");
#endif
#ifdef AI_ADDRCONFIG
        if (a->ai_flags & AI_ADDRCONFIG)
            printf("AI_ADDRCONFIG ");
#endif
        //              if (a->ai_flags & AI_NUMERICSERV) printf("AI_NUMERICSERV ");
        printf("]\n");
        printf("\tFamily:    %d [%s]\n", a->ai_family,
               (a->ai_family == AF_UNSPEC) ? "AF_UNSPEC" :
               (a->ai_family == AF_INET) ? "AF_INET" :
               (a->ai_family == AF_INET6) ? "AF_INET6" : "Unknown");
        printf("\tSockType:  %d [%s]\n", a->ai_socktype,
               (a->ai_socktype == SOCK_STREAM) ? "SOCK_STREAM" :
               (a->ai_socktype == SOCK_DGRAM) ? "SOCK_DGRAM" :
               (a->ai_socktype == SOCK_RAW) ? "SOCK_RAW" : "Unknown");
        printf("\tProtocol:  %d [%s]\n", a->ai_protocol,
               (a->ai_protocol == IPPROTO_IP) ? "IPPROTO_IP" :
               (a->ai_protocol == IPPROTO_TCP) ? "IPPROTO_TCP" :
               (a->ai_protocol == IPPROTO_UDP) ? "IPPROTO_UDP" :
               "Unknown");
        printf("\tAddrLen:   %d\n", a->ai_addrlen);

        if (a->ai_addr != NULL) {
            const char *addr = NULL;
            printf("\tAddrPtr:   %p\n", a->ai_addr);
            if (a->ai_family == AF_INET) {
                s_inaddr = (struct sockaddr_in *) (a->ai_addr);
                INET_NTOP(AF_INET, ((struct sockaddr *)s_inaddr), sizeof(s_inaddr),
                          buf, buflen, addr);
                printf("\tAddr:      %s\n", addr);
            } else if (a->ai_family == AF_INET6) {
                s_in6addr = (struct sockaddr_in6 *) (a->ai_addr);
                INET_NTOP(AF_INET6, ((struct sockaddr *)s_in6addr), sizeof(s_in6addr),
                          buf, buflen, addr);
                printf("\tAddr:      %s\n", addr);
            } else
                printf
                    ("\tAddr:      Cannot parse address. Unknown protocol family\n");
        } else
            printf("\tAddr:      (null)\n");

        if (a->ai_canonname)
            printf("\tCanonName: %s\n", a->ai_canonname);
        else
            printf("\tCanonName: (null)\n");

        printf("}\n");

        a = (struct addrinfo *) (a->ai_next);
    }
}