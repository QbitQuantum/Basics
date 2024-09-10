bool UdpComm::joinMulticast(const char* addrStr)
{
  sockaddr_in group;
  if(!resolve(addrStr, 0, &group))
    return false;

  //join multicast group for every interface
  if(IN_MULTICAST(ntohl(group.sin_addr.s_addr)))
  {
#ifndef WINDOWS
    ip_mreq mreq;
    ifconf ifc;
    ifreq* item;
    char buf[1024];

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if(ioctl(sock, SIOCGIFCONF, &ifc) < 0)
    {
      std::cerr << "cannot get interface list" << std::endl;
      return false;
    }
    else
    {
      bool could_join(false);
      for(unsigned int i = 0; i < ifc.ifc_len / sizeof(ifreq); i++)
      {
        item = &ifc.ifc_req[i];
        mreq.imr_multiaddr = group.sin_addr;
        mreq.imr_interface = ((sockaddr_in*)&item->ifr_addr)->sin_addr;
        if(0 == setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&mreq, sizeof(mreq)))
          could_join = true;
      }
      if(!could_join)
      {
        std::cerr << "join multicast group failed for interface" << std::endl;
        return false;
      }
    }
#else
    char host[128];
    hostent* pHost;
    if(gethostname(host, sizeof(host)) < 0 || !(pHost = (hostent*)gethostbyname(host)))
    {
      std::cerr << "cannot get interface list" << std::endl;
      return false;
    }

    ip_mreq mreq;
    bool couldJoin(false);
    for(int i = 0; pHost->h_addr_list[i]; i++)
    {
      mreq.imr_multiaddr = group.sin_addr;
      mreq.imr_interface = *((in_addr*)pHost->h_addr_list[i]);
      if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) == 0)
        couldJoin = true;
    }
    if(!couldJoin)
    {
      std::cerr << "join multicast group failed for interface" << std::endl;
      return false;
    }
#endif
    return true;
  }
  else
    std::cerr << "not a multicast address" << std::endl;
  return false;
}