	// for a given destination address - return the local endpoint address and the gateway address that 
    // will be used for a connection to the destination.
    // if the local address and the gateway address are the same then the destination is on a local network.
    void getRouteInfo (net::InetAddress destination, net::InetAddress& localAddr, net::InetAddress& gatewayAddr)
    {
        MIB_IPFORWARDROW routeInfo;
        DWORD res = GetBestRoute(htonl(destination.getIPAddress()), 0, &routeInfo);
        if (res != NO_ERROR)
            throw PacketException ("getRouteInfo: Error");

        gatewayAddr.set(ntohl(routeInfo.dwForwardNextHop), 0);

        destination.setPortNumber(123); 
        net::Socket s(SOCK_DGRAM);
        s.connect(destination);
        localAddr = s.getLocalAddress();
    }