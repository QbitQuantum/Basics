static void mappedtov4(struct sockaddr *ss)
{
   struct sockaddr_in sin;
   struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)ss;

   debug(DEBUGLEVEL_INFO, "mappedtov4 %p\n", ss);

   if (ss->sa_family == AF_INET6 &&
         IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr) ) {
      memcpy(&sin.sin_addr, sin6->sin6_addr.s6_addr+12,
            sizeof(sin.sin_addr));
      sin.sin_port = ((struct sockaddr_in6 *)ss)->sin6_port;
      sin.sin_family = AF_INET;
#ifdef SIN6_LEN
      sin.sin_len = 16;
#endif
      memcpy(ss, &sin, sizeof(sin));
   }
}