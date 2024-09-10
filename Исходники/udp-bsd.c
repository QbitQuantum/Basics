NiceSocket *
nice_udp_bsd_socket_new (NiceAddress *addr)
{
  int sockfd = -1;
  struct sockaddr_storage name;
  socklen_t name_len = sizeof (name);
  NiceSocket *sock = g_slice_new0 (NiceSocket);

  if (addr != NULL) {
    nice_address_copy_to_sockaddr(addr, (struct sockaddr *)&name);
  } else {
    memset (&name, 0, sizeof (name));
    name.ss_family = AF_UNSPEC;
  }

  if (name.ss_family == AF_UNSPEC || name.ss_family == AF_INET) {
    sockfd = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    name.ss_family = AF_INET;
#ifdef HAVE_SA_LEN
    name.ss_len = sizeof (struct sockaddr_in);
#endif
  } else if (name.ss_family == AF_INET6) {
    sockfd = socket (PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    name.ss_family = AF_INET6;
#ifdef HAVE_SA_LEN
    name.ss_len = sizeof (struct sockaddr_in6);
#endif
  }

  if (sockfd == -1) {
    g_slice_free (NiceSocket, sock);
    return NULL;
  }

#ifdef FD_CLOEXEC
  fcntl (sockfd, F_SETFD, fcntl (sockfd, F_GETFD) | FD_CLOEXEC);
#endif
#ifdef O_NONBLOCK
  fcntl (sockfd, F_SETFL, fcntl (sockfd, F_GETFL) | O_NONBLOCK);
#endif

  if(bind (sockfd, (struct sockaddr *) &name,
          name.ss_family == AF_INET? sizeof (struct sockaddr_in) :
          sizeof(struct sockaddr_in6)) < 0) {
    g_slice_free (NiceSocket, sock);
#ifdef G_OS_WIN32
    closesocket(sockfd);
#else
    close (sockfd);
#endif
    return NULL;
  }

  name_len = name.ss_family == AF_INET? sizeof (struct sockaddr_in) :
      sizeof(struct sockaddr_in6);
  if (getsockname (sockfd, (struct sockaddr *) &name, &name_len) < 0) {
    g_slice_free (NiceSocket, sock);
#ifdef G_OS_WIN32
    closesocket(sockfd);
#else
    close (sockfd);
#endif
    return NULL;
  }

  nice_address_set_from_sockaddr (&sock->addr, (struct sockaddr *)&name);
  sock->fileno = sockfd;

  sock->send = socket_send;
  sock->recv = socket_recv;
  sock->is_reliable = socket_is_reliable;
  sock->close = socket_close;

  return sock;
}