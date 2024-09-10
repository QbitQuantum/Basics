static
int decode_tcp_hdr(struct tcphdr *tcphd)
{
    cprintf("TCP Header\n");
    cprintf("SRC Port:\t%d\n", NTOHS(tcphd->tcp_source));
    cprintf("DST Port:\t%d\n", NTOHS(tcphd->tcp_dest));
    cprintf("seq #:   \t%lu\n", (long)NTOHL(tcphd->tcp_seq));
    cprintf("ack #:   \t%lu\n", (long)NTOHL(tcphd->tcp_ack_seq));
    cprintf("hdr len: \t%d\n", tcphd->tcp_doff * 4);
    cprintf("rst:     \t%d\n", tcphd->tcp_rst);
    cprintf("syn:     \t%d\n", tcphd->tcp_syn);
    cprintf("fin:     \t%d\n", tcphd->tcp_fin);
    cprintf("window:  \t%d\n", NTOHS(tcphd->tcp_window));
    cprintf("cksum:   \t%d\n", NTOHS(tcphd->tcp_sum));
    cprintf("urg_ptr: \t%d\n", NTOHS(tcphd->tcp_urg_ptr));
    cprintf("P: %d, A: %d, U: %d, R1: %d, R2: %d\n",
            tcphd->tcp_psh, tcphd->tcp_ack, tcphd->tcp_urg, tcphd->tcp_res1,
            tcphd->tcp_res2);

    return 0;
}