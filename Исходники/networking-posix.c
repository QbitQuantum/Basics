int
mono_get_address_info (const char *hostname, int port, int flags, MonoAddressInfo **result)
{
	char service_name [16];
	struct addrinfo hints, *res = NULL, *info;
	MonoAddressEntry *cur = NULL, *prev = NULL;
	MonoAddressInfo *addr_info;
	int ret;

	memset (&hints, 0, sizeof (struct addrinfo));
	*result = NULL;

	hints.ai_family = PF_UNSPEC;
	if (flags & MONO_HINT_IPV4)
		hints.ai_family = PF_INET;
	else if (flags & MONO_HINT_IPV6)
		hints.ai_family = PF_INET6;

	hints.ai_socktype = SOCK_STREAM;

	if (flags & MONO_HINT_CANONICAL_NAME)
		hints.ai_flags = AI_CANONNAME;

/* Some ancient libc don't define AI_ADDRCONFIG */
#ifdef AI_ADDRCONFIG
	if (flags & MONO_HINT_CONFIGURED_ONLY)
		hints.ai_flags = AI_ADDRCONFIG;
#endif
	sprintf (service_name, "%d", port);

	MONO_ENTER_GC_SAFE;
	ret = getaddrinfo (hostname, service_name, &hints, &info);
	MONO_EXIT_GC_SAFE;

	if (ret)
		return 1; /* FIXME propagate the error */

	res = info;
	*result = addr_info = g_new0 (MonoAddressInfo, 1);

	while (res) {
		cur = g_new0 (MonoAddressEntry, 1);
		cur->family = res->ai_family;
		cur->socktype = res->ai_socktype;
		cur->protocol = res->ai_protocol;
		if (cur->family == PF_INET) {
			cur->address_len = sizeof (struct in_addr);
			cur->address.v4 = ((struct sockaddr_in*)res->ai_addr)->sin_addr;
		} else if (cur->family == PF_INET6) {
			cur->address_len = sizeof (struct in6_addr);
			cur->address.v6 = ((struct sockaddr_in6*)res->ai_addr)->sin6_addr;
		} else {
			g_warning ("Cannot handle address family %d", cur->family);
			res = res->ai_next;
			g_free (cur);
			continue;
		}

		if (res->ai_canonname)
			cur->canonical_name = g_strdup (res->ai_canonname);

		if (prev)
			prev->next = cur;
		else
			addr_info->entries = cur;
			
		prev = cur;
		res = res->ai_next;
	}

	freeaddrinfo (info);
	return 0;
}