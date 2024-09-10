static int
gaih_inet(const char *name, const struct gaih_service *service,
		const struct addrinfo *req, struct addrinfo **pai)
{
	struct gaih_servtuple nullserv;

	const struct gaih_typeproto *tp;
	struct gaih_servtuple *st;
	struct gaih_addrtuple *at;
	int rc;
	int v4mapped = (req->ai_family == PF_UNSPEC || req->ai_family == PF_INET6)
			&& (req->ai_flags & AI_V4MAPPED);
	unsigned seen = 0;
	if (req->ai_flags & AI_ADDRCONFIG) {
		/* "seen" is only used when AI_ADDRCONFIG is specified.
		   Avoid unnecessary call to __check_pf() otherwise
		   since it can be costly especially when RSBAC-Net is enabled.  */
		seen = __check_pf();
	}

	memset(&nullserv, 0, sizeof(nullserv));

	tp = gaih_inet_typeproto;
	if (req->ai_protocol || req->ai_socktype) {
		++tp;
		while (tp->name[0]) {
			if ((req->ai_socktype == 0 || req->ai_socktype == tp->socktype)
			 && (req->ai_protocol == 0 || req->ai_protocol == tp->protocol || (tp->protoflag & GAI_PROTO_PROTOANY))
			) {
				goto found;
			}
			++tp;
		}
		if (req->ai_socktype)
			return (GAIH_OKIFUNSPEC | -EAI_SOCKTYPE);
		return (GAIH_OKIFUNSPEC | -EAI_SERVICE);
 found: ;
	}

	st = &nullserv;
	if (service != NULL) {
		if ((tp->protoflag & GAI_PROTO_NOSERVICE) != 0)
			return (GAIH_OKIFUNSPEC | -EAI_SERVICE);

		if (service->num < 0) {
			if (tp->name[0]) {
				st = alloca(sizeof(struct gaih_servtuple));
				rc = gaih_inet_serv(service->name, tp, req, st);
				if (rc)
					return rc;
			} else {
				struct gaih_servtuple **pst = &st;
				for (tp++; tp->name[0]; tp++) {
					struct gaih_servtuple *newp;

					if ((tp->protoflag & GAI_PROTO_NOSERVICE) != 0)
						continue;

					if (req->ai_socktype != 0 && req->ai_socktype != tp->socktype)
						continue;
					if (req->ai_protocol != 0
					 && !(tp->protoflag & GAI_PROTO_PROTOANY)
					 && req->ai_protocol != tp->protocol)
						continue;

					newp = alloca(sizeof(struct gaih_servtuple));
					rc = gaih_inet_serv(service->name, tp, req, newp);
					if (rc) {
						if (rc & GAIH_OKIFUNSPEC)
							continue;
						return rc;
					}

					*pst = newp;
					pst = &(newp->next);
				}
				if (st == &nullserv)
					return (GAIH_OKIFUNSPEC | -EAI_SERVICE);
			}
		} else {
			st = alloca(sizeof(struct gaih_servtuple));
			st->next = NULL;
			st->socktype = tp->socktype;
			st->protocol = ((tp->protoflag & GAI_PROTO_PROTOANY)
					? req->ai_protocol : tp->protocol);
			st->port = htons(service->num);
		}
	} else if (req->ai_socktype || req->ai_protocol) {
		st = alloca(sizeof(struct gaih_servtuple));
		st->next = NULL;
		st->socktype = tp->socktype;
		st->protocol = ((tp->protoflag & GAI_PROTO_PROTOANY)
				? req->ai_protocol : tp->protocol);
		st->port = 0;
	} else {
		/*
		 * Neither socket type nor protocol is set.  Return all socket types
		 * we know about.
		 */
		struct gaih_servtuple **lastp = &st;
		for (++tp; tp->name[0]; ++tp) {
			struct gaih_servtuple *newp;

			newp = alloca(sizeof(struct gaih_servtuple));
			newp->next = NULL;
			newp->socktype = tp->socktype;
			newp->protocol = tp->protocol;
			newp->port = 0;

			*lastp = newp;
			lastp = &newp->next;
		}
	}

	at = NULL;
	if (name != NULL) {
		at = alloca(sizeof(struct gaih_addrtuple));
		at->family = AF_UNSPEC;
		at->scopeid = 0;
		at->next = NULL;

		if (inet_pton(AF_INET, name, at->addr) > 0) {
			if (req->ai_family != AF_UNSPEC && req->ai_family != AF_INET && !v4mapped)
				return -EAI_FAMILY;
			at->family = AF_INET;
		}

#if defined __UCLIBC_HAS_IPV6__
		if (at->family == AF_UNSPEC) {
			char *namebuf = strdupa(name);
			char *scope_delim;

			scope_delim = strchr(namebuf, SCOPE_DELIMITER);
			if (scope_delim != NULL)
				*scope_delim = '\0';

			if (inet_pton(AF_INET6, namebuf, at->addr) > 0) {
				if (req->ai_family != AF_UNSPEC && req->ai_family != AF_INET6)
					return -EAI_FAMILY;
				at->family = AF_INET6;
				if (scope_delim != NULL) {
					int try_numericscope = 0;
					uint32_t *a32 = (uint32_t*)at->addr;
					if (IN6_IS_ADDR_LINKLOCAL(a32) || IN6_IS_ADDR_MC_LINKLOCAL(at->addr)) {
						at->scopeid = if_nametoindex(scope_delim + 1);
						if (at->scopeid == 0)
							try_numericscope = 1;
					} else
						try_numericscope = 1;

					if (try_numericscope != 0) {
						char *end;
						assert(sizeof(uint32_t) <= sizeof(unsigned long));
						at->scopeid = (uint32_t)strtoul(scope_delim + 1, &end, 10);
						if (*end != '\0')
							return (GAIH_OKIFUNSPEC | -EAI_NONAME);
					}
				}
			}
		}
#endif

		if (at->family == AF_UNSPEC && !(req->ai_flags & AI_NUMERICHOST)) {
			struct hostent *h;
			struct gaih_addrtuple **pat = &at;
			int no_data = 0;
			int no_inet6_data;

			/*
			 * If we are looking for both IPv4 and IPv6 address we don't want
			 * the lookup functions to automatically promote IPv4 addresses to
			 * IPv6 addresses.
			 */
#if defined __UCLIBC_HAS_IPV6__
			if (req->ai_family == AF_UNSPEC || req->ai_family == AF_INET6)
				if (!(req->ai_flags & AI_ADDRCONFIG) || (seen & SEEN_IPV6))
					gethosts(AF_INET6, struct in6_addr);
#endif
			no_inet6_data = no_data;

			if (req->ai_family == AF_INET
			 || (!v4mapped && req->ai_family == AF_UNSPEC)
			 || (v4mapped && (no_inet6_data != 0 || (req->ai_flags & AI_ALL)))
			) {
				if (!(req->ai_flags & AI_ADDRCONFIG) || (seen & SEEN_IPV4))
					gethosts(AF_INET, struct in_addr);
			}

			if (no_data != 0 && no_inet6_data != 0) {
				/* If both requests timed out report this. */
				if (no_data == EAI_AGAIN && no_inet6_data == EAI_AGAIN)
					return -EAI_AGAIN;
				/*
				 * We made requests but they turned out no data.
				 * The name is known, though.
				 */
				return (GAIH_OKIFUNSPEC | -EAI_AGAIN);
			}
		}

		if (at->family == AF_UNSPEC)
			return (GAIH_OKIFUNSPEC | -EAI_NONAME);
	} else {
		struct gaih_addrtuple *atr;

		atr = at = alloca(sizeof(struct gaih_addrtuple));
		memset(at, '\0', sizeof(struct gaih_addrtuple));
		if (req->ai_family == 0) {
			at->next = alloca(sizeof(struct gaih_addrtuple));
			memset(at->next, '\0', sizeof(struct gaih_addrtuple));
		}
#if defined __UCLIBC_HAS_IPV6__
		if (req->ai_family == 0 || req->ai_family == AF_INET6) {
			at->family = AF_INET6;
			if ((req->ai_flags & AI_PASSIVE) == 0)
				memcpy(at->addr, &in6addr_loopback, sizeof(struct in6_addr));
			atr = at->next;
		}
#endif
		if (req->ai_family == 0 || req->ai_family == AF_INET) {
			atr->family = AF_INET;
			if ((req->ai_flags & AI_PASSIVE) == 0) {
				uint32_t *a = (uint32_t*)atr->addr;
				*a = htonl(INADDR_LOOPBACK);
			}
		}
	}

	if (pai == NULL)
		return 0;

	{
		const char *c = NULL;
		struct gaih_servtuple *st2;
		struct gaih_addrtuple *at2 = at;
		size_t socklen, namelen;
		sa_family_t family;

		/*
		 * buffer is the size of an unformatted IPv6 address in
		 * printable format.
		 */
		char buffer[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")];

		while (at2 != NULL) {
			c = inet_ntop(at2->family, at2->addr, buffer, sizeof(buffer));
			if (c) {
				namelen = strlen(c) + 1;
			} else if (req->ai_flags & AI_CANONNAME) {
				struct hostent *h = NULL;
				int herrno;
				struct hostent th;
				size_t tmpbuflen = 512;
				char *tmpbuf;

				/* Hint says numeric, but address is not */
				if (req->ai_flags & AI_NUMERICHOST)
					return -EAI_NONAME;

				do {
					tmpbuflen *= 2;
					tmpbuf = alloca(tmpbuflen);
					rc = gethostbyaddr_r(at2->addr,
#ifdef __UCLIBC_HAS_IPV6__
						((at2->family == AF_INET6)
						 ? sizeof(struct in6_addr)
						 : sizeof(struct in_addr)),
#else
						sizeof(struct in_addr),
#endif
						at2->family,
						&th, tmpbuf, tmpbuflen,
						&h, &herrno);
				} while (rc == ERANGE && herrno == NETDB_INTERNAL);

				if (rc != 0 && herrno == NETDB_INTERNAL) {
					__set_h_errno(herrno);
					return -EAI_SYSTEM;
				}

				if (h != NULL)
					c = h->h_name;

				if (c == NULL)
					return (GAIH_OKIFUNSPEC | -EAI_NONAME);

				namelen = strlen(c) + 1;
			} else
				namelen = 0;

#if defined __UCLIBC_HAS_IPV6__
			if (at2->family == AF_INET6 || v4mapped) {
				family = AF_INET6;
				socklen = sizeof(struct sockaddr_in6);
			}
#endif
#if defined __UCLIBC_HAS_IPV4__ && defined __UCLIBC_HAS_IPV6__
			else
#endif
#if defined __UCLIBC_HAS_IPV4__
			{
				family = AF_INET;
				socklen = sizeof(struct sockaddr_in);
			}
#endif
			for (st2 = st; st2 != NULL; st2 = st2->next) {
				if (req->ai_flags & AI_ADDRCONFIG) {
					if (family == AF_INET && !(seen & SEEN_IPV4))
						break;
#if defined __UCLIBC_HAS_IPV6__
					else if (family == AF_INET6 && !(seen & SEEN_IPV6))
						break;
#endif
				}
				*pai = malloc(sizeof(struct addrinfo) + socklen + namelen);
				if (*pai == NULL)
					return -EAI_MEMORY;

				(*pai)->ai_flags = req->ai_flags;
				(*pai)->ai_family = family;
				(*pai)->ai_socktype = st2->socktype;
				(*pai)->ai_protocol = st2->protocol;
				(*pai)->ai_addrlen = socklen;
				(*pai)->ai_addr = (void *) (*pai) + sizeof(struct addrinfo);
#if defined SALEN
				(*pai)->ai_addr->sa_len = socklen;
#endif
				(*pai)->ai_addr->sa_family = family;

#if defined __UCLIBC_HAS_IPV6__
				if (family == AF_INET6)	{
					struct sockaddr_in6 *sin6p = (struct sockaddr_in6 *) (*pai)->ai_addr;

					sin6p->sin6_flowinfo = 0;
					if (at2->family == AF_INET6) {
						memcpy(&sin6p->sin6_addr,
							at2->addr, sizeof(struct in6_addr));
					} else {
						sin6p->sin6_addr.s6_addr32[0] = 0;
						sin6p->sin6_addr.s6_addr32[1] = 0;
						sin6p->sin6_addr.s6_addr32[2] = htonl(0x0000ffff);
						memcpy(&sin6p->sin6_addr.s6_addr32[3],
							at2->addr, sizeof(sin6p->sin6_addr.s6_addr32[3]));
					}
					sin6p->sin6_port = st2->port;
					sin6p->sin6_scope_id = at2->scopeid;
				}
#endif
#if defined __UCLIBC_HAS_IPV4__ && defined __UCLIBC_HAS_IPV6__
				else
#endif
#if defined __UCLIBC_HAS_IPV4__
				{
					struct sockaddr_in *sinp = (struct sockaddr_in *) (*pai)->ai_addr;

					memcpy(&sinp->sin_addr, at2->addr, sizeof(struct in_addr));
					sinp->sin_port = st2->port;
					memset(sinp->sin_zero, '\0', sizeof(sinp->sin_zero));
				}
#endif
				if (c) {
					(*pai)->ai_canonname = ((void *) (*pai) +
							sizeof(struct addrinfo) + socklen);
					strcpy((*pai)->ai_canonname, c);
				} else {
					(*pai)->ai_canonname = NULL;
				}
				(*pai)->ai_next = NULL;
				pai = &((*pai)->ai_next);
			}

			at2 = at2->next;
		}
	}
	return 0;
}