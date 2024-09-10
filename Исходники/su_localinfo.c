/** Build a list of local IPv6 addresses and append it to *return_result. */
static
int localinfo6(su_localinfo_t const *hints, su_localinfo_t **return_result)
{
  su_localinfo_t *li = NULL;
  su_sockaddr_t su[1] = {{ 0 }}, *addr;
  int error = ELI_NOADDRESS;
  char *canonname = NULL;
  char line[80];
  FILE *f;

  if ((f = fopen("/proc/net/if_inet6", "r"))) {
    for (;error;) {
      struct in6_addr in6;
      unsigned if_index, prefix_len, scope, flags;
      int addrlen, if_namelen;
      char ifname[16];

      if (!fgets(line, sizeof(line), f)) {
	if (feof(f))
	  error = ELI_NOERROR;
	break;
      }

      if (sscanf(line, "%08x%08x%08x%08x %2x %2x %2x %02x %016s\n",
		 &in6.s6_addr32[0],
		 &in6.s6_addr32[1],
		 &in6.s6_addr32[2],
		 &in6.s6_addr32[3],
		 &if_index, &prefix_len, &scope, &flags, ifname) != 9)
	break;

      flags = 0;

      /* Fix global scope (it is 0) */
      if (!scope) scope = LI_SCOPE_GLOBAL;

      in6.s6_addr32[0] = htonl(in6.s6_addr32[0]);
      in6.s6_addr32[1] = htonl(in6.s6_addr32[1]);
      in6.s6_addr32[2] = htonl(in6.s6_addr32[2]);
      in6.s6_addr32[3] = htonl(in6.s6_addr32[3]);

      if (IN6_IS_ADDR_V4MAPPED(&in6) || IN6_IS_ADDR_V4COMPAT(&in6)) {
	uint32_t ip4 = *(uint32_t *)(in6.s6_addr + 12);
	scope = li_scope4(ip4);
      }

      if ((hints->li_scope && (hints->li_scope & scope) == 0) ||
	  (hints->li_index && hints->li_index != if_index) ||
	  (hints->li_ifname && strcmp(hints->li_ifname, ifname) != 0))
	continue;

      su->su_family = AF_INET6;
      su->su_sin6.sin6_addr = in6;

      addrlen = su_sockaddr_size(su);

      if ((error = li_name(hints, 0, su, &canonname)) < 0)
	break;
      else if (error > 0)
	continue;
      else
	error = ELI_NOADDRESS;

      if (canonname &&
	  (strchr(canonname, ':') ||
	   strspn(canonname, "0123456789.") == strlen(canonname)))
	flags |= LI_NUMERIC;

      if (hints->li_flags & LI_IFNAME)
	if_namelen = strlen(ifname) + 1;
      else
	if_namelen = 0;

      if ((li = calloc(1, sizeof *li + addrlen + if_namelen)) == NULL) {
	error = ELI_MEMORY;
	break;
      }
      addr = (su_sockaddr_t*)memcpy((li + 1), su, addrlen);
      *return_result = li; return_result = &li->li_next;

      li->li_flags = flags;
      li->li_family = AF_INET6;
      li->li_scope = scope;
      li->li_index = if_index;
      li->li_addr = addr;
      li->li_addrlen = addrlen;
      li->li_canonname = canonname;
      if (if_namelen)
	li->li_ifname = memcpy(addrlen + (char *)addr, ifname, if_namelen);

      canonname = NULL;
    }

    fclose(f);
  }

  if (canonname)
    free(canonname);

  return error;
}