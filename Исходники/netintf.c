/************************************************************************** 
  Finds the next (lowest) free port.
**************************************************************************/ 
int find_next_free_port(int starting_port, int highest_port,
                        enum fc_addr_family family,
                        char *net_interface, bool not_avail_ok)
{
  int port;
  int s;
  int gafamily;
  bool found = FALSE;

#ifndef IPV6_SUPPORT
  fc_assert(family == FC_ADDR_IPV4 || family == FC_ADDR_ANY);
#endif

  switch (family) {
   case FC_ADDR_IPV4:
     gafamily = AF_INET;
     break;
#ifdef IPV6_SUPPORT
   case FC_ADDR_IPV6:
     gafamily = AF_INET6;
     break;
#endif /* IPV6_SUPPORT */
   case FC_ADDR_ANY:
     gafamily = AF_UNSPEC;
     break;
   default:
     fc_assert(FALSE);
     log_error("Port from unsupported address family requested!");

     return -1;
  }

  for (port = starting_port; !found && highest_port > port; port++) {
    /* HAVE_GETADDRINFO implies IPv6 support */
#ifdef HAVE_GETADDRINFO
    struct addrinfo hints;
    int err;
    char servname[8];
    struct addrinfo *res;

    fc_snprintf(servname, sizeof(servname), "%d", port);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = gafamily;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE | FC_AI_NUMERICSERV;

    err = getaddrinfo(net_interface, servname, &hints, &res);
    if (!err) {
      struct addrinfo *current = res;
      bool unusable = FALSE;

      while (current != NULL && !unusable) {
        s = socket(current->ai_family, SOCK_STREAM, 0);

        if (s == -1) {
          log_error("socket(): %s", fc_strerror(fc_get_errno()));
        } else {
          if (bind(s, current->ai_addr, current->ai_addrlen) != 0) {
            if (!not_avail_ok || fc_get_errno() != EADDRNOTAVAIL) {
              unusable = TRUE;
            }
          }
        }
        current = current->ai_next;
        fc_closesocket(s);
      }

      freeaddrinfo(res);

      if (!unusable && res != NULL) {
        found = TRUE;
      }
    }
#else /* HAVE_GETADDRINFO */
    union fc_sockaddr tmp;
    struct sockaddr_in *sock4;

    s = socket(gafamily, SOCK_STREAM, 0);

    sock4 = &tmp.saddr_in4;
    memset(&tmp, 0, sizeof(tmp));
    sock4->sin_family = AF_INET;
    sock4->sin_port = htons(port);
    if (net_interface != NULL) {
#if defined(HAVE_INET_ATON)
      if (inet_aton(net_interface, &sock4->sin_addr) == 0) {
#else /* HAVE_INET_ATON */
      sock4->sin_addr.s_addr = inet_addr(net_interface);
      if (sock4->sin_addr.s_addr == INADDR_NONE) {
#endif /* HAVE_INET_ATON */
        struct hostent *hp;

        hp = gethostbyname(net_interface);
        if (hp == NULL) {
          log_error("No hostent for %s!", net_interface);

          return -1;
        }
        if (hp->h_addrtype != AF_INET) {
          log_error("Requested IPv4 address for %s, got something else! (%d)",
                    net_interface, hp->h_addrtype);

          return -1;
        }

        memcpy(&sock4->sin_addr, hp->h_addr, hp->h_length);
      }
    } else {
      sock4->sin_addr.s_addr = htonl(INADDR_ANY);
    }

    if (bind(s, &tmp.saddr, sockaddr_size(&tmp)) == 0) {
      found = TRUE;
    }

    fc_closesocket(s);
#endif /* HAVE_GETADDRINFO */
  }

  if (!found) {
    log_error("None of the ports %d - %d is available.",
              starting_port, highest_port);

    return -1;
  }

  /* Rollback the last increment from the loop, back to the port
   * number found to be free. */
  port--;

  return port;
}