/* Convert IPv4 compatible IPv6 address to IPv4 address. */
static void
sockunion_normalise_mapped (union sockunion *su)
{
  struct sockaddr_in sin;
  
#ifdef HAVE_IPV6
  if (su->sa.sa_family == AF_INET6 
      && IN6_IS_ADDR_V4MAPPED (&su->sin6.sin6_addr))
    {
      memset (&sin, 0, sizeof (struct sockaddr_in));
      sin.sin_family = AF_INET;
      sin.sin_port = su->sin6.sin6_port;
      memcpy (&sin.sin_addr, ((char *)&su->sin6.sin6_addr) + 12, 4);
      memcpy (su, &sin, sizeof (struct sockaddr_in));
    }
#endif /* HAVE_IPV6 */
}