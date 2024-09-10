static inline bool
mroute_is_mcast (const in_addr_t addr)
{
  return ((addr & htonl(IP_MCAST_SUBNET_MASK)) == htonl(IP_MCAST_NETWORK));
}