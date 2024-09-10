/*******************************************************
  * Get the host name associated with an address.
  *****************************************************/
char *get_cached_nameinfo(const struct sockaddr_in  *sai)
  {
  return cache.getHostName(sai->sin_addr.s_addr);
  } /* END get_cached_nameinfo() */