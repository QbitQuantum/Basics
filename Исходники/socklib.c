/**
 * Canonize interface name. If attempt is not NULL, pick the interface
 * which has that address.
 * If attempt is NULL, pick interfaces in the following order of preference
 * 1. eth0
 * 2. Anything starting with eth0:
 * 3. Anything starting with eth
 * 4. Anything else
 * 5. localhost
 * 6. zero address
 */
net_if_t *getNetIf(const char *wanted) {
#ifndef __MINGW32__
	struct ifreq *ifrp, *ifend, *chosen;
	struct ifconf ifc;
	int s;
#else /* __MINGW32__ */
	int i;

	int etherNo=-1;
	int wantedEtherNo=-2; /* Wanted ethernet interface */

	MIB_IPADDRTABLE *iptab=NULL;
	MIB_IFTABLE *iftab=NULL;

	MIB_IPADDRROW *iprow, *chosen=NULL;
	MIB_IFROW *chosenIf=NULL;
	WORD wVersionRequested; /* Version of Winsock to load */
	WSADATA wsaData; /* Winsock implementation details */
	ULONG a;

	int r;
#endif /* __MINGW32__ */

	int lastGoodness=0;
	struct in_addr wantedAddress;
	int isAddress=0;
	int wantedLen=0;
	net_if_t *net_if;

	if(wanted == NULL) {
	    wanted = getenv("IFNAME");
	}

	if(wanted && INET_ATON(wanted, &wantedAddress))
	    isAddress=1;
	else
	    wantedAddress.s_addr=0;

	if(wanted)
	    wantedLen=strlen(wanted);

	net_if = MALLOC(net_if_t);
	if(net_if == NULL)
	    udpc_fatal(1, "Out of memory error");

#ifndef __MINGW32__

	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
	    perror("make socket");
	    exit(1);
	}

	ifc.ifc_len = sizeof(struct ifreq) * 10;
	while(1) {
	    size_t len = ifc.ifc_len;
	    ifc.ifc_buf = (caddr_t) malloc(ifc.ifc_len);
	    if(ifc.ifc_buf == NULL) {
		udpc_fatal(1, "Out of memory error");
	    }

	    if (ioctl(s, SIOCGIFCONF, (char *)&ifc) < 0 ||
		ifc.ifc_len < (signed int)sizeof(struct ifreq)) {
		perror("udpcast: SIOCGIFCONF: ");
		exit(1);
	    }

	    if(len == ifc.ifc_len) {
		ifc.ifc_len += sizeof(struct ifreq) * 10;
		free(ifc.ifc_buf);
	    } else
		break;
	}

	ifend = (struct ifreq *)((char *)ifc.ifc_buf + ifc.ifc_len);
	chosen=NULL;

	for (ifrp = (struct ifreq *) ifc.ifc_buf ; ifrp < ifend;
#ifdef IFREQ_SIZE
	     ifrp = IFREQ_SIZE(*ifrp) + (char *)ifrp
#else
	     ifrp++
#endif
	     ) {
	    unsigned long iaddr = getSinAddr(&ifrp->ifr_addr).s_addr;
	    int goodness;

	    if(ifrp->ifr_addr.sa_family != PF_INET)
		continue;

	    if(wanted) {
		if(isAddress && iaddr == wantedAddress.s_addr) {
		    goodness=8;
		} else if(strcmp(wanted, ifrp->ifr_name) ==0) {
		    /* perfect match on interface name */
		    goodness=12;
		} else if(wanted != NULL &&
			  strncmp(wanted, ifrp->ifr_name, wantedLen) ==0) {
		    /* prefix match on interface name */
		    goodness=7;
		} else {
		    /* no match, try next */
		    continue;
		}
	    } else {
		if(iaddr == 0) {
		    /* disregard interfaces whose address is zero */
		    goodness = 1;
		} else if(iaddr == htonl(0x7f000001)) {
		    /* disregard localhost type devices */
		    goodness = 2;
		} else if(strcmp("eth0", ifrp->ifr_name) == 0 ||
			  strcmp("en0",  ifrp->ifr_name) == 0) {
		    /* prefer first ethernet interface */
		    goodness = 6;
		} else if(strncmp("eth0:", ifrp->ifr_name, 5) == 0) {
		    /* second choice: any secondary addresses of first ethernet */
		    goodness = 5;
		} else if(strncmp("eth", ifrp->ifr_name, 3) == 0 ||
			  strncmp("en",  ifrp->ifr_name, 2) == 0) {
		    /* and, if not available, any other ethernet device */
		    goodness = 4;
		} else {
		    goodness = 3;
		}
	    }

	    if(hasLink(s, ifrp->ifr_name))
	      /* Good or unknown link status privileged over known
	       * disconnected */
	      goodness += 3;

	    /* If all else is the same, prefer interfaces that
	     * have broadcast */
	    goodness = goodness * 2;
	    if(goodness >= lastGoodness) {
		/* Privilege broadcast-enabled interfaces */
		if(ioctl(s,  SIOCGIFBRDADDR, ifrp) < 0)
		    udpc_fatal(-1, "Error getting broadcast address for %s: %s",
			       ifrp->ifr_name, strerror(errno));
		if(getSinAddr(&ifrp->ifr_ifru.ifru_broadaddr).s_addr)
		    goodness++;
	    }

	    if(goodness > lastGoodness) {
		chosen = ifrp;
		lastGoodness = goodness;
		net_if->addr.s_addr = iaddr;
	    }
	}


	if(!chosen) {
	    fprintf(stderr, "No suitable network interface found\n");
	    fprintf(stderr, "The following interfaces are available:\n");

	    for (ifrp = (struct ifreq *) ifc.ifc_buf ; ifrp < ifend;
#ifdef IFREQ_SIZE
		 ifrp = IFREQ_SIZE(*ifrp) + (char *)ifrp
#else
		 ifrp++
#endif
		 ) {
		char buffer[16];

		if(ifrp->ifr_addr.sa_family != PF_INET)
		    continue;

		fprintf(stderr, "\t%s\t%s\n",
			ifrp->ifr_name,
			udpc_getIpString((struct sockaddr_in *)&ifrp->ifr_addr, buffer));
	    }
	    exit(1);
	}

	net_if->name = strdup(chosen->ifr_name);

#ifdef HAVE_STRUCT_IP_MREQN_IMR_IFINDEX
	/* Index for multicast subscriptions */
	if(ioctl(s,  SIOCGIFINDEX, chosen) < 0)
	    udpc_fatal(-1, "Error getting index for %s: %s", net_if->name,
		       strerror(errno));
	net_if->index = chosen->ifr_ifindex;
#endif

	/* Broadcast */
	if(ioctl(s,  SIOCGIFBRDADDR, chosen) < 0)
	    udpc_fatal(-1, "Error getting broadcast address for %s: %s",
		       net_if->name, strerror(errno));
	net_if->bcast = getSinAddr(&chosen->ifr_ifru.ifru_broadaddr);

	close(s);
	free(ifc.ifc_buf);

#else /* __MINGW32__ */

	/* WINSOCK initialization */
	wVersionRequested = MAKEWORD(2, 0); /* Request Winsock v2.0 */
	if (WSAStartup(wVersionRequested, &wsaData) != 0) /* Load Winsock DLL */ {
	    fprintf(stderr,"WSAStartup() failed");
	    exit(1);
	}
	/* End WINSOCK initialization */


	a=0;
	r=GetIpAddrTable(iptab, &a, TRUE);
	iptab=malloc(a);
	r=GetIpAddrTable(iptab, &a, TRUE);

	a=0;
	r=GetIfTable(iftab, &a, TRUE);
	iftab=malloc(a);
	r=GetIfTable(iftab, &a, TRUE);

	if(wanted && !strncmp(wanted, "eth", 3) && wanted[3]) {
	    char *ptr;
	    int n = strtoul(wanted+3, &ptr, 10);
	    if(!*ptr)
		wantedEtherNo=n;
	}

	for(i=0; i<iptab->dwNumEntries; i++) {
	    int goodness=-1;
	    unsigned long iaddr;
	    int isEther=0;
	    MIB_IFROW *ifrow;

	    iprow = &iptab->table[i];
	    iaddr = iprow->dwAddr;

	    ifrow = getIfRow(iftab, iprow->dwIndex);

	    if(ifrow && ifrow->dwPhysAddrLen == 6 && iprow->dwBCastAddr) {
		isEther=1;
		etherNo++;
	    }

	    if(wanted) {
		if(isAddress && iaddr == wantedAddress.s_addr) {
		    goodness=8;
		} else if(isEther && wantedEtherNo == etherNo) {
			goodness=9;
		} else if(ifrow->dwPhysAddrLen) {
		    int j;
		    const char *ptr=wanted;
		    for(j=0; *ptr && j<ifrow->dwPhysAddrLen; j++) {
			int digit = strtoul(ptr, (char**)&ptr, 16);
			if(digit != ifrow->bPhysAddr[j])
			    break; /* Digit mismatch */
			if(*ptr == '-' || *ptr == ':') {
			    ptr++;
			}
		    }
		    if(!*ptr && j == ifrow->dwPhysAddrLen) {
			goodness=9;
		    }
		}
	    } else {
		if(iaddr == 0) {
		    /* disregard interfaces whose address is zero */
		    goodness = 1;
		} else if(iaddr == htonl(0x7f000001)) {
		    /* disregard localhost type devices */
		    goodness = 2;
		} else if(isEther) {
		    /* prefer ethernet */
		    goodness = 6;
		} else if(ifrow->dwPhysAddrLen) {
		    /* then prefer interfaces which have a physical address */
		    goodness = 4;
		} else {
		    goodness = 3;
		}
	    }

	    goodness = goodness * 2;
	    /* If all else is the same, prefer interfaces that
	     * have broadcast */
	    if(goodness >= lastGoodness) {
		/* Privilege broadcast-enabled interfaces */
		if(iprow->dwBCastAddr)
		    goodness++;
	    }

	    if(goodness > lastGoodness) {
		chosen = iprow;
		chosenIf = ifrow;
		lastGoodness = goodness;
	    }
	}

	if(!chosen) {
	    fprintf(stderr, "No suitable network interface found%s%s\n",
		    wanted ? " for " : "", wanted ? wanted : "");
	    fprintf(stderr, "The following interfaces are available:\n");

	    for(i=0; i<iptab->dwNumEntries; i++) {
		char buffer[16];
		struct sockaddr_in addr;
		MIB_IFROW *ifrow;
		char *name=NULL;
		iprow = &iptab->table[i];
		addr.sin_addr.s_addr = iprow->dwAddr;
		ifrow = getIfRow(iftab, iprow->dwIndex);
		name = fmtName(ifrow);
		fprintf(stderr, " %15s  %s\n",
			udpc_getIpString(&addr, buffer),
			name ? name : "");
		if(name)
		    free(name);
	    }
	    exit(1);
	}

	net_if->bcast.s_addr = net_if->addr.s_addr = chosen->dwAddr;
	if(chosen->dwBCastAddr)
	    net_if->bcast.s_addr |= ~chosen->dwMask;
	if(chosenIf) {
	    net_if->name = fmtName(chosenIf);
	} else {
	    net_if->name = "*";
	}
	free(iftab);
	free(iptab);
#endif /* __MINGW32__ */

	return net_if;
}