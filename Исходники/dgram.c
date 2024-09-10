ssize_t
dgram_recv(
    dgram_t *		dgram,
    int			timeout,
    sockaddr_union *fromaddr)
{
    SELECT_ARG_TYPE ready;
    struct timeval to;
    ssize_t size;
    int sock;
    socklen_t_equiv addrlen;
    ssize_t nfound;
    int save_errno;

    sock = dgram->socket;

    FD_ZERO(&ready);
    FD_SET(sock, &ready);
    to.tv_sec = timeout;
    to.tv_usec = 0;

    dbprintf(_("dgram_recv(dgram=%p, timeout=%u, fromaddr=%p)\n"),
		dgram, timeout, fromaddr);
    
    nfound = (ssize_t)select(sock+1, &ready, NULL, NULL, &to);
    if(nfound <= 0 || !FD_ISSET(sock, &ready)) {
	save_errno = errno;
	if(nfound < 0) {
	    dbprintf(_("dgram_recv: select() failed: %s\n"), strerror(save_errno));
	} else if(nfound == 0) {
	    dbprintf(plural(_("dgram_recv: timeout after %d second\n"),
			    _("dgram_recv: timeout after %d seconds\n"),
			    timeout),
		     timeout);
	    nfound = 0;
	} else if (!FD_ISSET(sock, &ready)) {
	    int i;

	    for(i = 0; i < sock + 1; i++) {
		if(FD_ISSET(i, &ready)) {
		    dbprintf(_("dgram_recv: got fd %d instead of %d\n"), i, sock);
		}
	    }
	    save_errno = EBADF;
	    nfound = -1;
	}
	errno = save_errno;
	return nfound;
    }

    addrlen = (socklen_t_equiv)sizeof(sockaddr_union);
    size = recvfrom(sock, dgram->data, (size_t)MAX_DGRAM, 0,
		    (struct sockaddr *)fromaddr, &addrlen);
    if(size == -1) {
	save_errno = errno;
	dbprintf(_("dgram_recv: recvfrom() failed: %s\n"), strerror(save_errno));
	errno = save_errno;
	return -1;
    }
    dump_sockaddr(fromaddr);
    dgram->len = (size_t)size;
    dgram->data[size] = '\0';
    dgram->cur = dgram->data;
    return size;
}