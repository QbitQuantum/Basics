static int 
ip_fw_chk(struct ip **pip, int hlen,
	struct ifnet *oif, int ignport, struct mbuf **m)
{
	struct ip_fw_chain *chain;
	struct ip_fw *rule = NULL;
	struct ip *ip = *pip;
	struct ifnet *const rif = (*m)->m_pkthdr.rcvif;
	u_short offset = (ip->ip_off & IP_OFFMASK);
	u_short src_port, dst_port;

	/*
	 * Go down the chain, looking for enlightment
	 */
	for (chain=ip_fw_chain.lh_first; chain; chain = chain->chain.le_next) {
		register struct ip_fw *const f = chain->rule;

		/* Check direction inbound */
		if (!oif && !(f->fw_flg & IP_FW_F_IN))
			continue;

		/* Check direction outbound */
		if (oif && !(f->fw_flg & IP_FW_F_OUT))
			continue;

		/* Fragments */
		if ((f->fw_flg & IP_FW_F_FRAG) && !(ip->ip_off & IP_OFFMASK))
			continue;

		/* If src-addr doesn't match, not this rule. */
		if (((f->fw_flg & IP_FW_F_INVSRC) != 0) ^ ((ip->ip_src.s_addr
		    & f->fw_smsk.s_addr) != f->fw_src.s_addr))
			continue;

		/* If dest-addr doesn't match, not this rule. */
		if (((f->fw_flg & IP_FW_F_INVDST) != 0) ^ ((ip->ip_dst.s_addr
		    & f->fw_dmsk.s_addr) != f->fw_dst.s_addr))
			continue;

		/* Interface check */
		if ((f->fw_flg & IF_FW_F_VIAHACK) == IF_FW_F_VIAHACK) {
			struct ifnet *const iface = oif ? oif : rif;

			/* Backwards compatibility hack for "via" */
			if (!iface || !iface_match(iface,
			    &f->fw_in_if, f->fw_flg & IP_FW_F_OIFNAME))
				continue;
		} else {
			/* Check receive interface */
			if ((f->fw_flg & IP_FW_F_IIFACE)
			    && (!rif || !iface_match(rif,
			      &f->fw_in_if, f->fw_flg & IP_FW_F_IIFNAME)))
				continue;
			/* Check outgoing interface */
			if ((f->fw_flg & IP_FW_F_OIFACE)
			    && (!oif || !iface_match(oif,
			      &f->fw_out_if, f->fw_flg & IP_FW_F_OIFNAME)))
				continue;
		}

		/* Check IP options */
		if (f->fw_ipopt != f->fw_ipnopt && !ipopts_match(ip, f))
			continue;

		/* Check protocol; if wildcard, match */
		if (f->fw_prot == IPPROTO_IP)
			goto got_match;

		/* If different, don't match */
		if (ip->ip_p != f->fw_prot) 
			continue;

#define PULLUP_TO(len)	do {						\
			    if ((*m)->m_len < (len)			\
				&& (*m = m_pullup(*m, (len))) == 0) {	\
				    goto bogusfrag;			\
			    }						\
			    *pip = ip = mtod(*m, struct ip *);		\
			    offset = (ip->ip_off & IP_OFFMASK);		\
			} while (0)

		/* Protocol specific checks */
		switch (ip->ip_p) {
		case IPPROTO_TCP:
		    {
			struct tcphdr *tcp;

			if (offset == 1)	/* cf. RFC 1858 */
				goto bogusfrag;
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
			PULLUP_TO(hlen + 14);
			tcp = (struct tcphdr *) ((u_long *)ip + ip->ip_hl);
			if (f->fw_tcpf != f->fw_tcpnf && !tcpflg_match(tcp, f))
				continue;
			src_port = ntohs(tcp->th_sport);
			dst_port = ntohs(tcp->th_dport);
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
			PULLUP_TO(hlen + 4);
			udp = (struct udphdr *) ((u_long *)ip + ip->ip_hl);
			src_port = ntohs(udp->uh_sport);
			dst_port = ntohs(udp->uh_dport);
check_ports:
			if (!port_match(&f->fw_pts[0],
			    IP_FW_GETNSRCP(f), src_port,
			    f->fw_flg & IP_FW_F_SRNG))
				continue;
			if (!port_match(&f->fw_pts[IP_FW_GETNSRCP(f)],
			    IP_FW_GETNDSTP(f), dst_port,
			    f->fw_flg & IP_FW_F_DRNG)) 
				continue;
			break;
		    }

		case IPPROTO_ICMP:
		    {
			struct icmp *icmp;

			if (offset != 0)	/* Type isn't valid */
				break;
			PULLUP_TO(hlen + 2);
			icmp = (struct icmp *) ((u_long *)ip + ip->ip_hl);
			if (!icmptype_match(icmp, f))
				continue;
			break;
		    }
#undef PULLUP_TO

bogusfrag:
			if (fw_verbose)
				ipfw_report(NULL, ip, rif, oif);
			goto dropit;
		}

got_match:
		/* Ignore divert/tee rule if socket port is "ignport" */
		switch (f->fw_flg & IP_FW_F_COMMAND) {
		case IP_FW_F_DIVERT:
		case IP_FW_F_TEE:
			if (f->fw_divert_port == ignport)
				continue;       /* ignore this rule */
			break;
		}

		/* Update statistics */
		f->fw_pcnt += 1;
		f->fw_bcnt += ip->ip_len;
		f->timestamp = rtems_bsdnet_seconds_since_boot();

		/* Log to console if desired */
		if ((f->fw_flg & IP_FW_F_PRN) && fw_verbose)
			ipfw_report(f, ip, rif, oif);

		/* Take appropriate action */
		switch (f->fw_flg & IP_FW_F_COMMAND) {
		case IP_FW_F_ACCEPT:
			return(0);
		case IP_FW_F_COUNT:
			continue;
		case IP_FW_F_DIVERT:
			return(f->fw_divert_port);
		case IP_FW_F_TEE:
			/*
			 * XXX someday tee packet here, but beware that you
			 * can't use m_copym() or m_copypacket() because
			 * the divert input routine modifies the mbuf
			 * (and these routines only increment reference
			 * counts in the case of mbuf clusters), so need
			 * to write custom routine.
			 */
			continue;
		case IP_FW_F_SKIPTO:
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
		panic("ip_fw: chain");
#endif

	/*
	 * At this point, we're going to drop the packet.
	 * Send a reject notice if all of the following are true:
	 *
	 * - The packet matched a reject rule
	 * - The packet is not an ICMP packet
	 * - The packet is not a multicast or broadcast packet
	 */
	if ((rule->fw_flg & IP_FW_F_COMMAND) == IP_FW_F_REJECT
	    && ip->ip_p != IPPROTO_ICMP
	    && !((*m)->m_flags & (M_BCAST|M_MCAST))
	    && !IN_MULTICAST(ntohl(ip->ip_dst.s_addr))) {
		switch (rule->fw_reject_code) {
		case IP_FW_REJECT_RST:
		  {
			struct tcphdr *const tcp =
				(struct tcphdr *) ((u_long *)ip + ip->ip_hl);
			struct tcpiphdr ti, *const tip = (struct tcpiphdr *) ip;

			if (offset != 0 || (tcp->th_flags & TH_RST))
				break;
			ti.ti_i = *((struct ipovly *) ip);
			ti.ti_t = *tcp;
			bcopy(&ti, ip, sizeof(ti));
			NTOHL(tip->ti_seq);
			NTOHL(tip->ti_ack);
			tip->ti_len = ip->ip_len - hlen - (tip->ti_off << 2);
			if (tcp->th_flags & TH_ACK) {
				tcp_respond(NULL, tip, *m,
				    (tcp_seq)0, ntohl(tcp->th_ack), TH_RST);
			} else {
				if (tcp->th_flags & TH_SYN)
					tip->ti_len++;
				tcp_respond(NULL, tip, *m, tip->ti_seq
				    + tip->ti_len, (tcp_seq)0, TH_RST|TH_ACK);
			}
			*m = NULL;
			break;
		  }
		default:	/* Send an ICMP unreachable using code */
			icmp_error(*m, ICMP_UNREACH,
			    rule->fw_reject_code, 0L, 0);
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