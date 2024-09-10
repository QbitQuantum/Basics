static struct in6_addr *
ospf6_interface_get_linklocal_address (struct interface *ifp)
{
  struct listnode *n;
  struct connected *c;
  struct in6_addr *l = (struct in6_addr *) NULL;

  /* for each connected address */
  for (ALL_LIST_ELEMENTS_RO (ifp->connected, n, c))
    {
      /* if family not AF_INET6, ignore */
      if (c->address->family != AF_INET6)
        continue;

      /* linklocal scope check */
      if (IN6_IS_ADDR_LINKLOCAL (&c->address->u.prefix6))
        l = &c->address->u.prefix6;
    }
  return l;
}