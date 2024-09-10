const char *
ACE_INET_Addr::get_host_addr (char *dst, int size) const
{
#if defined (ACE_HAS_IPV6)
  if (this->get_type () == AF_INET6)
    {
      // [email protected] - Aug-26, 2005
      // I don't think this should be done because it results in a decimal address
      // representation which is not distinguishable from the IPv4 form which makes
      // it impossible to resolve back to an IPv6 INET_Addr without prior knowledge
      // that this was such an address to begin with.

      //if (IN6_IS_ADDR_V4MAPPED (&this->inet_addr_.in6_.sin6_addr))
      //{
      //  ACE_UINT32 addr;
      //  addr = this->get_ip_address();
      //  addr = ACE_HTONL (addr);
      //  return ACE_OS::inet_ntop (AF_INET, &addr, dst, size);
      //}

#  if defined (ACE_WIN32)
      if (0 == ::getnameinfo (reinterpret_cast<const sockaddr*> (&this->inet_addr_.in6_),
                              this->get_size (),
                              dst,
                              size,
                              0, 0,    // Don't want service name
                              NI_NUMERICHOST))
        return dst;
      ACE_OS::set_errno_to_wsa_last_error ();
      return 0;
#  else
      const char *ch = ACE_OS::inet_ntop (AF_INET6,
                                          &this->inet_addr_.in6_.sin6_addr,
                                          dst,
                                          size);
#if defined (__linux__)
      if ((IN6_IS_ADDR_LINKLOCAL (&this->inet_addr_.in6_.sin6_addr) ||
           IN6_IS_ADDR_MC_LINKLOCAL (&this->inet_addr_.in6_.sin6_addr)) &&
          this->inet_addr_.in6_.sin6_scope_id != 0)
        {
          char scope_buf[32];
          ACE_OS::sprintf (scope_buf, "%%%u", this->inet_addr_.in6_.sin6_scope_id);
          if ((ACE_OS::strlen (ch)+ACE_OS::strlen (scope_buf)) < (size_t)size)
            {
              ACE_OS::strcat (dst, scope_buf);
            }
        }
#endif
      return ch;
#  endif /* ACE_WIN32 */
    }
#endif /* ACE_HAS_IPV6 */

  return ACE_OS::inet_ntop (AF_INET,
          &this->inet_addr_.in4_.sin_addr,
          dst,
          size);
}