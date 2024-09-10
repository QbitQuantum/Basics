/*
 * Opening a UDP socket is a little more tricky, since
 * UDP works in a way which is different from TCP...
 *
 * Our goal is to hide this difference for the end-user
 */
tree_cell *
nasl_open_sock_udp (lex_ctxt * lexic)
{
  int soc;
  tree_cell *retc;
  int port;
  struct sockaddr_in soca;
  struct sockaddr_in6 soca6;
  struct arglist *script_infos = lexic->script_infos;
  struct in6_addr *ia;

  port = get_int_var_by_num (lexic, 0, -1);
  if (port < 0)
    return NULL;

  ia = plug_get_host_ip (script_infos);
  if (ia == NULL)
    return NULL;
  if (IN6_IS_ADDR_V4MAPPED (ia))
    {
      bzero (&soca, sizeof (soca));
      soca.sin_addr.s_addr = ia->s6_addr32[3];
      soca.sin_port = htons (port);
      soca.sin_family = AF_INET;

      soc = socket (AF_INET, SOCK_DGRAM, 0);
      openvas_source_set_socket (soc, 0, AF_INET);
      connect (soc, (struct sockaddr *) &soca, sizeof (soca));
    }
  else
    {
      bzero (&soca6, sizeof (soca6));
      memcpy (&soca6.sin6_addr, ia, sizeof (struct in6_addr));
      soca6.sin6_port = htons (port);
      soca6.sin6_family = AF_INET6;

      soc = socket (AF_INET6, SOCK_DGRAM, 0);
      openvas_source_set_socket (soc, 0, AF_INET6);
      connect (soc, (struct sockaddr *) &soca6, sizeof (soca6));
    }


  retc = alloc_tree_cell (0, NULL);
  retc->type = CONST_INT;
  retc->x.i_val = soc < 0 ? 0 : soc;
  return retc;
}