void  WinTCPSocketServer::configSocket(unsigned short port)
{
  sockaddr_in	service;
  hostent*	thisHost;
  char		hostName[255];
  char*		ip;

  service.sin_family = AF_INET;
  WSAHtons(this->_sock, port, &service.sin_port);
  gethostname(hostName, 255);
  if (!(thisHost = gethostbyname(hostName)))
    throw WSAException("TCPSocketServer: gethostbyname");
  ip = inet_ntoa(*(struct in_addr *)*thisHost->h_addr_list);
  service.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->_sock, (SOCKADDR*) &service, sizeof(SOCKADDR)) == SOCKET_ERROR)
  {
    int	code = WSAGetLastError();

    if (closesocket(this->_sock) == SOCKET_ERROR)
      throw WSAException("TCPSocketServer: closesocket");
    throw WSAException("TCPSocketServer: bind", code);
  }
  if (listen(this->_sock, 20) == SOCKET_ERROR)
  {
    int	code = WSAGetLastError();

    if (closesocket(this->_sock) == SOCKET_ERROR)
      throw WSAException("TCPSocketServer: closesocket");
    throw WSAException("TCPSocketServer: listen", code);
  }
}