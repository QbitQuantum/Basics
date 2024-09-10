int
libnet_write_raw_ipv4(libnet_t *l, const uint8_t *packet, uint32_t size)
{
    int c;
    struct sockaddr_in sin;
    struct libnet_ipv4_hdr *ip_hdr;

    if (l == NULL)
    { 
        return (-1);
    } 

    ip_hdr = (struct libnet_ipv4_hdr *)packet;

#if (LIBNET_BSD_BYTE_SWAP)
    /*
     *  For link access, we don't need to worry about the inconsistencies of
     *  certain BSD kernels.  However, raw socket nuances abound.  Certain
     *  BSD implmentations require the ip_len and ip_off fields to be in host
     *  byte order.
     */
    ip_hdr->ip_len = FIX(ip_hdr->ip_len);
    ip_hdr->ip_off = FIX(ip_hdr->ip_off);
#endif /* LIBNET_BSD_BYTE_SWAP */

    memset(&sin, 0, sizeof(sin));
    sin.sin_family  = AF_INET;
    sin.sin_addr.s_addr = ip_hdr->ip_dst.s_addr;
#if (__WIN32__)
    /* set port for TCP */
    /*
     *  XXX - should first check to see if there's a pblock for a TCP
     *  header, if not we can use a dummy value for the port.
     */
    if (ip_hdr->ip_p == 6)
    {
        struct libnet_tcp_hdr *tcph_p =
                (struct libnet_tcp_hdr *)(packet + (ip_hdr->ip_hl << 2));
        sin.sin_port = tcph_p->th_dport;
    }
    /* set port for UDP */
    /*
     *  XXX - should first check to see if there's a pblock for a UDP
     *  header, if not we can use a dummy value for the port.
     */
    else if (ip_hdr->ip_p == 17)
    {
        struct libnet_udp_hdr *udph_p =
                (struct libnet_udp_hdr *)(packet + (ip_hdr->ip_hl << 2));
       sin.sin_port = udph_p->uh_dport;
    }
#endif /* __WIN32__ */

    c = sendto(l->fd, packet, size, 0, (struct sockaddr *)&sin,
            sizeof(sin));

#if (LIBNET_BSD_BYTE_SWAP)
    ip_hdr->ip_len = UNFIX(ip_hdr->ip_len);
    ip_hdr->ip_off = UNFIX(ip_hdr->ip_off);
#endif /* LIBNET_BSD_BYTE_SWAP */

    if (c != size)
    {
#if !(__WIN32__)
        snprintf(l->err_buf, LIBNET_ERRBUF_SIZE,
                "%s(): %d bytes written (%s)", __func__, c,
                strerror(errno));
#else /* __WIN32__ */
        snprintf(l->err_buf, LIBNET_ERRBUF_SIZE,
                "%s(): %d bytes written (%d)", __func__, c,
                WSAGetLastError());
#endif /* !__WIN32__ */
    }
    return (c);
}