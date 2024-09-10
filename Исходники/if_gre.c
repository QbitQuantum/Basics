int
gre_output(struct ifnet *ifp, struct mbuf *m, struct sockaddr *dst,
	   struct rtentry *rt)
{
	int error = 0;
	struct gre_softc *sc = (struct gre_softc *) (ifp->if_softc);
	struct greip *gh = NULL;
	struct ip *inp = NULL;
	u_int8_t ip_tos = 0;
	u_int16_t etype = 0;
	struct mobile_h mob_h;
	struct m_tag *mtag;

	if ((ifp->if_flags & IFF_UP) == 0 ||
	    sc->g_src.s_addr == INADDR_ANY || sc->g_dst.s_addr == INADDR_ANY) {
		m_freem(m);
		error = ENETDOWN;
		goto end;
	}

#ifdef DIAGNOSTIC
	if (ifp->if_rdomain != rtable_l2(m->m_pkthdr.ph_rtableid)) {
		printf("%s: trying to send packet on wrong domain. "
		    "if %d vs. mbuf %d, AF %d\n", ifp->if_xname,
		    ifp->if_rdomain, rtable_l2(m->m_pkthdr.ph_rtableid),
		    dst->sa_family);
	}
#endif

	/* Try to limit infinite recursion through misconfiguration. */
	for (mtag = m_tag_find(m, PACKET_TAG_GRE, NULL); mtag;
	     mtag = m_tag_find(m, PACKET_TAG_GRE, mtag)) {
		if (!bcmp((caddr_t)(mtag + 1), &ifp, sizeof(struct ifnet *))) {
			IF_DROP(&ifp->if_snd);
			m_freem(m);
			error = EIO;
			goto end;
		}
	}

	mtag = m_tag_get(PACKET_TAG_GRE, sizeof(struct ifnet *), M_NOWAIT);
	if (mtag == NULL) {
		IF_DROP(&ifp->if_snd);
		m_freem(m);
		error = ENOBUFS;
		goto end;
	}
	bcopy(&ifp, (caddr_t)(mtag + 1), sizeof(struct ifnet *));
	m_tag_prepend(m, mtag);

	m->m_flags &= ~(M_BCAST|M_MCAST);

#if NBPFILTER > 0
	if (ifp->if_bpf)
		bpf_mtap_af(ifp->if_bpf, dst->sa_family, m, BPF_DIRECTION_OUT);
#endif

	if (sc->g_proto == IPPROTO_MOBILE) {
		if (ip_mobile_allow == 0) {
			IF_DROP(&ifp->if_snd);
			m_freem(m);
			error = EACCES;
			goto end;
		}

		if (dst->sa_family == AF_INET) {
			struct mbuf *m0;
			int msiz;

			/*
			 * Make sure the complete IP header (with options)
			 * is in the first mbuf.
			 */
			if (m->m_len < sizeof(struct ip)) {
				m = m_pullup(m, sizeof(struct ip));
				if (m == NULL) {
					IF_DROP(&ifp->if_snd);
					error = ENOBUFS;
					goto end;
				} else
					inp = mtod(m, struct ip *);

				if (m->m_len < inp->ip_hl << 2) {
					m = m_pullup(m, inp->ip_hl << 2);
					if (m == NULL) {
						IF_DROP(&ifp->if_snd);
						error = ENOBUFS;
						goto end;
					}
				}
			}

			inp = mtod(m, struct ip *);

			bzero(&mob_h, MOB_H_SIZ_L);
			mob_h.proto = (inp->ip_p) << 8;
			mob_h.odst = inp->ip_dst.s_addr;
			inp->ip_dst.s_addr = sc->g_dst.s_addr;

			/*
			 * If the packet comes from our host, we only change
			 * the destination address in the IP header.
			 * Otherwise we need to save and change the source.
			 */
			if (inp->ip_src.s_addr == sc->g_src.s_addr) {
				msiz = MOB_H_SIZ_S;
			} else {
				mob_h.proto |= MOB_H_SBIT;
				mob_h.osrc = inp->ip_src.s_addr;
				inp->ip_src.s_addr = sc->g_src.s_addr;
				msiz = MOB_H_SIZ_L;
			}

			HTONS(mob_h.proto);
			mob_h.hcrc = gre_in_cksum((u_int16_t *) &mob_h, msiz);

			/* Squeeze in the mobility header */
			if ((m->m_data - msiz) < m->m_pktdat) {
				/* Need new mbuf */
				MGETHDR(m0, M_DONTWAIT, MT_HEADER);
				if (m0 == NULL) {
					IF_DROP(&ifp->if_snd);
					m_freem(m);
					error = ENOBUFS;
					goto end;
				}
				M_MOVE_HDR(m0, m);

				m0->m_len = msiz + (inp->ip_hl << 2);
				m0->m_data += max_linkhdr;
				m0->m_pkthdr.len = m->m_pkthdr.len + msiz;
				m->m_data += inp->ip_hl << 2;
				m->m_len -= inp->ip_hl << 2;

				bcopy((caddr_t) inp, mtod(m0, caddr_t),
				    sizeof(struct ip));

				m0->m_next = m;
				m = m0;
			} else {  /* we have some space left in the old one */
				m->m_data -= msiz;
				m->m_len += msiz;
				m->m_pkthdr.len += msiz;
				bcopy(inp, mtod(m, caddr_t),
				    inp->ip_hl << 2);
			}

			/* Copy Mobility header */
			inp = mtod(m, struct ip *);
			bcopy(&mob_h, (caddr_t)(inp + 1), (unsigned) msiz);
			inp->ip_len = htons(ntohs(inp->ip_len) + msiz);
		} else {  /* AF_INET */