/*
 * Curl_getaddrinfo() when built ipv6-enabled (non-threading and
 * non-ares version).
 *
 * Returns name information about the given hostname and port number. If
 * successful, the 'addrinfo' is returned and the forth argument will point to
 * memory we need to free after use. That memory *MUST* be freed with
 * Curl_freeaddrinfo(), nothing else.
 */
Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                const char *hostname,
                                int port,
                                int *waitp)
{
  struct addrinfo hints;
  Curl_addrinfo *res;
  int error;
  char sbuf[NI_MAXSERV];
  char *sbufptr = NULL;
  char addrbuf[128];
  int pf;
  struct SessionHandle *data = conn->data;

  *waitp = 0; /* synchronous response only */

  /*
   * Check if a limited name resolve has been requested.
   */
  switch(data->set.ip_version) {
  case CURL_IPRESOLVE_V4:
    pf = PF_INET;
    break;
  case CURL_IPRESOLVE_V6:
    pf = PF_INET6;
    break;
  default:
    pf = PF_UNSPEC;
    break;
  }

  if (pf != PF_INET) {
    /* see if we have an IPv6 stack */
    curl_socket_t s = socket(PF_INET6, SOCK_DGRAM, 0);
    if(s == CURL_SOCKET_BAD) {
      /* Some non-IPv6 stacks have been found to make very slow name resolves
       * when PF_UNSPEC is used, so thus we switch to a mere PF_INET lookup if
       * the stack seems to be a non-ipv6 one. */

      pf = PF_INET;
    }
    else {
      /* This seems to be an IPv6-capable stack, use PF_UNSPEC for the widest
       * possible checks. And close the socket again.
       */
      sclose(s);
    }
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = pf;
  hints.ai_socktype = conn->socktype;

  if((1 == Curl_inet_pton(AF_INET, hostname, addrbuf)) ||
     (1 == Curl_inet_pton(AF_INET6, hostname, addrbuf))) {
    /* the given address is numerical only, prevent a reverse lookup */
    hints.ai_flags = AI_NUMERICHOST;
  }
#ifdef HAVE_GSSAPI
  if(conn->data->set.krb)
    /* if krb is used, we (might) need the canonical host name */
    hints.ai_flags |= AI_CANONNAME;
#endif

  if(port) {
    snprintf(sbuf, sizeof(sbuf), "%d", port);
    sbufptr=sbuf;
  }
  error = Curl_getaddrinfo_ex(hostname, sbufptr, &hints, &res);
  if(error) {
    infof(data, "getaddrinfo(3) failed for %s:%d\n", hostname, port);
    return NULL;
  }

  dump_addrinfo(conn, res);

  return res;
}