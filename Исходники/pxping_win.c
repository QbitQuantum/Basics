static void
pxping_icmp6_callback(struct pong6 *pong)
{
    DWORD nreplies;
    ICMPV6_ECHO_REPLY *reply;
    struct pbuf *p;
    struct icmp6_echo_hdr *icmph;
    size_t icmplen;
    ip6_addr_t src;
    int mapped;

    nreplies = Icmp6ParseReplies(pong->buf, (DWORD)pong->bufsize);
    if (nreplies == 0) {
        DWORD error = GetLastError();
        if (error == IP_REQ_TIMED_OUT) {
            DPRINTF2(("pong6: %p timed out\n", (void *)pong));
        }
        else {
            DPRINTF(("pong6: %p: Icmp6ParseReplies: error %d\n",
                     (void *)pong, error));
        }
        return;
    }

    reply = (ICMPV6_ECHO_REPLY *)pong->buf;

    mapped = pxremap_inbound_ip6(&src, (ip6_addr_t *)reply->Address.sin6_addr);
    if (mapped == PXREMAP_FAILED) {
        return;
    }

    /*
     * Reply data follows ICMPV6_ECHO_REPLY structure in memory, but
     * it doesn't tell us its size.  Assume it's equal the size of the
     * request.
     */
    icmplen = sizeof(*icmph) + pong->reqsize;
    p = pbuf_alloc(PBUF_IP, (u16_t)icmplen, PBUF_RAM);
    if (RT_UNLIKELY(p == NULL)) {
        return;
    }

    icmph = (struct icmp6_echo_hdr *)p->payload;
    icmph->type = ICMP6_TYPE_EREP;
    icmph->code = 0;
    icmph->chksum = 0;
    icmph->id = pong->reqicmph.id;
    icmph->seqno = pong->reqicmph.seqno;

    memcpy((u8_t *)p->payload + sizeof(*icmph),
           pong->buf + sizeof(*reply), pong->reqsize);

    icmph->chksum = ip6_chksum_pseudo(p, IP6_NEXTH_ICMP6, p->tot_len,
                                      &src, &pong->reqsrc);
    ip6_output_if(p, /* :src */ &src, /* :dst */ &pong->reqsrc,
                  LWIP_ICMP6_HL, 0, IP6_NEXTH_ICMP6,
                  pong->netif);
    pbuf_free(p);
}