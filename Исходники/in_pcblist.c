__private_extern__ void
inpcb_get_ports_used(uint32_t ifindex, int protocol, uint32_t flags,
    bitstr_t *bitfield, struct inpcbinfo *pcbinfo)
{
	struct inpcb *inp;
	struct socket *so;
	inp_gen_t gencnt;
	bool iswildcard, wildcardok, nowakeok;
	bool recvanyifonly, extbgidleok;
	bool activeonly;

	wildcardok = ((flags & INPCB_GET_PORTS_USED_WILDCARDOK) != 0);
	nowakeok = ((flags & INPCB_GET_PORTS_USED_NOWAKEUPOK) != 0);
	recvanyifonly = ((flags & INPCB_GET_PORTS_USED_RECVANYIFONLY) != 0);
	extbgidleok = ((flags & INPCB_GET_PORTS_USED_EXTBGIDLEONLY) != 0);
	activeonly = ((flags & INPCB_GET_PORTS_USED_ACTIVEONLY) != 0);

	lck_rw_lock_shared(pcbinfo->ipi_lock);
	gencnt = pcbinfo->ipi_gencnt;

	for (inp = LIST_FIRST(pcbinfo->ipi_listhead); inp;
	    inp = LIST_NEXT(inp, inp_list)) {
		uint16_t port;

		if (inp->inp_gencnt > gencnt ||
		    inp->inp_state == INPCB_STATE_DEAD ||
		    inp->inp_wantcnt == WNT_STOPUSING)
			continue;

		if ((so = inp->inp_socket) == NULL ||
		    (so->so_state & SS_DEFUNCT) ||
		    (so->so_state & SS_ISDISCONNECTED))
			continue;

		/*
		 * If protocol is specified, filter out inpcbs that
		 * are not relevant to the protocol family of interest.
		 */
		if (protocol != PF_UNSPEC) {
			if (protocol == PF_INET) {
				/*
				 * If protocol of interest is IPv4, skip the inpcb
				 * if the family is not IPv4.
				 * OR
				 * If the family is IPv4, skip if the IPv4 flow is
				 * CLAT46 translated.
				 */
				if ((inp->inp_vflag & INP_IPV4) == 0 ||
				    (inp->inp_flags2 & INP2_CLAT46_FLOW) != 0) {
					continue;
				}
			} else if (protocol == PF_INET6) {
				/*
				 * If protocol of interest is IPv6, skip the inpcb
				 * if the family is not IPv6.
				 * AND
				 * The flow is not a CLAT46'd flow.
				 */
				if ((inp->inp_vflag & INP_IPV6) == 0 &&
				    (inp->inp_flags2 & INP2_CLAT46_FLOW) == 0) {
					continue;
				}
			} else {
				/* Protocol family not supported */
				continue;
			}
		}

		if (SOCK_PROTO(inp->inp_socket) != IPPROTO_UDP &&
		    SOCK_PROTO(inp->inp_socket) != IPPROTO_TCP)
			continue;

		iswildcard = (((inp->inp_vflag & INP_IPV4) &&
		    inp->inp_laddr.s_addr == INADDR_ANY) ||
		    ((inp->inp_vflag & INP_IPV6) &&
		    IN6_IS_ADDR_UNSPECIFIED(&inp->in6p_laddr)));

		if (!wildcardok && iswildcard)
			continue;

		if ((so->so_options & SO_NOWAKEFROMSLEEP) &&
			!nowakeok)
			continue;

		if (!(inp->inp_flags & INP_RECV_ANYIF) &&
			recvanyifonly)
			continue;

		if (!(so->so_flags1 & SOF1_EXTEND_BK_IDLE_WANTED) &&
			extbgidleok)
			continue;

		if (!iswildcard &&
		    !(ifindex == 0 || inp->inp_last_outifp == NULL ||
		    ifindex == inp->inp_last_outifp->if_index))
			continue;

		if (SOCK_PROTO(inp->inp_socket) == IPPROTO_UDP &&
		    so->so_state & SS_CANTRCVMORE)
			continue;

		if (SOCK_PROTO(inp->inp_socket) == IPPROTO_TCP) {
			struct  tcpcb *tp = sototcpcb(inp->inp_socket);

			/*
			 * Workaround race where inp_ppcb is NULL during
			 * socket initialization
			 */
			if (tp == NULL)
				continue;

			switch (tp->t_state) {
				case TCPS_CLOSED:
					continue;
					/* NOT REACHED */
				case TCPS_LISTEN:
				case TCPS_SYN_SENT:
				case TCPS_SYN_RECEIVED:
				case TCPS_ESTABLISHED:
				case TCPS_FIN_WAIT_1:
					/*
					 * Note: FIN_WAIT_1 is an active state
					 * because we need our FIN to be
					 * acknowledged
					 */
					break;
				case TCPS_CLOSE_WAIT:
				case TCPS_CLOSING:
				case TCPS_LAST_ACK:
				case TCPS_FIN_WAIT_2:
					/*
					 * In the closing states, the connection
					 * is not idle when there is outgoing
					 * data having to be acknowledged
					 */
					if (activeonly && so->so_snd.sb_cc == 0)
						continue;
					break;
				case TCPS_TIME_WAIT:
					continue;
					/* NOT REACHED */
			}
		}
		/*
		 * Final safeguard to exclude unspecified local port
		 */
		port = ntohs(inp->inp_lport);
		if (port == 0)
			continue;
		bitstr_set(bitfield, port);

		if_ports_used_add_inpcb(ifindex, inp);
	}
	lck_rw_done(pcbinfo->ipi_lock);
}