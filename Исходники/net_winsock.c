socket_t
htsp_tcp_connect_addr(struct addrinfo* addr, char *errbuf, size_t errbufsize,
	    int timeout)
{
  socket_t fd;
  int r, err, val;
  socklen_t errlen = sizeof(int);

  fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
  if(fd == -1) {
    snprintf(errbuf, errbufsize, "Unable to create socket: %s",
	     strerror(WSAGetLastError()));
    return -1;
  }

  /**
   * Switch to nonblocking
   */
  val = 1;
  ioctlsocket(fd, FIONBIO, &val);

  r = connect(fd, addr->ai_addr, addr->ai_addrlen);

  if(r == -1) {
    if(WSAGetLastError() == EINPROGRESS ||
       WSAGetLastError() == EAGAIN) {
      fd_set fd_write, fd_except;
      struct timeval tv;

      tv.tv_sec  =         timeout / 1000;
      tv.tv_usec = 1000 * (timeout % 1000);

      FD_ZERO(&fd_write);
      FD_ZERO(&fd_except);

      FD_SET(fd, &fd_write);
      FD_SET(fd, &fd_except);

      r = select((int)fd+1, NULL, &fd_write, &fd_except, &tv);

      if(r == 0) {
        /* Timeout */
        snprintf(errbuf, errbufsize, "Connection attempt timed out");
        closesocket(fd);
        return -1;
      }

      if(r == -1) {
        snprintf(errbuf, errbufsize, "select() error: %s", strerror(WSAGetLastError()));
        closesocket(fd);
        return -1;
      }

      getsockopt(fd, SOL_SOCKET, SO_ERROR, (void *)&err, &errlen);
    } else {
      err = WSAGetLastError();
    }
  } else {
    err = 0;
  }

  if(err != 0) {
    snprintf(errbuf, errbufsize, "%s", strerror(err));
    closesocket(fd);
    return -1;
  }

  val = 0;
  ioctlsocket(fd, FIONBIO, &val);

  val = 1;
  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const char*)&val, sizeof(val));

  return fd;
}