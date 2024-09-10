static int setup_listener(char *name, char *port, char *interface, int queue, int ttl, int tos, int reuse, int keepalive)
{
  int fd;
  struct sockaddr_in addr;
  int addrlen;
  int prt;
  struct hostent *hst;
  struct servent *srv;

  addr.sin_family = AF_INET;

  if (port == NULL) {
    fatal_failure(LINET_USAGE, 0, "require a port to bind (-p port)");
  }
  prt = atoi(port);
  if (prt == 0) {
    srv = getservbyname(port, LINET_TCP);
    if (srv == NULL) {
      fatal_failure(LINET_USAGE, 0, "could not convert %s to a nonzero number", port);
    }
    addr.sin_port = srv->s_port;
  } else {
    addr.sin_port = htons(prt);
  }

  if (interface) {
    if (inet_aton(interface, &(addr.sin_addr)) == 0) {
      hst = gethostbyname(interface);
      if (hst == NULL) {
	fatal_failure(LINET_USAGE, 0, "could not convert %s to an address", interface);
      }
      if (hst->h_addrtype != AF_INET) {
	fatal_failure(LINET_USAGE, 0, "%s does not resolve to an ip4 address", interface);
      }
      addr.sin_addr = *(struct in_addr *) hst->h_addr;
    }
  } else {
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
  }

  fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (fd < 0) {
    fatal_failure(LINET_SYSTEM, errno, "could not create an internet socket");
  }

  if(reuse){
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (void *)&reuse, sizeof(int));
  }

  if(keepalive){
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepalive, sizeof(int));
  }

  addrlen = sizeof(addr);
  if (bind(fd, (struct sockaddr *) &addr, addrlen) == (-1)) {
    fatal_failure(LINET_SYSTEM, errno, "could not bind an internet socket");
  }

  if (listen(fd, queue) == (-1)) {
    fatal_failure(LINET_SYSTEM, errno, "could not listen on socket");
  }

  if(ttl) {
    if (setsockopt(fd, SOL_IP, IP_TTL, (void *)&ttl, sizeof(int))) {
      fatal_failure(LINET_SYSTEM, errno, "could not set time to live to %d hops", ttl);
    }
  }

  if(tos) {
    if (setsockopt(fd, SOL_IP, IP_TOS, (void *)&tos, sizeof(int))) {
      fatal_failure(LINET_SYSTEM, errno, "could not set type of service to 0x%02x", tos);
    }
  }

  return fd;
}