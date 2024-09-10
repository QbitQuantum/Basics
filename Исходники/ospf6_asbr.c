void
ospf6_asbr_external_lsa_update (struct ospf6_route_req *request)
{
  char buffer [MAXLSASIZE];
  u_int16_t size;
  struct ospf6_lsa_as_external *external;
  char *p;
  struct ospf6_route_req route;
  char pbuf[BUFSIZ];

  /* assert this is best path; if not, return */
  ospf6_route_lookup (&route, &request->route.prefix, request->table);
  if (memcmp (&route.path, &request->path, sizeof (route.path)))
    return;

  if (IS_OSPF6_DUMP_LSA)
    zlog_info ("Update AS-External: ID: %lu",
               (u_long) ntohl (request->path.origin.id));

  /* prepare buffer */
  memset (buffer, 0, sizeof (buffer));
  size = sizeof (struct ospf6_lsa_as_external);
  external = (struct ospf6_lsa_as_external *) buffer;
  p = (char *) (external + 1);

  if (route.path.metric_type == 2)
    SET_FLAG (external->bits_metric, OSPF6_ASBR_BIT_E);   /* type2 */
  else
    UNSET_FLAG (external->bits_metric, OSPF6_ASBR_BIT_E); /* type1 */

  /* forwarding address */
  if (! IN6_IS_ADDR_UNSPECIFIED (&route.nexthop.address))
    SET_FLAG (external->bits_metric, OSPF6_ASBR_BIT_F);
  else
    UNSET_FLAG (external->bits_metric, OSPF6_ASBR_BIT_F);

  /* external route tag */
  UNSET_FLAG (external->bits_metric, OSPF6_ASBR_BIT_T);

  /* set metric. note: related to E bit */
  OSPF6_ASBR_METRIC_SET (external, route.path.cost);

  /* prefixlen */
  external->prefix.prefix_length = route.route.prefix.prefixlen;

  /* PrefixOptions */
  external->prefix.prefix_options = route.path.prefix_options;

  /* don't use refer LS-type */
  external->prefix.prefix_refer_lstype = htons (0);

  if (IS_OSPF6_DUMP_LSA)
    {
      prefix2str (&route.route.prefix, pbuf, sizeof (pbuf));
      zlog_info ("  Prefix: %s", pbuf);
    }

  /* set Prefix */
  memcpy (p, &route.route.prefix.u.prefix6,
          OSPF6_PREFIX_SPACE (route.route.prefix.prefixlen));
  ospf6_prefix_apply_mask (&external->prefix);
  size += OSPF6_PREFIX_SPACE (route.route.prefix.prefixlen);
  p += OSPF6_PREFIX_SPACE (route.route.prefix.prefixlen);

  /* Forwarding address */
  if (CHECK_FLAG (external->bits_metric, OSPF6_ASBR_BIT_F))
    {
      memcpy (p, &route.nexthop.address, sizeof (struct in6_addr));
      size += sizeof (struct in6_addr);
      p += sizeof (struct in6_addr);
    }

  /* External Route Tag */
  if (CHECK_FLAG (external->bits_metric, OSPF6_ASBR_BIT_T))
    {
      /* xxx */
    }

  ospf6_lsa_originate (htons (OSPF6_LSA_TYPE_AS_EXTERNAL),
                       route.path.origin.id, ospf6->router_id,
                       (char *) external, size, ospf6);
  return;
}