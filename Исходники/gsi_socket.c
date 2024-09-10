char *
GSI_SOCKET_get_peer_hostname(GSI_SOCKET *self)
{
    struct sockaddr_storage addr;
    socklen_t			addr_len = sizeof(addr);
    char host			[NI_MAXHOST];
    int					loopback=0;

    if (getpeername(self->sock, (struct sockaddr *) &addr,
		    &addr_len) < 0) {
        self->error_number = errno;
        GSI_SOCKET_set_error_string(self, "Could not get peer address");
        return NULL;
    }

    if (getnameinfo((struct sockaddr *) &addr, addr_len,
                    host, sizeof(host),
                    NULL, 0, NI_NAMEREQD)) {
        self->error_number = errno;
        GSI_SOCKET_set_error_string(self, "Could not get peer hostname");
        return NULL;
    }

    /* check for localhost / loopback */
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in sadder;

        memcpy(&sadder, &addr, sizeof(sadder));
        if (ntohl(sadder.sin_addr.s_addr) == INADDR_LOOPBACK) {
            loopback = 1;
        }
    }
#ifdef AF_INET6
    else if (addr.ss_family == AF_INET6) {
        struct sockaddr_in6 saddr6;

        memcpy(&saddr6, &addr, sizeof(saddr6));
        if (IN6_IS_ADDR_LOOPBACK(&saddr6.sin6_addr)) {
            loopback = 1;
        }
    }
#endif

    if (loopback) {
        char buf[MAXHOSTNAMELEN];
        if (gethostname(buf, sizeof(buf)) < 0) {
            self->error_number = errno;
            GSI_SOCKET_set_error_string(self, "gethostname() failed");
            return NULL;
        }
        return strdup(buf);
    }

    return strdup(host);
}