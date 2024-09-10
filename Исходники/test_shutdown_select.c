static MHD_socket
start_socket_listen(int domain)
{
/* Create sockets similarly to daemon.c */
  MHD_socket fd;
  int cloexec_set;
  struct sockaddr_in sock_addr;
  socklen_t addrlen;

#ifdef MHD_WINSOCK_SOCKETS
  unsigned long flags = 1;
#else  /* MHD_POSIX_SOCKETS */
  int flags;
#endif /* MHD_POSIX_SOCKETS */

#if defined(MHD_POSIX_SOCKETS) && defined(SOCK_CLOEXEC)
  fd = socket (domain, SOCK_STREAM | SOCK_CLOEXEC, 0);
  cloexec_set = 1;
#elif defined(MHD_WINSOCK_SOCKETS) && defined (WSA_FLAG_NO_HANDLE_INHERIT)
  fd = WSASocketW (domain, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_NO_HANDLE_INHERIT);
  cloexec_set = 1;
#else  /* !SOCK_CLOEXEC */
  fd = socket (domain, SOCK_STREAM, 0);
  cloexec_set = 0;
#endif /* !SOCK_CLOEXEC */
  if ( (MHD_INVALID_SOCKET == fd) && (cloexec_set) )
    {
      fd = socket (domain, SOCK_STREAM, 0);
      cloexec_set = 0;
    }
  if (MHD_INVALID_SOCKET == fd)
    {
      fprintf (stderr, "Can't create socket: %u\n",
               (unsigned)sock_errno);
      return MHD_INVALID_SOCKET;
    }

  if (!cloexec_set)
    {
#ifdef MHD_WINSOCK_SOCKETS
    if (!SetHandleInformation ((HANDLE)fd, HANDLE_FLAG_INHERIT, 0))
      fprintf (stderr, "Failed to make socket non-inheritable: %u\n",
               (unsigned int)GetLastError ());
#else  /* MHD_POSIX_SOCKETS */
    flags = fcntl (fd, F_GETFD);
    if ( ( (-1 == flags) ||
           ( (flags != (flags | FD_CLOEXEC)) &&
             (0 != fcntl (fd, F_SETFD, flags | FD_CLOEXEC)) ) ) )
      fprintf (stderr, "Failed to make socket non-inheritable: %s\n",
               MHD_socket_last_strerr_ ());
#endif /* MHD_POSIX_SOCKETS */
    }

  memset (&sock_addr, 0, sizeof (struct sockaddr_in));
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons (0);
#if HAVE_SOCKADDR_IN_SIN_LEN
  sock_addr.sin_len = sizeof (struct sockaddr_in);
#endif
  addrlen = sizeof (struct sockaddr_in);

  if (bind (fd, (const struct sockaddr*) &sock_addr, addrlen) < 0)
    {
      fprintf (stderr, "Failed to bind socket: %u\n",
               (unsigned)sock_errno);
      MHD_socket_close_chk_ (fd);
      return MHD_INVALID_SOCKET;
    }

#ifdef MHD_WINSOCK_SOCKETS
  if (0 != ioctlsocket (fd, FIONBIO, &flags))
    {
      fprintf (stderr, "Failed to make socket non-blocking: %u\n",
               (unsigned)sock_errno);
      MHD_socket_close_chk_ (fd);
      return MHD_INVALID_SOCKET;
    }
#else  /* MHD_POSIX_SOCKETS */
  flags = fcntl (fd, F_GETFL);
  if ( ( (-1 == flags) ||
         ( (flags != (flags | O_NONBLOCK)) &&
           (0 != fcntl (fd, F_SETFL, flags | O_NONBLOCK)) ) ) )
    {
      fprintf (stderr, "Failed to make socket non-blocking: %s\n",
              MHD_socket_last_strerr_ ());
      MHD_socket_close_chk_ (fd);
      return MHD_INVALID_SOCKET;
    }
#endif /* MHD_POSIX_SOCKETS */

  if (listen(fd, SOMAXCONN) < 0)
    {
      fprintf (stderr, "Failed to listen on socket: %u\n",
               (unsigned)sock_errno);
      MHD_socket_close_chk_ (fd);
      return MHD_INVALID_SOCKET;
    }

  return fd;
}