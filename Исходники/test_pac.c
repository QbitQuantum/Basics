int is_notified(notifier_t n, struct timeval *timeout)
{
    fd_set fds;

    FD_ZERO(&fds);
    FD_SET(n, &fds);

#if defined(_WIN32) || defined(__CYGWIN__)
    char buf[64];
    if (select(100000, &fds, NULL, NULL, timeout) > 0) {
        recv(n, buf, sizeof(buf), 0);
#else
    unsigned char buf[64];
    if (select(n + 1, &fds, NULL, NULL, timeout) > 0) {
        int rc = read(n, buf, sizeof(buf));
        if (rc < 0) {
            fprintf(stderr, "Warning, notifier socket error\n");
            perror("read()");
        } else if (rc == 0) {
            fprintf(stderr, "Warning, notifier socket EOF\n");
        }
#endif
        return 1;
    } else {
        return 0;
    }
}

/*
 * Based on evutil_socketpair() from libevent.
 */
int create_notifier(notifier_t not[2])
{
#if defined(_WIN32) || defined(__CYGWIN__)
    SOCKET listener = -1, connector = -1, acceptor = -1;
    struct sockaddr_in listen_addr, connect_addr;
    int size;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
        return -1;
    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    listen_addr.sin_port = 0;	/* kernel chooses port.	 */
    if (bind(listener, (struct sockaddr *) &listen_addr, sizeof (listen_addr))
        == -1)
        goto out;
    if (listen(listener, 1) == -1)
        goto out;

    connector = socket(AF_INET, SOCK_STREAM, 0);
    if (connector < 0)
        goto out;

    /* We want to find out the port number to connect to.  */
    size = sizeof(connect_addr);
    if (getsockname(listener, (struct sockaddr *) &connect_addr, &size) == -1)
        goto out;
    if (size != sizeof(connect_addr))
        goto out;
    if (connect(connector, (struct sockaddr *) &connect_addr,
                sizeof(connect_addr)) == -1)
        goto out;

    size = sizeof(listen_addr);
    acceptor = accept(listener, (struct sockaddr *) &listen_addr, &size);
    if (acceptor < 0)
        goto out;
    if (size != sizeof(listen_addr))
        goto out;
    /* Now check we are talking to ourself by matching port and host on the
       two sockets.	 */
    if (getsockname(connector, (struct sockaddr *) &connect_addr, &size) == -1)
        goto out;
    if (size != sizeof(connect_addr)
        || listen_addr.sin_family != connect_addr.sin_family
        || listen_addr.sin_addr.s_addr != connect_addr.sin_addr.s_addr
        || listen_addr.sin_port != connect_addr.sin_port)
        goto out;
    closesocket(listener);
    not[0] = (int)connector;
    not[1] = (int)acceptor;

    return 0;

out:
    if (listener != -1)
        closesocket(listener);
    if (connector != -1)
        closesocket(connector);
    if (acceptor != -1)
        closesocket(acceptor);
    return -1;
#else
    return pipe(not);
#endif
}