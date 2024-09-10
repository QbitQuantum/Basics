static int do_connect(char *host, int port) {
  int sock;
  struct sockaddr_in addr, check_connect;
  fd_set rset, wset;

  struct timeval timeout;

  // start unconnected
  int connected = 0;

#ifdef WIN32
  WORD version;
  WSADATA wsaData;
  int size, error;
  u_long no = 0;
  const char yes = 1;

  version = MAKEWORD(2,2);
  error = WSAStartup(version, &wsaData);

  if (error != 0) {
    return 0;
  }

  // create socket
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == INVALID_SOCKET) {
    return 0;
  }

#else
  uint size;
  int yes = 1;

  // create socket
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    croak("couldn't create socket: %s\n", strerror(errno));
    return -1;
  }
#endif

  // timeout
  timeout.tv_sec = 20;
  timeout.tv_usec = 0;

  // get addresses
  if (!mongo_link_sockaddr(&addr, host, port)) {
    return -1;
  }

  setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &yes, INT_32);
  setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &yes, INT_32);

#ifdef WIN32
  ioctlsocket(sock, FIONBIO, (u_long*)&yes);
#else
  fcntl(sock, F_SETFL, O_NONBLOCK);
#endif

  FD_ZERO(&rset);
  FD_SET(sock, &rset);
  FD_ZERO(&wset);
  FD_SET(sock, &wset);

  // connect
  if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
#ifdef WIN32
    errno = WSAGetLastError();
    if (errno != WSAEINPROGRESS &&
		errno != WSAEWOULDBLOCK)
#else
    if (errno != EINPROGRESS)
#endif
    {
      return -1;
    }

    if (!select(sock+1, &rset, &wset, 0, &timeout)) {
      return -1;
    }

    size = sizeof(check_connect);

    connected = getpeername(sock, (struct sockaddr*)&addr, &size);
    if (connected == -1) {
      return -1;
    }
  }
  
// reset flags
#ifdef WIN32
  ioctlsocket(sock, FIONBIO, &no);
#else
  fcntl(sock, F_SETFL, 0);
#endif
  return sock;
}