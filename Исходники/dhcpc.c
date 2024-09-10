//----------------------------------------------------------------------------
//Sendet DHCP messages an Broadcast
void dhcp_message (unsigned char type)
{
  struct dhcp_msg *msg;
  unsigned char   *options;
  
  for (unsigned int i=0; i < sizeof (struct dhcp_msg); i++) //clear eth_buffer to 0
  {
    eth_buffer[UDP_DATA_START+i] = 0;
  }
  
  msg = (struct dhcp_msg *)&eth_buffer[UDP_DATA_START];
  msg->op          = 1; // BOOTREQUEST
  msg->htype       = 1; // Ethernet
  msg->hlen        = 6; // Ethernet MAC
  msg->xid[0]      = MYMAC6; //use the MAC as the ID to be unique in the LAN
  msg->xid[1]      = MYMAC5;
  msg->xid[2]      = MYMAC4;
  msg->xid[3]      = MYMAC3;
  msg->flags       = HTONS(0x8000);
  msg->chaddr[0]   = MYMAC1;
  msg->chaddr[1]   = MYMAC2;
  msg->chaddr[2]   = MYMAC3;
  msg->chaddr[3]   = MYMAC4;
  msg->chaddr[4]   = MYMAC5;
  msg->chaddr[5]   = MYMAC6;
  
  options = &msg->options[0];  //options
  *options++       = 99;       //magic cookie
  *options++       = 130;
  *options++       = 83;
  *options++       = 99;

  *options++       = 53;    // Option 53: DHCP message type DHCP Discover
  *options++       = 1;     // len = 1
  *options++       = type;  // 1 = DHCP Discover
  
  *options++       = 55;    // Option 55: parameter request list
  *options++       = 3;     // len = 3
  *options++       = 1;     // netmask
  *options++       = 3;     // router
  *options++       = 6;     // dns

  *options++       = 50;    // Option 54: requested IP
  *options++       = 4;     // len = 4
  *options++       = dhcp_offer_ip[0];
  *options++       = dhcp_offer_ip[1];
  *options++       = dhcp_offer_ip[2];
  *options++       = dhcp_offer_ip[3];

  switch (type)
  {
    case DHCPDISCOVER:
      dhcp_state = DHCP_STATE_DISCOVER_SENT;
      DHCP_DEBUG("DISCOVER sent\r\n");
    break;
    case DHCPREQUEST:
      *options++       = 54;    // Option 54: server ID
      *options++       = 4;     // len = 4
      *options++       = cache.serv_id[0];
      *options++       = cache.serv_id[1];
      *options++       = cache.serv_id[2];
      *options++       = cache.serv_id[3];
      dhcp_state = DHCP_STATE_REQUEST_SENT;
      DHCP_DEBUG("REQUEST sent\r\n");
    break;
    default:
      DHCP_DEBUG("Wrong DHCP msg type\r\n");
    break;
  }

  *options++       = 12;    // Option 12: host name
  *options++       = 12;     // len = 8
  *options++       = 'A';
  *options++       = 'V';
  *options++       = 'R';
  *options++       = '-';
  *options++       = 'L';
  *options++       = 'I';
  *options++       = 'G';
  *options++       = 'H';
  *options++       = 'T';
  *options++       = 'C';
  *options++       = 'T';
  *options++       = 'R';
  
  *options         = 0xff;  //end option

  create_new_udp_packet(sizeof (struct dhcp_msg),DHCP_CLIENT_PORT,DHCP_SERVER_PORT,(unsigned long)0xffffffff);
  DHCP_DEBUG("\r\nmyip   %1i.%1i.%1i.%1i\r\n", myip[0]     , myip[1]     , myip[2]     , myip[3]);
  DHCP_DEBUG("\r\nofferip   %1i.%1i.%1i.%1i\r\n", dhcp_offer_ip[0] , dhcp_offer_ip[1] , dhcp_offer_ip[2] , dhcp_offer_ip[3]);
}