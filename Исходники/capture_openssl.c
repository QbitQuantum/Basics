int
tls_process_segment(packet_t *packet, struct tcphdr *tcp)
{
    struct SSLConnection *conn;
    const u_char *payload = packet_payload(packet);
    uint32_t size_payload = packet_payloadlen(packet);
    uint8_t *out;
    uint32_t outl = packet->payload_len;
    out = sng_malloc(outl);
    struct in_addr ip_src, ip_dst;
    uint16_t sport = packet->src.port;
    uint16_t dport = packet->dst.port;

    // Convert addresses
    inet_pton(AF_INET, packet->src.ip, &ip_src);
    inet_pton(AF_INET, packet->dst.ip, &ip_dst);

    // Try to find a session for this ip
    if ((conn = tls_connection_find(ip_src, sport))) {
        // Update last connection direction
        conn->direction = tls_connection_dir(conn, ip_src, sport);

        // Check current connection state
        switch (conn->state) {
            case TCP_STATE_SYN:
                // First SYN received, this package must be SYN/ACK
                if (tcp->th_flags & TH_SYN & ~TH_ACK)
                    conn->state = TCP_STATE_SYN_ACK;
                break;
            case TCP_STATE_SYN_ACK:
                // We expect an ACK packet here
                if (tcp->th_flags & ~TH_SYN & TH_ACK)
                    conn->state = TCP_STATE_ESTABLISHED;
                break;
            case TCP_STATE_ACK:
            case TCP_STATE_ESTABLISHED:
                // Process data segment!
                if (tls_process_record(conn, payload, size_payload, &out, &outl) == 0) {
                    if ((int32_t) outl > 0) {
                        packet_set_payload(packet, out, outl);
                        packet_set_type(packet, PACKET_SIP_TLS);
                        return 0;
                    }
                }
                break;
            case TCP_STATE_FIN:
            case TCP_STATE_CLOSED:
                // We can delete this connection
                tls_connection_destroy(conn);
                break;
        }
    } else {
        if (tcp->th_flags & TH_SYN & ~TH_ACK) {
            // New connection, store it status and leave
            tls_connection_create(ip_src, sport, ip_dst, dport);
        }
    }

    sng_free(out);
    return 0;
}