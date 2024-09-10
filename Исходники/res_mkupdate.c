/*%
 * Form update packets.
 * Returns the size of the resulting packet if no error
 *
 * On error,
 *	returns 
 *\li              -1 if error in reading a word/number in rdata
 *		   portion for update packets
 *\li		-2 if length of buffer passed is insufficient
 *\li		-3 if zone section is not the first section in
 *		   the linked list, or section order has a problem
 *\li		-4 on a number overflow
 *\li		-5 unknown operation or no records
 */
int
res_nmkupdate(res_state statp, ns_updrec *rrecp_in, u_char *buf, int buflen) {
	ns_updrec *rrecp_start = rrecp_in;
	HEADER *hp;
	u_char *cp, *sp2, *startp, *endp;
	int n, i, soanum, multiline;
	ns_updrec *rrecp;
	struct in_addr ina;
	struct in6_addr in6a;
        char buf2[MAXDNAME];
	u_char buf3[MAXDNAME];
	int section, numrrs = 0, counts[ns_s_max];
	u_int16_t rtype, rclass;
	u_int32_t n1, rttl;
	u_char *dnptrs[20], **dpp, **lastdnptr;
#ifndef _LIBC
	int siglen;
#endif
	int keylen, certlen;

	/*
	 * Initialize header fields.
	 */
	if ((buf == NULL) || (buflen < HFIXEDSZ))
		return (-1);
	memset(buf, 0, HFIXEDSZ);
	hp = (HEADER *) buf;
	hp->id = htons(++statp->id);
	hp->opcode = ns_o_update;
	hp->rcode = NOERROR;
	cp = buf + HFIXEDSZ;
	buflen -= HFIXEDSZ;
	dpp = dnptrs;
	*dpp++ = buf;
	*dpp++ = NULL;
	lastdnptr = dnptrs + sizeof dnptrs / sizeof dnptrs[0];

	if (rrecp_start == NULL)
		return (-5);
	else if (rrecp_start->r_section != S_ZONE)
		return (-3);

	memset(counts, 0, sizeof counts);
	for (rrecp = rrecp_start; rrecp; rrecp = NEXT(rrecp, r_glink)) {
		numrrs++;
                section = rrecp->r_section;
		if (section < 0 || section >= ns_s_max)
			return (-1);
		counts[section]++;
		for (i = section + 1; i < ns_s_max; i++)
			if (counts[i])
				return (-3);
		rtype = rrecp->r_type;
		rclass = rrecp->r_class;
		rttl = rrecp->r_ttl;
		/* overload class and type */
		if (section == S_PREREQ) {
			rttl = 0;
			switch (rrecp->r_opcode) {
			case YXDOMAIN:
				rclass = C_ANY;
				rtype = T_ANY;
				rrecp->r_size = 0;
				break;
			case NXDOMAIN:
				rclass = C_NONE;
				rtype = T_ANY;
				rrecp->r_size = 0;
				break;
			case NXRRSET:
				rclass = C_NONE;
				rrecp->r_size = 0;
				break;
			case YXRRSET:
				if (rrecp->r_size == 0)
					rclass = C_ANY;
				break;
			default:
				fprintf(stderr,
					"res_mkupdate: incorrect opcode: %d\n",
					rrecp->r_opcode);
				fflush(stderr);
				return (-1);
			}
		} else if (section == S_UPDATE) {
			switch (rrecp->r_opcode) {
			case DELETE:
				rclass = rrecp->r_size == 0 ? C_ANY : C_NONE;
				break;
			case ADD:
				break;
			default:
				fprintf(stderr,
					"res_mkupdate: incorrect opcode: %d\n",
					rrecp->r_opcode);
				fflush(stderr);
				return (-1);
			}
		}

		/*
		 * XXX	appending default domain to owner name is omitted,
		 *	fqdn must be provided
		 */
		if ((n = dn_comp(rrecp->r_dname, cp, buflen, dnptrs,
				 lastdnptr)) < 0)
			return (-1);
		cp += n;
		ShrinkBuffer(n + 2*INT16SZ);
		PUTSHORT(rtype, cp);
		PUTSHORT(rclass, cp);
		if (section == S_ZONE) {
			if (numrrs != 1 || rrecp->r_type != T_SOA)
				return (-3);
			continue;
		}
		ShrinkBuffer(INT32SZ + INT16SZ);
		PUTLONG(rttl, cp);
		sp2 = cp;  /*%< save pointer to length byte */
		cp += INT16SZ;
		if (rrecp->r_size == 0) {
			if (section == S_UPDATE && rclass != C_ANY)
				return (-1);
			else {
				PUTSHORT(0, sp2);
				continue;
			}
		}
		startp = rrecp->r_data;
		endp = startp + rrecp->r_size - 1;
		/* XXX this should be done centrally. */
		switch (rrecp->r_type) {
		case T_A:
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			if (!inet_aton(buf2, &ina))
				return (-1);
			n1 = ntohl(ina.s_addr);
			ShrinkBuffer(INT32SZ);
			PUTLONG(n1, cp);
			break;
		case T_CNAME:
		case T_MB:
		case T_MG:
		case T_MR:
		case T_NS:
		case T_PTR:
		case ns_t_dname:
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			n = dn_comp(buf2, cp, buflen, dnptrs, lastdnptr);
			if (n < 0)
				return (-1);
			cp += n;
			ShrinkBuffer(n);
			break;
		case T_MINFO:
		case T_SOA:
		case T_RP:
			for (i = 0; i < 2; i++) {
				if (!getword_str(buf2, sizeof buf2, &startp,
						 endp))
				return (-1);
				n = dn_comp(buf2, cp, buflen,
					    dnptrs, lastdnptr);
				if (n < 0)
					return (-1);
				cp += n;
				ShrinkBuffer(n);
			}
			if (rrecp->r_type == T_SOA) {
				ShrinkBuffer(5 * INT32SZ);
				while (isspace(*startp) || !*startp)
					startp++;
				if (*startp == '(') {
					multiline = 1;
					startp++;
				} else
					multiline = 0;
				/* serial, refresh, retry, expire, minimum */
				for (i = 0; i < 5; i++) {
					soanum = getnum_str(&startp, endp);
					if (soanum < 0)
						return (-1);
					PUTLONG(soanum, cp);
				}
				if (multiline) {
					while (isspace(*startp) || !*startp)
						startp++;
					if (*startp != ')')
						return (-1);
				}
			}
			break;
		case T_MX:
		case T_AFSDB:
		case T_RT:
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			n = dn_comp(buf2, cp, buflen, dnptrs, lastdnptr);
			if (n < 0)
				return (-1);
			cp += n;
			ShrinkBuffer(n);
			break;
		case T_SRV:
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);

			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);

			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);

			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			n = dn_comp(buf2, cp, buflen, NULL, NULL);
			if (n < 0)
				return (-1);
			cp += n;
			ShrinkBuffer(n);
			break;
		case T_PX:
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			PUTSHORT(n, cp);
			ShrinkBuffer(INT16SZ);
			for (i = 0; i < 2; i++) {
				if (!getword_str(buf2, sizeof buf2, &startp,
						 endp))
					return (-1);
				n = dn_comp(buf2, cp, buflen, dnptrs,
					    lastdnptr);
				if (n < 0)
					return (-1);
				cp += n;
				ShrinkBuffer(n);
			}
			break;
		case T_WKS: {
			char bm[MAXPORT/8];
			unsigned int maxbm = 0;

			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			if (!inet_aton(buf2, &ina))
				return (-1);
			n1 = ntohl(ina.s_addr);
			ShrinkBuffer(INT32SZ);
			PUTLONG(n1, cp);

			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			if ((i = res_protocolnumber(buf2)) < 0)
				return (-1);
			ShrinkBuffer(1);
			*cp++ = i & 0xff;
			 
			for (i = 0; i < MAXPORT/8 ; i++)
				bm[i] = 0;

			while (getword_str(buf2, sizeof buf2, &startp, endp)) {
				if ((n = res_servicenumber(buf2)) <= 0)
					return (-1);

				if (n < MAXPORT) {
					bm[n/8] |= (0x80>>(n%8));
					if ((unsigned)n > maxbm)
						maxbm = n;
				} else
					return (-1);
			}
			maxbm = maxbm/8 + 1;
			ShrinkBuffer(maxbm);
			memcpy(cp, bm, maxbm);
			cp += maxbm;
			break;
		}
		case T_HINFO:
			for (i = 0; i < 2; i++) {
				if ((n = getstr_str(buf2, sizeof buf2,
						&startp, endp)) < 0)
					return (-1);
				if (n > 255)
					return (-1);
				ShrinkBuffer(n+1);
				*cp++ = n;
				memcpy(cp, buf2, n);
				cp += n;
			}
			break;
		case T_TXT:
			for (;;) {
				if ((n = getstr_str(buf2, sizeof buf2,
						&startp, endp)) < 0) {
					if (cp != (sp2 + INT16SZ))
						break;
					return (-1);
				}
				if (n > 255)
					return (-1);
				ShrinkBuffer(n+1);
				*cp++ = n;
				memcpy(cp, buf2, n);
				cp += n;
			}
			break;
		case T_X25:
			/* RFC1183 */
			if ((n = getstr_str(buf2, sizeof buf2, &startp,
					 endp)) < 0)
				return (-1);
			if (n > 255)
				return (-1);
			ShrinkBuffer(n+1);
			*cp++ = n;
			memcpy(cp, buf2, n);
			cp += n;
			break;
		case T_ISDN:
			/* RFC1183 */
			if ((n = getstr_str(buf2, sizeof buf2, &startp,
					 endp)) < 0)
				return (-1);
			if ((n > 255) || (n == 0))
				return (-1);
			ShrinkBuffer(n+1);
			*cp++ = n;
			memcpy(cp, buf2, n);
			cp += n;
			if ((n = getstr_str(buf2, sizeof buf2, &startp,
					 endp)) < 0)
				n = 0;
			if (n > 255)
				return (-1);
			ShrinkBuffer(n+1);
			*cp++ = n;
			memcpy(cp, buf2, n);
			cp += n;
			break;
		case T_NSAP:
			if ((n = inet_nsap_addr((char *)startp, (u_char *)buf2, sizeof(buf2))) != 0) {
				ShrinkBuffer(n);
				memcpy(cp, buf2, n);
				cp += n;
			} else {
				return (-1);
			}
			break;
		case T_LOC:
			if ((n = loc_aton((char *)startp, (u_char *)buf2)) != 0) {
				ShrinkBuffer(n);
				memcpy(cp, buf2, n);
				cp += n;
			} else
				return (-1);
			break;
		case ns_t_sig:
#ifdef _LIBC
			return (-1);
#else
		    {
			int sig_type, success, dateerror;
			u_int32_t exptime, timesigned;

			/* type */
			if ((n = getword_str(buf2, sizeof buf2,
					     &startp, endp)) < 0)
				return (-1);
			sig_type = sym_ston(__p_type_syms, buf2, &success);
			if (!success || sig_type == ns_t_any)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(sig_type, cp);
			/* alg */
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(1);
			*cp++ = n;
			/* labels */
			n = getnum_str(&startp, endp);
			if (n <= 0 || n > 255)
				return (-1);
			ShrinkBuffer(1);
			*cp++ = n;
			/* ottl  & expire */
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			exptime = ns_datetosecs(buf2, &dateerror);
			if (!dateerror) {
				ShrinkBuffer(INT32SZ);
				PUTLONG(rttl, cp);
			}
			else {
				char *ulendp;
				u_int32_t ottl;

				errno = 0;
				ottl = strtoul(buf2, &ulendp, 10);
				if (errno != 0 ||
				    (ulendp != NULL && *ulendp != '\0'))
					return (-1);
				ShrinkBuffer(INT32SZ);
				PUTLONG(ottl, cp);
				if (!getword_str(buf2, sizeof buf2, &startp,
						 endp))
					return (-1);
				exptime = ns_datetosecs(buf2, &dateerror);
				if (dateerror)
					return (-1);
			}
			/* expire */
			ShrinkBuffer(INT32SZ);
			PUTLONG(exptime, cp);
			/* timesigned */
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			timesigned = ns_datetosecs(buf2, &dateerror);
			if (!dateerror) {
				ShrinkBuffer(INT32SZ);
				PUTLONG(timesigned, cp);
			}
			else
				return (-1);
			/* footprint */
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);
			/* signer name */
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			n = dn_comp(buf2, cp, buflen, dnptrs, lastdnptr);
			if (n < 0)
				return (-1);
			cp += n;
			ShrinkBuffer(n);
			/* sig */
			if ((n = getword_str(buf2, sizeof buf2,
					     &startp, endp)) < 0)
				return (-1);
			siglen = b64_pton(buf2, buf3, sizeof(buf3));
			if (siglen < 0)
				return (-1);
			ShrinkBuffer(siglen);
			memcpy(cp, buf3, siglen);
			cp += siglen;
			break;
		    }
#endif
		case ns_t_key:
			/* flags */
			n = gethexnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);
			/* proto */
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(1);
			*cp++ = n;
			/* alg */
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(1);
			*cp++ = n;
			/* key */
			if ((n = getword_str(buf2, sizeof buf2,
					     &startp, endp)) < 0)
				return (-1);
			keylen = b64_pton(buf2, buf3, sizeof(buf3));
			if (keylen < 0)
				return (-1);
			ShrinkBuffer(keylen);
			memcpy(cp, buf3, keylen);
			cp += keylen;
			break;
		case ns_t_nxt:
		    {
			int success, nxt_type;
			u_char data[32];
			int maxtype;

			/* next name */
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			n = dn_comp(buf2, cp, buflen, NULL, NULL);
			if (n < 0)
				return (-1);
			cp += n;
			ShrinkBuffer(n);
			maxtype = 0;
			memset(data, 0, sizeof data);
			for (;;) {
				if (!getword_str(buf2, sizeof buf2, &startp,
						 endp))
					break;
				nxt_type = sym_ston(__p_type_syms, buf2,
						    &success);
				if (!success || !ns_t_rr_p(nxt_type))
					return (-1);
				NS_NXT_BIT_SET(nxt_type, data);
				if (nxt_type > maxtype)
					maxtype = nxt_type;
			}
			n = maxtype/NS_NXT_BITS+1;
			ShrinkBuffer(n);
			memcpy(cp, data, n);
			cp += n;
			break;
		    }
		case ns_t_cert:
			/* type */
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);
			/* key tag */
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);
			/* alg */
			n = getnum_str(&startp, endp);
			if (n < 0)
				return (-1);
			ShrinkBuffer(1);
			*cp++ = n;
			/* cert */
			if ((n = getword_str(buf2, sizeof buf2,
					     &startp, endp)) < 0)
				return (-1);
			certlen = b64_pton(buf2, buf3, sizeof(buf3));
			if (certlen < 0)
				return (-1);
			ShrinkBuffer(certlen);
			memcpy(cp, buf3, certlen);
			cp += certlen;
			break;
		case ns_t_aaaa:
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			if (inet_pton(AF_INET6, buf2, &in6a) <= 0)
				return (-1);
			ShrinkBuffer(NS_IN6ADDRSZ);
			memcpy(cp, &in6a, NS_IN6ADDRSZ);
			cp += NS_IN6ADDRSZ;
			break;
		case ns_t_naptr:
			/* Order Preference Flags Service Replacement Regexp */
			/* Order */
			n = getnum_str(&startp, endp);
			if (n < 0 || n > 65535)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);
			/* Preference */
			n = getnum_str(&startp, endp);
			if (n < 0 || n > 65535)
				return (-1);
			ShrinkBuffer(INT16SZ);
			PUTSHORT(n, cp);
			/* Flags */
			if ((n = getstr_str(buf2, sizeof buf2,
					&startp, endp)) < 0) {
				return (-1);
			}
			if (n > 255)
				return (-1);
			ShrinkBuffer(n+1);
			*cp++ = n;
			memcpy(cp, buf2, n);
			cp += n;
			/* Service Classes */
			if ((n = getstr_str(buf2, sizeof buf2,
					&startp, endp)) < 0) {
				return (-1);
			}
			if (n > 255)
				return (-1);
			ShrinkBuffer(n+1);
			*cp++ = n;
			memcpy(cp, buf2, n);
			cp += n;
			/* Pattern */
			if ((n = getstr_str(buf2, sizeof buf2,
					&startp, endp)) < 0) {
				return (-1);
			}
			if (n > 255)
				return (-1);
			ShrinkBuffer(n+1);
			*cp++ = n;
			memcpy(cp, buf2, n);
			cp += n;
			/* Replacement */
			if (!getword_str(buf2, sizeof buf2, &startp, endp))
				return (-1);
			n = dn_comp(buf2, cp, buflen, NULL, NULL);
			if (n < 0)
				return (-1);
			cp += n;
			ShrinkBuffer(n);
			break;
		default:
			return (-1);
		} /*switch*/