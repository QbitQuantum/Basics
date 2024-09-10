int
_eXosip_recvfrom (int s, char *buf, int len, unsigned int flags,
                  struct sockaddr *from, socklen_t * fromlen)
{
  int message_size = 0;
  int length_done = 0;
  int real_size = 0;
  int i;
  int extra_data_discarded;

  if (!eXosip.http_port)
    {
      return recvfrom (s, buf, len, flags, from, fromlen);
    }

  /* we get the size of the HTTP data */
  i = recv (eXosip.net_interfaces[0].net_socket, (char *) &(message_size), 4, 0);

  real_size = message_size;
  if (message_size < 0)
    {
      return -1;                /* Connection error? */
    }
  if (message_size == 0)
    {
      buf[0] = '\0';
      return 0;
    }
  if (message_size > len - 1)
    message_size = len - 1;

  length_done = 0;

  i = recv (eXosip.net_interfaces[0].net_socket, buf, message_size, 0);
  length_done = i;

  if (length_done == real_size)
    {
      return length_done;
    }

  if (length_done < message_size)
    {
      /* continue reading up to message_size */
      while (length_done < message_size)
        {
          i =
            recv (eXosip.net_interfaces[0].net_socket, buf + length_done,
                  message_size - length_done, 0);
          length_done = length_done + i;
        }
    }

  extra_data_discarded = length_done;
  while (extra_data_discarded < real_size)
    {
      char buf2[2048];

      /* We have to discard the end of data... up to the next message */
      i = recv (eXosip.net_interfaces[0].net_socket, buf2, 2048, 0);
      extra_data_discarded = extra_data_discarded + i;
    }
  return length_done;
}