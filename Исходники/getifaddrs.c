static void copy_addr(struct sockaddr** r,
                      int af,
                      union sockany* sa,
                      void* addr,
                      size_t addrlen,
                      int ifindex) {
  uint8_t* dst;
  int len;

  switch (af) {
    case AF_INET:
      dst = (uint8_t*)&sa->v4.sin_addr;
      len = 4;
      break;
    case AF_INET6:
      dst = (uint8_t*)&sa->v6.sin6_addr;
      len = 16;
      if (IN6_IS_ADDR_LINKLOCAL(addr) || IN6_IS_ADDR_MC_LINKLOCAL(addr))
        sa->v6.sin6_scope_id = ifindex;
      break;
    default:
      return;
  }
  if (addrlen < len)
    return;
  sa->sa.sa_family = af;
  memcpy(dst, addr, len);
  *r = &sa->sa;
}