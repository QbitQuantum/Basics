static int
ip6_fw_chk(struct ip6_hdr **pip6,
	struct ifnet *oif, struct mbuf **m)
{
	struct ip6_fw_chain *chain;
	struct ip6_fw *rule = NULL;
	struct ip6_hdr *ip6 = *pip6;
	struct ifnet *const rif = (*m)->m_pkthdr.rcvif;
	u_short offset = 0;
	int off = sizeof(struct ip6_hdr), nxt = ip6->ip6_nxt;
	u_short src_port, dst_port;
#ifdef	IP6FW_DIVERT_RESTART
	u_int16_t skipto = 0;
#else
	u_int16_t ignport = 0;
#endif

	/*
	 * Go down the chain, looking for enlightment
	 * #ifdef IP6FW_DIVERT_RESTART
	 * If we've been asked to start at a given rule immediatly, do so.
	 * #endif
	 */
	chain = LIST_FIRST(&ip6_fw_chain);
#ifdef IP6FW_DIVERT_RESTART
	if (skipto) {
		if (skipto >= 65535)
			goto dropit;
		while (chain && (chain->rule->fw_number <= skipto)) {
			chain = LIST_NEXT(chain, chain);
		}
		if (! chain) goto dropit;
	}
#endif /* IP6FW_DIVERT_RESTART */
	for (; chain; chain = LIST_NEXT(chain, chain)) {
		struct ip6_fw *const f = chain->rule;

		if (oif) {
			/* Check direction outbound */
			if (!(f->fw_flg & IPV6_FW_F_OUT))
				continue;
		} else {
			/* Check direction inbound */
			if (!(f->fw_flg & IPV6_FW_F_IN))
				continue;
		}

#define IN6_ARE_ADDR_MASKEQUAL(x,y,z) (\
	(((x)->s6_addr32[0] & (y)->s6_addr32[0]) == (z)->s6_addr32[0]) && \
	(((x)->s6_addr32[1] & (y)->s6_addr32[1]) == (z)->s6_addr32[1]) && \
	(((x)->s6_addr32[2] & (y)->s6_addr32[2]) == (z)->s6_addr32[2]) && \
	(((x)->s6_addr32[3] & (y)->s6_addr32[3]) == (z)->s6_addr32[3]))

		/* If src-addr doesn't match, not this rule. */
		if (((f->fw_flg & IPV6_FW_F_INVSRC) != 0) ^
			(!IN6_ARE_ADDR_MASKEQUAL(&ip6->ip6_src,&f->fw_smsk,&f->fw_src)))
			continue;

		/* If dest-addr doesn't match, not this rule. */
		if (((f->fw_flg & IPV6_FW_F_INVDST) != 0) ^
			(!IN6_ARE_ADDR_MASKEQUAL(&ip6->ip6_dst,&f->fw_dmsk,&f->fw_dst)))
			continue;

#undef IN6_ARE_ADDR_MASKEQUAL
		/* Interface check */
		if ((f->fw_flg & IF6_FW_F_VIAHACK) == IF6_FW_F_VIAHACK) {
			struct ifnet *const iface = oif ? oif : rif;

			/* Backwards compatibility hack for "via" */
			if (!iface || !iface_match(iface,
			    &f->fw_in_if, f->fw_flg & IPV6_FW_F_OIFNAME))
				continue;
		} else {
			/* Check receive interface */
			if ((f->fw_flg & IPV6_FW_F_IIFACE)
			    && (!rif || !iface_match(rif,
			      &f->fw_in_if, f->fw_flg & IPV6_FW_F_IIFNAME)))
				continue;
			/* Check outgoing interface */
			if ((f->fw_flg & IPV6_FW_F_OIFACE)
			    && (!oif || !iface_match(oif,
			      &f->fw_out_if, f->fw_flg & IPV6_FW_F_OIFNAME)))
				continue;
		}

		/* Check IP options */
		if (!ip6opts_match(&ip6, f, m, &off, &nxt, &offset))
			continue;

		/* Fragments */
		if ((f->fw_flg & IPV6_FW_F_FRAG) && !offset)
			continue;

		/* Check protocol; if wildcard, match */
		if (f->fw_prot == IPPROTO_IPV6)
			goto got_match;

		/* If different, don't match */
		if (nxt != f->fw_prot)
			continue;

#define PULLUP_TO(len)	do {						\
			    if ((*m)->m_len < (len)			\
				&& (*m = m_pullup(*m, (len))) == 0) {	\
				    goto dropit;			\
			    }						\
			    *pip6 = ip6 = mtod(*m, struct ip6_hdr *);	\
			} while (0)

		/* Protocol specific checks */
		switch (nxt) {
		case IPPROTO_TCP:
		    {
			struct tcphdr *tcp6;

			if (offset == 1) {	/* cf. RFC 1858 */
				PULLUP_TO(off + 4); /* XXX ? */
				goto bogusfrag;
			}
			if (offset != 0) {
				/*
				 * TCP flags and ports aren't available in this
				 * packet -- if this rule specified either one,
				 * we consider the rule a non-match.
				 */
				if (f->fw_nports != 0 ||
				    f->fw_tcpf != f->fw_tcpnf)
					continue;

				break;
			}
			PULLUP_TO(off + 14);
			tcp6 = (struct tcphdr *) ((caddr_t)ip6 + off);
			if (((f->fw_tcpf != f->fw_tcpnf) ||
			   (f->fw_ipflg & IPV6_FW_IF_TCPEST))  &&
			   !tcp6flg_match(tcp6, f))
				continue;
			src_port = ntohs(tcp6->th_sport);
			dst_port = ntohs(tcp6->th_dport);
			goto check_ports;
		    }

		case IPPROTO_UDP:
		    {
			struct udphdr *udp;

			if (offset != 0) {
				/*
				 * Port specification is unavailable -- if this
				 * rule specifies a port, we consider the rule
				 * a non-match.
				 */
				if (f->fw_nports != 0)
					continue;

				break;
			}
			PULLUP_TO(off + 4);
			udp = (struct udphdr *) ((caddr_t)ip6 + off);
			src_port = ntohs(udp->uh_sport);
			dst_port = ntohs(udp->uh_dport);
check_ports:
			if (!port_match6(&f->fw_pts[0],
			    IPV6_FW_GETNSRCP(f), src_port,
			    f->fw_flg & IPV6_FW_F_SRNG))
				continue;
			if (!port_match6(&f->fw_pts[IPV6_FW_GETNSRCP(f)],
			    IPV6_FW_GETNDSTP(f), dst_port,
			    f->fw_flg & IPV6_FW_F_DRNG))
				continue;
			break;
		    }

		case IPPROTO_ICMPV6:
		    {
			struct icmp6_hdr *icmp;

			if (offset != 0)	/* Type isn't valid */
				break;
			PULLUP_TO(off + 2);
			icmp = (struct icmp6_hdr *) ((caddr_t)ip6 + off);
			if (!icmp6type_match(icmp, f))
				continue;
			break;
		    }
#undef PULLUP_TO

bogusfrag:
			if (fw6_verbose)
				ip6fw_report(NULL, ip6, rif, oif, off, nxt);
			goto dropit;
		}

got_match:
#ifndef IP6FW_DIVERT_RESTART
		/* Ignore divert/tee rule if socket port is "ignport" */
		switch (f->fw_flg & IPV6_FW_F_COMMAND) {
		case IPV6_FW_F_DIVERT:
		case IPV6_FW_F_TEE:
			if (f->fw_divert_port == ignport)
				continue;       /* ignore this rule */
			break;
		}

#endif /* IP6FW_DIVERT_RESTART */
		/* Update statistics */
		f->fw_pcnt += 1;
		f->fw_bcnt += ntohs(ip6->ip6_plen);
#if defined(__FreeBSD__) && __FreeBSD__ >= 3
		f->timestamp = time_second;
#else
		f->timestamp = time.tv_sec;
#endif

		/* Log to console if desired */
		if ((f->fw_flg & IPV6_FW_F_PRN) && fw6_verbose)
			ip6fw_report(f, ip6, rif, oif, off, nxt);

		/* Take appropriate action */
		switch (f->fw_flg & IPV6_FW_F_COMMAND) {
		case IPV6_FW_F_ACCEPT:
			return(0);
		case IPV6_FW_F_COUNT:
			continue;
		case IPV6_FW_F_DIVERT:
			return(f->fw_divert_port);
		case IPV6_FW_F_TEE:
			/*
			 * XXX someday tee packet here, but beware that you
			 * can't use m_copym() or m_copypacket() because
			 * the divert input routine modifies the mbuf
			 * (and these routines only increment reference
			 * counts in the case of mbuf clusters), so need
			 * to write custom routine.
			 */
			continue;
		case IPV6_FW_F_SKIPTO:
#ifdef DIAGNOSTIC
			while (chain->chain.le_next
			    && chain->chain.le_next->rule->fw_number
				< f->fw_skipto_rule)
#else
			while (chain->chain.le_next->rule->fw_number
			    < f->fw_skipto_rule)
#endif
				chain = chain->chain.le_next;
			continue;
		}

		/* Deny/reject this packet using this rule */
		rule = f;
		break;
	}

#ifdef DIAGNOSTIC
	/* Rule 65535 should always be there and should always match */
	if (!chain)
		panic("ip6_fw: chain");
#endif

	/*
	 * At this point, we're going to drop the packet.
	 * Send a reject notice if all of the following are true:
	 *
	 * - The packet matched a reject rule
	 * - The packet is not an ICMP packet, or is an ICMP query packet
	 * - The packet is not a multicast or broadcast packet
	 */
	if ((rule->fw_flg & IPV6_FW_F_COMMAND) == IPV6_FW_F_REJECT
	    && (nxt != IPPROTO_ICMPV6 || is_icmp6_query(ip6, off))
	    && !((*m)->m_flags & (M_BCAST|M_MCAST))
	    && !IN6_IS_ADDR_MULTICAST(&ip6->ip6_dst)) {
		switch (rule->fw_reject_code) {
		case IPV6_FW_REJECT_RST:
#if 1	/* not tested */
		  {
			struct tcphdr *const tcp =
				(struct tcphdr *) ((caddr_t)ip6 + off);
			struct {
				struct ip6_hdr ip6;
				struct tcphdr th;
			} ti;
			tcp_seq ack, seq;
			int flags;

			if (offset != 0 || (tcp->th_flags & TH_RST))
				break;

			ti.ip6 = *ip6;
			ti.th = *tcp;
			NTOHL(ti.th.th_seq);
			NTOHL(ti.th.th_ack);
			ti.ip6.ip6_nxt = IPPROTO_TCP;
			if (ti.th.th_flags & TH_ACK) {
				ack = 0;
				seq = ti.th.th_ack;
				flags = TH_RST;
			} else {
				ack = ti.th.th_seq;
				if (((*m)->m_flags & M_PKTHDR) != 0) {
					ack += (*m)->m_pkthdr.len - off
						- (ti.th.th_off << 2);
				} else if (ip6->ip6_plen) {
					ack += ntohs(ip6->ip6_plen) + sizeof(*ip6)
						- off - (ti.th.th_off << 2);
				} else {
					m_freem(*m);
					*m = 0;
					break;
				}
				seq = 0;
				flags = TH_RST|TH_ACK;
			}
			bcopy(&ti, ip6, sizeof(ti));
#ifdef TCP6
			tcp6_respond(NULL, ip6, (struct tcp6hdr *)(ip6 + 1),
				*m, ack, seq, flags);
#elif defined(__NetBSD__)
			tcp_respond(NULL, NULL, *m, (struct tcphdr *)(ip6 + 1),
				ack, seq, flags);
#elif defined(__FreeBSD__) && __FreeBSD__ >= 4
			tcp_respond(NULL, ip6, (struct tcphdr *)(ip6 + 1),
				*m, ack, seq, flags);
#elif defined(__FreeBSD__) && __FreeBSD__ >= 3
			tcp_respond(NULL, ip6, (struct tcphdr *)(ip6 + 1),
				*m, ack, seq, flags, 1);
#else
			m_freem(*m);
#endif
			*m = NULL;
			break;
		  }
#endif
		default:	/* Send an ICMP unreachable using code */
			if (oif)
				(*m)->m_pkthdr.rcvif = oif;
			icmp6_error(*m, ICMP6_DST_UNREACH,
			    rule->fw_reject_code, 0);
			*m = NULL;
			break;
		}
	}

dropit:
	/*
	 * Finally, drop the packet.
	 */
	if (*m) {
		m_freem(*m);
		*m = NULL;
	}
	return(0);
}