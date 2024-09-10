void mappedtov4(union sockunion *sa)
{
  struct sockaddr_in sin;
  struct sockaddr_in6 *sin6 = &sa->sa6;

  byte_zero(&sin, sizeof(sin));
  if (sin6->sin6_family == AF_INET6 &&
    IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr) ) {
      byte_copy(&sin.sin_addr, sizeof(sin.sin_addr), sin6->sin6_addr.s6_addr+12);
      sin.sin_port = sin6->sin6_port;
      sin.sin_family = AF_INET;
#ifdef HASSALEN
      sin.sin_len = sizeof(sin);
#endif
      byte_copy(&sa->sa4, sizeof(sin), &sin);
  }
}