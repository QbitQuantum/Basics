/* returns socket fd, and sets ipaddr to IP (4 or 6) of host when connected */
int fsaf_connect_to_admind(char *host, int port, struct addrinfo *hints,
                           char *ipaddr)
{
    char cport[6]; /* 16 bit int + '\0' */
    int rv;
    int sock_fd;
    struct addrinfo *server_ai, *p;

    /* convert integer port to string */
    sprintf(cport, "%d", port);
    rv = getaddrinfo(host, cport, hints, &server_ai);
    if (rv != 0) {
        fsa_error(LOG_DEBUG, "getaddrinfo failed: %s", gai_strerror(rv));
        errno = rv; /* use gai_strerror to get value */
        return -1;
    }

    /* connect to first available socket */
    for (p = server_ai; p != NULL; p = p->ai_next) {
        sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sock_fd == -1) {
            fsa_error(LOG_DEBUG, "socket failed: %s", strerror(errno));
            continue;
        }

        rv = connect(sock_fd, p->ai_addr, p->ai_addrlen);
        if (rv == -1) {
            fsa_error(LOG_DEBUG, "connect failed: %s", strerror(errno));
            close(sock_fd);
            continue;
        }

        /* no errors, so break */
        break;
    }


    /* check that we actually connected */
    if (p == NULL) {
        fsa_error(LOG_DEBUG, "failed to connect to %s:%d", host, port);
        freeaddrinfo(server_ai);
        errno = ADM_ERR_CONN_FAILED;
        return -1;
    }

    if (server_ai->ai_family == AF_INET6) {
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)server_ai->ai_addr;
        inet_ntop(AF_INET6, &(ipv6->sin6_addr),
                  ipaddr, INET6_ADDRSTRLEN);
    }
    else if (server_ai->ai_family == AF_INET) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)server_ai->ai_addr;
        inet_ntop(AF_INET, &(ipv4->sin_addr),
                  ipaddr, INET6_ADDRSTRLEN);
    }
    freeaddrinfo(server_ai);

    fsa_error(LOG_DEBUG, "connected to %s:%d (%s) on sock_fd %d",
              host, port, ipaddr, sock_fd);
    return sock_fd;
}