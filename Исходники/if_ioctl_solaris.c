struct connected *
if_lookup_linklocal (struct interface *ifp)
{
#ifdef HAVE_IPV6
  struct listnode *node;
  struct connected *ifc;

  if (ifp == NULL)
    return NULL;

  for (ALL_LIST_ELEMENTS_RO(ifp->connected, node, ifc))
    {
      if ((ifc->address->family == AF_INET6) &&
          (IN6_IS_ADDR_LINKLOCAL (&ifc->address->u.prefix6)))
        return ifc;
    }
#endif /* HAVE_IPV6 */

  return NULL;
}