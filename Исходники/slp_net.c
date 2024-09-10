/** Determines the IPv6 scope of a specified address.
 *
 * @param[in] v6Addr - The IPv6 address to be checked.
 *
 * @return The ipv6 scope of the address.
 *
 * @remarks The @p v6Addr parameter must be pointer to a 16-byte IPv6 
 *    address in binary form.
 * 
 * @internal
 */
static int setScopeFromAddress(const struct in6_addr * v6Addr)
{
   if (IN6_IS_ADDR_MULTICAST(v6Addr))
   {
      if (IN6_IS_ADDR_MC_GLOBAL(v6Addr))
         return SLP_SCOPE_GLOBAL;

      if (IN6_IS_ADDR_MC_ORGLOCAL(v6Addr))
         return SLP_SCOPE_ORG_LOCAL;

      if (IN6_IS_ADDR_MC_SITELOCAL(v6Addr))
         return SLP_SCOPE_SITE_LOCAL;

      if (IN6_IS_ADDR_MC_NODELOCAL(v6Addr))
         return SLP_SCOPE_NODE_LOCAL;

      if (IN6_IS_ADDR_MC_LINKLOCAL(v6Addr))
         return SLP_SCOPE_LINK_LOCAL;
   }
   if (IN6_IS_ADDR_SITELOCAL(v6Addr))
      return SLP_SCOPE_SITE_LOCAL;

   if (SLP_IN6_IS_ADDR_LOOPBACK(v6Addr))
      return SLP_SCOPE_NODE_LOCAL;

   if (IN6_IS_ADDR_LINKLOCAL(v6Addr))
      return SLP_SCOPE_LINK_LOCAL;

   return 0;
}