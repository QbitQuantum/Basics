int scamper_addr2mac_add(int ifindex, scamper_addr_t *ip, scamper_addr_t *mac)
{
  addr2mac_t *a2m = NULL;
  char ipstr[128], macstr[128];

  if(scamper_addr2mac_whohas(ifindex, ip) != NULL)
    return 0;

  if((a2m = addr2mac_alloc(ifindex, ip, mac, 0)) == NULL)
    return -1;

  if(splaytree_insert(tree, a2m) == NULL)
    {
      printerror(errno, strerror, __func__, "could not add %s:%s to tree",
		 scamper_addr_tostr(a2m->ip, ipstr, sizeof(ipstr)),
		 scamper_addr_tostr(a2m->mac, macstr, sizeof(macstr)));
      addr2mac_free(a2m);
      return -1;
    }

  scamper_debug(__func__, "ifindex %d ip %s mac %s", ifindex,
		scamper_addr_tostr(a2m->ip, ipstr, sizeof(ipstr)),
		scamper_addr_tostr(a2m->mac, macstr, sizeof(macstr)));
  return 0;
}