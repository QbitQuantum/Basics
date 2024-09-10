void
ip6_forward(struct mbuf *m, int srcrt)
{
    struct ip6_hdr *ip6 = mtod(m, struct ip6_hdr *);
    struct sockaddr_in6 *dst;
    struct rtentry *rt;
    int error = 0, type = 0, code = 0;
    struct mbuf *mcopy = NULL;
#ifdef IPSEC
    u_int8_t sproto = 0;
    struct m_tag *mtag;
    union sockaddr_union sdst;
    struct tdb_ident *tdbi;
    u_int32_t sspi;
    struct tdb *tdb;
#if NPF > 0
    struct ifnet *encif;
#endif
#endif /* IPSEC */
    u_int rtableid = 0;
    char src6[INET6_ADDRSTRLEN], dst6[INET6_ADDRSTRLEN];

    /*
     * Do not forward packets to multicast destination (should be handled
     * by ip6_mforward().
     * Do not forward packets with unspecified source.  It was discussed
     * in July 2000, on ipngwg mailing list.
     */
    if ((m->m_flags & (M_BCAST|M_MCAST)) != 0 ||
            IN6_IS_ADDR_MULTICAST(&ip6->ip6_dst) ||
            IN6_IS_ADDR_UNSPECIFIED(&ip6->ip6_src)) {
        ip6stat.ip6s_cantforward++;
        if (ip6_log_time + ip6_log_interval < time_second) {
            ip6_log_time = time_second;
            inet_ntop(AF_INET6, &ip6->ip6_src, src6, sizeof(src6));
            inet_ntop(AF_INET6, &ip6->ip6_dst, dst6, sizeof(dst6));
            log(LOG_DEBUG,
                "cannot forward "
                "from %s to %s nxt %d received on inteface %u\n",
                src6, dst6,
                ip6->ip6_nxt,
                m->m_pkthdr.ph_ifidx);
        }
        m_freem(m);
        return;
    }

    if (ip6->ip6_hlim <= IPV6_HLIMDEC) {
        icmp6_error(m, ICMP6_TIME_EXCEEDED,
                    ICMP6_TIME_EXCEED_TRANSIT, 0);
        return;
    }
    ip6->ip6_hlim -= IPV6_HLIMDEC;

    /*
     * Save at most ICMPV6_PLD_MAXLEN (= the min IPv6 MTU -
     * size of IPv6 + ICMPv6 headers) bytes of the packet in case
     * we need to generate an ICMP6 message to the src.
     * Thanks to M_EXT, in most cases copy will not occur.
     *
     * It is important to save it before IPsec processing as IPsec
     * processing may modify the mbuf.
     */
    mcopy = m_copym(m, 0, imin(m->m_pkthdr.len, ICMPV6_PLD_MAXLEN),
                    M_NOWAIT);

#if NPF > 0
reroute:
#endif

#ifdef IPSEC
    if (!ipsec_in_use)
        goto done_spd;

    /*
     * Check if there was an outgoing SA bound to the flow
     * from a transport protocol.
     */

    /* Do we have any pending SAs to apply ? */
    tdb = ipsp_spd_lookup(m, AF_INET6, sizeof(struct ip6_hdr),
                          &error, IPSP_DIRECTION_OUT, NULL, NULL, 0);

    if (tdb == NULL) {
        if (error == 0) {
            /*
            * No IPsec processing required, we'll just send the
             * packet out.
             */
            sproto = 0;

            /* Fall through to routing/multicast handling */
        } else {
            /*
            * -EINVAL is used to indicate that the packet should
             * be silently dropped, typically because we've asked
             * key management for an SA.
             */
            if (error == -EINVAL) /* Should silently drop packet */
                error = 0;

            m_freem(m);
            goto freecopy;
        }
    } else {
        /* Loop detection */
        for (mtag = m_tag_first(m); mtag != NULL;
                mtag = m_tag_next(m, mtag)) {
            if (mtag->m_tag_id != PACKET_TAG_IPSEC_OUT_DONE)
                continue;
            tdbi = (struct tdb_ident *)(mtag + 1);
            if (tdbi->spi == tdb->tdb_spi &&
                    tdbi->proto == tdb->tdb_sproto &&
                    tdbi->rdomain == tdb->tdb_rdomain &&
                    !bcmp(&tdbi->dst, &tdb->tdb_dst,
                          sizeof(union sockaddr_union))) {
                sproto = 0; /* mark as no-IPsec-needed */
                goto done_spd;
            }
        }

        /* We need to do IPsec */
        bcopy(&tdb->tdb_dst, &sdst, sizeof(sdst));
        sspi = tdb->tdb_spi;
        sproto = tdb->tdb_sproto;
    }

    /* Fall through to the routing/multicast handling code */
done_spd:
#endif /* IPSEC */

#if NPF > 0
    rtableid = m->m_pkthdr.ph_rtableid;
#endif

    dst = &ip6_forward_rt.ro_dst;
    if (!srcrt) {
        /*
         * ip6_forward_rt.ro_dst.sin6_addr is equal to ip6->ip6_dst
         */
        if (ip6_forward_rt.ro_rt == NULL ||
                (ip6_forward_rt.ro_rt->rt_flags & RTF_UP) == 0 ||
                ip6_forward_rt.ro_tableid != rtableid) {
            if (ip6_forward_rt.ro_rt) {
                rtfree(ip6_forward_rt.ro_rt);
                ip6_forward_rt.ro_rt = NULL;
            }
            /* this probably fails but give it a try again */
            ip6_forward_rt.ro_tableid = rtableid;
            ip6_forward_rt.ro_rt = rtalloc_mpath(
                                       sin6tosa(&ip6_forward_rt.ro_dst),
                                       &ip6->ip6_src.s6_addr32[0],
                                       ip6_forward_rt.ro_tableid);
        }

        if (ip6_forward_rt.ro_rt == NULL) {
            ip6stat.ip6s_noroute++;
            if (mcopy) {
                icmp6_error(mcopy, ICMP6_DST_UNREACH,
                            ICMP6_DST_UNREACH_NOROUTE, 0);
            }
            m_freem(m);
            return;
        }
    } else if (ip6_forward_rt.ro_rt == NULL ||
               (ip6_forward_rt.ro_rt->rt_flags & RTF_UP) == 0 ||
               !IN6_ARE_ADDR_EQUAL(&ip6->ip6_dst, &dst->sin6_addr) ||
               ip6_forward_rt.ro_tableid != rtableid) {
        if (ip6_forward_rt.ro_rt) {
            rtfree(ip6_forward_rt.ro_rt);
            ip6_forward_rt.ro_rt = NULL;
        }
        bzero(dst, sizeof(*dst));
        dst->sin6_len = sizeof(struct sockaddr_in6);
        dst->sin6_family = AF_INET6;
        dst->sin6_addr = ip6->ip6_dst;
        ip6_forward_rt.ro_tableid = rtableid;
        ip6_forward_rt.ro_rt = rtalloc_mpath(
                                   sin6tosa(&ip6_forward_rt.ro_dst),
                                   &ip6->ip6_src.s6_addr32[0],
                                   ip6_forward_rt.ro_tableid);

        if (ip6_forward_rt.ro_rt == NULL) {
            ip6stat.ip6s_noroute++;
            if (mcopy) {
                icmp6_error(mcopy, ICMP6_DST_UNREACH,
                            ICMP6_DST_UNREACH_NOROUTE, 0);
            }
            m_freem(m);
            return;
        }
    }
    rt = ip6_forward_rt.ro_rt;

    /*
     * Scope check: if a packet can't be delivered to its destination
     * for the reason that the destination is beyond the scope of the
     * source address, discard the packet and return an icmp6 destination
     * unreachable error with Code 2 (beyond scope of source address).
     * [draft-ietf-ipngwg-icmp-v3-00.txt, Section 3.1]
     */
    if (in6_addr2scopeid(m->m_pkthdr.ph_ifidx, &ip6->ip6_src) !=
            in6_addr2scopeid(rt->rt_ifp->if_index, &ip6->ip6_src)) {
        ip6stat.ip6s_cantforward++;
        ip6stat.ip6s_badscope++;

        if (ip6_log_time + ip6_log_interval < time_second) {
            ip6_log_time = time_second;
            inet_ntop(AF_INET6, &ip6->ip6_src, src6, sizeof(src6));
            inet_ntop(AF_INET6, &ip6->ip6_dst, dst6, sizeof(dst6));
            log(LOG_DEBUG,
                "cannot forward "
                "src %s, dst %s, nxt %d, rcvif %u, outif %u\n",
                src6, dst6,
                ip6->ip6_nxt,
                m->m_pkthdr.ph_ifidx, rt->rt_ifp->if_index);
        }
        if (mcopy)
            icmp6_error(mcopy, ICMP6_DST_UNREACH,
                        ICMP6_DST_UNREACH_BEYONDSCOPE, 0);
        m_freem(m);
        goto freert;
    }

#ifdef IPSEC
    /*
     * Check if the packet needs encapsulation.
     * ipsp_process_packet will never come back to here.
     * XXX ipsp_process_packet() calls ip6_output(), and there'll be no
     * PMTU notification.  is it okay?
     */
    if (sproto != 0) {
        tdb = gettdb(rtable_l2(m->m_pkthdr.ph_rtableid),
                     sspi, &sdst, sproto);
        if (tdb == NULL) {
            error = EHOSTUNREACH;
            m_freem(m);
            goto senderr;	/*XXX*/
        }

#if NPF > 0
        if ((encif = enc_getif(tdb->tdb_rdomain,
                               tdb->tdb_tap)) == NULL ||
                pf_test(AF_INET6, PF_FWD, encif, &m) != PF_PASS) {
            error = EHOSTUNREACH;
            m_freem(m);
            goto senderr;
        }
        if (m == NULL)
            goto senderr;
        ip6 = mtod(m, struct ip6_hdr *);
        /*
         * PF_TAG_REROUTE handling or not...
         * Packet is entering IPsec so the routing is
         * already overruled by the IPsec policy.
         * Until now the change was not reconsidered.
         * What's the behaviour?
         */
        in6_proto_cksum_out(m, encif);
#endif
        m->m_flags &= ~(M_BCAST | M_MCAST);	/* just in case */

        /* Callee frees mbuf */
        error = ipsp_process_packet(m, tdb, AF_INET6, 0);
        m_freem(mcopy);
        goto freert;
    }