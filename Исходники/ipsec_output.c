/*
 * Loop over a tdb chain, taking into consideration protocol tunneling. The
 * fourth argument is set if the first encapsulation header is already in
 * place.
 */
int
ipsp_process_packet(struct mbuf *m, struct tdb *tdb, int af, int tunalready)
{
	struct timeval tv;
	int i, off, error;
	struct mbuf *mp;
#ifdef INET6
	struct ip6_ext ip6e;
	int nxt;
	int dstopt = 0;
#endif

#ifdef INET
	int setdf = 0;
	struct ip *ip;
#endif /* INET */
#ifdef INET6
	struct ip6_hdr *ip6;
#endif /* INET6 */

	/* Check that the transform is allowed by the administrator. */
	if ((tdb->tdb_sproto == IPPROTO_ESP && !esp_enable) ||
	    (tdb->tdb_sproto == IPPROTO_AH && !ah_enable) ||
	    (tdb->tdb_sproto == IPPROTO_IPCOMP && !ipcomp_enable)) {
		DPRINTF(("ipsp_process_packet(): IPsec outbound packet "
		    "dropped due to policy (check your sysctls)\n"));
		m_freem(m);
		return EHOSTUNREACH;
	}

	/* Sanity check. */
	if (!tdb->tdb_xform) {
		DPRINTF(("ipsp_process_packet(): uninitialized TDB\n"));
		m_freem(m);
		return EHOSTUNREACH;
	}

	/* Check if the SPI is invalid. */
	if (tdb->tdb_flags & TDBF_INVALID) {
		DPRINTF(("ipsp_process_packet(): attempt to use invalid "
		    "SA %s/%08x/%u\n", ipsp_address(tdb->tdb_dst),
		    ntohl(tdb->tdb_spi), tdb->tdb_sproto));
		m_freem(m);
		return ENXIO;
	}

	/* Check that the network protocol is supported */
	switch (tdb->tdb_dst.sa.sa_family) {
#ifdef INET
	case AF_INET:
		break;
#endif /* INET */

#ifdef INET6
	case AF_INET6:
		break;
#endif /* INET6 */

	default:
		DPRINTF(("ipsp_process_packet(): attempt to use "
		    "SA %s/%08x/%u for protocol family %d\n",
		    ipsp_address(tdb->tdb_dst), ntohl(tdb->tdb_spi),
		    tdb->tdb_sproto, tdb->tdb_dst.sa.sa_family));
		m_freem(m);
		return ENXIO;
	}

	/*
	 * Register first use if applicable, setup relevant expiration timer.
	 */
	if (tdb->tdb_first_use == 0) {
		tdb->tdb_first_use = time_second;

		tv.tv_usec = 0;

		tv.tv_sec = tdb->tdb_first_use + tdb->tdb_exp_first_use;
		if (tdb->tdb_flags & TDBF_FIRSTUSE)
			timeout_add(&tdb->tdb_first_tmo,
			    hzto(&tv));

		tv.tv_sec = tdb->tdb_first_use + tdb->tdb_soft_first_use;
		if (tdb->tdb_flags & TDBF_SOFT_FIRSTUSE)
			timeout_add(&tdb->tdb_sfirst_tmo,
			    hzto(&tv));
	}

	/*
	 * Check for tunneling if we don't have the first header in place.
	 * When doing Ethernet-over-IP, we are handed an already-encapsulated
	 * frame, so we don't need to re-encapsulate.
	 */
	if (tunalready == 0) {
		/*
		 * If the target protocol family is different, we know we'll be
		 * doing tunneling.
		 */
		if (af == tdb->tdb_dst.sa.sa_family) {
#ifdef INET
			if (af == AF_INET)
				i = sizeof(struct ip);
#endif /* INET */

#ifdef INET6
			if (af == AF_INET6)
				i = sizeof(struct ip6_hdr);
#endif /* INET6 */

			/* Bring the network header in the first mbuf. */
			if (m->m_len < i) {
				if ((m = m_pullup(m, i)) == NULL)
					return ENOBUFS;
			}

#ifdef INET
			if (af == AF_INET) {
				ip = mtod(m, struct ip *);

				/*
				 * This is not a bridge packet, remember if we
				 * had IP_DF.
				 */
				setdf = ip->ip_off & htons(IP_DF);
			}
#endif /* INET */

#ifdef INET6
			if (af == AF_INET6)
				ip6 = mtod(m, struct ip6_hdr *);
#endif /* INET6 */
		}

		/* Do the appropriate encapsulation, if necessary. */
		if ((tdb->tdb_dst.sa.sa_family != af) || /* PF mismatch */
		    (tdb->tdb_flags & TDBF_TUNNELING) || /* Tunneling needed */
		    (tdb->tdb_xform->xf_type == XF_IP4) || /* ditto */
#ifdef INET
		    ((tdb->tdb_dst.sa.sa_family == AF_INET) &&
			(tdb->tdb_dst.sin.sin_addr.s_addr != INADDR_ANY) &&
			(tdb->tdb_dst.sin.sin_addr.s_addr != ip->ip_dst.s_addr)) ||
#endif /* INET */
#ifdef INET6
		    ((tdb->tdb_dst.sa.sa_family == AF_INET6) &&
			(!IN6_IS_ADDR_UNSPECIFIED(&tdb->tdb_dst.sin6.sin6_addr)) &&
			(!IN6_ARE_ADDR_EQUAL(&tdb->tdb_dst.sin6.sin6_addr,
			    &ip6->ip6_dst))) ||
#endif /* INET6 */
		    0) {
#ifdef INET
			/* Fix IPv4 header checksum and length. */
			if (af == AF_INET) {
				if (m->m_len < sizeof(struct ip))
					if ((m = m_pullup(m,
					    sizeof(struct ip))) == NULL)
						return ENOBUFS;

				ip = mtod(m, struct ip *);
				ip->ip_len = htons(m->m_pkthdr.len);
				ip->ip_sum = 0;
				ip->ip_sum = in_cksum(m, ip->ip_hl << 2);
			}
#endif /* INET */

#ifdef INET6
			/* Fix IPv6 header payload length. */
			if (af == AF_INET6) {
				if (m->m_len < sizeof(struct ip6_hdr))
					if ((m = m_pullup(m,
					    sizeof(struct ip6_hdr))) == NULL)
						return ENOBUFS;

				if (m->m_pkthdr.len - sizeof(*ip6) >
				    IPV6_MAXPACKET) {
					/* No jumbogram support. */
					m_freem(m);
					return ENXIO;	/*?*/
				}
				ip6 = mtod(m, struct ip6_hdr *);
				ip6->ip6_plen = htons(m->m_pkthdr.len
				    - sizeof(*ip6));
			}
#endif /* INET6 */

			/* Encapsulate -- the last two arguments are unused. */
			error = ipip_output(m, tdb, &mp, 0, 0);
			if ((mp == NULL) && (!error))
				error = EFAULT;
			if (error) {
				if (mp)	{
					m_freem(mp);
					mp = NULL;
				}
				return error;
			}

			m = mp;
			mp = NULL;

#ifdef INET
			if (tdb->tdb_dst.sa.sa_family == AF_INET && setdf) {
				if (m->m_len < sizeof(struct ip))
					if ((m = m_pullup(m,
					    sizeof(struct ip))) == NULL)
						return ENOBUFS;

				ip = mtod(m, struct ip *);
				ip->ip_off |= htons(IP_DF);
			}
#endif

			/* Remember that we appended a tunnel header. */
			tdb->tdb_flags |= TDBF_USEDTUNNEL;
		}

		/* We may be done with this TDB */
		if (tdb->tdb_xform->xf_type == XF_IP4)
			return ipsp_process_done(m, tdb);
	} else {