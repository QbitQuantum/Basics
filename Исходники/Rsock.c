int R_SockConnect(int port, char *host, int timeout)
{
    SOCKET s;
    fd_set wfd, rfd;
    struct timeval tv;
    int status = 0;
    double used = 0.0;
    struct sockaddr_in server;
    struct hostent *hp;

    check_init();
    s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == -1)  return -1;

#ifdef Win32
    {
	u_long one = 1;

	status = ioctlsocket(s, FIONBIO, &one) == SOCKET_ERROR ? -1 : 0;
    }
#else
#ifdef HAVE_FCNTL
    if ((status = fcntl(s, F_GETFL, 0)) != -1) {
#ifdef O_NONBLOCK
	status |= O_NONBLOCK;
#else /* O_NONBLOCK */
#ifdef F_NDELAY
	status |= F_NDELAY;
#endif /* F_NDELAY */
#endif /* !O_NONBLOCK */
	status = fcntl(s, F_SETFL, status);
    }
#endif
    if (status < 0) {
	closesocket(s);
	return(-1);
    }
#endif

    if (! (hp = gethostbyname(host))) return -1;

    memcpy((char *)&server.sin_addr, hp->h_addr_list[0], hp->h_length);
    server.sin_port = htons((short)port);
    server.sin_family = AF_INET;

    if ((connect(s, (struct sockaddr *) &server, sizeof(server)) == -1)) {

	switch (socket_errno()) {
	case EINPROGRESS:
	case EWOULDBLOCK:
	    break;
	default:
	    closesocket(s);
	    return(-1);
	}
    }

    while(1) {
	int maxfd = 0;
	R_ProcessEvents();
#ifdef Unix
	if(R_wait_usec > 0) {
	    R_PolledEvents();
	    tv.tv_sec = 0;
	    tv.tv_usec = R_wait_usec;
	} else {
	    tv.tv_sec = timeout;
	    tv.tv_usec = 0;
	}
#elif defined(Win32)
	tv.tv_sec = 0;
	tv.tv_usec = 2e5;
#else
	tv.tv_sec = timeout;
	tv.tv_usec = 0;
#endif


#ifdef Unix
	maxfd = setSelectMask(R_InputHandlers, &rfd);
#else
	FD_ZERO(&rfd);
#endif
	FD_ZERO(&wfd);
	FD_SET(s, &wfd);
	if(maxfd < s) maxfd = s;

	switch(R_SelectEx(maxfd+1, &rfd, &wfd, NULL, &tv, NULL))
	{
	case 0:
	    /* Time out */
	    used += tv.tv_sec + 1e-6 * tv.tv_usec;
	    if(used < timeout) continue;
	    closesocket(s);
	    return(-1);
	case -1:
	    /* Ermm.. ?? */
	    closesocket(s);
	    return(-1);
	}

	if ( FD_ISSET(s, &wfd) ) {
	    R_SOCKLEN_T len;
	    len = sizeof(status);
	    if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char*)&status, &len) < 0){
		/* Solaris error code */
		return (-1);
	    }
	    if ( status ) {
		closesocket(s);
		errno = status;
		return (-1);
	    } else return(s);
#ifdef Unix
	} else { /* some other handler needed */
	    InputHandler *what;
	    what = getSelectedHandler(R_InputHandlers, &rfd);
	    if(what != NULL) what->handler((void*) NULL);
	    continue;
#endif
	}
    }
    /* not reached
    return(-1); */
}