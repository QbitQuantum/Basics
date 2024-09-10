char *
pcap_ex_lookupdev(char *ebuf)
{
#ifdef _WIN32
	/* XXX - holy poo this sux */
	static char _ifname[8];
	MIB_IPADDRTABLE *ipaddrs;
	DWORD i, dsz, outip;
	pcap_if_t *pifs, *pif;
	struct pcap_addr *pa;
	char *name = NULL;
	int idx;
	
	/* Find our primary IP address. */
	ipaddrs = malloc((dsz = sizeof(*ipaddrs)));
	while (GetIpAddrTable(ipaddrs, &dsz, 0) == ERROR_INSUFFICIENT_BUFFER) {
		free(ipaddrs);
		ipaddrs = malloc(dsz);
	}
	outip = 0;
	for (i = 0; i < ipaddrs->dwNumEntries; i++) {
		if (ipaddrs->table[i].dwAddr != 0 &&
		    ipaddrs->table[i].dwAddr != 0x100007f
#if 0
		    /* XXX -no wType/MIB_IPADDR_PRIMARY in w32api/iprtrmib.h */
		    && ipaddrs->table[i].unused2 & 0x01
#endif
		    ) {
			outip = ipaddrs->table[i].dwAddr;
			break;
		}
	}
	free(ipaddrs);
	if (outip == 0) {
		/* XXX - default to first Ethernet interface. */
		return ("eth0");
	}
	/* Find matching pcap interface by IP. */
	if (_pcap_ex_findalldevs(&pifs, ebuf) == -1)
		return (name);
	
	for (pif = pifs, idx = 0; pif != NULL && name == NULL;
	    pif = pif->next, idx++) {
		for (pa = pif->addresses; pa != NULL; pa = pa->next) {
			if (pa->addr->sa_family == AF_INET &&
			    ((struct sockaddr_in *)pa->addr)->sin_addr.S_un.S_addr == outip) {
				sprintf(_ifname, "eth%d", idx);
				name = _ifname;
				break;
			}
		}
	}
	pcap_freealldevs(pifs);
	return (name);
#else
	return (pcap_lookupdev(ebuf));
#endif
}