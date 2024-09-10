/*-----------------------------------------------------------------------------------*/
void
uip_arp_out(void)
{
  struct arp_entry *tabptr = 0;
  /* Find the destination IP address in the ARP table and construct
     the Ethernet header. If the destination IP addres isn't on the
     local network, we use the default router's IP address instead.

     If not ARP table entry is found, we overwrite the original IP
     packet with an ARP request for the IP address. */

  /* Check if the destination address is on the local network. */
  if((IPBUF->destipaddr[0] & uip_arp_netmask[0]) !=
     (uip_hostaddr[0] & uip_arp_netmask[0]) ||
     (IPBUF->destipaddr[1] & uip_arp_netmask[1]) !=
     (uip_hostaddr[1] & uip_arp_netmask[1])) {
    /* Destination address was not on the local network, so we need to
       use the default router's IP address instead of the destination
       address when determining the MAC address. */
    ipaddr[0] = uip_arp_draddr[0];
    ipaddr[1] = uip_arp_draddr[1];
  } else {
    /* Else, we use the destination IP address. */
    ipaddr[0] = IPBUF->destipaddr[0];
    ipaddr[1] = IPBUF->destipaddr[1];
  }
      
  for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {
    tabptr = &arp_table[i];
    if(ipaddr[0] == tabptr->ipaddr[0] &&
       ipaddr[1] == tabptr->ipaddr[1])
      break;
  }

  if(i == UIP_ARPTAB_SIZE) {
    /* The destination address was not in our ARP table, so we
       overwrite the IP packet with an ARP request. */

    memset(BUF->ethhdr.dest.addr, 0xff, 6);
    memset(BUF->dhwaddr.addr, 0x00, 6);
    memcpy(BUF->ethhdr.src.addr, uip_ethaddr.addr, 6);
    memcpy(BUF->shwaddr.addr, uip_ethaddr.addr, 6);
    
    BUF->dipaddr[0] = ipaddr[0];
    BUF->dipaddr[1] = ipaddr[1];
    BUF->sipaddr[0] = uip_hostaddr[0];
    BUF->sipaddr[1] = uip_hostaddr[1];
    BUF->opcode = HTONS(ARP_REQUEST); /* ARP request. */
    BUF->hwtype = HTONS(ARP_HWTYPE_ETH);
    BUF->protocol = HTONS(UIP_ETHTYPE_IP);
    BUF->hwlen = 6;
    BUF->protolen = 4;
    BUF->ethhdr.type = HTONS(UIP_ETHTYPE_ARP);

    uip_appdata = &uip_buf[40 + UIP_LLH_LEN];
    
    uip_len = sizeof(struct arp_hdr);
    return;
  }

  /* Build an ethernet header. */
  memcpy(IPBUF->ethhdr.dest.addr, tabptr->ethaddr.addr, 6);
  memcpy(IPBUF->ethhdr.src.addr, uip_ethaddr.addr, 6);
  
  IPBUF->ethhdr.type = HTONS(UIP_ETHTYPE_IP);

  uip_len += sizeof(struct uip_eth_hdr);
}