SOCKET connectTcpSocket(struct sockaddr_storage* dstaddr, SOCKADDR_LEN addrlen, unsigned short port, int timeoutSec) {
    SOCKET s;
    struct sockaddr_in6 addr;
    int err;
#if defined(LC_DARWIN) || defined(FIONBIO)
    int val;
#endif

    s = socket(dstaddr->ss_family, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        Limelog("socket() failed: %d\n", (int)LastSocketError());
        return INVALID_SOCKET;
    }
    
#ifdef LC_DARWIN
    // Disable SIGPIPE on iOS
    val = 1;
    setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, (char*)&val, sizeof(val));
#endif
    
#ifdef FIONBIO
    // Enable non-blocking I/O for connect timeout support
    val = 1;
    ioctlsocket(s, FIONBIO, &val);
#endif

    // Start connection
    memcpy(&addr, dstaddr, sizeof(addr));
    addr.sin6_port = htons(port);
    err = connect(s, (struct sockaddr*) &addr, addrlen);
    if (err < 0) {
        err = (int)LastSocketError();
    }
    
#ifdef FIONBIO
    {
        struct fd_set writefds, exceptfds;
        struct timeval tv;
        
        FD_ZERO(&writefds);
        FD_ZERO(&exceptfds);
        FD_SET(s, &writefds);
        FD_SET(s, &exceptfds);
        
        tv.tv_sec = timeoutSec;
        tv.tv_usec = 0;
        
        // Wait for the connection to complete or the timeout to elapse
        err = select(s + 1, NULL, &writefds, &exceptfds, &tv);
        if (err < 0) {
            // select() failed
            err = LastSocketError();
            Limelog("select() failed: %d\n", err);
            closeSocket(s);
            SetLastSocketError(err);
            return INVALID_SOCKET;
        }
        else if (err == 0) {
            // select() timed out
            Limelog("select() timed out after %d seconds\n", timeoutSec);
            closeSocket(s);
#if defined(LC_WINDOWS)
            SetLastSocketError(WSAEWOULDBLOCK);
#else
            SetLastSocketError(EWOULDBLOCK);
#endif
            return INVALID_SOCKET;
        }
        else if (FD_ISSET(s, &writefds) || FD_ISSET(s, &exceptfds)) {
            // The socket was signalled
            SOCKADDR_LEN len = sizeof(err);
            getsockopt(s, SOL_SOCKET, SO_ERROR, (char*)&err, &len);
            if (err != 0 || FD_ISSET(s, &exceptfds)) {
                // Get the error code
                err = (err != 0) ? err : LastSocketFail();
            }
        }
        
        // Disable non-blocking I/O now that the connection is established
        val = 0;
        ioctlsocket(s, FIONBIO, &val);
    }
#endif
    
    if (err != 0) {
        Limelog("connect() failed: %d\n", err);
        closeSocket(s);
        SetLastSocketError(err);
        return INVALID_SOCKET;
    }

    return s;
}