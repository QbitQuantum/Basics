int winsock_getipnettable(LPSTMACADDRESS mac_address,unsigned int ip_address){
#ifdef _WIN32
#ifdef I_USE_WINDOWS_SDK
  MIB_IPNETTABLE* m;

  static char buf[65536];

  int len;
  int i;

  len=sizeof(buf);
  m=(MIB_IPNETTABLE*)buf;
  memset(buf,0,sizeof(buf));

  GetIpNetTable(m,&len,0);

  for(i=0;i<(int)m->dwNumEntries;i++)
  {
    if(m->table[i].dwAddr==ip_address)
    {

      unsigned int w;


      w=(unsigned char)(m->table[i].bPhysAddr[0]);
      w<<=8;
      w|=(unsigned char)(m->table[i].bPhysAddr[1]);
      mac_address->hi=w;

      w=(unsigned char)(m->table[i].bPhysAddr[2]);
      w<<=8;
      w|=(unsigned char)(m->table[i].bPhysAddr[3]);
      w<<=8;
      w|=(unsigned char)(m->table[i].bPhysAddr[4]);
      w<<=8;
      w|=(unsigned char)(m->table[i].bPhysAddr[5]);

      mac_address->lo=w;

      return 1;
    }
  }
  return 0;
#else
  return 0;
#endif
#endif
#if (defined _SH2)||(defined _SH4)
  char buf[6];
  int ret;
  unsigned int w;

  ret=tfGetArpEntryByIpAddr(ip_address,buf,sizeof(buf));
  if(ret)return 0;

  w=(unsigned char)buf[0];
  w<<=8;
  w|=(unsigned char)buf[1];
  mac_address->hi=w;

  w=(unsigned char)buf[2];
  w<<=8;
  w|=(unsigned char)buf[3];
  w<<=8;
  w|=(unsigned char)buf[4];
  w<<=8;
  w|=(unsigned char)buf[5];

  mac_address->lo=w;

  return 1;
#endif
#if (defined linux)&&!(defined __CYGWIN__)
  int sock;
  struct arpreq req;
  struct sockaddr_in * sin;
  unsigned int w, i;
  unsigned char * ptr;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if( sock < 0 ){
	  close( sock );
	  return 0;
  }

  memset(&req, 0, sizeof(struct arpreq));
  strncpy(req.arp_dev, NIFNAME, NIFNAMESIZE+1); //device name

  sin = (struct sockaddr_in *)&req.arp_pa;
  memset(sin, 0, sizeof(struct sockaddr_in));

  sin->sin_family = AF_INET; //Address Familiy
  memcpy( &sin->sin_addr, &ip_address, sizeof(struct in_addr)); //IP

  if( ioctl(sock, SIOCGARP, &req) < 0 ){
	  close(sock);
	  return 0;
  }
  close( sock );

  ptr = (unsigned char*)(&req.arp_ha.sa_data[0]);

  /*MACが 0 ではないことを確認*/
  for( i=0; i<SL_SIZE_OF_MAC; i++){
	  if( *(ptr+i) ){ break; }
  }
  if( SL_SIZE_OF_MAC==i ){ return 0; }

  memset( &w, 0, sizeof(unsigned int));
  w=(unsigned char)*ptr;
  w<<=8;
  w|=(unsigned char)*(ptr+1);
  mac_address->hi=w;

  memset( &w, 0, sizeof(unsigned int));
  w=(unsigned char)*(ptr+2);
  w<<=8;
  w|=(unsigned char)*(ptr+3);
  w<<=8;
  w|=(unsigned char)*(ptr+4);
  w<<=8;
  w|=(unsigned char)*(ptr+5);

  mac_address->lo=w;

  return 1;
#endif

  return 0;
}