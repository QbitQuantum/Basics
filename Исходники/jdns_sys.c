static jdns_dnsparams_t *dnsparams_get_winreg()
{
	int n;
	jdns_dnsparams_t *params;
	HKEY key;
	int ret;
	char sep;
	jdns_string_t *str_domain, *str_nameserver, *str_searchlist;
	jdns_stringlist_t *list_nameserver, *list_searchlist;

	sep = ' ';
	ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
		"System\\CurrentControlSet\\Services\\Tcpip\\Parameters",
		0, KEY_READ, &key);
	if(ret != ERROR_SUCCESS)
	{
		sep = ',';
		ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
			"System\\CurrentControlSet\\Services\\VxD\\MSTCP",
			0, KEY_READ, &key);
		if(ret != ERROR_SUCCESS)
			return 0;
	}

	str_domain = reg_readString(key, "DhcpDomain");
	if(!str_domain)
		str_domain = reg_readString(key, "Domain");
	str_nameserver = reg_readString(key, "DhcpNameServer");
	if(!str_nameserver)
		str_nameserver = reg_readString(key, "NameServer");
	str_searchlist = reg_readString(key, "SearchList");

	RegCloseKey(key);

	list_nameserver = 0;
	if(str_nameserver)
	{
		list_nameserver = string_split(str_nameserver, sep);
		jdns_string_delete(str_nameserver);
	}
	list_searchlist = 0;
	if(str_searchlist)
	{
		// lowercase the string
		jdns_string_t *p = string_tolower(str_searchlist);
		jdns_string_delete(str_searchlist);
		str_searchlist = p;

		list_searchlist = string_split(str_searchlist, sep);
		jdns_string_delete(str_searchlist);
	}

	params = jdns_dnsparams_new();
	if(list_nameserver)
	{
		// qt seems to do a strange thing here by running each name
		//   server address through the q3dns setLabel function, and
		//   then pulls the result as a list of addresses.  i have
		//   no idea why they do this, or how one IP address would
		//   turn into anything else, let alone several addresses.
		// so, uh, we're not going to do that.
		for(n = 0; n < list_nameserver->count; ++n)
		{
			jdns_address_t *addr = jdns_address_new();
			if(jdns_address_set_cstr(addr, (char *)list_nameserver->item[n]->data))
				jdns_dnsparams_append_nameserver(params, addr, JDNS_UNICAST_PORT);
			jdns_address_delete(addr);
		}
		jdns_stringlist_delete(list_nameserver);
	}
	if(str_domain)
	{
		if(str_domain->size > 0)
			jdns_dnsparams_append_domain(params, str_domain);
		jdns_string_delete(str_domain);
	}
	if(list_searchlist)
	{
		for(n = 0; n < list_searchlist->count; ++n)
		{
			if(list_searchlist->item[n]->size > 0)
				jdns_dnsparams_append_domain(params, list_searchlist->item[n]);
		}
		jdns_stringlist_delete(list_searchlist);
	}

	return params;
}