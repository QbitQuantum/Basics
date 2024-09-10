static void
print_fd (int fd, int depth)
{
#ifdef DBUS_UNIX
  int ret;
  struct stat statbuf = {0,};
  union {
      struct sockaddr sa;
      struct sockaddr_storage storage;
      struct sockaddr_un un;
      struct sockaddr_in ipv4;
      struct sockaddr_in6 ipv6;
  } addr, peer;
  char hostip[INET6_ADDRSTRLEN];
  int addrlen = sizeof (addr);
  int peerlen = sizeof (peer);
  int has_peer;
#endif

  /* Don't print the fd number: it is different in every process and since
   * dbus-monitor closes the fd after reading it, the same number would be
   * printed again and again.
   */
  printf ("file descriptor\n");
  if (fd == -1)
    return;

#ifdef DBUS_UNIX
  ret = fstat (fd, &statbuf);
  if (ret == -1)
    return;

  indent (depth+1);
  printf ("inode: %d\n", (int) statbuf.st_ino);

  indent (depth+1);
  printf ("type: ");
  if (S_ISREG(statbuf.st_mode))
    printf ("file\n");
  if (S_ISDIR(statbuf.st_mode))
    printf ("directory\n");
  if (S_ISCHR(statbuf.st_mode))
    printf ("char\n");
  if (S_ISBLK(statbuf.st_mode))
    printf ("block\n");
  if (S_ISFIFO(statbuf.st_mode))
    printf ("fifo\n");
  if (S_ISLNK(statbuf.st_mode))
    printf ("link\n");
  if (S_ISSOCK(statbuf.st_mode))
    printf ("socket\n");

  /* If it's not a socket, getsockname will just return -1 with errno
   * ENOTSOCK. */

  memset (&addr, 0, sizeof (addr));
  memset (&peer, 0, sizeof (peer));

  if (getsockname(fd, &addr.sa, &addrlen))
    return;

  has_peer = !getpeername(fd, &peer.sa, &peerlen);

  indent (depth+1);
  printf ("address family: ");
  switch (addr.sa.sa_family)
    {
      case AF_UNIX:
        printf("unix\n");
        if (addr.un.sun_path[0] == '\0')
          {
            /* Abstract socket might not be zero-terminated and length is
             * variable. Who designed this interface?
             * Write the name in the same way as /proc/net/unix
             * See manual page unix(7)
             */
            indent (depth+1);
            printf ("name @%.*s\n",
                    (int) (addrlen - sizeof (sa_family_t) - 1),
                    &(addr.un.sun_path[1]));

            if (has_peer)
              {
                indent (depth+1);
                printf ("peer @%.*s\n",
                        (int) (addrlen - sizeof (sa_family_t) - 1),
                        &(addr.un.sun_path[1]));
              }
          }
        else
          {
            indent (depth+1);
            printf ("name %s\n", addr.un.sun_path);
            if (has_peer)
              {
                indent (depth+1);
                printf ("peer %s\n", peer.un.sun_path);
              }
          }
        break;

      case AF_INET:
        printf ("inet\n");
        if (inet_ntop (AF_INET, &addr.ipv4.sin_addr, hostip, sizeof (hostip)))
          {
            indent (depth+1);
            printf ("name %s port %u\n", hostip, ntohs (addr.ipv4.sin_port));
          }
        if (has_peer && inet_ntop (AF_INET, &peer.ipv4.sin_addr, hostip, sizeof (hostip)))
          {
            indent (depth+1);
            printf ("peer %s port %u\n", hostip, ntohs (peer.ipv4.sin_port));
          }

        break;

#ifdef AF_INET6
      case AF_INET6:
        printf ("inet6\n");
        if (inet_ntop (AF_INET6, &addr.ipv6.sin6_addr, hostip, sizeof (hostip)))
          {
            indent (depth+1);
            printf ("name %s port %u\n", hostip, ntohs (addr.ipv6.sin6_port));
          }
        if (has_peer && inet_ntop (AF_INET6, &peer.ipv6.sin6_addr, hostip, sizeof (hostip)))
          {
            indent (depth+1);
            printf ("peer %s port %u\n", hostip, ntohs (peer.ipv6.sin6_port));
          }
        break;
#endif

#ifdef AF_BLUETOOTH
      case AF_BLUETOOTH:
        printf ("bluetooth\n");
        break;
#endif

      default:
        printf ("unknown (%d)\n", addr.sa.sa_family);
        break;
    }
#endif
}