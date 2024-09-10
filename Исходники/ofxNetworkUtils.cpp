void ofxNetworkUtils::init(unsigned int filterFlags, unsigned int excludeFlags){
	networkInterfaces.clear(); // 
	struct ifaddrs * ifap;
	if (getifaddrs(&ifap) == 0)
	{
		struct ifaddrs * p = ifap;
		while(p)
		{
			int ifaAddr  = SockAddrToUint(p->ifa_addr);
			int maskAddr = SockAddrToUint(p->ifa_netmask);
			int dstAddr  = SockAddrToUint(p->ifa_dstaddr);
			if (ifaAddr != 0 && (p->ifa_flags & filterFlags) && (p->ifa_flags & excludeFlags) == 0)
			{
				
				networkInterface aNetworkInterface;
				
				char ifaAddrStr[32];  Inet_NtoA(ifaAddr,  ifaAddrStr);
				char maskAddrStr[32]; Inet_NtoA(maskAddr, maskAddrStr);
				char dstAddrStr[32];  Inet_NtoA(dstAddr,  dstAddrStr);
				
				char logMsg[512];
				sprintf(logMsg, "Found interface: name=[%s] address=[%s] netmask=[%s] broadcastAddr=[%s]\n", p->ifa_name, ifaAddrStr, maskAddrStr, dstAddrStr);
				
				ofLog(OF_LOG_NOTICE, logMsg);
				networkInterfaces.push_back( new networkInterface(p->ifa_name, ifaAddrStr, maskAddrStr, dstAddrStr));
				
			}
			p = p->ifa_next;
		}
		freeifaddrs(ifap);
	}
	
}