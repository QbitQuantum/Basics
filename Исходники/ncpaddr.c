static void
adjust_linklocal(struct sockaddr_in6 *sin6)
{
    /* XXX: ?????!?!?!!!!!  This is horrible ! */
    /*
     * The kernel does not understand sin6_scope_id for routing at this moment.
     * We should rather keep the embedded ID.
     * [email protected], 20011026
     */
    if (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr) ||
        IN6_IS_ADDR_MC_LINKLOCAL(&sin6->sin6_addr)) {
      sin6->sin6_scope_id =
        ntohs(*(u_short *)&sin6->sin6_addr.s6_addr[2]);
      *(u_short *)&sin6->sin6_addr.s6_addr[2] = 0;
    }
}