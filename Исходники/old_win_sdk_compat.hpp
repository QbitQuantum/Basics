inline int IN6_IS_ADDR_MC_GLOBAL(const in6_addr_emulation* a)
{
  return IN6_IS_ADDR_MULTICAST(a) && ((a->s6_addr[1] & 0xf) == 0xe);
}