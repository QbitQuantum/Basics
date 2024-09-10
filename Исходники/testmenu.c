int
arp_flood (void * pio)
{
   PACKET arppkt;
   struct ethhdr *   ethhdr;
   struct arp_hdr *  arphdr;
   NET net;
   long  i;
   int   e;
   ip_addr ipaddr;

#ifdef MULTI_HOMED
   ip_addr phost;    /* phoney host for pass to iproute */
   net = iproute(activehost, &phost);
#else
   net = nets[0];
#endif

   if (!net)
   {
      ns_printf(pio, "ARP flood: no route");
      return -1;
   }

   ns_printf(pio, "sending ARP flood of %ld pkts to %u.%u.%u.%u..", 
    pktcount, PUSH_IPADDR(activehost) );


   for (i = 0; i < pktcount; i++)
   {
      if (pktwait("ARP", pio))
         return -1;

      /******** code cribbed from et_arp.c: ********/
      LOCK_NET_RESOURCE(FREEQ_RESID);
      arppkt = pk_alloc(arpsize);
      UNLOCK_NET_RESOURCE(FREEQ_RESID);
      if (!arppkt)
         return ENP_RESOURCE;
      arppkt->nb_prot = arppkt->nb_buff;
      arppkt->nb_plen = arpsize;
      arppkt->net = net;

      /* build arp request packet */
      ethhdr = (struct ethhdr *)(arppkt->nb_buff + ETHHDR_BIAS);     /* ethernet header at start of buffer */
      arphdr = (struct arp_hdr *)(arppkt->nb_buff + ETHHDR_SIZE); /* arp header follows */
      arphdr->ar_hd = ARPHW;     /* net endian arp hardware type (ethernet) */
      arphdr->ar_pro = ARPIP;
      arphdr->ar_hln = 6;
      arphdr->ar_pln = 4;
      arphdr->ar_op = ARREQ;
      arphdr->ar_tpa = activehost;        /* target's IP address */

      /* FLOOD TEST MOD: just for grins, rotate our IP address so we 
       * flood everybody's arp tables. Remember that we store IP 
       * addresses 
       */
      ipaddr = i & (0x00FFFFFE & htonl(~net->snmask));   /* make host portion */
      arphdr->ar_spa = (net->n_ipaddr | htonl(ipaddr));  /* add net portion */

      MEMCPY(arphdr->ar_sha, net->n_mib->ifPhysAddress, 6);
      MEMSET(&(ethhdr->e_dst[0]), 0xFF, 6);     /* destination to broadcast (all FFs) */
      MEMCPY(ethhdr->e_src, net->n_mib->ifPhysAddress, 6);
      ethhdr->e_type = ET_ARP;   /* 0x0806 - ARP type on ethernet */

#ifdef NO_CC_PACKING    /* move ARP fields to proper network boundaries */
      {
         struct arp_wire * arwp  =  (struct  arp_wire *)arphdr;
         MEMMOVE(&arwp->data[AR_SHA], arphdr->ar_sha, 6);
         MEMMOVE(&arwp->data[AR_SPA], &arphdr->ar_spa, 4);
         MEMMOVE(&arwp->data[AR_THA], arphdr->ar_tha, 6);
         MEMMOVE(&arwp->data[AR_TPA], &arphdr->ar_tpa, 4);
      }
#endif   /* NO_CC_PACKING */

      /* send arp request - if a packet oriented send exists, use it: */
      if (net->pkt_send)
         e = net->pkt_send(arppkt);    /* driver should free arppkt later */
      else  /* use old raw send */
      {
         e = net->raw_send(arppkt->net, arppkt->nb_buff, arpsize);
         LOCK_NET_RESOURCE(FREEQ_RESID);
         pk_free(arppkt);
         UNLOCK_NET_RESOURCE(FREEQ_RESID);
      }

      arpReqsOut++;
      /******** end of code cribbed from et_arp.c: ********/

      if (e < 0)
      {
         ns_printf(pio, "ARP flood send error %d on pkt %ld\n",e,i);
         return -1;
      }
      if ((i & 0x0f) == 0x0f)
         ns_printf(pio, ".");
   }

   return 0;
}