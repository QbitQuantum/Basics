/** Basic setup to connect NIC to socket.
 * @param[in] port        = port context struct
 * @param[in] ifname      = Name of NIC device, f.e. "eth0"
 * @param[in] secondary   = if >0 then use secondary stack instead of primary
 * @return >0 if succeeded
 */
int ecx_setupnic(ecx_portt *port, const char *ifname, int secondary) 
{
   int i;
   int r, rval, ifindex;
   struct timeval timeout;
   struct ifreq ifr;
   struct sockaddr_ll sll;
   int *psock;

   rval = 0;
   if (secondary)
   {
      /* secondary port stuct available? */
      if (port->redport)
      {
         /* when using secondary socket it is automatically a redundant setup */
         psock = &(port->redport->sockhandle);
         *psock = -1;
         port->redstate                   = ECT_RED_DOUBLE;
         port->redport->stack.sock        = &(port->redport->sockhandle);
         port->redport->stack.txbuf       = &(port->txbuf);
         port->redport->stack.txbuflength = &(port->txbuflength);
         port->redport->stack.tempbuf     = &(port->redport->tempinbuf);
         port->redport->stack.rxbuf       = &(port->redport->rxbuf);
         port->redport->stack.rxbufstat   = &(port->redport->rxbufstat);
         port->redport->stack.rxsa        = &(port->redport->rxsa);
      }
      else
      {
         /* fail */
         return 0;
      }
   }
   else
   {	  
      rt_mutex_create(&port->getindex_mutex, "getindex_mutex");
      rt_mutex_create(&port->tx_mutex, "tx_mutex");
      rt_mutex_create(&port->rx_mutex, "rx_mutex");
     
      port->sockhandle        = -1;
      port->lastidx           = 0;
      port->redstate          = ECT_RED_NONE;
      port->stack.sock        = &(port->sockhandle);
      port->stack.txbuf       = &(port->txbuf);
      port->stack.txbuflength = &(port->txbuflength);
      port->stack.tempbuf     = &(port->tempinbuf);
      port->stack.rxbuf       = &(port->rxbuf);
      port->stack.rxbufstat   = &(port->rxbufstat);
      port->stack.rxsa        = &(port->rxsa);
      psock = &(port->sockhandle);
   }   
   /* we use RAW packet socket, with packet type ETH_P_ECAT */
   *psock = SOCKET(PF_PACKET, SOCK_RAW, htons(ETH_P_ECAT));
   
   timeout.tv_sec =  0;
   timeout.tv_usec = 1; 
   
   r = SETSOCKOPT(*psock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
   r = SETSOCKOPT(*psock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
   i = 1;
   r = SETSOCKOPT(*psock, SOL_SOCKET, SO_DONTROUTE, &i, sizeof(i));
   /* connect socket to NIC by name */
   strcpy(ifr.ifr_name, ifname);
   r = IOCTL(*psock, SIOCGIFINDEX, &ifr);
   ifindex = ifr.ifr_ifindex;
   strcpy(ifr.ifr_name, ifname);
   ifr.ifr_flags = 0;
   /* reset flags of NIC interface */
   r = IOCTL(*psock, SIOCGIFFLAGS, &ifr); 
   /* set flags of NIC interface, here promiscuous and broadcast */
   ifr.ifr_flags = ifr.ifr_flags || IFF_PROMISC || IFF_BROADCAST;
   r = IOCTL(*psock, SIOCGIFFLAGS, &ifr);
   /* bind socket to protocol, in this case RAW EtherCAT */
   sll.sll_family = AF_PACKET;
   sll.sll_ifindex = ifindex;
   sll.sll_protocol = htons(ETH_P_ECAT);
   r = BIND(*psock, (struct sockaddr *)&sll, sizeof(sll));
   /* setup ethernet headers in tx buffers so we don't have to repeat it */
   for (i = 0; i < EC_MAXBUF; i++) 
   {
      ec_setupheader(&(port->txbuf[i]));
      port->rxbufstat[i] = EC_BUF_EMPTY;
   }
   ec_setupheader(&(port->txbuf2));
   if (r == 0) rval = 1;
   
   return rval;
}