/*
 * Ip input routine.  Checksum and byte swap header.  If fragmented
 * try to reassemble.  Process options.  Pass to next level.
 */
void
ip_input(PNATState pData, struct mbuf *m)
{
    register struct ip *ip;
    int hlen = 0;
    int mlen = 0;

    STAM_PROFILE_START(&pData->StatIP_input, a);

    LogFlowFunc(("ENTER: m = %lx\n", (long)m));
    ip = mtod(m, struct ip *);
    Log2(("ip_dst=%RTnaipv4(len:%d) m_len = %d\n", ip->ip_dst, RT_N2H_U16(ip->ip_len), m->m_len));

    ipstat.ips_total++;
    {
        int rc;
        STAM_PROFILE_START(&pData->StatALIAS_input, b);
        rc = LibAliasIn(select_alias(pData, m), mtod(m, char *), m_length(m, NULL));
        STAM_PROFILE_STOP(&pData->StatALIAS_input, b);
        Log2(("NAT: LibAlias return %d\n", rc));
        if (m->m_len != RT_N2H_U16(ip->ip_len))
            m->m_len = RT_N2H_U16(ip->ip_len);
    }

    mlen = m->m_len;

    if (mlen < sizeof(struct ip))
    {
        ipstat.ips_toosmall++;
        goto bad_free_m;
    }

    ip = mtod(m, struct ip *);
    if (ip->ip_v != IPVERSION)
    {
        ipstat.ips_badvers++;
        goto bad_free_m;
    }

    hlen = ip->ip_hl << 2;
    if (   hlen < sizeof(struct ip)
        || hlen > m->m_len)
    {
        /* min header length */
        ipstat.ips_badhlen++;                     /* or packet too short */
        goto bad_free_m;
    }

    /* keep ip header intact for ICMP reply
     * ip->ip_sum = cksum(m, hlen);
     * if (ip->ip_sum) {
     */
    if (cksum(m, hlen))
    {
        ipstat.ips_badsum++;
        goto bad_free_m;
    }

    /*
     * Convert fields to host representation.
     */
    NTOHS(ip->ip_len);
    if (ip->ip_len < hlen)
    {
        ipstat.ips_badlen++;
        goto bad_free_m;
    }

    NTOHS(ip->ip_id);
    NTOHS(ip->ip_off);

    /*
     * Check that the amount of data in the buffers
     * is as at least much as the IP header would have us expect.
     * Trim mbufs if longer than we expect.
     * Drop packet if shorter than we expect.
     */
    if (mlen < ip->ip_len)
    {
        ipstat.ips_tooshort++;
        goto bad_free_m;
    }

    /* Should drop packet if mbuf too long? hmmm... */
    if (mlen > ip->ip_len)
        m_adj(m, ip->ip_len - m->m_len);

    /* check ip_ttl for a correct ICMP reply */
    if (ip->ip_ttl==0 || ip->ip_ttl == 1)
    {
        icmp_error(pData, m, ICMP_TIMXCEED, ICMP_TIMXCEED_INTRANS, 0, "ttl");
        goto no_free_m;
    }

    ip->ip_ttl--;
    /*
     * If offset or IP_MF are set, must reassemble.
     * Otherwise, nothing need be done.
     * (We could look in the reassembly queue to see
     * if the packet was previously fragmented,
     * but it's not worth the time; just let them time out.)
     *
     */
    if (ip->ip_off & (IP_MF | IP_OFFMASK))
    {
        m = ip_reass(pData, m);
        if (m == NULL)
            goto no_free_m;
        ip = mtod(m, struct ip *);
        hlen = ip->ip_hl << 2;
    }