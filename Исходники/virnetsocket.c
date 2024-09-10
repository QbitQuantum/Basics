int virNetSocketNewListenTCP(const char *nodename,
                             const char *service,
                             virNetSocketPtr **retsocks,
                             size_t *nretsocks)
{
    virNetSocketPtr *socks = NULL;
    size_t nsocks = 0;
    struct addrinfo *ai = NULL;
    struct addrinfo hints;
    int fd = -1;
    int i;
    int addrInUse = false;

    *retsocks = NULL;
    *nretsocks = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_socktype = SOCK_STREAM;

    int e = getaddrinfo(nodename, service, &hints, &ai);
    if (e != 0) {
        virNetError(VIR_ERR_SYSTEM_ERROR,
                    _("Unable to resolve address '%s' service '%s': %s"),
                    nodename, service, gai_strerror(e));
        return -1;
    }

    struct addrinfo *runp = ai;
    while (runp) {
        virSocketAddr addr;

        memset(&addr, 0, sizeof(addr));

        if ((fd = socket(runp->ai_family, runp->ai_socktype,
                         runp->ai_protocol)) < 0) {
            virReportSystemError(errno, "%s", _("Unable to create socket"));
            goto error;
        }

        int opt = 1;
        if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            virReportSystemError(errno, "%s", _("Unable to enable port reuse"));
            goto error;
        }

#ifdef IPV6_V6ONLY
        if (runp->ai_family == PF_INET6) {
            int on = 1;
            /*
             * Normally on Linux an INET6 socket will bind to the INET4
             * address too. If getaddrinfo returns results with INET4
             * first though, this will result in INET6 binding failing.
             * We can trivially cope with multiple server sockets, so
             * we force it to only listen on IPv6
             */
            if (setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY,
                           (void*)&on, sizeof(on)) < 0) {
                virReportSystemError(errno, "%s",
                                     _("Unable to force bind to IPv6 only"));
                goto error;
            }
        }
#endif

        if (bind(fd, runp->ai_addr, runp->ai_addrlen) < 0) {
            if (errno != EADDRINUSE) {
                virReportSystemError(errno, "%s", _("Unable to bind to port"));
                goto error;
            }
            addrInUse = true;
            VIR_FORCE_CLOSE(fd);
            runp = runp->ai_next;
            continue;
        }

        addr.len = sizeof(addr.data);
        if (getsockname(fd, &addr.data.sa, &addr.len) < 0) {
            virReportSystemError(errno, "%s", _("Unable to get local socket name"));
            goto error;
        }

        VIR_DEBUG("%p f=%d f=%d", &addr, runp->ai_family, addr.data.sa.sa_family);

        if (VIR_EXPAND_N(socks, nsocks, 1) < 0) {
            virReportOOMError();
            goto error;
        }

        if (!(socks[nsocks-1] = virNetSocketNew(&addr, NULL, false, fd, -1, 0)))
            goto error;
        runp = runp->ai_next;
        fd = -1;
    }

    if (nsocks == 0 &&
        addrInUse) {
        virReportSystemError(EADDRINUSE, "%s", _("Unable to bind to port"));
        goto error;
    }

    freeaddrinfo(ai);

    *retsocks = socks;
    *nretsocks = nsocks;
    return 0;

error:
    for (i = 0 ; i < nsocks ; i++)
        virNetSocketFree(socks[i]);
    VIR_FREE(socks);
    freeaddrinfo(ai);
    VIR_FORCE_CLOSE(fd);
    return -1;
}