/*
 * This is the IPv6 interface for "gethostbyaddr".
 */
struct hostent *
getipnodebyaddr(const void *src, size_t len, int type, int *error_num)
{
	struct in6_addr *addr6 = 0;
	struct in_addr *addr4 = 0;
	nss_XbyY_buf_t *buf = 0;
	nss_XbyY_buf_t *res = 0;
	struct netconfig *nconf;
	struct hostent *hp = 0;
	struct	nss_netdirbyaddr_in nssin;
	union	nss_netdirbyaddr_out nssout;
	int neterr;
	char tmpbuf[64];

	if (type == AF_INET6) {
		if ((addr6 = (struct in6_addr *)src) == NULL) {
			*error_num = HOST_NOT_FOUND;
			return (NULL);
		}
	} else if (type == AF_INET) {
		if ((addr4 = (struct in_addr *)src) == NULL) {
			*error_num = HOST_NOT_FOUND;
			return (NULL);
		}
	} else {
		*error_num = HOST_NOT_FOUND;
		return (NULL);
	}
	/*
	 * Specific case: query for "::"
	 */
	if (type == AF_INET6 && IN6_IS_ADDR_UNSPECIFIED(addr6)) {
		*error_num = HOST_NOT_FOUND;
		return (NULL);
	}
	/*
	 * Step 1: IPv4-mapped address  or IPv4 Compat
	 */
	if ((type == AF_INET6 && len == 16) &&
	    ((IN6_IS_ADDR_V4MAPPED(addr6)) ||
	    (IN6_IS_ADDR_V4COMPAT(addr6)))) {
		if ((buf = __IPv6_alloc(NSS_BUFLEN_IPNODES)) == 0) {
			*error_num = NO_RECOVERY;
			return (NULL);
		}
		if ((nconf = __rpc_getconfip("udp")) == NULL &&
		    (nconf = __rpc_getconfip("tcp")) == NULL) {
			*error_num = NO_RECOVERY;
			__IPv6_cleanup(buf);
			return (NULL);
		}
		nssin.op_t = NSS_HOST6;
		if (IN6_IS_ADDR_V4COMPAT(addr6)) {
			(void) memcpy(tmpbuf, addr6, sizeof (*addr6));
			tmpbuf[10] = 0xffU;
			tmpbuf[11] = 0xffU;
			nssin.arg.nss.host.addr = (const char *)tmpbuf;
		} else {
			nssin.arg.nss.host.addr = (const char *)addr6;
		}
		nssin.arg.nss.host.len = sizeof (struct in6_addr);
		nssin.arg.nss.host.type = AF_INET6;
		nssin.arg.nss.host.buf = buf->buffer;
		nssin.arg.nss.host.buflen = buf->buflen;

		nssout.nss.host.hent = buf->result;
		nssout.nss.host.herrno_p = error_num;
		/*
		 * We pass in nconf and let the implementation of the
		 * long-named func decide whether to use the switch based on
		 * nc_nlookups.
		 */
		neterr =
		    _get_hostserv_inetnetdir_byaddr(nconf, &nssin, &nssout);

		(void) freenetconfigent(nconf);
		if (neterr != ND_OK) {
			/* Failover case, try hosts db for v4 address */
			if (!gethostbyaddr_r(((char *)addr6) + 12,
			    sizeof (in_addr_t), AF_INET, buf->result,
			    buf->buffer, buf->buflen, error_num)) {
				__IPv6_cleanup(buf);
				return (NULL);
			}
			/* Found one, now format it into mapped/compat addr */
			if ((res = __IPv6_alloc(NSS_BUFLEN_IPNODES)) == 0) {
				__IPv6_cleanup(buf);
				*error_num = NO_RECOVERY;
				return (NULL);
			}
			/* Convert IPv4 to mapped/compat address w/name */
			hp = res->result;
			(void) __mapv4tov6(buf->result, 0, res,
			    IN6_IS_ADDR_V4MAPPED(addr6));
			__IPv6_cleanup(buf);
			free(res);
			return (hp);
		}
		/*
		 * At this point, we'll have a v4mapped hostent. If that's
		 * what was passed in, just return. If the request was a compat,
		 * twiggle the two bytes to make the mapped address a compat.
		 */
		hp = buf->result;
		if (IN6_IS_ADDR_V4COMPAT(addr6)) {
			/* LINTED pointer cast */
			addr6 = (struct in6_addr *)hp->h_addr_list[0];
			addr6->s6_addr[10] = 0;
			addr6->s6_addr[11] = 0;
		}
		free(buf);
		return (hp);
	}
	/*
	 * Step 2: AF_INET, v4 lookup. Since we're going to search the
	 * ipnodes (v6) path first, we need to treat this as a v4mapped
	 * address. nscd(1m) caches v4 from ipnodes as mapped v6's. The
	 * switch backend knows to lookup v4's (not v4mapped) from the
	 * name services.
	 */
	if (type == AF_INET) {
		struct in6_addr v4mapbuf;
		addr6 = &v4mapbuf;

		IN6_INADDR_TO_V4MAPPED(addr4, addr6);
		if ((nconf = __rpc_getconfip("udp")) == NULL &&
		    (nconf = __rpc_getconfip("tcp")) == NULL) {
			*error_num = NO_RECOVERY;
			return (NULL);
		}
		if ((buf = __IPv6_alloc(NSS_BUFLEN_IPNODES)) == 0) {
			*error_num = NO_RECOVERY;
			freenetconfigent(nconf);
			return (NULL);
		}
		nssin.op_t = NSS_HOST6;
		nssin.arg.nss.host.addr = (const char *)addr6;
		nssin.arg.nss.host.len = sizeof (struct in6_addr);
		nssin.arg.nss.host.type = AF_INET6;
		nssin.arg.nss.host.buf = buf->buffer;
		nssin.arg.nss.host.buflen = buf->buflen;

		nssout.nss.host.hent = buf->result;
		nssout.nss.host.herrno_p = error_num;
		/*
		 * We pass in nconf and let the implementation of the
		 * long-named func decide whether to use the switch based on
		 * nc_nlookups.
		 */
		neterr =
		    _get_hostserv_inetnetdir_byaddr(nconf, &nssin, &nssout);

		(void) freenetconfigent(nconf);
		if (neterr != ND_OK) {
			/* Failover case, try hosts db for v4 address */
			hp = buf->result;
			if (!gethostbyaddr_r(src, len, type, buf->result,
			    buf->buffer, buf->buflen, error_num)) {
				__IPv6_cleanup(buf);
				return (NULL);
			}
			free(buf);
			return (hp);
		}
		if ((hp = __mappedtov4(buf->result, error_num)) == NULL) {
			__IPv6_cleanup(buf);
			return (NULL);
		}
		__IPv6_cleanup(buf);
		return (hp);
	}
	/*
	 * Step 3: AF_INET6, plain vanilla v6 getipnodebyaddr() call.
	 */
	if (type == AF_INET6) {
		if ((nconf = __rpc_getconfip("udp")) == NULL &&
		    (nconf = __rpc_getconfip("tcp")) == NULL) {
			*error_num = NO_RECOVERY;
			return (NULL);
		}
		if ((buf = __IPv6_alloc(NSS_BUFLEN_IPNODES)) == 0) {
			*error_num = NO_RECOVERY;
			freenetconfigent(nconf);
			return (NULL);
		}
		nssin.op_t = NSS_HOST6;
		nssin.arg.nss.host.addr = (const char *)addr6;
		nssin.arg.nss.host.len = len;
		nssin.arg.nss.host.type = type;
		nssin.arg.nss.host.buf = buf->buffer;
		nssin.arg.nss.host.buflen = buf->buflen;

		nssout.nss.host.hent = buf->result;
		nssout.nss.host.herrno_p = error_num;
		/*
		 * We pass in nconf and let the implementation of the
		 * long-named func decide whether to use the switch based on
		 * nc_nlookups.
		 */
		neterr =
		    _get_hostserv_inetnetdir_byaddr(nconf, &nssin, &nssout);

		(void) freenetconfigent(nconf);
		if (neterr != ND_OK) {
			__IPv6_cleanup(buf);
			return (NULL);
		}
		free(buf);
		return (nssout.nss.host.hent);
	}
	/*
	 * If we got here, unknown type.
	 */
	*error_num = HOST_NOT_FOUND;
	return (NULL);
}