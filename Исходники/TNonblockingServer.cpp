/**
 * Creates a socket to listen on and binds it to the local port.
 */
void TNonblockingServer::createAndListenOnSocket() {
#ifdef _WIN32
  TWinsockSingleton::create();
#endif // _WIN32

  THRIFT_SOCKET s;

  struct addrinfo hints, *res, *res0;
  int error;

  char port[sizeof("65536") + 1];
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
  sprintf(port, "%d", port_);

  // Wildcard address
  error = getaddrinfo(NULL, port, &hints, &res0);
  if (error) {
    throw TException("TNonblockingServer::serve() getaddrinfo "
                     + string(THRIFT_GAI_STRERROR(error)));
  }

  // Pick the ipv6 address first since ipv4 addresses can be mapped
  // into ipv6 space.
  for (res = res0; res; res = res->ai_next) {
    if (res->ai_family == AF_INET6 || res->ai_next == NULL)
      break;
  }

  // Create the server socket
  s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (s == -1) {
    freeaddrinfo(res0);
    throw TException("TNonblockingServer::serve() socket() -1");
  }

#ifdef IPV6_V6ONLY
  if (res->ai_family == AF_INET6) {
    int zero = 0;
    if (-1 == setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, const_cast_sockopt(&zero), sizeof(zero))) {
      GlobalOutput("TServerSocket::listen() IPV6_V6ONLY");
    }
  }
#endif // #ifdef IPV6_V6ONLY

  int one = 1;

  // Set THRIFT_NO_SOCKET_CACHING to avoid 2MSL delay on server restart
  setsockopt(s, SOL_SOCKET, THRIFT_NO_SOCKET_CACHING, const_cast_sockopt(&one), sizeof(one));

  if (::bind(s, res->ai_addr, static_cast<int>(res->ai_addrlen)) == -1) {
    ::THRIFT_CLOSESOCKET(s);
    freeaddrinfo(res0);
    throw TTransportException(TTransportException::NOT_OPEN,
                              "TNonblockingServer::serve() bind",
                              THRIFT_GET_SOCKET_ERROR);
  }

  // Done with the addr info
  freeaddrinfo(res0);

  // Set up this file descriptor for listening
  listenSocket(s);
}