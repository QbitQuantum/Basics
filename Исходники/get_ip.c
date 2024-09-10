struct hostent * W32_CALL
getipnodebyaddr (const void *src, size_t len, int af, int *error)
{
  struct hostent *he1, *he2;
  const  BYTE *cp = (const BYTE*) src;

  SOCK_DEBUGF (("\ngetipnodebyaddr: "));

  if (!src)
  {
    *error = NO_RECOVERY;
    return (NULL);
  }

  switch (af)
  {
    case AF_INET:
         if (len < INADDRSZ)
         {
           *error = NO_RECOVERY;
           return (NULL);
         }
         break;
#if defined(USE_IPV6)
    case AF_INET6:
         if (len < IN6ADDRSZ)
         {
           *error = NO_RECOVERY;
           return (NULL);
         }
         break;
#endif
    default:
         *error = NO_RECOVERY;
         return (NULL);
  }

  /* Look up IPv4 and IPv4 mapped/compatible addresses.
   */
  if ((af == AF_INET6 && IN6_IS_ADDR_V4COMPAT(cp)) ||
      (af == AF_INET6 && IN6_IS_ADDR_V4MAPPED(cp)) ||
      (af == AF_INET))
  {
    if (af == AF_INET6)
       cp += 12;

    SOCK_ENTER_SCOPE();
    he1 = gethostbyaddr ((const char*)cp, 4, AF_INET);
    SOCK_LEAVE_SCOPE();

    if (af == AF_INET)
       goto ret_copy;

    /* Convert from AF_INET to AF_INET6.
     */
    he2 = copyandmerge (he1, NULL, af, error);
    if (he2)
    {
      memcpy (he2->h_addr, src, len);  /* Restore original address */
      SOCK_DEBUGF (("%s", af == AF_INET ?
                    inet_ntoa(*(struct in_addr*)&he2->h_addr) :
                    _inet6_ntoa(he2->h_addr)));
    }
    return (he2);
  }

  he1 = gethostbyaddr (src, len, AF_INET6);   /* Lookup IPv6 address */

ret_copy:
  if (!he1)
  {
    *error = HOST_NOT_FOUND;
    return (NULL);
  }
  return copyandmerge (he1, NULL, af, error);
}