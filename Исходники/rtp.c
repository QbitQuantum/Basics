/**
 * RTP send packets
 */
static void
rtp_send_packets( int sock, struct sockaddr_in* to)
{
  struct rtp_hdr* rtphdr;
  u8_t*           rtp_payload;
  int             rtp_payload_size;
  size_t          rtp_data_index;

  /* prepare RTP packet */
  rtphdr = (struct rtp_hdr*)rtp_send_packet;
  rtphdr->version     = RTP_VERSION;
  rtphdr->payloadtype = 0;
  rtphdr->ssrc        = PP_HTONL(RTP_SSRC);
  rtphdr->timestamp   = lwip_htonl(lwip_ntohl(rtphdr->timestamp) + RTP_TIMESTAMP_INCREMENT);

  /* send RTP stream packets */
  rtp_data_index = 0;
  do {
    rtp_payload      = rtp_send_packet+sizeof(struct rtp_hdr);
    rtp_payload_size = LWIP_MIN(RTP_PAYLOAD_SIZE, (sizeof(rtp_data) - rtp_data_index));

    MEMCPY(rtp_payload, rtp_data + rtp_data_index, rtp_payload_size);

    /* set MARKER bit in RTP header on the last packet of an image */
    rtphdr->payloadtype = RTP_PAYLOADTYPE | (((rtp_data_index + rtp_payload_size)
      >= sizeof(rtp_data)) ? RTP_MARKER_MASK : 0);

    /* send RTP stream packet */
    if (sendto(sock, rtp_send_packet, sizeof(struct rtp_hdr) + rtp_payload_size,
        0, (struct sockaddr *)to, sizeof(struct sockaddr)) >= 0) {
      rtphdr->seqNum  = lwip_htons(lwip_ntohs(rtphdr->seqNum) + 1);
      rtp_data_index += rtp_payload_size;
    } else {
      LWIP_DEBUGF(RTP_DEBUG, ("rtp_sender: not sendto==%i\n", errno));
    }
  }while (rtp_data_index < sizeof(rtp_data));
}