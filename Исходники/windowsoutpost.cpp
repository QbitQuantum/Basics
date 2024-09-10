bool windowsoutpost_telnet(const ustring & hostname)
// This makes a connection with the Outpost on "host" and then disconnects again.
// It returns true if this worked out.
{
  bool success = false;
  struct sockaddr_in address;
  struct hostent *host;
  int sock;
  host = gethostbyname(hostname.c_str());
  if (host) {
#ifdef WIN32
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) != SOCKET_ERROR)
#else
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) >= 0)
#endif
    {
      address.sin_family = AF_INET;
      memcpy(&address.sin_addr, host->h_addr_list[0], sizeof(address.sin_addr));
#ifdef WIN32
      WSAHtons(sock, 51515, &address.sin_port);
      if (connect(sock, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
#else
      address.sin_port = htons(51515);
      if (connect(sock, (struct sockaddr *)&address, sizeof(address)))
#endif
      {
        ; // success = false;
      } else {
        success = true;
      }
#ifdef WIN32
      closesocket(sock);
#else
      close(sock);
#endif
    }
  }
  return success;
}