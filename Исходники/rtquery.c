/*
 * Handle an incoming RIP packet.
 */
static void
rip_input(struct sockaddr_in *from, int size, uint_t ifindex)
{
	struct netinfo *n, *lim;
	struct in_addr in;
	const char *name;
	char net_buf[80];
	uchar_t hash[RIP_AUTH_MD5_LEN];
	MD5_CTX md5_ctx;
	uchar_t md5_authed = 0;
	in_addr_t mask, dmask;
	struct in_addr tmp_addr;
	char *sp;
	char  ifname[IF_NAMESIZE+1];
	int i;
	struct hostent *hp;
	struct netent *np;
	struct netauth *na;
	char srcaddr[MAXHOSTNAMELEN + sizeof (" (123.123.123.123)") + 1];
	char ifstring[IF_NAMESIZE + 3*sizeof (ifindex) + sizeof (" ()") + 1];

	if (!nflag && (hp = gethostbyaddr((char *)&from->sin_addr,
	    sizeof (struct in_addr), AF_INET)) != NULL) {
		(void) snprintf(srcaddr, sizeof (srcaddr), "%s (%s)",
		    hp->h_name, inet_ntoa(from->sin_addr));
	} else {
		/* safe; cannot overflow destination */
		(void) strcpy(srcaddr, inet_ntoa(from->sin_addr));
	}
	if (ifindex == 0) {
		(void) printf("%s:", srcaddr);
	} else {
		if (if_indextoname(ifindex, ifname) != NULL)
			(void) snprintf(ifstring, sizeof (ifstring), "%s (%d)",
			    ifname, ifindex);
		else
			(void) snprintf(ifstring, sizeof (ifstring), "%d",
			    ifindex);
		(void) printf(gettext("%1$s received on interface %2$s:"),
		    srcaddr, ifstring);
	}

	if (IMSG.rip_cmd != RIPCMD_RESPONSE) {
		(void) printf(gettext("\n    unexpected response type %d\n"),
		    IMSG.rip_cmd);
		return;
	}
	(void) printf(gettext(" RIPv%1$d%2$s %3$d bytes\n"), IMSG.rip_vers,
	    (IMSG.rip_vers != RIPv1 && IMSG.rip_vers != RIPv2) ? " ?" : "",
	    size);
	if (size > MAXPACKETSIZE) {
		if (size > sizeof (imsg_buf) - sizeof (*n)) {
			(void) printf(
			    gettext("       at least %d bytes too long\n"),
			    size-MAXPACKETSIZE);
			size = sizeof (imsg_buf) - sizeof (*n);
		} else {
			(void) printf(gettext("       %d bytes too long\n"),
			    size-MAXPACKETSIZE);
		}
	} else if (size%sizeof (*n) != sizeof (struct rip)%sizeof (*n)) {
		(void) printf(gettext("    response of bad length=%d\n"), size);
	}

	n = IMSG.rip_nets;
	lim = n + (size - 4) / sizeof (struct netinfo);
	for (; n < lim; n++) {
		name = "";
		if (n->n_family == RIP_AF_INET) {
			in.s_addr = n->n_dst;
			(void) strlcpy(net_buf, inet_ntoa(in),
			    sizeof (net_buf));

			tmp_addr.s_addr = (n->n_mask);
			mask = ntohl(n->n_mask);
			dmask = mask & -mask;
			if (mask != 0) {
				sp = &net_buf[strlen(net_buf)];
				if (IMSG.rip_vers == RIPv1) {
					(void) snprintf(sp,
					    (sizeof (net_buf) -
					    strlen(net_buf)),
					    gettext(" mask=%s ? "),
					    inet_ntoa(tmp_addr));
					mask = 0;
				} else if (mask + dmask == 0) {
					i = ffs(mask) - 1;
					(void) snprintf(sp,
					    (sizeof (net_buf) -
					    strlen(net_buf)), "/%d", 32-i);
				} else {
					(void) snprintf(sp,
					    (sizeof (net_buf) -
						strlen(net_buf)),
					    gettext(" (mask %s)"),
					    inet_ntoa(tmp_addr));
				}
			}

			if (!nflag) {
				if (mask == 0) {
					mask = std_mask(in.s_addr);
					if ((ntohl(in.s_addr) & ~mask) != 0)
						mask = 0;
				}
				/*
				 * Without a netmask, do not worry about
				 * whether the destination is a host or a
				 * network. Try both and use the first name
				 * we get.
				 *
				 * If we have a netmask we can make a
				 * good guess.
				 */
				if ((in.s_addr & ~mask) == 0) {
					np = getnetbyaddr((long)in.s_addr,
					    AF_INET);
					if (np != NULL)
						name = np->n_name;
					else if (in.s_addr == 0)
						name = "default";
				}
				if (name[0] == '\0' &&
				    ((in.s_addr & ~mask) != 0 ||
				    mask == 0xffffffff)) {
					hp = gethostbyaddr((char *)&in,
					    sizeof (in), AF_INET);
					if (hp != NULL)
						name = hp->h_name;
				}
			}

		} else if (n->n_family == RIP_AF_AUTH) {
			na = (struct netauth *)n;
			if (na->a_type == RIP_AUTH_PW &&
			    n == IMSG.rip_nets) {
				(void) printf(
				    gettext("  Password Authentication:"
				    " \"%s\"\n"),
				    qstring(na->au.au_pw,
				    RIP_AUTH_PW_LEN));
				continue;
			}

			if (na->a_type == RIP_AUTH_MD5 &&
			    n == IMSG.rip_nets) {
				(void) printf(gettext("  MD5 Auth"
				    " len=%1$d KeyID=%2$d"
				    " auth_len=%3$d"
				    " seqno=%4$#x"
				    " rsvd=%5$#x,%6$#x\n"),
				    ntohs(na->au.a_md5.md5_pkt_len),
				    na->au.a_md5.md5_keyid,
				    na->au.a_md5.md5_auth_len,
				    (int)ntohl(na->au.a_md5.md5_seqno),
				    na->au.a_md5.rsvd[0],
				    na->au.a_md5.rsvd[1]);
				md5_authed = 1;
				continue;
			}
			(void) printf(gettext("  Authentication type %d: "),
			    ntohs(na->a_type));
			for (i = 0; i < sizeof (na->au.au_pw); i++)
				(void) printf("%02x ",
				    na->au.au_pw[i]);
			(void) putchar('\n');
			if (md5_authed && n+1 > lim &&
			    na->a_type == RIP_AUTH_TRAILER) {
				MD5Init(&md5_ctx);
				MD5Update(&md5_ctx, (uchar_t *)&IMSG,
				    (char *)na-(char *)&IMSG);
				MD5Update(&md5_ctx,
				    (uchar_t *)passwd, RIP_AUTH_MD5_LEN);
				MD5Final(hash, &md5_ctx);
				(void) printf(gettext("    %s hash\n"),
				    memcmp(hash, na->au.au_pw, sizeof (hash)) ?
				    gettext("WRONG") : gettext("correct"));
			} else if (md5_authed && n+1 > lim &&
			    na->a_type != RIP_AUTH_TRAILER) {
				(void) printf(gettext("Error -"
				"authentication entry missing hash\n"));
			}
			continue;

		} else {
			tmp_addr.s_addr = n->n_dst;
			(void) snprintf(net_buf, sizeof (net_buf),
			    gettext("(address family %1$u) %2$s"),
			    ntohs(n->n_family), inet_ntoa(tmp_addr));
		}

		(void) printf(gettext("  %1$-18s metric %2$2lu %3$-10s"),
		    net_buf, ntohl(n->n_metric), name);

		if (n->n_nhop != 0) {
			in.s_addr = n->n_nhop;
			if (nflag)
				hp = NULL;
			else
				hp = gethostbyaddr((char *)&in, sizeof (in),
				    AF_INET);
			(void) printf(gettext(" nhop=%1$-15s%2$s"),
			    (hp != NULL) ? hp->h_name : inet_ntoa(in),
			    (IMSG.rip_vers == RIPv1) ? " ?" : "");
		}
		if (n->n_tag != 0)
			(void) printf(gettext(" tag=%1$#x%2$s"), n->n_tag,
			    (IMSG.rip_vers == RIPv1) ? " ?" : "");
		(void) putchar('\n');
	}
}