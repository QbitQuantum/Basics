static void
browse_record_callback_v6(AvahiRecordBrowser *b, AvahiIfIndex intf, AvahiProtocol proto,
			  AvahiBrowserEvent event, const char *hostname, uint16_t clazz, uint16_t type,
			  const void *rdata, size_t size, AvahiLookupResultFlags flags, void *userdata)
{
  char address[INET6_ADDRSTRLEN + IF_NAMESIZE + 1];
  char ifname[IF_NAMESIZE];
  struct in6_addr addr;
  struct mdns_record_browser *rb_data;
  int ll;
  int len;
  int ret;

  rb_data = (struct mdns_record_browser *)userdata;

  switch (event)
    {
      case AVAHI_BROWSER_NEW:
	if (size != sizeof(addr.s6_addr))
	  {
	    DPRINTF(E_WARN, L_MDNS, "Got RR type AAAA size %ld (should be %ld)\n", (long)size, (long)sizeof(addr.s6_addr));

	    return;
	  }

	memcpy(&addr.s6_addr, rdata, sizeof(addr.s6_addr));

	ll = is_v6ll(&addr);
	if (ll && !(rb_data->mb->flags & MDNS_WANT_V6LL))
	  {
	    DPRINTF(E_DBG, L_MDNS, "Discarding IPv6 LL, not interested (service %s)\n", rb_data->name);
	    return;
	  }
	else if (!ll && !(rb_data->mb->flags & MDNS_WANT_V6))
	  {
	    DPRINTF(E_DBG, L_MDNS, "Discarding IPv6, not interested (service %s)\n", rb_data->name);
	    return;
	  }

	if (!inet_ntop(AF_INET6, &addr.s6_addr, address, sizeof(address)))
	  {
	    DPRINTF(E_LOG, L_MDNS, "Could not print IPv6 address: %s\n", strerror(errno));

	    return;
	  }

	if (ll)
	  {
	    if (!if_indextoname(intf, ifname))
	      {
		DPRINTF(E_LOG, L_MDNS, "Could not map interface index %d to a name\n", intf);

		return;
	      }

	    len = strlen(address);
	    ret = snprintf(address + len, sizeof(address) - len, "%%%s", ifname);
	    if ((ret < 0) || (ret > sizeof(address) - len))
	      {
		DPRINTF(E_LOG, L_MDNS, "Buffer too short for scoped IPv6 LL\n");

		return;
	      }
	  }

	DPRINTF(E_DBG, L_MDNS, "Service %s, hostname %s resolved to %s\n", rb_data->name, hostname, address);

	/* Execute callback (mb->cb) with all the data */
	rb_data->mb->cb(rb_data->name, rb_data->mb->type, rb_data->domain, hostname, AF_INET6, address, rb_data->port, &rb_data->txt_kv);
	/* Got a suitable address, stop record browser */
	break;

      case AVAHI_BROWSER_REMOVE:
	/* Not handled - record browser lifetime too short for this to happen */
	return;

      case AVAHI_BROWSER_CACHE_EXHAUSTED:
      case AVAHI_BROWSER_ALL_FOR_NOW:
	DPRINTF(E_DBG, L_MDNS, "Avahi Record Browser (%s v6): no more results (%s)\n", hostname,
		(event == AVAHI_BROWSER_CACHE_EXHAUSTED) ? "CACHE_EXHAUSTED" : "ALL_FOR_NOW");	

	break;

      case AVAHI_BROWSER_FAILURE:
	DPRINTF(E_LOG, L_MDNS, "Avahi Record Browser (%s v6) failure: %s\n", hostname,
		avahi_strerror(avahi_client_errno(avahi_record_browser_get_client(b))));

	break;
    }

  /* Cleanup when done/error */
  keyval_clear(&rb_data->txt_kv);      
  free(rb_data->name);
  free(rb_data->domain);
  free(rb_data);

  avahi_record_browser_free(b);
}