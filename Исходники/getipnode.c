/*% performs a reverse lookup of address src which is len bytes long. af denotes the protocol family, typically #PF_INET or PF_INET6. */
struct hostent *
lwres_getipnodebyaddr(const void *src, size_t len, int af, int *error_num) {
	struct hostent *he1, *he2;
	lwres_context_t *lwrctx = NULL;
	lwres_gnbaresponse_t *by = NULL;
	lwres_result_t n;
	union {
		const void *konst;
		struct in6_addr *in6;
	} u;

	/*
	 * Sanity checks.
	 */
	if (src == NULL) {
		*error_num = NO_RECOVERY;
		return (NULL);
	}

	switch (af) {
	case AF_INET:
		if (len != (unsigned int)INADDRSZ) {
			*error_num = NO_RECOVERY;
			return (NULL);
		}
		break;
	case AF_INET6:
		if (len != (unsigned int)IN6ADDRSZ) {
			*error_num = NO_RECOVERY;
			return (NULL);
		}
		break;
	default:
		*error_num = NO_RECOVERY;
		return (NULL);
	}

	/*
	 * The de-"const"-ing game is done because at least one
	 * vendor's system (RedHat 6.0) defines the IN6_IS_ADDR_*
	 * macros in such a way that they discard the const with
	 * internal casting, and gcc ends up complaining.  Rather
	 * than replacing their own (possibly optimized) definitions
	 * with our own, cleanly discarding the const is the easiest
	 * thing to do.
	 */
	u.konst = src;

	/*
	 * Look up IPv4 and IPv4 mapped/compatible addresses.
	 */
	if ((af == AF_INET6 && IN6_IS_ADDR_V4COMPAT(u.in6)) ||
	    (af == AF_INET6 && IN6_IS_ADDR_V4MAPPED(u.in6)) ||
	    (af == AF_INET)) {
		const unsigned char *cp = src;

		if (af == AF_INET6)
			cp += 12;
		n = lwres_context_create(&lwrctx, NULL, NULL, NULL, 0);
		if (n == LWRES_R_SUCCESS)
			(void) lwres_conf_parse(lwrctx, lwres_resolv_conf);
		if (n == LWRES_R_SUCCESS)
			n = lwres_getnamebyaddr(lwrctx, LWRES_ADDRTYPE_V4,
						INADDRSZ, cp, &by);
		if (n != LWRES_R_SUCCESS) {
			lwres_conf_clear(lwrctx);
			lwres_context_destroy(&lwrctx);
			if (n == LWRES_R_NOTFOUND)
				*error_num = HOST_NOT_FOUND;
			else
				*error_num = NO_RECOVERY;
			return (NULL);
		}
		he1 = hostfromaddr(by, AF_INET, cp);
		lwres_gnbaresponse_free(lwrctx, &by);
		lwres_conf_clear(lwrctx);
		lwres_context_destroy(&lwrctx);
		if (af != AF_INET6)
			return (he1);

		/*
		 * Convert from AF_INET to AF_INET6.
		 */
		he2 = copyandmerge(he1, NULL, af, error_num);
		lwres_freehostent(he1);
		if (he2 == NULL)
			return (NULL);
		/*
		 * Restore original address.
		 */
		memcpy(he2->h_addr, src, len);
		return (he2);
	}

	/*
	 * Lookup IPv6 address.
	 */
	if (memcmp(src, &in6addr_any, IN6ADDRSZ) == 0) {
		*error_num = HOST_NOT_FOUND;
		return (NULL);
	}

	n = lwres_context_create(&lwrctx, NULL, NULL, NULL, 0);
	if (n == LWRES_R_SUCCESS)
		(void) lwres_conf_parse(lwrctx, lwres_resolv_conf);
	if (n == LWRES_R_SUCCESS)
		n = lwres_getnamebyaddr(lwrctx, LWRES_ADDRTYPE_V6, IN6ADDRSZ,
					src, &by);
	if (n != 0) {
		lwres_conf_clear(lwrctx);
		lwres_context_destroy(&lwrctx);

		if (n == LWRES_R_NOTFOUND)
		       *error_num = HOST_NOT_FOUND;
		else
		       *error_num = NO_RECOVERY;

		return (NULL);
	}

	he1 = hostfromaddr(by, AF_INET6, src);
	lwres_gnbaresponse_free(lwrctx, &by);
	if (he1 == NULL)
		*error_num = NO_RECOVERY;
	lwres_conf_clear(lwrctx);
	lwres_context_destroy(&lwrctx);
	return (he1);
}