static int GetAddrInfoNonLinux(const char* hostname, int port,
                               struct addrinfo** addr_info) {
// Get the host data depending on the OS.
  struct sockaddr_in* address;
  *addr_info = new struct addrinfo;
  memset(*addr_info, 0, sizeof(struct addrinfo));
  address = new struct sockaddr_in;
  memset(address, 0, sizeof(struct sockaddr_in));

  (*addr_info)->ai_addr = (struct sockaddr*) address;
  (*addr_info)->ai_addrlen = sizeof(struct sockaddr);
  (*addr_info)->ai_family = AF_INET;
  (*addr_info)->ai_socktype = SOCK_STREAM;

  struct hostent *name;
#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(1, 1), &wsaData);
  name = gethostbyname(hostname);
#else
  name = gethostbyname(hostname);
#endif

  if (name == NULL) {
    FreeAddrInfo(*addr_info);
    *addr_info = NULL;
    return -1;
  }

  // Fill in the appropriate variables to be able to connect to the server.
  address->sin_family = name->h_addrtype;
  memcpy((char *) &address->sin_addr.s_addr,
         name->h_addr_list[0], name->h_length);
  address->sin_port = htons(port);
  return 0;
}