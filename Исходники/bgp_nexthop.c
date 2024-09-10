/* If nexthop exists on connected network return 1. */
int
bgp_nexthop_onlink (afi_t afi, struct attr *attr)
{
  struct bgp_node *rn;
  
  /* If zebra is not enabled return */
  if (zlookup->sock < 0)
    return 1;
  
  /* Lookup the address is onlink or not. */
  if (afi == AFI_IP)
    {
      rn = bgp_node_match_ipv4 (bgp_connected_table[AFI_IP], &attr->nexthop);
      if (rn)
	{
	  bgp_unlock_node (rn);
	  return 1;
	}
    }
#ifdef HAVE_IPV6
  else if (afi == AFI_IP6)
    {
      if (attr->extra->mp_nexthop_len == 32)
	return 1;
      else if (attr->extra->mp_nexthop_len == 16)
	{
	  if (IN6_IS_ADDR_LINKLOCAL (&attr->extra->mp_nexthop_global))
	    return 1;

	  rn = bgp_node_match_ipv6 (bgp_connected_table[AFI_IP6],
				      &attr->extra->mp_nexthop_global);
	  if (rn)
	    {
	      bgp_unlock_node (rn);
	      return 1;
	    }
	}
    }
#endif /* HAVE_IPV6 */
  return 0;
}