static int dns_lookup(nsp_state *N, obj_t *tobj, const char *domain)
{
#define __FN__ __FILE__ ":dns_lookup()"
#ifdef WIN32
	DNS_FREE_TYPE freetype;
	DNS_STATUS status;
	PDNS_RECORD pDnsRecord;
	PDNS_RECORD pDnsCur;
	obj_t *stobj;
	IN_ADDR ipaddr;
	char namebuf[8];
	register int i;

	freetype = DnsFreeRecordListDeep;
	/* status=DnsQuery_A(domain, DNS_TYPE_ANY, DNS_QUERY_STANDARD, NULL, &pDnsRecord, NULL); */
	status = DnsQuery_A(domain, DNS_TYPE_ANY, DNS_QUERY_BYPASS_CACHE, NULL, &pDnsRecord, NULL);
	if (status) {
		if (N->debug) n_warn(N, __FN__, "res_search failed");
		return -1;
	}
	/* Loop through the answer buffer and extract records. */
	i = 0;
	pDnsCur = pDnsRecord;
	while (pDnsCur != NULL) {
		stobj = nsp_settable(N, tobj, n_ntoa(N, namebuf, i, 10, 0));
		switch (pDnsCur->wType) {
		case DNS_TYPE_A: {
			ipaddr.S_un.S_addr = (pDnsCur->Data.A.IpAddress);
			nsp_setstr(N, stobj, "type", "A", -1);
			nsp_setstr(N, stobj, "host", pDnsCur->pName, -1);
			nsp_setstr(N, stobj, "addr", inet_ntoa(ipaddr), -1);
			if (N->debug) n_warn(N, __FN__, "A  [%s]", inet_ntoa(ipaddr));
			break;
		}
		case DNS_TYPE_NS: {
			nsp_setstr(N, stobj, "type", "NS", -1);
			/* is PTR the right struct? */
			nsp_setstr(N, stobj, "host", pDnsCur->Data.PTR.pNameHost, -1);
			if (N->debug) n_warn(N, __FN__, "NS [%s]", pDnsCur->Data.PTR.pNameHost);
			break;
		}
		case DNS_TYPE_SOA: {
			nsp_setstr(N, stobj, "type", "SOA", -1);
			nsp_setstr(N, stobj, "host", pDnsCur->Data.SOA.pNamePrimaryServer, -1);
			nsp_setstr(N, stobj, "mail", pDnsCur->Data.SOA.pNameAdministrator, -1);
			nsp_setnum(N, stobj, "serial", pDnsCur->Data.SOA.dwSerialNo);
			nsp_setnum(N, stobj, "refresh", pDnsCur->Data.SOA.dwRefresh);
			nsp_setnum(N, stobj, "retry", pDnsCur->Data.SOA.dwRetry);
			nsp_setnum(N, stobj, "expire", pDnsCur->Data.SOA.dwExpire);
			nsp_setnum(N, stobj, "minttl", pDnsCur->Data.SOA.dwDefaultTtl);
			break;
		}
		case DNS_TYPE_PTR: {
			nsp_setstr(N, stobj, "type", "PTR", -1);
			nsp_setstr(N, stobj, "host", pDnsCur->Data.PTR.pNameHost, -1);
			if (N->debug) n_warn(N, __FN__, "PTR [%s]", pDnsCur->Data.PTR.pNameHost);
			break;
		}
		case DNS_TYPE_MX: {
			nsp_setstr(N, stobj, "type", "MX", -1);
			nsp_setnum(N, stobj, "pref", pDnsCur->Data.MX.wPreference);
			nsp_setstr(N, stobj, "host", pDnsCur->Data.MX.pNameExchange, -1);
			if (N->debug) n_warn(N, __FN__, "MX [%s]", pDnsCur->Data.MX.pNameExchange);
			break;
		}
		default: {
			/* skip data we're too dumb to parse */
			nsp_setnum(N, stobj, "type", pDnsCur->wType);
			/* if (N->debug) */ n_warn(N, __FN__, "xx[%d]", pDnsCur->wType);
			break;
		}
		}
		i++;
		pDnsCur = pDnsCur->pNext;
	}
	DnsRecordListFree(pDnsRecord, freetype);
	return 0;
#else
	char hostbuf[HOSTBUF + 1];
	char abuf[20];
	char namebuf[8];
	querybuf answer;
	HEADER *hp;
	int ancount, qdcount;
	uchar *msg, *eom, *cp;
	//int type, class, ttl, dlen;
	int type, dlen;
	unsigned short pref;
	register int i;
	register int n;
	uchar *e;
	obj_t *stobj;

	/* Query the nameserver to retrieve mx records for the given domain. */
	n = res_search(domain, C_ANY, T_ANY, (u_char *)&answer, sizeof(answer));
	if (n < 0) {
		if (N->debug) n_warn(N, __FN__, "res_search failed");
		return -1;
	}
	if (n < HFIXEDSZ) return -1;
	/* avoid problems after truncation in tcp packets */
	if (n > (int)sizeof(answer)) n = (int)sizeof(answer);
	/* Valid answer received. Skip the query record. */
	hp = (HEADER *)&answer;
	qdcount = ntohs((u_short)hp->qdcount);
	ancount = ntohs((u_short)hp->ancount);
	msg = (u_char *)&answer;
	eom = (u_char *)&answer + n;
	cp = (u_char *)&answer + HFIXEDSZ;
	while (qdcount-->0 && cp < eom) {
		n = dn_skipname(cp, eom);
		if (n < 0) return -1;
		cp += n;
		cp += QFIXEDSZ;
	}
	/* Loop through the answer buffer and extract records. */
	i = 0;
	memset(hostbuf, 0, sizeof(hostbuf));
	while (ancount-->0 && cp < eom) {
		stobj = nsp_settable(N, tobj, n_ntoa(N, namebuf, i, 10, 0));
		if ((n = dn_expand(msg, eom, cp, hostbuf, HOSTBUF)) < 0) break;
		if (N->debug) n_warn(N, __FN__, "?[%s]", hostbuf);
		cp += n;
		GETSHORT(type, cp);
		//		GETSHORT(class, cp);
		//		GETLONG(ttl, cp);
		GETSHORT(dlen, cp);
		e = cp + dlen;
		switch (type) {
		case T_A: {
			snprintf(abuf, sizeof(abuf), "%d.%d.%d.%d", (int)cp[0], (int)cp[1], (int)cp[2], (int)cp[3]);
			nsp_setstr(N, stobj, "type", "A", -1);
			nsp_setstr(N, stobj, "host", hostbuf, -1);
			nsp_setstr(N, stobj, "addr", abuf, -1);
			if (N->debug) n_warn(N, __FN__, "A  [%s]", abuf);
			cp += dlen;
			break;
		}
		case T_NS: {
			if ((n = dn_expand(msg, eom, cp, hostbuf, HOSTBUF)) < 0) return -1;
			cp += n;
			n = strlen(hostbuf);
			nsp_setstr(N, stobj, "type", "NS", -1);
			nsp_setstr(N, stobj, "host", hostbuf, n);
			if (N->debug) n_warn(N, __FN__, "NS [%s]", hostbuf);
			break;
		}
		case T_SOA: {
			unsigned int n;

			nsp_setstr(N, stobj, "type", "SOA", -1);
			if ((n = dn_expand(msg, eom, cp, hostbuf, HOSTBUF)) < 0) return -1;
			cp += n;
			nsp_setstr(N, stobj, "host", hostbuf, -1);
			if ((n = dn_expand(msg, eom, cp, hostbuf, HOSTBUF)) < 0) return -1;
			cp += n;
			nsp_setstr(N, stobj, "mail", hostbuf, -1);
			GETLONG(n, cp); nsp_setnum(N, stobj, "serial", n);
			GETLONG(n, cp); nsp_setnum(N, stobj, "refresh", n);
			GETLONG(n, cp); nsp_setnum(N, stobj, "retry", n);
			GETLONG(n, cp); nsp_setnum(N, stobj, "expire", n);
			GETLONG(n, cp); nsp_setnum(N, stobj, "minttl", n);
			break;
		}
		case T_PTR: {
			if ((n = dn_expand(msg, eom, cp, hostbuf, HOSTBUF)) < 0) return -1;
			cp += n;
			n = strlen(hostbuf);
			nsp_setstr(N, stobj, "type", "PTR", -1);
			nsp_setstr(N, stobj, "host", hostbuf, n);
			if (N->debug) n_warn(N, __FN__, "PTR [%s]", hostbuf);
			break;
		}
		case T_MX: {
			GETSHORT(pref, cp);
			if ((n = dn_expand(msg, eom, cp, hostbuf, HOSTBUF)) < 0) return -1;
			cp += n;
			n = strlen(hostbuf);
			nsp_setstr(N, stobj, "type", "MX", -1);
			nsp_setnum(N, stobj, "pref", pref);
			nsp_setstr(N, stobj, "host", hostbuf, n);
			if (N->debug) n_warn(N, __FN__, "MX [%s]", hostbuf);
			break;
		}
		default: {
			/* skip data we're too dumb to parse */
			nsp_setnum(N, stobj, "type", type);
			/* if (N->debug) */ n_warn(N, __FN__, "xx[%d]", type);
			cp += dlen;
			break;
		}
		}
		i++;
		if (cp != e) n_warn(N, __FN__, "SOA[%d %d]", cp, e);
		cp = e;
	}
#endif
	return 0;
#undef __FN__
}