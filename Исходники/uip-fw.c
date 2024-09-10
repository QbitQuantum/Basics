/*------------------------------------------------------------------------------*/
u8_t
uip_fw_forward(void)
{
  struct fwcache_entry *fw;

  /* First check if the packet is destined for ourselves and return 0
     to indicate that the packet should be processed locally. */
  if(BUF->destipaddr[0] == uip_hostaddr[0] &&
     BUF->destipaddr[1] == uip_hostaddr[1]) {
    return UIP_FW_LOCAL;
  }

  /* If we use ping IP address configuration, and our IP address is
     not yet configured, we should intercept all ICMP echo packets. */
#if UIP_PINGADDRCONF
  if((uip_hostaddr[0] | uip_hostaddr[1]) == 0 &&
     BUF->proto == UIP_PROTO_ICMP &&
     ICMPBUF->type == ICMP_ECHO) {
    return UIP_FW_LOCAL;
  }
#endif /* UIP_PINGADDRCONF */

  /* Check if the packet is in the forwarding cache already, and if so
     we drop it. */

  for(fw = fwcache; fw < &fwcache[FWCACHE_SIZE]; ++fw) {
    if(fw->timer != 0 &&
#if UIP_REASSEMBLY > 0
       fw->len == BUF->len &&
       fw->offset == BUF->ipoffset &&
#endif
       fw->ipid == BUF->ipid &&
       fw->srcipaddr[0] == BUF->srcipaddr[0] &&
       fw->srcipaddr[1] == BUF->srcipaddr[1] &&
       fw->destipaddr[0] == BUF->destipaddr[0] &&
       fw->destipaddr[1] == BUF->destipaddr[1] &&
#if notdef
       fw->payload[0] == BUF->srcport &&
       fw->payload[1] == BUF->destport &&
#endif
       fw->proto == BUF->proto) {
      /* Drop packet. */
      return UIP_FW_FORWARDED;
    }
  }

  /* If the TTL reaches zero we produce an ICMP time exceeded message
     in the uip_buf buffer and forward that packet back to the sender
     of the packet. */
  if(BUF->ttl <= 1) {
    /* No time exceeded for broadcasts and multicasts! */
    if(BUF->destipaddr[0] == 0xffff && BUF->destipaddr[1] == 0xffff) {
      return UIP_FW_LOCAL;
    }
    time_exceeded();
  }

  /* Decrement the TTL (time-to-live) value in the IP header */
  BUF->ttl = BUF->ttl - 1;

  /* Update the IP checksum. */
  if(BUF->ipchksum >= HTONS(0xffff - 0x0100)) {
    BUF->ipchksum = BUF->ipchksum + HTONS(0x0100) + 1;
  } else {
    BUF->ipchksum = BUF->ipchksum + HTONS(0x0100);
  }

  if(uip_len > 0) {
    uip_appdata = &uip_buf[UIP_LLH_LEN + UIP_TCPIP_HLEN];
    uip_fw_output();
  }

#if UIP_BROADCAST
  if(BUF->destipaddr[0] == 0xffff && BUF->destipaddr[1] == 0xffff) {
    return UIP_FW_LOCAL;
  }
#endif /* UIP_BROADCAST */

  /* Return non-zero to indicate that the packet was forwarded and that no
     other processing should be made. */
  return UIP_FW_FORWARDED;
}