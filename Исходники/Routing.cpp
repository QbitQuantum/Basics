  /*!
   * @if jp
   * @brief 宛先アドレスから利用されるエンドポイントアドレスを得る
   * @else
   * @brief Getting network interface name from destination address
   * @endif
   */
  bool dest_to_endpoint(std::string dest_addr, std::string& endpoint)
  {
    Winsock winsock;
    {
      struct hostent* hp;
      hp = ::gethostbyname(dest_addr.c_str());
      if (hp == 0) { return false; }

      int i(0);
      while (hp->h_addr_list[i] != 0)
        {
          if(hp->h_addrtype == AF_INET)
            {
              struct sockaddr_in addr;
              memset((char*)&addr, 0, sizeof(addr));
              memcpy((char*)&addr.sin_addr, hp->h_addr_list[i], hp->h_length);
              dest_addr = inet_ntoa(addr.sin_addr);
              break;
            }
          ++i;
        }
    }
    
    UINT ipaddress(inet_addr(dest_addr.c_str()));
    if (ipaddress == INADDR_NONE) { return false; }
    
    DWORD bestifindex;
    if (NO_ERROR != GetBestInterface(ipaddress, &bestifindex)) { return false; }
        
    PMIB_IPADDRTABLE ipaddr_table;
    ipaddr_table = (MIB_IPADDRTABLE *) MALLOC(sizeof (MIB_IPADDRTABLE));
    if (ipaddr_table == 0) { return false; }

    // Make an initial call to GetIpAddrTable to get the
    // necessary size into the size variable
    DWORD size(0);
    if (GetIpAddrTable(ipaddr_table, &size, 0) == ERROR_INSUFFICIENT_BUFFER)
      {
        FREE(ipaddr_table);
        ipaddr_table = (MIB_IPADDRTABLE *) MALLOC(size);
      }
    if (ipaddr_table == 0) { return false; }
    if (GetIpAddrTable(ipaddr_table, &size, 0) != NO_ERROR) { return false; }
    
    for (int i(0); i < (int) ipaddr_table->dwNumEntries; ++i)
      {
        if (bestifindex == ipaddr_table->table[i].dwIndex)
          {
            IN_ADDR inipaddr;
            inipaddr.S_un.S_addr = (u_long) ipaddr_table->table[i].dwAddr;
            endpoint = inet_ntoa(inipaddr);
            return true;
          }
      }
    return false;
  }