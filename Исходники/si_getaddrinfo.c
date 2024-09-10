/*
 * getnameinfo
 *
 * We handle some "trival" cases locally.  If the caller passes
 * NI_NUMERICHOST (only), then this call turns into a getservbyport
 * to get the service name + inet_pton() to create a host string.
 * If the caller passes NI_NUMERICSERV (only), then we zero out the port
 * number, complete the getnameinfo, and use printf() to create a service
 * string.  If the caller specifies both NI_NUMERICHOST and NI_NUMERICSERV,
 * we inet_ntop() and printf() and return the results.
 */
si_item_t *
si_nameinfo(si_mod_t *si, const struct sockaddr *sa, int flags, const char *interface, uint32_t *err)
{
	si_item_t *out = NULL;
	const struct sockaddr *lookup_sa;
	struct sockaddr_in s4;
	struct in_addr a4;
	struct in6_addr a6;
	const uint32_t unused = 0;
	void *addr = NULL;
	char *host = NULL;
	char *serv = NULL;
	uint32_t ifnum = 0;
	uint16_t port = 0;

	int do_host_lookup = ((flags & NI_NUMERICHOST) == 0);
	int do_serv_lookup = ((flags & NI_NUMERICSERV) == 0);

	/* check input */
	if ((si == NULL) || (sa == NULL))
	{
		if (err != NULL) *err = SI_STATUS_EAI_FAIL;
		return NULL;
	}

	if (err != NULL) *err = SI_STATUS_NO_ERROR;

	lookup_sa = sa;

	if (sa->sa_family == AF_INET)
	{
		struct sockaddr_in *s4 = (struct sockaddr_in *)sa;
		memcpy(&a4, &s4->sin_addr, sizeof(a4));
		port = s4->sin_port;
		addr = &a4;
	}
	else if (sa->sa_family == AF_INET6)
	{
		struct sockaddr_in6 *s6 = (struct sockaddr_in6 *)sa;
		memcpy(&a6, &s6->sin6_addr, sizeof(a6));
		port = s6->sin6_port;

		/* Look for scope id in IPv6 Link Local, Multicast Node Local, and Multicast Link Local */
		if (IN6_IS_ADDR_LINKLOCAL(&s6->sin6_addr) || IN6_IS_ADDR_MC_NODELOCAL(&s6->sin6_addr) || IN6_IS_ADDR_MC_LINKLOCAL(&s6->sin6_addr))
		{
			ifnum = ntohs(a6.__u6_addr.__u6_addr16[1]);
			if (ifnum == 0)
			{
				ifnum = s6->sin6_scope_id;
				a6.__u6_addr.__u6_addr16[1] = htons(ifnum);
			}

			if ((ifnum != s6->sin6_scope_id) && (s6->sin6_scope_id != 0))
			{
				if (err != NULL) *err = SI_STATUS_EAI_FAIL;
				return NULL;
			}
		}

		/* v4 mapped and compat addresses are converted to plain v4 */
		if (IN6_IS_ADDR_V4MAPPED(&s6->sin6_addr) || IN6_IS_ADDR_V4COMPAT(&s6->sin6_addr))
		{
			memcpy(&a4, &s6->sin6_addr.s6_addr[12], sizeof(a4));
			addr = &a4;
			memset(&s4, 0, sizeof(s4));
			s4.sin_len = sizeof(s4);
			s4.sin_family = AF_INET;
			s4.sin_port = port;
			memcpy(&s4.sin_addr, &a4, sizeof(s4.sin_addr));
			lookup_sa = (const struct sockaddr *)&s4;
		}
		else
		{
			addr = &a6;
		}
	}
	else
	{
		if (err != NULL) *err = SI_STATUS_EAI_FAMILY;
		return NULL;
	}

	if (do_host_lookup == 1)
	{
		si_item_t *item = si_host_byaddr(si, addr, lookup_sa->sa_family, interface, NULL);
		if (item != NULL)
		{
			struct hostent *h;
			h = (struct hostent *)((uintptr_t)item + sizeof(si_item_t));
			host = strdup(h->h_name);
			si_item_release(item);
			if (host == NULL)
			{
				if (err != NULL) *err = SI_STATUS_EAI_MEMORY;
				return NULL;
			}
		}
	}

	if ((do_serv_lookup == 1) && (port != 0))
	{
		si_item_t *item = si_service_byport(si, port, NULL);
		if (item != NULL)
		{
			struct servent *s;
			s = (struct servent *)((uintptr_t)item + sizeof(si_item_t));
			serv = strdup(s->s_name);
			si_item_release(item);
			if (serv == NULL)
			{
				free(host);
				if (err != NULL) *err = SI_STATUS_EAI_MEMORY;
				return NULL;
			}
		}
	}

	/*
	 * Return numeric host name for NI_NUMERICHOST or if lookup failed, but not
	 * if NI_NAMEREQD is specified (so that we later fail with EAI_NONAME).
	 */
	if ((host == NULL) && ((flags & NI_NAMEREQD) == 0))
	{
		char tmp[INET6_ADDRSTRLEN + 1 + IF_NAMESIZE + 1];
		tmp[0] = '\0';
		if (sa->sa_family == AF_INET)
		{
			char buf[INET_ADDRSTRLEN];
			if (inet_ntop(AF_INET, &a4, buf, sizeof(buf)) != 0)
			{
				host = strdup(buf);
			}
		}
		else if (sa->sa_family == AF_INET6)
		{
			char buf[INET6_ADDRSTRLEN];

			/* zero the embedded scope ID */
			if (ifnum != 0)
			{
				a6.__u6_addr.__u6_addr16[1] = 0;
			}

			if (inet_ntop(AF_INET6, &a6, buf, sizeof(buf)) != 0)
			{
				if (ifnum != 0)
				{
					char ifname[IF_NAMESIZE];
					if (if_indextoname(ifnum, ifname) != NULL)
					{
						asprintf(&host, "%s%%%s", buf, ifname);
					}
					else
					{
						/* ENXIO */
						if (err != NULL) *err = SI_STATUS_EAI_FAIL;
						return NULL;
					}
				}
				else
				{
					host = strdup(buf);
				}
			}
		}
	}

	/* Return numeric service name for NI_NUMERICSERV or if lookup failed. */
	if (serv == NULL)
	{
		asprintf(&serv, "%hu", ntohs(port));
	}

	if ((host == NULL) || (serv == NULL))
	{
		if (err != NULL)
		{
			if ((flags & NI_NAMEREQD) != 0)
			{
				*err = SI_STATUS_EAI_NONAME;
			}
			else
			{
				*err = SI_STATUS_EAI_MEMORY;
			}
		}
	}
	else
	{
		out = (si_item_t *)LI_ils_create("L4444ss", (unsigned long)si, CATEGORY_NAMEINFO, 1, unused, unused, host, serv);
	}

	free(host);
	free(serv);
	return out;
}