/* Stolen from my GGN */
static int addiflist(void)
{
#if 0
	unsigned cnt=MAX_BRDINTERFACES,i,j;
	WSADATA info;
	INTERFACE_INFO *ifo;
	SOCKET sock;
	struct sockaddr_in *sinp,*sinmp;

	D2_FREE(broads);
	if ((sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		FAIL("Creating socket() failure during broadcast detection: %m");

#ifdef SIOCGIFCOUNT
	if (ioctl(sock,SIOCGIFCOUNT,&cnt))
		{ /* msg("Getting iterface count error: %m"); */ }
	else
		cnt=cnt*2+2;
#endif

	memset(&ifo[0], 0, sizeof(ifo);
	chk(ifo = alloca(cnt * sizeof(INTERFACE_INFO));

	if (wsaioctl(sock, SIO_GET_INTERFACE_LIST, NULL, 0, &ifo[0], cnt * sizeof(INTERFACE_INFO), &br, NULL, NULL)) != 0) {
		closesocket(sock);
		FAIL("ioctl(SIOCGIFCONF) failure during broadcast detection: %m");
		}
#if 0
	cnt=ifconf.ifc_len/sizeof(struct ifreq);
#endif
	chk(broads=D2_ALLOC(cnt*sizeof(*broads));
	broadsize=cnt;
	for (i=j=0;i<cnt;i++) {
		if (ioctl(sock,SIOCGIFFLAGS,ifconf.ifc_req+i)) {
			closesocket(sock);
			FAIL("ioctl(udp,\"%s\",SIOCGIFFLAGS) error: %m",ifconf.ifc_req[i].ifr_name);
			}
		if (((ifconf.ifc_req[i].ifrFlags&IF_REQFLAGS)!=IF_REQFLAGS)||
				 (ifconf.ifc_req[i].ifrFlags&IF_NOTFLAGS))
			continue;
		if (ioctl(sock,(ifconf.ifc_req[i].ifrFlags&IFF_BROADCAST?SIOCGIFBRDADDR:SIOCGIFDSTADDR),ifconf.ifc_req+i)) {
			closesocket(sock);
			FAIL("ioctl(udp,\"%s\",SIOCGIF{DST/BRD}ADDR) error: %m",ifconf.ifc_req[i].ifr_name);
			}

		sinp = (struct sockaddr_in *)&ifconf.ifc_req[i].ifr_broadaddr;
#if 0 // old, not portable code
		sinmp = (struct sockaddr_in *)&ifconf.ifc_req[i].ifr_netmask;
#else // portable code
		if (ioctl(sock, SIOCGIFNETMASK, ifconf.ifc_req+i)) {
			closesocket(sock);
			FAIL("ioctl(udp,\"%s\",SIOCGIFNETMASK) error: %m", ifconf.ifc_req[i].ifr_name);
		}
		sinmp = (struct sockaddr_in *)&ifconf.ifc_req[i].ifr_addr;
#endif
		if (sinp->sin_family!=AF_INET || sinmp->sin_family!=AF_INET) continue;
		broads[j]=*sinp;
		broads[j].sin_port=UDP_BASEPORT; //FIXME: No possibility to override from cmdline
		broadmasks[j]=*sinmp;
		j++;
		}
	broadnum=j;
	masksnum=j;
#endif
	return(0);
}