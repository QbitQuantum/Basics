int
if_send_spoof_request(char *dev,
		      unsigned int new_ip, unsigned int r_ip,
                      unsigned char *remote_mac,
		      int count,int icmp) {
  int i,ic;
  struct ifreq ifr;
  struct ether_header *eth;
  struct arphdr *arp;
  struct interface ifs[1024];
  unsigned char *cp, *dest_mac;
  static unsigned char buffer[60];
  static unsigned char my_mac[ETH_ALEN];
  static unsigned char bc_mac[ETH_ALEN] =
                {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  memset(&ifr, sizeof(struct ifreq), 0);
  strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  if (ioctl(_if_bpf, BIOCSETIF, (caddr_t)&ifr) < 0) {
     perror("ioctl (BIOCSETIF)");
     exit (EXIT_FAILURE);
  }
  ic = if_list_ips(ifs, 1024);
  for(i=0; i<ic; i++) {
    if(!strncmp(ifs[i].ifname, ifr.ifr_name, strlen(ifr.ifr_name)) &&
	(ifs[i].mac[0] || ifs[i].mac[1] || ifs[i].mac[2] ||
	 ifs[i].mac[3] || ifs[i].mac[4] || ifs[i].mac[5]) ) {
      memcpy(my_mac, ifs[i].mac, ETH_ALEN);
      break;
    }
  }
  memset(buffer, 0, 60);
  eth = (struct ether_header *)buffer;
  memcpy(eth->ether_shost, my_mac, ETH_ALEN);
  memcpy(eth->ether_dhost, bc_mac, ETH_ALEN);
  eth->ether_type = htons(ETH_P_ARP);
  arp = (struct arphdr *)(eth+1);
  arp->ar_hrd = htons(ARPHRD_ETHER);
  arp->ar_pro = htons(ETH_P_IP);
  arp->ar_hln = ETH_ALEN;
  arp->ar_pln = 4;
  arp->ar_op  = htons(ARPOP_REPLY);
  cp = (unsigned char *)(arp+1);
  memcpy(cp, my_mac, ETH_ALEN); cp+=ETH_ALEN;
  memcpy(cp, &new_ip, 4); cp+=4;
  dest_mac = cp;
  memcpy(cp, bc_mac, ETH_ALEN); cp+=ETH_ALEN;
  memcpy(cp, &r_ip, 4); cp+=4;
  for(i=0;i<count;i++)
    write(_if_bpf, buffer, 60);
  if(remote_mac) {
    memcpy(dest_mac, remote_mac, ETH_ALEN);
    memcpy(eth->ether_dhost, remote_mac, ETH_ALEN);
    for(i=0;i<count;i++)
      write(_if_bpf, buffer, 60);
    if(icmp) {
      compose_ping(buffer, my_mac, remote_mac, new_ip, r_ip);
      write(_if_bpf, buffer, 42);
    }
  }
  return i;
}