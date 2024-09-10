void
register_service (int port)
{
    int dnsfd;
    GSource *source;

    if (DNSServiceRegister (&g_sdref, 0, 0, NULL, "_xmms2._tcp", NULL, NULL,
                            g_htons (port), 0, NULL, dns_callback, NULL)
            != kDNSServiceErr_NoError) {
        printf ("failed to register!\n");
        exit (1);
    }

    dnsfd = DNSServiceRefSockFD (g_sdref);
    if (dnsfd == -1) {
        printf ("no fd!?\n");
        exit (1);
    }

    pollfd = g_new0 (GPollFD, 1);
    pollfd->fd = dnsfd;
    pollfd->events = G_IO_IN | G_IO_HUP | G_IO_ERR;

    source = g_source_new (&dns_ipc_func, sizeof (GSource));

    g_source_add_poll (source, pollfd);
    g_source_attach (source, NULL);
}