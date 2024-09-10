/*-----------------------------------------------------------------------------------*/
void
uip_arp_out(void)
{
	struct arp_entry *tabptr;

	/* Find the destination IP address in the ARP table and construct
	   the Ethernet header. If the destination IP addres isn't on the
	   local network, we use the default router's IP address instead.

	   If not ARP table entry is found, we overwrite the original IP
	   packet with an ARP request for the IP address. */

	/* First check if destination is a local broadcast. */
	if(uip_ipaddr_cmp(IPBUF->destipaddr, broadcast_ipaddr)) {
		memcpy(IPBUF->ethhdr.dest.addr, broadcast_ethaddr.addr, 6);
	} else {
		/* Check if the destination address is on the local network. */
		if(!uip_ipaddr_maskcmp(IPBUF->destipaddr, uip_hostaddr, uip_netmask)) {
			/* Destination address was not on the local network, so we need to
			   use the default router's IP address instead of the destination
			   address when determining the MAC address. */
			uip_ipaddr_copy(ipaddr, uip_draddr);
		} else {
			/* Else, we use the destination IP address. */
			uip_ipaddr_copy(ipaddr, IPBUF->destipaddr);
		}

		for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {
			tabptr = &arp_table[i];
			if(uip_ipaddr_cmp(ipaddr, tabptr->ipaddr)) {
				break;
			}
		}

		if(i == UIP_ARPTAB_SIZE) {
			/* The destination address was not in our ARP table, so we
			   overwrite the IP packet with an ARP request. */

#if 0	
			memset(BUF->ethhdr.dest.addr, 0xff, 6);
			memset(BUF->dhwaddr.addr, 0x00, 6);
			memcpy(BUF->ethhdr.src.addr, uip_ethaddr.addr, 6);
			memcpy(BUF->shwaddr.addr, uip_ethaddr.addr, 6);

			uip_ipaddr_copy(BUF->dipaddr, ipaddr);
			uip_ipaddr_copy(BUF->sipaddr, uip_hostaddr);
			BUF->opcode = HTONS(ARP_REQUEST); /* ARP request. */
			BUF->hwtype = HTONS(ARP_HWTYPE_ETH);
			BUF->protocol = HTONS(UIP_ETHTYPE_IP);
			BUF->hwlen = 6;
			BUF->protolen = 4;
			BUF->ethhdr.type = HTONS(UIP_ETHTYPE_ARP);
#else
			uip_create_broadcast_eth_arp_pkt(BUF, ipaddr,
							 ARP_REQUEST);
#endif

			uip_appdata = &uip_buf[UIP_TCPIP_HLEN + UIP_LLH_LEN];

			uip_len = sizeof(struct arp_hdr);
			return;
		}

		/* Build an ethernet header. */
		memcpy(IPBUF->ethhdr.dest.addr, tabptr->ethaddr.addr, 6);
	}
	memcpy(IPBUF->ethhdr.src.addr, uip_ethaddr.addr, 6);

	IPBUF->ethhdr.type = HTONS(UIP_ETHTYPE_IP);

	uip_len += sizeof(struct uip_eth_hdr);
}