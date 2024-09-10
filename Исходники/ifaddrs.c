static struct sockaddr *
ifa_make_sockaddr_mask (sa_family_t family,
			struct sockaddr *sa, uint32_t prefixlen)
{
  int i;
  char *p = NULL, c;
  uint32_t max_prefixlen = 0;

  if (sa == NULL)
    return NULL;
  switch (family)
    {
    case AF_INET:
      memset (&((struct sockaddr_in *) sa)->sin_addr, 0,
	      sizeof (((struct sockaddr_in *) sa)->sin_addr));
      p = (char *) &((struct sockaddr_in *) sa)->sin_addr;
      max_prefixlen = 32;
      break;
    case AF_INET6:
      memset (&((struct sockaddr_in6 *) sa)->sin6_addr, 0,
	      sizeof (((struct sockaddr_in6 *) sa)->sin6_addr));
      p = (char *) &((struct sockaddr_in6 *) sa)->sin6_addr;
#if 0				/* XXX: fill scope-id? */
      if (IN6_IS_ADDR_LINKLOCAL (p) || IN6_IS_ADDR_MC_LINKLOCAL (p))
	{
	  ((struct sockaddr_in6 *) sa)->sin6_scope_id = scopeid;
	}
#endif
      max_prefixlen = 128;
      break;
    default:
      return NULL;
    }
  sa->sa_family = family;
#ifdef HAVE_SOCKADDR_SA_LEN
  sa->sa_len = ifa_sa_len (family, len);
#endif
  if (p)
    {
      if (prefixlen > max_prefixlen)
	prefixlen = max_prefixlen;
      for (i = 0; i < (prefixlen / 8); i++)
	*p++ = 0xff;
      c = 0xff;
      c <<= (8 - (prefixlen % 8));
      *p = c;
    }
  return sa;
}