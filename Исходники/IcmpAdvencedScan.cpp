DWORD WINAPI IcmpWrongPortScan (LPVOID pPar)
{
	ThreadSyn cSynEntry;
	SetBoolTrue cSBT(&bIcmpSending);
	DWORD dwThreadId;
	CreateThread(NULL,0,IcmpReceiver,pPar,0,&dwThreadId);;

	pcap_if_t *pSelectDev;
	ThreadParament * pThreadParament=(ThreadParament *)pPar;
	pSelectDev=pThreadParament->SelectDev;
	pcap_t *fp;
	char error[256];
	char bDestMac[6];
	memset(bDestMac,0xff,6);

	UdpPacket thePacket;

	DWORD dwNetMask=pThreadParament->dwNetMAsk;
	DWORD dwDefaultGatewayIp=pThreadParament->dwDefaultGateway;
	ULONG bGatewayMac[2];
	ULONG ulLen=6;
	SendARP (htonl(dwDefaultGatewayIp), 0, bGatewayMac, &ulLen);
	memcpy(thePacket.theEthHead.bDestMac,bGatewayMac,6);
	memcpy(thePacket.theEthHead.bSourceMac,pThreadParament->HostMac,6);
	thePacket.theEthHead.usEthernetType=0x8;
	thePacket.theIpHead.ucVersionAndHeadLength=0x45;
	thePacket.theIpHead.ucTos=0;
	thePacket.theIpHead.usTotalLength=htons(30);
	thePacket.theIpHead.usIdentification=1234;
	thePacket.theIpHead.usFlagsAndFragmentOffset=0;
	thePacket.theIpHead.ucTtl=119;
	thePacket.theIpHead.ucProtocol=17;//udp
	thePacket.theIpHead.dwSourceAddr=htonl(pThreadParament->dwHostIP);
	
	thePacket.theUdpHead.usSourcePort=ntohs(12345);
	thePacket.theUdpHead.usDestPort=ntohs(567);
	thePacket.theUdpHead.usLength=ntohs(10);
	thePacket.theUdpHead.usData=0x6664;


	UdpFakeHeader theFakeHeader;
	theFakeHeader.bZero=0;
	theFakeHeader.bUdpLength=htons(sizeof(UdpHead));
	theFakeHeader.bProtocolType=17;
	theFakeHeader.dwSourceAddr=htonl(pThreadParament->dwHostIP);
	
	if((fp = pcap_open_live(pSelectDev->name, 65536, 1, 1000, error) ) == NULL)
	{
		return 0;
	}
	for(DWORD dwIP=pThreadParament->dwOriginalIP;dwIP<=pThreadParament->dwLastIP&&!bStop;dwIP++)
	{
		char  strLog[256];
		in_addr tmp;
		tmp.S_un.S_addr=htonl(dwIP);
		sprintf(strLog,"Scaning Host %s.",inet_ntoa(tmp));
		pMainWindow->SendMessage(WM_UPDATA_LOG,(WPARAM)strLog);
		if((dwIP&dwNetMask)==(dwDefaultGatewayIp&dwNetMask))
		{
			ulLen=6;
			ULONG bHostMac[2];
			
			if(SendARP(htonl(dwIP),0,bHostMac,&ulLen)!=NO_ERROR)
			{
				continue;
			}
			memcpy(thePacket.theEthHead.bDestMac,bHostMac,6);

		}
		thePacket.theIpHead.dwDestAddr=htonl(dwIP);
		
		thePacket.theIpHead.usCrc=0;
		thePacket.theIpHead.usCrc=CheckSum((USHORT*)(&(thePacket.theIpHead)),sizeof(IpHead));
		
		thePacket.theUdpHead.usCrc=0;
		theFakeHeader.dwDestAddr=htonl(dwIP);
		thePacket.theUdpHead.usCrc=UdpCheckSum((char *)&(thePacket.theUdpHead),(char *)&theFakeHeader,sizeof(UdpHead));

		if(pcap_sendpacket(fp,(u_char *)(&thePacket),sizeof(thePacket))!=0)
		{
			pMainWindow->MessageBox("Send Data Error!");
		}
		while(bPause)
		{
			Sleep(100);
		}

	}
	return 0;
}