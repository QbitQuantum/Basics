/* upnpDiscover() :
 * return a chained list of all devices found or NULL if
 * no devices was found.
 * It is up to the caller to free the chained list
 * delay is in millisecond (poll) */
LIBSPEC struct UPNPDev * upnpDiscover(int delay, const char * multicastif,
                              const char * minissdpdsock, int sameport)
{
	struct UPNPDev * tmp;
	struct UPNPDev * devlist = 0;
	int opt = 1;
	static const char MSearchMsgFmt[] = 
	"M-SEARCH * HTTP/1.1\r\n"
	"HOST: " UPNP_MCAST_ADDR ":" XSTR(PORT) "\r\n"
	"ST: %s\r\n"
	"MAN: \"ssdp:discover\"\r\n"
	"MX: %u\r\n"
	"\r\n";
	static const char * const deviceList[] = {
		"urn:schemas-upnp-org:device:InternetGatewayDevice:1",
		"urn:schemas-upnp-org:service:WANIPConnection:1",
		"urn:schemas-upnp-org:service:WANPPPConnection:1",
		"upnp:rootdevice",
		0
	};
	int deviceIndex = 0;
	char bufr[1536];	/* reception and emission buffer */
	int sudp;
	int n;
	struct sockaddr sockudp_r;
	unsigned int mx;
	int rv;
	struct addrinfo hints, *servinfo, *p;
#ifdef WIN32
	MIB_IPFORWARDROW ip_forward;
#endif

#if !defined(WIN32) && !defined(__amigaos__) && !defined(__amigaos4__)
	/* first try to get infos from minissdpd ! */
	if(!minissdpdsock)
		minissdpdsock = "/var/run/minissdpd.sock";
	while(!devlist && deviceList[deviceIndex]) {
		devlist = getDevicesFromMiniSSDPD(deviceList[deviceIndex],
		                                  minissdpdsock);
		/* We return what we have found if it was not only a rootdevice */
		if(devlist && !strstr(deviceList[deviceIndex], "rootdevice"))
			return devlist;
		deviceIndex++;
	}
	deviceIndex = 0;
#endif
	/* fallback to direct discovery */
#ifdef WIN32
	sudp = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#else
	sudp = socket(PF_INET, SOCK_DGRAM, 0);
#endif
	if(sudp < 0)
	{
		PRINT_SOCKET_ERROR("socket");
		return NULL;
	}
	/* reception */
	memset(&sockudp_r, 0, sizeof(struct sockaddr));
	if(0/*ipv6*/) {
		struct sockaddr_in6 * p = (struct sockaddr_in6 *)&sockudp_r;
		p->sin6_family = AF_INET6;
		if(sameport)
			p->sin6_port = htons(PORT);
		p->sin6_addr = in6addr_any;//IN6ADDR_ANY_INIT;/*INADDR_ANY;*/
	} else {
		struct sockaddr_in * p = (struct sockaddr_in *)&sockudp_r;
		p->sin_family = AF_INET;
		if(sameport)
			p->sin_port = htons(PORT);
		p->sin_addr.s_addr = INADDR_ANY;
	}
#if 0
	/* emission */
	memset(&sockudp_w, 0, sizeof(struct sockaddr_in));
	sockudp_w.sin_family = AF_INET;
	sockudp_w.sin_port = htons(PORT);
	sockudp_w.sin_addr.s_addr = inet_addr(UPNP_MCAST_ADDR);
#endif
#ifdef WIN32
/* This code could help us to use the right Network interface for 
 * SSDP multicast traffic */
/* Get IP associated with the index given in the ip_forward struct
 * in order to give this ip to setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_IF) */
	if(GetBestRoute(inet_addr("223.255.255.255"), 0, &ip_forward) == NO_ERROR) {
		DWORD dwRetVal = 0;
		PMIB_IPADDRTABLE pIPAddrTable;
		DWORD dwSize = 0;
#ifdef DEBUG
		IN_ADDR IPAddr;
#endif
		int i;
#ifdef DEBUG
		printf("ifIndex=%lu nextHop=%lx \n", ip_forward.dwForwardIfIndex, ip_forward.dwForwardNextHop);
#endif
		pIPAddrTable = (MIB_IPADDRTABLE *) malloc(sizeof (MIB_IPADDRTABLE));
		if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
			free(pIPAddrTable);
			pIPAddrTable = (MIB_IPADDRTABLE *) malloc(dwSize);
		}
		if(pIPAddrTable) {
			dwRetVal = GetIpAddrTable( pIPAddrTable, &dwSize, 0 );
#ifdef DEBUG
			printf("\tNum Entries: %ld\n", pIPAddrTable->dwNumEntries);
#endif
			for (i=0; i < (int) pIPAddrTable->dwNumEntries; i++) {
#ifdef DEBUG
				printf("\n\tInterface Index[%d]:\t%ld\n", i, pIPAddrTable->table[i].dwIndex);
				IPAddr.S_un.S_addr = (u_long) pIPAddrTable->table[i].dwAddr;
				printf("\tIP Address[%d]:     \t%s\n", i, inet_ntoa(IPAddr) );
				IPAddr.S_un.S_addr = (u_long) pIPAddrTable->table[i].dwMask;
				printf("\tSubnet Mask[%d]:    \t%s\n", i, inet_ntoa(IPAddr) );
				IPAddr.S_un.S_addr = (u_long) pIPAddrTable->table[i].dwBCastAddr;
				printf("\tBroadCast[%d]:      \t%s (%ld)\n", i, inet_ntoa(IPAddr), pIPAddrTable->table[i].dwBCastAddr);
				printf("\tReassembly size[%d]:\t%ld\n", i, pIPAddrTable->table[i].dwReasmSize);
				printf("\tType and State[%d]:", i);
				printf("\n");
#endif
				if (pIPAddrTable->table[i].dwIndex == ip_forward.dwForwardIfIndex) {
					/* Set the address of this interface to be used */
					struct in_addr mc_if;
					memset(&mc_if, 0, sizeof(mc_if));
					mc_if.s_addr = pIPAddrTable->table[i].dwAddr;
					if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_IF, (const char *)&mc_if, sizeof(mc_if)) < 0) {
						PRINT_SOCKET_ERROR("setsockopt");
					}
					((struct sockaddr_in *)&sockudp_r)->sin_addr.s_addr = pIPAddrTable->table[i].dwAddr;
#ifndef DEBUG
					break;
#endif
				}
			}
			free(pIPAddrTable);
			pIPAddrTable = NULL;
		}
	}
#endif

#ifdef WIN32
	if (setsockopt(sudp, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof (opt)) < 0)
#else
	if (setsockopt(sudp, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) < 0)
#endif
	{
		PRINT_SOCKET_ERROR("setsockopt");
		return NULL;
	}

	if(multicastif)
	{
		struct in_addr mc_if;
		mc_if.s_addr = inet_addr(multicastif);
		if(0/*ipv6*/) {
		} else {
			((struct sockaddr_in *)&sockudp_r)->sin_addr.s_addr = mc_if.s_addr;
		}
		if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_IF, (const char *)&mc_if, sizeof(mc_if)) < 0)
		{
			PRINT_SOCKET_ERROR("setsockopt");
		}
	}

	/* Avant d'envoyer le paquet on bind pour recevoir la reponse */
    if (bind(sudp, &sockudp_r, 0/*ipv6*/?sizeof(struct sockaddr_in6):sizeof(struct sockaddr_in)) != 0)
	{
        PRINT_SOCKET_ERROR("bind");
		closesocket(sudp);
		return NULL;
    }

	/* Calculating maximum response time in seconds */
	mx = ((unsigned int)delay) / 1000u;
	/* receiving SSDP response packet */
	for(n = 0;;)
	{
	if(n == 0)
	{
		/* sending the SSDP M-SEARCH packet */
		n = snprintf(bufr, sizeof(bufr),
		             MSearchMsgFmt, deviceList[deviceIndex++], mx);
		/*printf("Sending %s", bufr);*/
#if 0
		n = sendto(sudp, bufr, n, 0,
		           (struct sockaddr *)&sockudp_w, sizeof(struct sockaddr_in));
		if (n < 0) {
			PRINT_SOCKET_ERROR("sendto");
			closesocket(sudp);
			return devlist;
		}
#endif
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC; // AF_INET6 or AF_INET
		hints.ai_socktype = SOCK_DGRAM;
		/*hints.ai_flags = */
		if ((rv = getaddrinfo(UPNP_MCAST_ADDR, XSTR(PORT), &hints, &servinfo)) != 0) {
#ifdef WIN32
		    fprintf(stderr, "getaddrinfo() failed: %d\n", rv);
#else
		    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
#endif
		    return devlist;
		}
		for(p = servinfo; p; p = p->ai_next) {
			n = sendto(sudp, bufr, n, 0, p->ai_addr, p->ai_addrlen);
			if (n < 0) {
				PRINT_SOCKET_ERROR("sendto");
				continue;
			}
		}
		freeaddrinfo(servinfo);
		if(n < 0) {
			closesocket(sudp);
			return devlist;
		}
	}
	/* Waiting for SSDP REPLY packet to M-SEARCH */
	n = ReceiveData(sudp, bufr, sizeof(bufr), delay);
	if (n < 0) {
		/* error */
		closesocket(sudp);
		return devlist;
	} else if (n == 0) {
		/* no data or Time Out */
		if (devlist || (deviceList[deviceIndex] == 0)) {
			/* no more device type to look for... */
			closesocket(sudp);
			return devlist;
		}
	} else {
		const char * descURL=NULL;
		int urlsize=0;
		const char * st=NULL;
		int stsize=0;
        /*printf("%d byte(s) :\n%s\n", n, bufr);*/ /* affichage du message */
		parseMSEARCHReply(bufr, n, &descURL, &urlsize, &st, &stsize);
		if(st&&descURL)
		{
#ifdef DEBUG
			printf("M-SEARCH Reply:\nST: %.*s\nLocation: %.*s\n",
			       stsize, st, urlsize, descURL);
#endif
			for(tmp=devlist; tmp; tmp = tmp->pNext) {
				if(memcmp(tmp->descURL, descURL, urlsize) == 0 &&
				   tmp->descURL[urlsize] == '\0' &&
				   memcmp(tmp->st, st, stsize) == 0 &&
				   tmp->st[stsize] == '\0')
					break;
			}
			/* at the exit of the loop above, tmp is null if
			 * no duplicate device was found */
			if(tmp)
				continue;
			tmp = (struct UPNPDev *)malloc(sizeof(struct UPNPDev)+urlsize+stsize);
			tmp->pNext = devlist;
			tmp->descURL = tmp->buffer;
			tmp->st = tmp->buffer + 1 + urlsize;
			memcpy(tmp->buffer, descURL, urlsize);
			tmp->buffer[urlsize] = '\0';
			memcpy(tmp->buffer + urlsize + 1, st, stsize);
			tmp->buffer[urlsize+1+stsize] = '\0';
			devlist = tmp;
		}
	}
	}
}