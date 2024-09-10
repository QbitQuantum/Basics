static int
ioctl_fd_maybe_socket (const struct fd_hook *remaining_list,
                       gl_ioctl_fn primary,
                       int fd, int request, void *arg)
{
  SOCKET sock;
  WSANETWORKEVENTS ev;

  /* Test whether fd refers to a socket.  */
  sock = FD_TO_SOCKET (fd);
  ev.lNetworkEvents = 0xDEADBEEF;
  WSAEnumNetworkEvents (sock, NULL, &ev);
  if (ev.lNetworkEvents != 0xDEADBEEF)
    {
      /* fd refers to a socket.  */
      if (ioctlsocket (sock, request, arg) < 0)
        {
          set_winsock_errno ();
          return -1;
        }
      else
        return 0;
    }
  else
    /* Some other type of file descriptor.  */
    return execute_ioctl_hooks (remaining_list, primary, fd, request, arg);
}