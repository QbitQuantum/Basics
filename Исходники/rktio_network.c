rktio_addrinfo_lookup_t *rktio_start_addrinfo_lookup(rktio_t *rktio,
                                                     const char *hostname, int portno,
                                                     int family, int passive, int tcp)
{
  rktio_addrinfo_lookup_t *lookup;
  char buf[32], *service;
  struct rktio_addrinfo_t *hints;

  if (portno >= 0) {
    service = buf;
    sprintf(buf, "%d", portno);
  } else
    service = NULL;
  
  if (!hostname && !service) {
    set_racket_error(RKTIO_ERROR_HOST_AND_PORT_BOTH_UNSPECIFIED);
    return NULL;
  }

  hints = malloc(sizeof(rktio_addrinfo_t));
  memset(hints, 0, sizeof(struct rktio_addrinfo_t));
  RKTIO_AS_ADDRINFO(hints)->ai_family = ((family < 0) ? PF_UNSPEC : family);
  if (passive) {
    RKTIO_AS_ADDRINFO(hints)->ai_flags |= rktio_AI_PASSIVE;
  }
  if (tcp) {
    RKTIO_AS_ADDRINFO(hints)->ai_socktype = SOCK_STREAM;
# ifndef PROTOENT_IS_INT
    if (!proto) {
      proto = getprotobyname("tcp");
    }
# endif
    RKTIO_AS_ADDRINFO(hints)->ai_protocol= PROTO_P_PROTO;
  } else {
    RKTIO_AS_ADDRINFO(hints)->ai_socktype = SOCK_DGRAM;
  }

  lookup = malloc(sizeof(rktio_addrinfo_lookup_t));
  lookup->name = (hostname ? MSC_IZE(strdup)(hostname) : NULL);
  lookup->svc = (service ? MSC_IZE(strdup)(service) : NULL);
  lookup->hints = hints;
  init_lookup(lookup);
 
  return start_lookup(rktio, lookup);
}