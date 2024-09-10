void cXVDRServer::NewClientConnected(int fd)
{
  struct sockaddr_storage sin;
  socklen_t len = sizeof(sin);
  in_addr_t *ipv4_addr = NULL;

  if (getpeername(fd, (struct sockaddr *)&sin, &len))
  {
    ERRORLOG("getpeername() failed, dropping new incoming connection %d", m_IdCnt);
    close(fd);
    return;
  }

  if (!m_IPv4Fallback)
  {
    if (IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *)&sin)->sin6_addr) ||
        IN6_IS_ADDR_V4COMPAT(&((struct sockaddr_in6 *)&sin)->sin6_addr))
      ipv4_addr = &((struct sockaddr_in6 *)&sin)->sin6_addr.s6_addr32[3];
  }
  else
    ipv4_addr = &((struct sockaddr_in *)&sin)->sin_addr.s_addr;

  // Acceptable() method only supports in_addr_t argument so we're currently checking IPv4 hosts only
  if (ipv4_addr)
  {
    cAllowedHosts AllowedHosts(m_AllowedHostsFile);
    if (!AllowedHosts.Acceptable(*ipv4_addr))
    {
      ERRORLOG("Address not allowed to connect (%s)", *m_AllowedHostsFile);
      close(fd);
      return;
    }
  }

  if (fcntl(fd, F_SETFL, fcntl (fd, F_GETFL) | O_NONBLOCK) == -1)
  {
    ERRORLOG("Error setting control socket to nonblocking mode");
    close(fd);
    return;
  }

  int val = 1;
  setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val));

#ifndef __FreeBSD__
  val = 30;
  setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &val, sizeof(val));

  val = 15;
  setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &val, sizeof(val));

  val = 5;
  setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &val, sizeof(val));
#endif

  val = 1;
  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val));

  if (!m_IPv4Fallback)
    INFOLOG("Client %s:%i with ID %d connected.", xvdr_inet_ntoa(((struct sockaddr_in6 *)&sin)->sin6_addr), ((struct sockaddr_in6 *)&sin)->sin6_port, m_IdCnt);
  else
    INFOLOG("Client %s:%i with ID %d connected.", inet_ntoa(((struct sockaddr_in *)&sin)->sin_addr), ((struct sockaddr_in *)&sin)->sin_port, m_IdCnt);
  cXVDRClient *connection = new cXVDRClient(fd, m_IdCnt);
  m_clients.push_back(connection);
  m_IdCnt++;
}