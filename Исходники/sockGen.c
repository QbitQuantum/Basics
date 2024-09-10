int socketOpenConnection(char *host, int port, socketAccept_t accept, int flags)
{
#if (!defined (NO_GETHOSTBYNAME) && !defined (VXWORKS))
    struct hostent		*hostent;					/* Host database entry */
#endif /* ! (NO_GETHOSTBYNAME || VXWORKS) */
    socket_t			*sp;
    struct sockaddr_in	sockaddr;
    int					sid, bcast, dgram, rc;

    if (port > SOCKET_PORT_MAX) {
        return -1;
    }
    /*
     *	Allocate a socket structure
     */
    if ((sid = socketAlloc(host, port, accept, flags)) < 0) {
        return -1;
    }
    sp = socketList[sid];
    a_assert(sp);

    /*
     *	Create the socket address structure
     */
    memset((char *) &sockaddr, '\0', sizeof(struct sockaddr_in));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons((short) (port & 0xFFFF));

    if (host == NULL) {
        sockaddr.sin_addr.s_addr = INADDR_ANY;
    } else {
        sockaddr.sin_addr.s_addr = inet_addr(host);
        if (sockaddr.sin_addr.s_addr == INADDR_NONE) {
            /*
             *			If the OS does not support gethostbyname functionality, the macro:
             *			NO_GETHOSTBYNAME should be defined to skip the use of gethostbyname.
             *			Unfortunatly there is no easy way to recover, the following code
             *			simply uses the basicGetHost IP for the sockaddr.
             */

#ifdef NO_GETHOSTBYNAME
            if (strcmp(host, basicGetHost()) == 0) {
                sockaddr.sin_addr.s_addr = inet_addr(basicGetAddress());
            }
            if (sockaddr.sin_addr.s_addr == INADDR_NONE) {
                socketFree(sid);
                return -1;
            }
#elif (defined (VXWORKS))
            sockaddr.sin_addr.s_addr = (unsigned long) hostGetByName(host);
            if (sockaddr.sin_addr.s_addr == NULL) {
                errno = ENXIO;
                socketFree(sid);
                return -1;
            }
#else
            hostent = gethostbyname(host);
            if (hostent != NULL) {
                memcpy((char *) &sockaddr.sin_addr,
                       (char *) hostent->h_addr_list[0],
                       (size_t) hostent->h_length);
            } else {
                char	*asciiAddress;
                char_t	*address;

                address = basicGetAddress();
                asciiAddress = ballocUniToAsc(address, gstrlen(address));
                sockaddr.sin_addr.s_addr = inet_addr(asciiAddress);
                bfree(B_L, asciiAddress);
                if (sockaddr.sin_addr.s_addr == INADDR_NONE) {
                    errno = ENXIO;
                    socketFree(sid);
                    return -1;
                }
            }
#endif /* (NO_GETHOSTBYNAME || VXWORKS) */
        }
    }

    bcast = sp->flags & SOCKET_BROADCAST;
    if (bcast) {
        sp->flags |= SOCKET_DATAGRAM;
    }
    dgram = sp->flags & SOCKET_DATAGRAM;

    /*
     *	Create the socket. Support for datagram sockets. Set the close on
     *	exec flag so children don't inherit the socket.
     */
    sp->sock = socket(AF_INET, dgram ? SOCK_DGRAM: SOCK_STREAM, 0);
    if (sp->sock < 0) {
        socketFree(sid);
        return -1;
    }
#ifndef __NO_FCNTL
    fcntl(sp->sock, F_SETFD, FD_CLOEXEC);
#endif
    socketHighestFd = max(socketHighestFd, sp->sock);

    /*
     *	If broadcast, we need to turn on broadcast capability.
     */
    if (bcast) {
        int broadcastFlag = 1;
        if (setsockopt(sp->sock, SOL_SOCKET, SO_BROADCAST,
                       (char *) &broadcastFlag, sizeof(broadcastFlag)) < 0) {
            socketFree(sid);
            return -1;
        }
    }

    /*
     *	Host is set if we are the client
     */
    if (host) {
        /*
         *		Connect to the remote server in blocking mode, then go into
         *		non-blocking mode if desired.
         */
        if (!dgram) {
            if (! (sp->flags & SOCKET_BLOCK)) {
                /*
                 *				sockGen.c is only used for Windows products when blocking
                 *				connects are expected.  This applies to webserver connectws.
                 *				Therefore the asynchronous connect code here is not compiled.
                 */
#if (defined (WIN) || defined (CE)) && (!defined (LITTLEFOOT) && !defined (WEBS))
                int flag;

                sp->flags |= SOCKET_ASYNC;
                /*
                 *				Set to non-blocking for an async connect
                 */
                flag = 1;
                if (ioctlsocket(sp->sock, FIONBIO, &flag) == SOCKET_ERROR) {
                    socketFree(sid);
                    return -1;
                }
#else
                socketSetBlock(sid, 1);
#endif /* #if (WIN || CE) && !(LITTLEFOOT || WEBS) */

            }
            if ((rc = connect(sp->sock, (struct sockaddr *) &sockaddr,
                              sizeof(sockaddr))) < 0 &&
                    (rc = tryAlternateConnect(sp->sock,
                                              (struct sockaddr *) &sockaddr)) < 0) {
#if (defined (WIN) || defined (CE))
                if (socketGetError() != EWOULDBLOCK) {
                    socketFree(sid);
                    return -1;
                }
#else
                socketFree(sid);
                return -1;

#endif /* WIN || CE */

            }
        }
    } else {
        /*
         *		Bind to the socket endpoint and the call listen() to start listening
         */
        rc = 1;
        setsockopt(sp->sock, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(rc));
        if (bind(sp->sock, (struct sockaddr *) &sockaddr,
                 sizeof(sockaddr)) < 0) {
            socketFree(sid);
            return -1;
        }

        if (! dgram) {
            if (listen(sp->sock, SOMAXCONN) < 0) {
                socketFree(sid);
                return -1;
            }
            sp->flags |= SOCKET_LISTENING;
        }
        sp->handlerMask |= SOCKET_READABLE;
    }

    /*
     *	Set the blocking mode
     */

    if (flags & SOCKET_BLOCK) {
        socketSetBlock(sid, 1);
    } else {
        socketSetBlock(sid, 0);
    }
    return sid;
}