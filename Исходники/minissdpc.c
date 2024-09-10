/* ssdpDiscoverDevices() :
 * return a chained list of all devices found or NULL if
 * no devices was found.
 * It is up to the caller to free the chained list
 * delay is in millisecond (poll).
 * UDA v1.1 says :
 *   The TTL for the IP packet SHOULD default to 2 and
 *   SHOULD be configurable. */
struct UPNPDev *
ssdpDiscoverDevices(const char * const deviceTypes[],
                    int delay, const char * multicastif,
                    int localport,
                    int ipv6, unsigned char ttl,
                    int * error,
                    int searchalltypes)
{
	struct UPNPDev * tmp;
	struct UPNPDev * devlist = 0;
	unsigned int scope_id = 0;
	int opt = 1;
	static const char MSearchMsgFmt[] =
	"M-SEARCH * HTTP/1.1\r\n"
	"HOST: %s:" XSTR(SSDP_PORT) "\r\n"
	"ST: %s\r\n"
	"MAN: \"ssdp:discover\"\r\n"
	"MX: %u\r\n"
	"\r\n";
	int deviceIndex;
	char bufr[1536];	/* reception and emission buffer */
	int sudp;
	int n;
	struct sockaddr_storage sockudp_r;
	unsigned int mx;
#ifdef NO_GETADDRINFO
	struct sockaddr_storage sockudp_w;
#else
	int rv;
	struct addrinfo hints, *servinfo, *p;
#endif
#ifdef _WIN32
	MIB_IPFORWARDROW ip_forward;
	unsigned long _ttl = (unsigned long)ttl;
#endif
	int linklocal = 1;

	if(error)
		*error = MINISSDPC_UNKNOWN_ERROR;

	if(localport==UPNP_LOCAL_PORT_SAME)
		localport = SSDP_PORT;

#ifdef _WIN32
	sudp = socket(ipv6 ? PF_INET6 : PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#else
	sudp = socket(ipv6 ? PF_INET6 : PF_INET, SOCK_DGRAM, 0);
#endif
	if(sudp < 0)
	{
		if(error)
			*error = MINISSDPC_SOCKET_ERROR;
		return NULL;
	}
	/* reception */
	memset(&sockudp_r, 0, sizeof(struct sockaddr_storage));
	if(ipv6) {
		struct sockaddr_in6 * p = (struct sockaddr_in6 *)&sockudp_r;
		p->sin6_family = AF_INET6;
		if(localport > 0 && localport < 65536)
			p->sin6_port = htons((unsigned short)localport);
		p->sin6_addr = in6addr_any; /* in6addr_any is not available with MinGW32 3.4.2 */
	} else {
		struct sockaddr_in * p = (struct sockaddr_in *)&sockudp_r;
		p->sin_family = AF_INET;
		if(localport > 0 && localport < 65536)
			p->sin_port = htons((unsigned short)localport);
		p->sin_addr.s_addr = INADDR_ANY;
	}
#ifdef _WIN32
/* This code could help us to use the right Network interface for
 * SSDP multicast traffic */
/* Get IP associated with the index given in the ip_forward struct
 * in order to give this ip to setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_IF) */
	if(!ipv6
	   && (GetBestRoute(inet_addr("223.255.255.255"), 0, &ip_forward) == NO_ERROR)) {
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
		if(pIPAddrTable) {
			if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
				free(pIPAddrTable);
				pIPAddrTable = (MIB_IPADDRTABLE *) malloc(dwSize);
			}
		}
		if(pIPAddrTable) {
			dwRetVal = GetIpAddrTable( pIPAddrTable, &dwSize, 0 );
			if (dwRetVal == NO_ERROR) {
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
						setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_IF, (const char *)&mc_if, sizeof(mc_if));
						((struct sockaddr_in *)&sockudp_r)->sin_addr.s_addr = pIPAddrTable->table[i].dwAddr;
#ifndef DEBUG
						break;
#endif
					}
				}
			}
			free(pIPAddrTable);
			pIPAddrTable = NULL;
		}
	}
#endif	/* _WIN32 */

#ifdef _WIN32
	if (setsockopt(sudp, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof (opt)) < 0)
#else
	if (setsockopt(sudp, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) < 0)
#endif
	{
		if(error)
			*error = MINISSDPC_SOCKET_ERROR;
		closesocket(sudp);
		return NULL;
	}

#ifdef _WIN32
	if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_TTL, (const char *)&_ttl, sizeof(_ttl)) < 0)
#else  /* _WIN32 */
	if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0)
#endif /* _WIN32 */
	{
		/* not a fatal error */
	}

	if(multicastif)
	{
		if(ipv6) {
#if !defined(_WIN32)
			/* according to MSDN, if_nametoindex() is supported since
			 * MS Windows Vista and MS Windows Server 2008.
			 * http://msdn.microsoft.com/en-us/library/bb408409%28v=vs.85%29.aspx */
			unsigned int ifindex = if_nametoindex(multicastif); /* eth0, etc. */
			if(setsockopt(sudp, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex, sizeof(ifindex)) < 0)
			{
			}
#else
#ifdef DEBUG
			printf("Setting of multicast interface not supported in IPv6 under Windows.\n");
#endif
#endif
		} else {
			struct in_addr mc_if;
			mc_if.s_addr = inet_addr(multicastif); /* ex: 192.168.x.x */
			if(mc_if.s_addr != INADDR_NONE)
			{
				((struct sockaddr_in *)&sockudp_r)->sin_addr.s_addr = mc_if.s_addr;
				if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_IF, (const char *)&mc_if, sizeof(mc_if)) < 0)
				{
				}
			} else {
#ifdef HAS_IP_MREQN
				/* was not an ip address, try with an interface name */
				struct ip_mreqn reqn;	/* only defined with -D_BSD_SOURCE or -D_GNU_SOURCE */
				memset(&reqn, 0, sizeof(struct ip_mreqn));
				reqn.imr_ifindex = if_nametoindex(multicastif);
				if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_IF, (const char *)&reqn, sizeof(reqn)) < 0)
				{
				}
#elif !defined(_WIN32)
				struct ifreq ifr;
				int ifrlen = sizeof(ifr);
				strncpy(ifr.ifr_name, multicastif, IFNAMSIZ);
				ifr.ifr_name[IFNAMSIZ-1] = '\0';
				if(ioctl(sudp, SIOCGIFADDR, &ifr, &ifrlen) < 0)
				{
				}
				mc_if.s_addr = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr;
				if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_IF, (const char *)&mc_if, sizeof(mc_if)) < 0)
				{
				}
#else /* _WIN32 */
#ifdef DEBUG
				printf("Setting of multicast interface not supported with interface name.\n");
#endif
#endif /* #ifdef HAS_IP_MREQN / !defined(_WIN32) */
			}
		}
	}

	/* Before sending the packed, we first "bind" in order to be able
	 * to receive the response */
	if (bind(sudp, (const struct sockaddr *)&sockudp_r,
	         ipv6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in)) != 0)
	{
		if(error)
			*error = MINISSDPC_SOCKET_ERROR;
		closesocket(sudp);
		return NULL;
	}

	if(error)
		*error = MINISSDPC_SUCCESS;
	/* Calculating maximum response time in seconds */
	mx = ((unsigned int)delay) / 1000u;
	if(mx == 0) {
		mx = 1;
		delay = 1000;
	}
	/* receiving SSDP response packet */
	for(deviceIndex = 0; deviceTypes[deviceIndex]; deviceIndex++) {
		/* sending the SSDP M-SEARCH packet */
		n = snprintf(bufr, sizeof(bufr),
		             MSearchMsgFmt,
		             ipv6 ?
		             (linklocal ? "[" UPNP_MCAST_LL_ADDR "]" :  "[" UPNP_MCAST_SL_ADDR "]")
		             : UPNP_MCAST_ADDR,
		             deviceTypes[deviceIndex], mx);
		if ((unsigned int)n >= sizeof(bufr)) {
			if(error)
				*error = MINISSDPC_MEMORY_ERROR;
			goto error;
		}
#ifdef DEBUG
		/*printf("Sending %s", bufr);*/
		printf("Sending M-SEARCH request to %s with ST: %s\n",
		       ipv6 ?
		       (linklocal ? "[" UPNP_MCAST_LL_ADDR "]" :  "[" UPNP_MCAST_SL_ADDR "]")
		       : UPNP_MCAST_ADDR,
		       deviceTypes[deviceIndex]);
#endif
#ifdef NO_GETADDRINFO
		/* the following code is not using getaddrinfo */
		/* emission */
		memset(&sockudp_w, 0, sizeof(struct sockaddr_storage));
		if(ipv6) {
			struct sockaddr_in6 * p = (struct sockaddr_in6 *)&sockudp_w;
			p->sin6_family = AF_INET6;
			p->sin6_port = htons(SSDP_PORT);
			inet_pton(AF_INET6,
			          linklocal ? UPNP_MCAST_LL_ADDR : UPNP_MCAST_SL_ADDR,
			          &(p->sin6_addr));
		} else {
			struct sockaddr_in * p = (struct sockaddr_in *)&sockudp_w;
			p->sin_family = AF_INET;
			p->sin_port = htons(SSDP_PORT);
			p->sin_addr.s_addr = inet_addr(UPNP_MCAST_ADDR);
		}
		n = sendto(sudp, bufr, n, 0, &sockudp_w,
		           ipv6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in));
		if (n < 0) {
			if(error)
				*error = MINISSDPC_SOCKET_ERROR;
			break;
		}
#else /* #ifdef NO_GETADDRINFO */
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC; /* AF_INET6 or AF_INET */
		hints.ai_socktype = SOCK_DGRAM;
		/*hints.ai_flags = */
		if ((rv = getaddrinfo_retro(ipv6
		                      ? (linklocal ? UPNP_MCAST_LL_ADDR : UPNP_MCAST_SL_ADDR)
		                      : UPNP_MCAST_ADDR,
		                      XSTR(SSDP_PORT), &hints, &servinfo)) != 0) {
			if(error)
				*error = MINISSDPC_SOCKET_ERROR;
#ifdef _WIN32
			fprintf(stderr, "getaddrinfo() failed: %d\n", rv);
#else
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
#endif
			break;
		}
		for(p = servinfo; p; p = p->ai_next) {
			n = (int)sendto(sudp, bufr, n, 0, p->ai_addr, p->ai_addrlen);
			if (n < 0) {
#ifdef DEBUG
				char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
				if (getnameinfo(p->ai_addr, p->ai_addrlen, hbuf, sizeof(hbuf), sbuf,
				                sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV) == 0) {
					fprintf(stderr, "host:%s port:%s\n", hbuf, sbuf);
				}
#endif
				continue;
			}
		}
		freeaddrinfo(servinfo);
		if(n < 0) {
			if(error)
				*error = MINISSDPC_SOCKET_ERROR;
			break;
		}
#endif /* #ifdef NO_GETADDRINFO */
		/* Waiting for SSDP REPLY packet to M-SEARCH
		 * if searchalltypes is set, enter the loop only
		 * when the last deviceType is reached */
		if(!searchalltypes || !deviceTypes[deviceIndex + 1]) do {
			n = receivedata(sudp, bufr, sizeof(bufr), delay, &scope_id);
			if (n < 0) {
				/* error */
				if(error)
					*error = MINISSDPC_SOCKET_ERROR;
				goto error;
			} else if (n == 0) {
				/* no data or Time Out */
#ifdef DEBUG
				printf("NODATA or TIMEOUT\n");
#endif /* DEBUG */
				if (devlist && !searchalltypes) {
					/* found some devices, stop now*/
					if(error)
						*error = MINISSDPC_SUCCESS;
					goto error;
				}
			} else {
				const char * descURL=NULL;
				int urlsize=0;
				const char * st=NULL;
				int stsize=0;
				const char * usn=NULL;
				int usnsize=0;
				parseMSEARCHReply(bufr, n, &descURL, &urlsize, &st, &stsize, &usn, &usnsize);
				if(st&&descURL) {
#ifdef DEBUG
					printf("M-SEARCH Reply:\n  ST: %.*s\n  USN: %.*s\n  Location: %.*s\n",
					       stsize, st, usnsize, (usn?usn:""), urlsize, descURL);
#endif /* DEBUG */
					for(tmp=devlist; tmp; tmp = tmp->pNext) {
						if(memcmp(tmp->descURL, descURL, urlsize) == 0 &&
						   tmp->descURL[urlsize] == '\0' &&
						   memcmp(tmp->st, st, stsize) == 0 &&
						   tmp->st[stsize] == '\0' &&
						   (usnsize == 0 || memcmp(tmp->usn, usn, usnsize) == 0) &&
						   tmp->usn[usnsize] == '\0')
							break;
					}
					/* at the exit of the loop above, tmp is null if
					 * no duplicate device was found */
					if(tmp)
						continue;
					tmp = (struct UPNPDev *)malloc(sizeof(struct UPNPDev)+urlsize+stsize+usnsize);
					if(!tmp) {
						/* memory allocation error */
						if(error)
							*error = MINISSDPC_MEMORY_ERROR;
						goto error;
					}
					tmp->pNext = devlist;
					tmp->descURL = tmp->buffer;
					tmp->st = tmp->buffer + 1 + urlsize;
					tmp->usn = tmp->st + 1 + stsize;
					memcpy(tmp->buffer, descURL, urlsize);
					tmp->buffer[urlsize] = '\0';
					memcpy(tmp->st, st, stsize);
					tmp->buffer[urlsize+1+stsize] = '\0';
					if(usn != NULL)
						memcpy(tmp->usn, usn, usnsize);
					tmp->buffer[urlsize+1+stsize+1+usnsize] = '\0';
					tmp->scope_id = scope_id;
					devlist = tmp;
				}
			}
		} while(n > 0);
		if(ipv6) {
			/* switch linklocal flag */
			if(linklocal) {
				linklocal = 0;
				--deviceIndex;
			} else {
				linklocal = 1;
			}
		}
	}
error:
	closesocket(sudp);
	return devlist;
}