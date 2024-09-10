/**************************************************************************
  Try to connect to a server (get_server_address() must be called first!):
   - try to create a TCP socket and connect it to `names'
   - if successful:
	  - start monitoring the socket for packets from the server
	  - send a "login request" packet to the server
      and - return 0
   - if unable to create the connection, close the socket, put an error
     message in ERRBUF and return the Unix error code (ie., errno, which
     will be non-zero).
**************************************************************************/
static int try_to_connect(const char *username, char *errbuf, int errbufsize)
{
  int i;
  int sock = -1;

  connections_set_close_callback(client_conn_close_callback);

  /* connection in progress? wait. */
  if (client.conn.used) {
    (void) fc_strlcpy(errbuf, _("Connection in progress."), errbufsize);
    return -1;
  }

  /* Try all (IPv4, IPv6, ...) addresses until we have a connection. */
  sock = -1;
  for (i = 0; i < name_count; i++) {
    if ((sock = socket(names[i].saddr.sa_family, SOCK_STREAM, 0)) == -1) {
      /* Probably EAFNOSUPPORT or EPROTONOSUPPORT. */
      continue;
    }

    if (fc_connect(sock, &names[i].saddr,
                   sockaddr_size(&names[i])) == -1) {
      fc_closesocket(sock);
      sock = -1;
      continue;
    } else {
      /* We have a connection! */
      break;
    }
  }

  client.conn.sock = sock;
  if (client.conn.sock == -1) {
    fc_errno err = fc_get_errno(); /* Save errno value before calling anything */

    (void) fc_strlcpy(errbuf, fc_strerror(err), errbufsize);
#ifdef HAVE_WINSOCK
    return -1;
#else
    return err;
#endif /* HAVE_WINSOCK */
  }

  make_connection(client.conn.sock, username);

  return 0;
}