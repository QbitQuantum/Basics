int
MConnector::connectUDP(const MString& host, int port,
		       CTN_SOCKET& returnSocket)
{

  MLogClient logClient;
#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(1, 1), &wsaData);
  int nOption = SO_SYNCHRONOUS_NONALERT;
  ::setsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE,
		   (char *) &nOption, sizeof(int));
#endif

  returnSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (returnSocket == CTN_BAD_SOCKET) {
    return 1;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  char tmp[1024]="";
  host.safeExport(tmp, sizeof tmp);
  struct hostent* hp = ::gethostbyname(tmp);
  if (hp == NULL) {
    return 1;
  }
  (void)::memcpy(&server.sin_addr, hp->h_addr, (unsigned long)hp->h_length);
  server.sin_port = (u_short)htons(port);
  if (::connect(returnSocket, (struct sockaddr*)& server, sizeof(server)) < 0) {
#ifdef _WIN32
    ::closesocket(returnSocket);
#else
    ::close(returnSocket);
#endif
    returnSocket = 0;
    return 1;
  }
  strstream x(tmp, sizeof(tmp));
  x << "MConnector::connectUDP(MLogClient:connectUDP " << host << ", " << port << ", internal socket " << returnSocket << '\0';
  logClient.log(MLogClient::MLOG_VERBOSE, tmp);
  return 0;
}