struct hostent *
getipnodebyaddr(const void *src, size_t len, int af, int *error_num) {
	struct hostent *he1, *he2;
	struct net_data *net_data = init();

	/* Sanity Checks. */
	if (src == NULL) {
		*error_num = NO_RECOVERY;
		return (NULL);
	}
		
	switch (af) {
	case AF_INET:
		if (len != (size_t)INADDRSZ) {
			*error_num = NO_RECOVERY;
			return (NULL);
		}
		break;
	case AF_INET6:
		if (len != (size_t)IN6ADDRSZ) {
			*error_num = NO_RECOVERY;
			return (NULL);
		}
		break;
	default:
		*error_num = NO_RECOVERY;
		return (NULL);
	}

	/*
	 * Lookup IPv4 and IPv4 mapped/compatible addresses
	 */
	if ((af == AF_INET6 &&
	     IN6_IS_ADDR_V4COMPAT((const struct in6_addr *)src)) ||
	    (af == AF_INET6 &&
	     IN6_IS_ADDR_V4MAPPED((const struct in6_addr *)src)) ||
	    (af == AF_INET)) {
		const char *cp = src;

		if (af == AF_INET6)
			cp += 12;
		he1 = gethostbyaddr_p(cp, 4, AF_INET, net_data);
		if (he1 == NULL) {
			*error_num = net_data->res->res_h_errno;
			return (NULL);
		}
		he2 = copyandmerge(he1, NULL, af, error_num);
		if (he2 == NULL)
			return (NULL);
		/*
		 * Restore original address if mapped/compatible.
		 */
		if (af == AF_INET6)
			memcpy(he1->h_addr, src, len);
		return (he2);
	}

	/*
	 * Lookup IPv6 address.
	 */
	if (memcmp((const struct in6_addr *)src, &in6addr_any, 16) == 0) {
		*error_num = HOST_NOT_FOUND;
		return (NULL);
	}

	he1 = gethostbyaddr_p(src, 16, AF_INET6, net_data);
	if (he1 == NULL) {
		*error_num = net_data->res->res_h_errno;
		return (NULL);
	}
	return (copyandmerge(he1, NULL, af, error_num));
}