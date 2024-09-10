int zmq::tcp_listener_t::set_address (const char *addr_)
{
    //  Convert the textual address into address structure.
    int rc = address.resolve (addr_, true, options.ipv4only ? true : false);
    if (rc != 0)
        return -1;

    //  Create a listening socket.
    s = open_socket (address.family (), SOCK_STREAM, IPPROTO_TCP);
#ifdef ZMQ_HAVE_WINDOWS
    if (s == INVALID_SOCKET)
        errno = wsa_error_to_errno (WSAGetLastError ());
#endif

    //  IPv6 address family not supported, try automatic downgrade to IPv4.
    if (address.family () == AF_INET6 && errno == EAFNOSUPPORT &&
          !options.ipv4only) {
        rc = address.resolve (addr_, true, true);
        if (rc != 0)
            return rc;
        s = ::socket (address.family (), SOCK_STREAM, IPPROTO_TCP);
    }

#ifdef ZMQ_HAVE_WINDOWS
    if (s == INVALID_SOCKET) {
        errno = wsa_error_to_errno (WSAGetLastError ());
        return -1;
    }
    //  On Windows, preventing sockets to be inherited by child processes.
    BOOL brc = SetHandleInformation ((HANDLE) s, HANDLE_FLAG_INHERIT, 0);
    win_assert (brc);
#else
    if (s == -1)
        return -1;
#endif

    //  On some systems, IPv4 mapping in IPv6 sockets is disabled by default.
    //  Switch it on in such cases.
    if (address.family () == AF_INET6)
        enable_ipv4_mapping (s);

    //  Allow reusing of the address.
    int flag = 1;
#ifdef ZMQ_HAVE_WINDOWS
    rc = setsockopt (s, SOL_SOCKET, SO_EXCLUSIVEADDRUSE,
        (const char*) &flag, sizeof (int));
    wsa_assert (rc != SOCKET_ERROR);
#else
    rc = setsockopt (s, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof (int));
    errno_assert (rc == 0);
#endif

    address.to_string (endpoint);

    //  Bind the socket to the network interface and port.
    rc = bind (s, address.addr (), address.addrlen ());
#ifdef ZMQ_HAVE_WINDOWS
    if (rc == SOCKET_ERROR) {
        errno = wsa_error_to_errno (WSAGetLastError ());
        goto error;
    }
#else
    if (rc != 0)
        goto error;
#endif

    //  Listen for incomming connections.
    rc = listen (s, options.backlog);
#ifdef ZMQ_HAVE_WINDOWS
    if (rc == SOCKET_ERROR) {
        errno = wsa_error_to_errno (WSAGetLastError ());
        goto error;
    }
#else
    if (rc != 0)
        goto error;
#endif

    socket->monitor_event (ZMQ_EVENT_LISTENING, addr_, s);
    return 0;

error:
    int err = errno;
    close ();
    errno = err;
    return -1;
}