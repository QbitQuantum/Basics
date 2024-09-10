int zmq::make_fdpair (fd_t *r_, fd_t *w_)
{
#if defined ZMQ_HAVE_EVENTFD
    int flags = 0;
#if defined ZMQ_HAVE_EVENTFD_CLOEXEC
    //  Setting this option result in sane behaviour when exec() functions
    //  are used. Old sockets are closed and don't block TCP ports, avoid
    //  leaks, etc.
    flags |= EFD_CLOEXEC;
#endif
    fd_t fd = eventfd (0, flags);
    if (fd == -1) {
        errno_assert (errno == ENFILE || errno == EMFILE);
        *w_ = *r_ = -1;
        return -1;
    } else {
        *w_ = *r_ = fd;
        return 0;
    }

#elif defined ZMQ_HAVE_WINDOWS
#if !defined _WIN32_WCE && !defined ZMQ_HAVE_WINDOWS_UWP
    //  Windows CE does not manage security attributes
    SECURITY_DESCRIPTOR sd;
    SECURITY_ATTRIBUTES sa;
    memset (&sd, 0, sizeof sd);
    memset (&sa, 0, sizeof sa);

    InitializeSecurityDescriptor (&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl (&sd, TRUE, 0, FALSE);

    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = &sd;
#endif

    //  This function has to be in a system-wide critical section so that
    //  two instances of the library don't accidentally create signaler
    //  crossing the process boundary.
    //  We'll use named event object to implement the critical section.
    //  Note that if the event object already exists, the CreateEvent requests
    //  EVENT_ALL_ACCESS access right. If this fails, we try to open
    //  the event object asking for SYNCHRONIZE access only.
    HANDLE sync = NULL;

    //  Create critical section only if using fixed signaler port
    //  Use problematic Event implementation for compatibility if using old port 5905.
    //  Otherwise use Mutex implementation.
    int event_signaler_port = 5905;

    if (signaler_port == event_signaler_port) {
#if !defined _WIN32_WCE && !defined ZMQ_HAVE_WINDOWS_UWP
        sync =
          CreateEventW (&sa, FALSE, TRUE, L"Global\\zmq-signaler-port-sync");
#else
        sync =
          CreateEventW (NULL, FALSE, TRUE, L"Global\\zmq-signaler-port-sync");
#endif
        if (sync == NULL && GetLastError () == ERROR_ACCESS_DENIED)
            sync = OpenEventW (SYNCHRONIZE | EVENT_MODIFY_STATE, FALSE,
                               L"Global\\zmq-signaler-port-sync");

        win_assert (sync != NULL);
    } else if (signaler_port != 0) {
        wchar_t mutex_name[MAX_PATH];
#ifdef __MINGW32__
        _snwprintf (mutex_name, MAX_PATH, L"Global\\zmq-signaler-port-%d",
                    signaler_port);
#else
        swprintf (mutex_name, MAX_PATH, L"Global\\zmq-signaler-port-%d",
                  signaler_port);
#endif

#if !defined _WIN32_WCE && !defined ZMQ_HAVE_WINDOWS_UWP
        sync = CreateMutexW (&sa, FALSE, mutex_name);
#else
        sync = CreateMutexW (NULL, FALSE, mutex_name);
#endif
        if (sync == NULL && GetLastError () == ERROR_ACCESS_DENIED)
            sync = OpenMutexW (SYNCHRONIZE, FALSE, mutex_name);

        win_assert (sync != NULL);
    }

    //  Windows has no 'socketpair' function. CreatePipe is no good as pipe
    //  handles cannot be polled on. Here we create the socketpair by hand.
    *w_ = INVALID_SOCKET;
    *r_ = INVALID_SOCKET;

    //  Create listening socket.
    SOCKET listener;
    listener = open_socket (AF_INET, SOCK_STREAM, 0);
    wsa_assert (listener != INVALID_SOCKET);

    //  Set SO_REUSEADDR and TCP_NODELAY on listening socket.
    BOOL so_reuseaddr = 1;
    int rc = setsockopt (listener, SOL_SOCKET, SO_REUSEADDR,
                         reinterpret_cast<char *> (&so_reuseaddr),
                         sizeof so_reuseaddr);
    wsa_assert (rc != SOCKET_ERROR);

    tune_socket (listener);

    //  Init sockaddr to signaler port.
    struct sockaddr_in addr;
    memset (&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
    addr.sin_port = htons (signaler_port);

    //  Create the writer socket.
    *w_ = open_socket (AF_INET, SOCK_STREAM, 0);
    wsa_assert (*w_ != INVALID_SOCKET);

    //  Set TCP_NODELAY on writer socket.
    tune_socket (*w_);

    if (sync != NULL) {
        //  Enter the critical section.
        DWORD dwrc = WaitForSingleObject (sync, INFINITE);
        zmq_assert (dwrc == WAIT_OBJECT_0 || dwrc == WAIT_ABANDONED);
    }

    //  Bind listening socket to signaler port.
    rc = bind (listener, reinterpret_cast<const struct sockaddr *> (&addr),
               sizeof addr);

    if (rc != SOCKET_ERROR && signaler_port == 0) {
        //  Retrieve ephemeral port number
        int addrlen = sizeof addr;
        rc = getsockname (listener, reinterpret_cast<struct sockaddr *> (&addr),
                          &addrlen);
    }

    //  Listen for incoming connections.
    if (rc != SOCKET_ERROR)
        rc = listen (listener, 1);

    //  Connect writer to the listener.
    if (rc != SOCKET_ERROR)
        rc = connect (*w_, reinterpret_cast<struct sockaddr *> (&addr),
                      sizeof addr);

    //  Accept connection from writer.
    if (rc != SOCKET_ERROR)
        *r_ = accept (listener, NULL, NULL);

    //  Send/receive large chunk to work around TCP slow start
    //  This code is a workaround for #1608
    if (*r_ != INVALID_SOCKET) {
        size_t dummy_size =
          1024 * 1024; //  1M to overload default receive buffer
        unsigned char *dummy =
          static_cast<unsigned char *> (malloc (dummy_size));
        wsa_assert (dummy);

        int still_to_send = static_cast<int> (dummy_size);
        int still_to_recv = static_cast<int> (dummy_size);
        while (still_to_send || still_to_recv) {
            int nbytes;
            if (still_to_send > 0) {
                nbytes = ::send (
                  *w_,
                  reinterpret_cast<char *> (dummy + dummy_size - still_to_send),
                  still_to_send, 0);
                wsa_assert (nbytes != SOCKET_ERROR);
                still_to_send -= nbytes;
            }
            nbytes = ::recv (
              *r_,
              reinterpret_cast<char *> (dummy + dummy_size - still_to_recv),
              still_to_recv, 0);
            wsa_assert (nbytes != SOCKET_ERROR);
            still_to_recv -= nbytes;
        }
        free (dummy);
    }

    //  Save errno if error occurred in bind/listen/connect/accept.
    int saved_errno = 0;
    if (*r_ == INVALID_SOCKET)
        saved_errno = WSAGetLastError ();

    //  We don't need the listening socket anymore. Close it.
    rc = closesocket (listener);
    wsa_assert (rc != SOCKET_ERROR);

    if (sync != NULL) {
        //  Exit the critical section.
        BOOL brc;
        if (signaler_port == event_signaler_port)
            brc = SetEvent (sync);
        else
            brc = ReleaseMutex (sync);
        win_assert (brc != 0);

        //  Release the kernel object
        brc = CloseHandle (sync);
        win_assert (brc != 0);
    }

    if (*r_ != INVALID_SOCKET) {
        make_socket_noninheritable (*r_);
        return 0;
    }
    //  Cleanup writer if connection failed
    if (*w_ != INVALID_SOCKET) {
        rc = closesocket (*w_);
        wsa_assert (rc != SOCKET_ERROR);
        *w_ = INVALID_SOCKET;
    }
    //  Set errno from saved value
    errno = wsa_error_to_errno (saved_errno);
    return -1;


#elif defined ZMQ_HAVE_OPENVMS

    //  Whilst OpenVMS supports socketpair - it maps to AF_INET only.  Further,
    //  it does not set the socket options TCP_NODELAY and TCP_NODELACK which
    //  can lead to performance problems.
    //
    //  The bug will be fixed in V5.6 ECO4 and beyond.  In the meantime, we'll
    //  create the socket pair manually.
    struct sockaddr_in lcladdr;
    memset (&lcladdr, 0, sizeof lcladdr);
    lcladdr.sin_family = AF_INET;
    lcladdr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
    lcladdr.sin_port = 0;

    int listener = open_socket (AF_INET, SOCK_STREAM, 0);
    errno_assert (listener != -1);

    int on = 1;
    int rc = setsockopt (listener, IPPROTO_TCP, TCP_NODELAY, &on, sizeof on);
    errno_assert (rc != -1);

    rc = setsockopt (listener, IPPROTO_TCP, TCP_NODELACK, &on, sizeof on);
    errno_assert (rc != -1);

    rc = bind (listener, (struct sockaddr *) &lcladdr, sizeof lcladdr);
    errno_assert (rc != -1);

    socklen_t lcladdr_len = sizeof lcladdr;

    rc = getsockname (listener, (struct sockaddr *) &lcladdr, &lcladdr_len);
    errno_assert (rc != -1);

    rc = listen (listener, 1);
    errno_assert (rc != -1);

    *w_ = open_socket (AF_INET, SOCK_STREAM, 0);
    errno_assert (*w_ != -1);

    rc = setsockopt (*w_, IPPROTO_TCP, TCP_NODELAY, &on, sizeof on);
    errno_assert (rc != -1);

    rc = setsockopt (*w_, IPPROTO_TCP, TCP_NODELACK, &on, sizeof on);
    errno_assert (rc != -1);

    rc = connect (*w_, (struct sockaddr *) &lcladdr, sizeof lcladdr);
    errno_assert (rc != -1);

    *r_ = accept (listener, NULL, NULL);
    errno_assert (*r_ != -1);

    close (listener);

    return 0;
#elif defined ZMQ_HAVE_VXWORKS
    struct sockaddr_in lcladdr;
    memset (&lcladdr, 0, sizeof lcladdr);
    lcladdr.sin_family = AF_INET;
    lcladdr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
    lcladdr.sin_port = 0;

    int listener = open_socket (AF_INET, SOCK_STREAM, 0);
    errno_assert (listener != -1);

    int on = 1;
    int rc =
      setsockopt (listener, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof on);
    errno_assert (rc != -1);

    rc = bind (listener, (struct sockaddr *) &lcladdr, sizeof lcladdr);
    errno_assert (rc != -1);

    socklen_t lcladdr_len = sizeof lcladdr;

    rc = getsockname (listener, (struct sockaddr *) &lcladdr,
                      (int *) &lcladdr_len);
    errno_assert (rc != -1);

    rc = listen (listener, 1);
    errno_assert (rc != -1);

    *w_ = open_socket (AF_INET, SOCK_STREAM, 0);
    errno_assert (*w_ != -1);

    rc = setsockopt (*w_, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof on);
    errno_assert (rc != -1);

    rc = connect (*w_, (struct sockaddr *) &lcladdr, sizeof lcladdr);
    errno_assert (rc != -1);

    *r_ = accept (listener, NULL, NULL);
    errno_assert (*r_ != -1);

    close (listener);

    return 0;
#else
    // All other implementations support socketpair()
    int sv[2];
    int type = SOCK_STREAM;
    //  Setting this option result in sane behaviour when exec() functions
    //  are used. Old sockets are closed and don't block TCP ports, avoid
    //  leaks, etc.
#if defined ZMQ_HAVE_SOCK_CLOEXEC
    type |= SOCK_CLOEXEC;
#endif
    int rc = socketpair (AF_UNIX, type, 0, sv);
    if (rc == -1) {
        errno_assert (errno == ENFILE || errno == EMFILE);
        *w_ = *r_ = -1;
        return -1;
    } else {
        make_socket_noninheritable (sv[0]);
        make_socket_noninheritable (sv[1]);

        *w_ = sv[0];
        *r_ = sv[1];
        return 0;
    }
#endif
}