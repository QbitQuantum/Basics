static void
reset_fds (GPollFD fds[],
           int     num_pollees)
{
  gint i;

  for (i = 0; i < num_pollees; i++)
    {
      WSAResetEvent ((HANDLE) fds[i].fd);
      fds[i].events =  G_IO_IN | G_IO_OUT | G_IO_ERR;
      fds[i].revents = 0;
    }
}