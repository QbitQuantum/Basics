int
rpki_validate_prefix(struct peer* peer, struct attr* attr,
    struct prefix *prefix)
{
  struct assegment* as_segment;
  as_t as_number = 0;
  struct ip_addr ip_addr_prefix;
  enum pfxv_state result;
  char buf[BUFSIZ];
  const char* prefix_string;

  if (!rpki_is_synchronized()
      || bgp_flag_check(peer->bgp, BGP_FLAG_VALIDATE_DISABLE))
    {
      return 0;
    }

  // No aspath means route comes from iBGP
  if (!attr->aspath || !attr->aspath->segments)
    {
      // Set own as number
      as_number = peer->bgp->as;
    }
  else
    {
      as_segment = attr->aspath->segments;
      // Find last AsSegment
      while (as_segment->next)
        {
          as_segment = as_segment->next;
        }
      if (as_segment->type == AS_SEQUENCE)
        {
          // Get rightmost asn
          as_number = as_segment->as[as_segment->length - 1];
        }
      else if (as_segment->type == AS_CONFED_SEQUENCE
          || as_segment->type == AS_CONFED_SET)
        {
          // Set own as number
          as_number = peer->bgp->as;
        }
      else
        {
          // RFC says: "Take distinguished value NONE as asn"
          // which means state is unknown
          return RPKI_NOTFOUND;
        }
    }

  // Get the prefix in requested format
  switch (prefix->family)
    {
    case AF_INET:
      ip_addr_prefix.ver = IPV4;
      ip_addr_prefix.u.addr4.addr = ntohl(prefix->u.prefix4.s_addr);
      break;

#ifdef HAVE_IPV6
    case AF_INET6:
      ip_addr_prefix.ver = IPV6;
      ipv6_addr_to_host_byte_order(prefix->u.prefix6.s6_addr32,
          ip_addr_prefix.u.addr6.addr);
      break;
#endif /* HAVE_IPV6 */

    default:
      return 0;
    }

  // Do the actual validation
  rtr_mgr_validate(rtr_config, as_number, &ip_addr_prefix, prefix->prefixlen,
      &result);

  // Print Debug output
  prefix_string = inet_ntop(prefix->family, &prefix->u.prefix, buf, BUFSIZ);
  switch (result)
    {
    case BGP_PFXV_STATE_VALID:
      RPKI_DEBUG("Validating Prefix %s/%hu from asn %u    Result: VALID",
          prefix_string, prefix->prefixlen, as_number)
      ;
      return RPKI_VALID;
    case BGP_PFXV_STATE_NOT_FOUND:
      RPKI_DEBUG("Validating Prefix %s/%hu from asn %u    Result: NOT FOUND",
          prefix_string, prefix->prefixlen, as_number)
      ;
      return RPKI_NOTFOUND;
    case BGP_PFXV_STATE_INVALID:
      RPKI_DEBUG("Validating Prefix %s/%hu from asn %u    Result: INVALID",
          prefix_string, prefix->prefixlen, as_number)
      ;
      return RPKI_INVALID;
    default:
      RPKI_DEBUG(
          "Validating Prefix %s/%hu from asn %u    Result: CANNOT VALIDATE",
          prefix_string, prefix->prefixlen, as_number)
      ;
      break;
    }
  return 0;
}