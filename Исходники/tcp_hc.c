socket_internal_t *decompress_tcp_packet(ipv6_hdr_t *temp_ipv6_header)
{
    uint8_t *packet_buffer = ((uint8_t *)temp_ipv6_header) + IPV6_HDR_LEN;
    uint16_t tcp_hc_header;
    socket_internal_t *current_socket = NULL;
    uint16_t packet_size = 0;

    /* Full header TCP segment */
    if (*(((uint8_t *)temp_ipv6_header) + IPV6_HDR_LEN) == 0x01) {
        switch_tcp_packet_byte_order(((tcp_hdr_t *)(((uint8_t *)temp_ipv6_header) +
                                      IPV6_HDR_LEN + 3)));
        current_socket = get_tcp_socket(temp_ipv6_header,
                                        ((tcp_hdr_t *)(((uint8_t *)temp_ipv6_header) +
                                                IPV6_HDR_LEN + 3)));

        if (current_socket != NULL) {
            if (current_socket->socket_values.tcp_control.state == LISTEN) {
                memcpy(&current_socket->socket_values.tcp_control.tcp_context.context_id,
                       ((uint8_t *)temp_ipv6_header) + IPV6_HDR_LEN + 1, 2);
                current_socket->socket_values.tcp_control.tcp_context.context_id =
                    NTOHS(current_socket->socket_values.tcp_control.tcp_context.context_id);
            }

            memmove(((uint8_t *)temp_ipv6_header) + IPV6_HDR_LEN,
                    (((uint8_t *)temp_ipv6_header) + IPV6_HDR_LEN + 3),
                    temp_ipv6_header->length - 3);
            temp_ipv6_header->length -= 3;
            return current_socket;
        }
        else {
            printf("Socket Null!\n");
            /* Found no matching socket for this packet -> Drop it */
            return NULL;
        }
    }
    /* Compressed header TCP segment */
    else {
        /* Temporary TCP Header */
        tcp_hdr_t full_tcp_header;
        memset(&full_tcp_header, 0, sizeof(tcp_hdr_t));

        /* Current context ID */
        uint16_t current_context;
        memcpy(&current_context, (packet_buffer + 2), 2);
        current_context = NTOHS(current_context);

        /* Copy TCP_HC header into local variable
         * (1,0,0,1|SEQ,SEQ,0)(1,0,0,1|0,0,0,0) */
        memcpy(&tcp_hc_header, packet_buffer, 2);
        tcp_hc_header = NTOHS(tcp_hc_header);

        uint8_t header_type = UNDEFINED;

        if (BITSET(tcp_hc_header, 15) && !BITSET(tcp_hc_header, 14) &&
            !BITSET(tcp_hc_header, 13)) {
            header_type = MOSTLY_COMPRESSED_HEADER;
        }
        else if (BITSET(tcp_hc_header, 15) && BITSET(tcp_hc_header, 14) &&
                 !BITSET(tcp_hc_header, 13)) {
            header_type = COMPRESSED_HEADER;
        }

        /* Setting pointer to first tcp_hc field */
        packet_buffer += 4;
        packet_size += 4;

        /* Current socket */
        socket_internal_t *current_socket =
            get_tcp_socket_by_context(temp_ipv6_header, current_context);

        if (current_socket == NULL) {
            printf("Current Socket == NULL!\n");
            return NULL;
        }

        /* Current TCP Context values */
        tcp_hc_context_t *current_tcp_context =
            &current_socket->socket_values.tcp_control.tcp_context;

        /*----------------------------------*/
        /*|     Sequence number handling   |*/
        /*----------------------------------*/
        if (!BITSET(tcp_hc_header, 11) && !BITSET(tcp_hc_header, 10)) {
            /* Seq = (0|0), sequence number didn't change, copy old value */
            memcpy(&full_tcp_header.seq_nr, &current_tcp_context->seq_rcv, 4);
        }
        /* The 24 most significant bits haven't changed from previous packet */
        else if (!BITSET(tcp_hc_header, 11) && BITSET(tcp_hc_header, 10)) {
            /* Seq = (0|1), copy 1 byte of tcp_hc packet and 3 bytes from
             * previous packet */
            full_tcp_header.seq_nr |= *packet_buffer;
            full_tcp_header.seq_nr |= ((current_tcp_context->seq_rcv) &
                                       0xFFFFFF00);
            packet_buffer += 1;
            packet_size += 1;
        }
        /* If the 16 most significant bits haven't changed from previous packet */
        else if (BITSET(tcp_hc_header, 11) && !BITSET(tcp_hc_header, 10)) {
            /* Seq = (1|0), copy 2 bytes of tcp_hc packet and 2 bytes from
             * previous packet */
            full_tcp_header.seq_nr |= NTOHS(*((uint16_t *)packet_buffer));
            full_tcp_header.seq_nr |= ((current_tcp_context->seq_rcv) & 0xFFFF0000);
            packet_buffer += 2;
            packet_size += 2;
        }
        /* Sending uncompressed sequence number */
        else {
            /* Seq = (1|1), copy 4 bytes of tcp_hc packet */
            memcpy(&full_tcp_header.seq_nr, packet_buffer, 4);
            full_tcp_header.seq_nr = NTOHL(full_tcp_header.seq_nr);
            packet_buffer += 4;
            packet_size += 4;
        }

        /*----------------------------------*/
        /*| Acknowledgment number handling |*/
        /*----------------------------------*/
        if (!BITSET(tcp_hc_header, 9) && !BITSET(tcp_hc_header, 8)) {
            /* Ack = (0|0), acknowledgment number didn't change, copy old value */
            memcpy(&full_tcp_header.ack_nr, &current_tcp_context->ack_rcv, 4);
        }
        /* The 24 most significant bits haven't changed from previous packet */
        else if (!BITSET(tcp_hc_header, 9) && BITSET(tcp_hc_header, 8)) {
            /* Ack = (0|1), copy 1 byte of tcp_hc packet and 3 bytes from
             * previous packet */
            full_tcp_header.ack_nr |= *packet_buffer;
            full_tcp_header.ack_nr |= ((current_tcp_context->ack_rcv) & 0xFFFFFF00);
            packet_buffer += 1;
            packet_size += 1;
            SET_TCP_ACK(full_tcp_header.reserved_flags);
        }
        /* If the 16 most significant bits haven't changed from previous packet */
        else if (BITSET(tcp_hc_header, 9) && !BITSET(tcp_hc_header, 8)) {
            /* Ack = (1|0), copy 2 bytes of tcp_hc packet and 2 bytes from
             * previous packet */
            full_tcp_header.ack_nr |= NTOHS(*((uint16_t *)packet_buffer));
            full_tcp_header.ack_nr |= ((current_tcp_context->ack_rcv) & 0xFFFF0000);
            packet_buffer += 2;
            packet_size += 2;
            SET_TCP_ACK(full_tcp_header.reserved_flags);
        }
        /* Sending uncompressed acknowledgment number */
        else {
            /* Ack = (1|1), copy 4 bytes of tcp_hc packet */
            memcpy(&full_tcp_header.ack_nr, packet_buffer, 4);
            full_tcp_header.ack_nr = NTOHL(full_tcp_header.ack_nr);
            packet_buffer += 4;
            packet_size += 4;

            if (header_type == COMPRESSED_HEADER) {
                SET_TCP_ACK(full_tcp_header.reserved_flags);
            }
        }

        /*----------------------------------*/
        /*|         Window handling        |*/
        /*----------------------------------*/
        if (!BITSET(tcp_hc_header, 7) && !BITSET(tcp_hc_header, 6)) {
            /* Wnd = (0|0), copy old value */
            memcpy(&full_tcp_header.window, &current_tcp_context->wnd_rcv, 2);
        }
        /* The 8 most significant bits haven't changed from previous packet */
        else if (!BITSET(tcp_hc_header, 7) && BITSET(tcp_hc_header, 6)) {
            /* Wnd = (0|1), copy 1 byte of tcp_hc packet and 1 byte from
             * previous packet */
            full_tcp_header.window |= *packet_buffer;
            full_tcp_header.window |= ((current_tcp_context->wnd_rcv) & 0xFF00);
            packet_buffer += 1;
            packet_size += 1;
        }
        /* If the 8 less significant bits haven't changed from previous packet */
        else if (BITSET(tcp_hc_header, 7) && !BITSET(tcp_hc_header, 6)) {
            /* Wnd = (1|0), copy 1 byte of tcp_hc packet and 1 byte from previous packet */
            full_tcp_header.window |= ((*((uint16_t *)packet_buffer)) & 0xFF00);
            full_tcp_header.window |= ((current_tcp_context->wnd_rcv) & 0x00FF);
            packet_buffer += 1;
            packet_size += 1;
        }
        /* Sending uncompressed window size */
        else {
            /* Wnd = (1|1), copy 2 bytes of tcp_hc packet */
            memcpy(&full_tcp_header.window, packet_buffer, 2);
            full_tcp_header.window = NTOHS(full_tcp_header.window);
            packet_buffer += 2;
            packet_size += 2;
        }

        /* FIN flag */
        if (BITSET(tcp_hc_header, 3)) {
            /* F = (1) */
            if (IS_TCP_ACK(full_tcp_header.reserved_flags)) {
                SET_TCP_FIN_ACK(full_tcp_header.reserved_flags);
            }
            else {
                SET_TCP_FIN(full_tcp_header.reserved_flags);
            }
        }

        /* Copy checksum into into tcp header */
        memcpy(&full_tcp_header.checksum, packet_buffer, 2);
        full_tcp_header.checksum = NTOHS(full_tcp_header.checksum);
        packet_buffer += 2;
        packet_size += 2;

        /* Copy dest. and src. port into tcp header */
        memcpy(&full_tcp_header.dst_port,
               &current_socket->socket_values.local_address.sin6_port, 2);
        memcpy(&full_tcp_header.src_port,
               &current_socket->socket_values.foreign_address.sin6_port, 2);

        /* Ordinary TCP header length */
        full_tcp_header.data_offset = TCP_HDR_LEN / 4;

        /* Move payload to end of tcp header */
        memmove(((uint8_t *)temp_ipv6_header) + IPV6_HDR_LEN + TCP_HDR_LEN,
                packet_buffer, temp_ipv6_header->length - packet_size);

        /* Copy TCP uncompressed header in front of payload */
        memcpy(((uint8_t *)temp_ipv6_header) + IPV6_HDR_LEN, &full_tcp_header,
               TCP_HDR_LEN);

        /* Set IPV6 header length */
        temp_ipv6_header->length = temp_ipv6_header->length - packet_size +
                                   TCP_HDR_LEN;
        return current_socket;
    }
}