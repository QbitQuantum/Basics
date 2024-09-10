static int make_fdpair (xs::fd_t *r_, xs::fd_t *w_)
{
#if defined XS_HAVE_EVENTFD

    // Create eventfd object.
#if defined EFD_CLOEXEC
    xs::fd_t fd = eventfd (0, EFD_CLOEXEC);
    if (fd == -1)
        return -1;
#else
    xs::fd_t fd = eventfd (0, 0);
    if (fd == -1)
        return -1;
#if defined FD_CLOEXEC
    int rc = fcntl (fd, F_SETFD, FD_CLOEXEC);
    errno_assert (rc != -1);
#endif
#endif
    *w_ = fd;
    *r_ = fd;
    return 0;

#elif defined XS_HAVE_WINDOWS

    //  On Windows we are using TCP sockets for in-process communication.
    //  That is a security hole -- other processes on the same box may connect
    //  to the bound TCP port and hook into internal signal processing of
    //  the library. To solve this problem we should use a proper in-process
    //  signaling mechanism such as private semaphore. However, on Windows,
    //  these cannot be polled on using select(). Other functions that allow
    //  polling on these objects (e.g. WaitForMulitpleObjects) don't allow
    //  to poll on sockets. Thus, the only way to fix the problem is to
    //  implement IOCP polling mechanism that allows to poll on both sockets
    //  and in-process synchronisation objects.

    //  Make the following critical section accessible to everyone.
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof (sa);
    sa.bInheritHandle = FALSE;
    SECURITY_DESCRIPTOR sd;
    BOOL ok = InitializeSecurityDescriptor (&sd, SECURITY_DESCRIPTOR_REVISION);
    win_assert (ok);
    ok = SetSecurityDescriptorDacl(&sd, TRUE, (PACL) NULL, FALSE);
    win_assert (ok);
    sa.lpSecurityDescriptor = &sd;

    //  This function has to be in a system-wide critical section so that
    //  two instances of the library don't accidentally create signaler
    //  crossing the process boundary.
    //  We'll use named event object to implement the critical section.
    HANDLE sync = CreateEvent (&sa, FALSE, TRUE, "xs-signaler-port-sync");
    win_assert (sync != NULL);

    //  Enter the critical section.
    DWORD dwrc = WaitForSingleObject (sync, INFINITE);
    xs_assert (dwrc == WAIT_OBJECT_0);

    //  Windows has no 'socketpair' function. CreatePipe is no good as pipe
    //  handles cannot be polled on. Here we create the socketpair by hand.
    *w_ = INVALID_SOCKET;
    *r_ = INVALID_SOCKET;

    //  Create listening socket.
    SOCKET listener;
    listener = xs::open_socket (AF_INET, SOCK_STREAM, 0);
    if (listener == xs::retired_fd)
        return -1;

    //  Set SO_REUSEADDR and TCP_NODELAY on listening socket.
    BOOL so_reuseaddr = 1;
    int rc = setsockopt (listener, SOL_SOCKET, SO_REUSEADDR,
        (char *)&so_reuseaddr, sizeof (so_reuseaddr));
    wsa_assert (rc != SOCKET_ERROR);
    BOOL tcp_nodelay = 1;
    rc = setsockopt (listener, IPPROTO_TCP, TCP_NODELAY,
        (char *)&tcp_nodelay, sizeof (tcp_nodelay));
    wsa_assert (rc != SOCKET_ERROR);

    //  Bind listening socket to the local port.
    struct sockaddr_in addr;
    memset (&addr, 0, sizeof (addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
    addr.sin_port = htons (xs::signaler_port);
    rc = bind (listener, (const struct sockaddr*) &addr, sizeof (addr));
    wsa_assert (rc != SOCKET_ERROR);

    //  Listen for incomming connections.
    rc = listen (listener, 1);
    wsa_assert (rc != SOCKET_ERROR);

    //  Create the writer socket.
    *w_ = WSASocket (AF_INET, SOCK_STREAM, 0, NULL, 0,  0);
    if (*w_ == xs::retired_fd) {
        rc = closesocket (listener);
        wsa_assert (rc != SOCKET_ERROR);
        return -1;
    }

    //  Set TCP_NODELAY on writer socket.
    rc = setsockopt (*w_, IPPROTO_TCP, TCP_NODELAY,
        (char *)&tcp_nodelay, sizeof (tcp_nodelay));
    wsa_assert (rc != SOCKET_ERROR);

    //  Connect writer to the listener.
    rc = connect (*w_, (sockaddr *) &addr, sizeof (addr));
    wsa_assert (rc != SOCKET_ERROR);

    //  Accept connection from writer.
    *r_ = accept (listener, NULL, NULL);
    if (*r_ == xs::retired_fd) {
        rc = closesocket (listener);
        wsa_assert (rc != SOCKET_ERROR);
        rc = closesocket (*w_);
        wsa_assert (rc != SOCKET_ERROR);
        return -1;
    }

    //  We don't need the listening socket anymore. Close it.
    rc = closesocket (listener);
    wsa_assert (rc != SOCKET_ERROR);

    //  Exit the critical section.
    BOOL brc = SetEvent (sync);
    win_assert (brc != 0);

    return 0;

#elif defined XS_HAVE_OPENVMS

    //  Whilst OpenVMS supports socketpair - it maps to AF_INET only.  Further,
    //  it does not set the socket options TCP_NODELAY and TCP_NODELACK which
    //  can lead to performance problems.
    //
    //  The bug will be fixed in V5.6 ECO4 and beyond.  In the meantime, we'll
    //  create the socket pair manually.
    sockaddr_in lcladdr;
    memset (&lcladdr, 0, sizeof (lcladdr));
    lcladdr.sin_family = AF_INET;
    lcladdr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
    lcladdr.sin_port = 0;

    int listener = open_socket (AF_INET, SOCK_STREAM, 0);
    errno_assert (listener != -1);

    int on = 1;
    int rc = setsockopt (listener, IPPROTO_TCP, TCP_NODELAY, &on, sizeof (on));
    errno_assert (rc != -1);

    rc = setsockopt (listener, IPPROTO_TCP, TCP_NODELACK, &on, sizeof (on));
    errno_assert (rc != -1);

    rc = bind(listener, (struct sockaddr*) &lcladdr, sizeof (lcladdr));
    errno_assert (rc != -1);

    socklen_t lcladdr_len = sizeof (lcladdr);

    rc = getsockname (listener, (struct sockaddr*) &lcladdr, &lcladdr_len);
    errno_assert (rc != -1);

    rc = listen (listener, 1);
    errno_assert (rc != -1);

    *w_ = open_socket (AF_INET, SOCK_STREAM, 0);
    errno_assert (*w_ != -1);

    rc = setsockopt (*w_, IPPROTO_TCP, TCP_NODELAY, &on, sizeof (on));
    errno_assert (rc != -1);

    rc = setsockopt (*w_, IPPROTO_TCP, TCP_NODELACK, &on, sizeof (on));
    errno_assert (rc != -1);

    rc = connect (*w_, (struct sockaddr*) &lcladdr, sizeof (lcladdr));
    errno_assert (rc != -1);

    *r_ = accept (listener, NULL, NULL);
    errno_assert (*r_ != -1);

    close (listener);

    return 0;

#else // All other implementations support socketpair()

    int sv [2];
#if defined XS_HAVE_SOCK_CLOEXEC
    int rc = socketpair (AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, sv);
    if (rc == -1)
        return -1;
#else
    int rc = socketpair (AF_UNIX, SOCK_STREAM, 0, sv);
    if (rc == -1)
        return -1;
    errno_assert (rc == 0);
#if defined FD_CLOEXEC
    rc = fcntl (sv [0], F_SETFD, FD_CLOEXEC);
    errno_assert (rc != -1);
    rc = fcntl (sv [1], F_SETFD, FD_CLOEXEC);
    errno_assert (rc != -1);
#endif
#endif
    *w_ = sv [0];
    *r_ = sv [1];
    return 0;

#endif
}