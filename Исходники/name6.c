struct hostent *
getipnodebyaddr(const void *src, size_t len, int af, int *errp)
{
	struct hostent *hp;
	int rval;
#ifdef INET6
	struct in6_addr addrbuf;
#else
	struct in_addr addrbuf;
#endif

	static const ns_dtab dtab[] = {
		NS_FILES_CB(_files_ghbyaddr, NULL)
		{ NSSRC_DNS, _dns_ghbyaddr, NULL },
		NS_NIS_CB(_nis_ghbyaddr, NULL)
#ifdef ICMPNL
		{ NSSRC_ICMP, _icmp_ghbyaddr, NULL },
#endif
		{ 0 }
	};

	*errp = HOST_NOT_FOUND;

	switch (af) {
	case AF_INET:
		if (len != sizeof(struct in_addr)) {
			*errp = NO_RECOVERY;
			return NULL;
		}
		if ((long)src & ~(sizeof(struct in_addr) - 1)) {
			memcpy(&addrbuf, src, len);
			src = &addrbuf;
		}
		if (((struct in_addr *)src)->s_addr == 0)
			return NULL;
		break;
#ifdef INET6
	case AF_INET6:
		if (len != sizeof(struct in6_addr)) {
			*errp = NO_RECOVERY;
			return NULL;
		}
		if ((long)src & ~(sizeof(struct in6_addr) / 2 - 1)) {	/*XXX*/
			memcpy(&addrbuf, src, len);
			src = &addrbuf;
		}
		if (IN6_IS_ADDR_UNSPECIFIED((struct in6_addr *)src))
			return NULL;
		if (IN6_IS_ADDR_V4MAPPED((struct in6_addr *)src)
		||  IN6_IS_ADDR_V4COMPAT((struct in6_addr *)src)) {
			src = (char *)src +
			    (sizeof(struct in6_addr) - sizeof(struct in_addr));
			af = AF_INET;
			len = sizeof(struct in_addr);
		}
		break;
#endif
	default:
		*errp = NO_RECOVERY;
		return NULL;
	}

	rval = nsdispatch(&hp, dtab, NSDB_HOSTS, "ghbyaddr", default_src,
			  src, len, af, errp);
	return (rval == NS_SUCCESS) ? hp : NULL;
}