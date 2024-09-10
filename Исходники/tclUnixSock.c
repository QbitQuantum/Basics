Tcl_Channel
Tcl_OpenTcpServer(
    Tcl_Interp *interp,		/* For error reporting - may be NULL. */
    int port,			/* Port number to open. */
    const char *myHost,		/* Name of local host. */
    Tcl_TcpAcceptProc *acceptProc,
				/* Callback for accepting connections from new
				 * clients. */
    ClientData acceptProcData)	/* Data for the callback. */
{
    int status = 0, sock = -1, reuseaddr = 1, chosenport = 0;
    struct addrinfo *addrlist = NULL, *addrPtr;	/* socket address */
    TcpState *statePtr = NULL;
    char channelName[SOCK_CHAN_LENGTH];
    const char *errorMsg = NULL;
    TcpFdList *fds = NULL, *newfds;

    /*
     * Try to record and return the most meaningful error message, i.e. the
     * one from the first socket that went the farthest before it failed.
     */

    enum { LOOKUP, SOCKET, BIND, LISTEN } howfar = LOOKUP;
    int my_errno = 0;

    if (!TclCreateSocketAddress(interp, &addrlist, myHost, port, 1, &errorMsg)) {
	my_errno = errno;
	goto error;
    }

    for (addrPtr = addrlist; addrPtr != NULL; addrPtr = addrPtr->ai_next) {
	sock = socket(addrPtr->ai_family, addrPtr->ai_socktype,
                addrPtr->ai_protocol);
	if (sock == -1) {
	    if (howfar < SOCKET) {
		howfar = SOCKET;
		my_errno = errno;
	    }
	    continue;
	}
	
	/*
	 * Set the close-on-exec flag so that the socket will not get
	 * inherited by child processes.
	 */
	
	fcntl(sock, F_SETFD, FD_CLOEXEC);
	
	/*
	 * Set kernel space buffering
	 */
	
	TclSockMinimumBuffers(INT2PTR(sock), SOCKET_BUFSIZE);
	
	/*
	 * Set up to reuse server addresses automatically and bind to the
	 * specified port.
	 */
	
	(void) setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, 
		(char *) &reuseaddr, sizeof(reuseaddr));
	
        /*
         * Make sure we use the same port number when opening two server
         * sockets for IPv4 and IPv6 on a random port.
         *
         * As sockaddr_in6 uses the same offset and size for the port member
         * as sockaddr_in, we can handle both through the IPv4 API.
         */

	if (port == 0 && chosenport != 0) {
	    ((struct sockaddr_in *) addrPtr->ai_addr)->sin_port =
                    htons(chosenport);
	}

#ifdef IPV6_V6ONLY
	/* Missing on: Solaris 2.8 */
        if (addrPtr->ai_family == AF_INET6) {
            int v6only = 1;

            (void) setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY,
                    &v6only, sizeof(v6only));
        }
#endif /* IPV6_V6ONLY */

	status = bind(sock, addrPtr->ai_addr, addrPtr->ai_addrlen);
        if (status == -1) {
	    if (howfar < BIND) {
		howfar = BIND;
		my_errno = errno;
	    }       
            close(sock);
            continue;
        }
        if (port == 0 && chosenport == 0) {
            address sockname;
            socklen_t namelen = sizeof(sockname);

            /*
             * Synchronize port numbers when binding to port 0 of multiple
             * addresses.
             */

            if (getsockname(sock, &sockname.sa, &namelen) >= 0) {
                chosenport = ntohs(sockname.sa4.sin_port);
            }
        }
        status = listen(sock, SOMAXCONN);
        if (status < 0) {
	    if (howfar < LISTEN) {
		howfar = LISTEN;
		my_errno = errno;
	    }
            close(sock);
            continue;
        }
        if (statePtr == NULL) {
            /*
             * Allocate a new TcpState for this socket.
             */
            
            statePtr = ckalloc(sizeof(TcpState));
            memset(statePtr, 0, sizeof(TcpState));
            statePtr->acceptProc = acceptProc;
            statePtr->acceptProcData = acceptProcData;
            sprintf(channelName, SOCK_TEMPLATE, (long) statePtr);
            newfds = &statePtr->fds;
        } else {
            newfds = ckalloc(sizeof(TcpFdList));
            memset(newfds, (int) 0, sizeof(TcpFdList));
            fds->next = newfds;
        }
        newfds->fd = sock;
        newfds->statePtr = statePtr;
        fds = newfds;
	
        /*
         * Set up the callback mechanism for accepting connections from new
         * clients.
         */
        
        Tcl_CreateFileHandler(sock, TCL_READABLE, TcpAccept, fds);
    }

  error:
    if (addrlist != NULL) {
	freeaddrinfo(addrlist);
    }
    if (statePtr != NULL) {
	statePtr->channel = Tcl_CreateChannel(&tcpChannelType, channelName,
		statePtr, 0);
	return statePtr->channel;
    }
    if (interp != NULL) {
        Tcl_Obj *errorObj = Tcl_NewStringObj("couldn't open socket: ", -1);

	if (errorMsg == NULL) {
            errno = my_errno;
            Tcl_AppendToObj(errorObj, Tcl_PosixError(interp), -1);
        } else {
	    Tcl_AppendToObj(errorObj, errorMsg, -1);
	}
        Tcl_SetObjResult(interp, errorObj);
    }
    if (sock != -1) {
	close(sock);
    }
    return NULL;
}