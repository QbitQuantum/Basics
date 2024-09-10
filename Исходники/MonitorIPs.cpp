void MonitorIPs::CheckIPAddress()
{
    ULONG ulSize = 0;

    Log(LOG_DEBUG,__LINE__,">> MonIPs.ChkIPAddrs");

    //Get number of bytes required
    if(GetIpAddrTable(NULL,&ulSize,0)==ERROR_INSUFFICIENT_BUFFER)
    {
        //Aloocate required memory
        PMIB_IPADDRTABLE piat = reinterpret_cast<PMIB_IPADDRTABLE>(LocalAlloc(LMEM_FIXED,ulSize));
        if(piat)
        {
            //Retrive the list of IPs
            if(GetIpAddrTable(piat,&ulSize,0)==ERROR_SUCCESS)
            {
                WaitForSingleObject(m_hSync,MINUTE);
                m_ips.clear();

                for(DWORD dwIndex=0;dwIndex<piat->dwNumEntries;dwIndex++)
                {
                    //Trace all IPs
                    string strip;
                    char ip[_MAX_PATH] = {0};

                    PMIB_IPADDRROW prow = &piat->table[dwIndex];
                    _snprintf(ip,sizeof(ip)-1,"Addr %u, Idx %u, Mask %u, BCastAddr %u, ReasmSz %u, Tp %X.",
                                 prow->dwAddr,prow->dwIndex,prow->dwMask,prow->dwBCastAddr,prow->dwReasmSize,prow->wType);
                    strip.assign(ip);
                    if(prow->wType&MIB_IPADDR_PRIMARY)
                        strip.append("Primary.");
                    if(prow->wType&MIB_IPADDR_DYNAMIC)
                        strip.append("Dynamic.");
                    if(prow->wType&MIB_IPADDR_DISCONNECTED)
                        strip.append("Disconnected.");
                    if(prow->wType&MIB_IPADDR_DELETED)
                        strip.append("Deleted.");
                    if(prow->wType&MIB_IPADDR_TRANSIENT)
                        strip.append("Transient.");
                    if(prow->wType&MIB_IPADDR_DNS_ELIGIBLE)
                        strip.append("Published in DNS.");

                    m_ips.push_back(strip);
                }
                ReleaseMutex(m_hSync);
            }
            LocalFree(piat);
        }
    }

    HANDLE h;
    NotifyAddrChange(&h, &m_o);

    Log(LOG_DEBUG,__LINE__,"<< MonIPs.ChkIPAddrs");
}