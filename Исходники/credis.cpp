REDIS credis_connect(const char *host, int port, int timeout)
{
  int fd, rc,flags ,yes = 1, use_he = 0;
  struct sockaddr_in sa;  
  struct hostent *he;
  REDIS rhnd;

#ifdef WIN32
  unsigned long addr;
  WSADATA data;
  
  if (WSAStartup(MAKEWORD(2,2), &data) != 0) {
    DEBUG("Failed to init Windows Sockets DLL\n");
    return NULL;
  }
#endif

  if ((rhnd = cr_new()) == NULL)
    return NULL;

  if (host == NULL)
    host = "127.0.0.1";
  if (port == 0)
    port = 6379;

#ifdef WIN32
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ||
      setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (const char *)&yes, sizeof(yes)) == -1 ||
      setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const char *)&yes, sizeof(yes)) == -1)
    goto error;
#else
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ||
      setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&yes, sizeof(yes)) == -1 ||
      setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void *)&yes, sizeof(yes)) == -1)
    goto error;
#endif

  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);

#ifdef WIN32
  /* TODO use getaddrinfo() instead! */
  addr = inet_addr(host);
  if (addr == INADDR_NONE) {
    he = gethostbyname(host);
    use_he = 1;
  }
  else {
    he = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET);
    use_he = 1;
  }
#else
  if (inet_aton(host, &sa.sin_addr) == 0) {
    he = gethostbyname(host);
    use_he = 1;
  }
#endif

  if (use_he) {
    if (he == NULL)
      goto error;
    memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
  } 

  /* connect with user specified timeout */

#ifndef WIN32
  flags = fcntl(fd, F_GETFL);
  if ((rc = fcntl(fd, F_SETFL, flags | O_NONBLOCK)) < 0) {
    DEBUG("Setting socket non-blocking failed with: %d\n", rc);
  }
#endif

  if (connect(fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
#ifndef WIN32
	  if (errno != EINPROGRESS)
      goto error;
#endif

    if (cr_selectwritable(fd, timeout) > 0) {
      int err;
      socklen_t len = sizeof(err);
      if (getsockopt(fd, SOL_SOCKET, SO_ERROR, (char *)&err, &len) == -1 || err)
        goto error;
    }
    else /* timeout or select error */
      goto error;
  }
  /* else connect completed immediately */

  strcpy(rhnd->ip, inet_ntoa(sa.sin_addr));
  rhnd->port = port;
  rhnd->fd = fd;
  rhnd->timeout = timeout;

  /* We can receive 2 version formats: x.yz and x.y.z, where x.yz was only used prior 
   * first 1.1.0 release(?), e.g. stable releases 1.02 and 1.2.6 */
  if (cr_sendfandreceive(rhnd, CR_BULK, "INFO\r\n") == 0) {
    int items = sscanf(rhnd->reply.bulk,
                       "redis_version:%d.%d.%d\r\n",
                       &(rhnd->version.major),
                       &(rhnd->version.minor),
                       &(rhnd->version.patch));

    if(items == 0)
      items = sscanf(rhnd->reply.bulk,
		     "# Server\r\nredis_version:%d.%d.%d\r\n",
		     &(rhnd->version.major),
		     &(rhnd->version.minor),
		     &(rhnd->version.patch));
    
    if (items < 2)
      goto error;
    if (items == 2) {
      rhnd->version.patch = rhnd->version.minor;
      rhnd->version.minor = 0;
    }
    DEBUG("Connected to Redis version: %d.%d.%d\n", 
          rhnd->version.major, rhnd->version.minor, rhnd->version.patch);
  }

  return rhnd;

error:
  if (fd > 0)
    close(fd);
  cr_delete(rhnd);

  return NULL;
}