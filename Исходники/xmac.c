/*---------------------------------------------------------------------------*/
static void
input_packet(void)
{
  struct xmac_hdr *hdr;

  if(NETSTACK_FRAMER.parse() >= 0) {
    hdr = packetbuf_dataptr();

    if(hdr->dispatch != DISPATCH) {
      someone_is_sending = 0;
      if(rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                                     &rimeaddr_node_addr) ||
	 rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                      &rimeaddr_null)) {
	/* This is a regular packet that is destined to us or to the
	   broadcast address. */

	/* We have received the final packet, so we can go back to being
	   asleep. */
	off();

        /* Check for duplicate packet by comparing the sequence number
           of the incoming packet with the last few ones we saw. */
        {
          int i;
          for(i = 0; i < MAX_SEQNOS; ++i) {
            if(packetbuf_attr(PACKETBUF_ATTR_PACKET_ID) == received_seqnos[i].seqno &&
               rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_SENDER),
                            &received_seqnos[i].sender)) {
              /* Drop the packet. */
              return;
            }
          }
          for(i = MAX_SEQNOS - 1; i > 0; --i) {
            memcpy(&received_seqnos[i], &received_seqnos[i - 1],
                   sizeof(struct seqno));
          }
          received_seqnos[0].seqno = packetbuf_attr(PACKETBUF_ATTR_PACKET_ID);
          rimeaddr_copy(&received_seqnos[0].sender,
                        packetbuf_addr(PACKETBUF_ADDR_SENDER));
        }

#if XMAC_CONF_COMPOWER
	/* Accumulate the power consumption for the packet reception. */
	compower_accumulate(&current_packet);
	/* Convert the accumulated power consumption for the received
	   packet to packet attributes so that the higher levels can
	   keep track of the amount of energy spent on receiving the
	   packet. */
	compower_attrconv(&current_packet);

	/* Clear the accumulated power consumption so that it is ready
	   for the next packet. */
	compower_clear(&current_packet);
#endif /* XMAC_CONF_COMPOWER */

	waiting_for_packet = 0;

        PRINTDEBUG("xmac: data(%u)\n", packetbuf_datalen());
	NETSTACK_MAC.input();
        return;
      } else {
        PRINTDEBUG("xmac: data not for us\n");
      }

    } else if(hdr->type == TYPE_STROBE) {
      someone_is_sending = 2;

      if(rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                      &rimeaddr_node_addr)) {
	/* This is a strobe packet for us. */

	/* If the sender address is someone else, we should
	   acknowledge the strobe and wait for the packet. By using
	   the same address as both sender and receiver, we flag the
	   message is a strobe ack. */
        waiting_for_packet = 1;
#if 0
	hdr->type = TYPE_STROBE_ACK;
	packetbuf_set_addr(PACKETBUF_ADDR_RECEIVER,
			   packetbuf_addr(PACKETBUF_ADDR_SENDER));
	packetbuf_set_addr(PACKETBUF_ADDR_SENDER, &rimeaddr_node_addr);
	packetbuf_compact();
	if(NETSTACK_FRAMER.create() >= 0) {
	  /* We turn on the radio in anticipation of the incoming
	     packet. */
	  someone_is_sending = 1;
	  waiting_for_packet = 1;
	  on();
	  NETSTACK_RADIO.send(packetbuf_hdrptr(), packetbuf_totlen());
	  PRINTDEBUG("xmac: send strobe ack %u\n", packetbuf_totlen());
	} else {
	  PRINTF("xmac: failed to send strobe ack\n");
	}
#endif /* 0 */
      } else if(rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                             &rimeaddr_null)) {
	/* If the receiver address is null, the strobe is sent to
	   prepare for an incoming broadcast packet. If this is the
	   case, we turn on the radio and wait for the incoming
	   broadcast packet. */
	waiting_for_packet = 1;
	on();
      } else {
        PRINTDEBUG("xmac: strobe not for us\n");
      }
      
      /* We are done processing the strobe and we therefore return
	 to the caller. */
      return;
#if XMAC_CONF_ANNOUNCEMENTS
    } else if(hdr->type == TYPE_ANNOUNCEMENT) {
      packetbuf_hdrreduce(sizeof(struct xmac_hdr));
      parse_announcements(packetbuf_addr(PACKETBUF_ADDR_SENDER));
#endif /* XMAC_CONF_ANNOUNCEMENTS */
    } else if(hdr->type == TYPE_STROBE_ACK) {
      PRINTDEBUG("xmac: stray strobe ack\n");
    } else {
      PRINTF("xmac: unknown type %u (%u/%u)\n", hdr->type,
             packetbuf_datalen(), len);
    }
  } else {
    PRINTF("xmac: failed to parse (%u)\n", packetbuf_totlen());
  }
}