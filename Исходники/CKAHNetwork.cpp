bool CNetWatcher::GetNewStatus ()
{
	//log.WriteFormat (_T("[CNetWatcher] GetNewStatus begins"), PEL_INFO);

    int newlistsize = 0;
    NetworkList * newlist = 0;

    if (m_getAdaptersAddresses)
    {
        // IPv6-supporting version (XP, Vista+)

        #define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x)) 
        #define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

        PIP_ADAPTER_ADDRESSES AdapterAddresses = NULL;
        ULONG OutBufferLength = 0;
        ULONG RetVal = 0, i;    

        for (i = 0; i < 5; i++) 
        {
            RetVal = SafeGetAdaptersAddresses(m_getAdaptersAddresses, AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, AdapterAddresses, &OutBufferLength);
            
            if (RetVal != ERROR_BUFFER_OVERFLOW) 
                break;

            if (AdapterAddresses != NULL) { FREE(AdapterAddresses); }
            
            AdapterAddresses = (PIP_ADAPTER_ADDRESSES) MALLOC(OutBufferLength);
            if (AdapterAddresses == NULL)
            {
                RetVal = GetLastError();
                break;
            }
        }
        
        if (RetVal == NO_ERROR) 
        {
            int entries = 0;
            for (PIP_ADAPTER_ADDRESSES Adapter1 = AdapterAddresses; Adapter1; Adapter1 = Adapter1->Next)
            {
                entries++;
            }

            newlistsize = sizeof(CKAHFW::Network)*entries + sizeof(int);

            newlist = (NetworkList *) new unsigned char [ newlistsize ];
            memset(newlist, 0, newlistsize);

            int entry = 0;
            PIP_ADAPTER_ADDRESSES Adapter = AdapterAddresses;

            while (Adapter) 
            {
                newlist->list[entry].HasIPv4 = FALSE;
                newlist->list[entry].HasIPv6 = FALSE;

                memset(newlist->list[entry].AdapterName, 0, CKAHFW::ADAPTERNAMELEN);
                strncpy(newlist->list[entry].AdapterName, __LPSTR(Adapter->FriendlyName), CKAHFW::ADAPTERNAMELEN);
                newlist->list[entry].AdapterName[CKAHFW::ADAPTERNAMELEN - 1] = 0;

                memset(newlist->list[entry].AdapterDesc, 0, CKAHFW::ADAPTERDESCLEN);
                strncpy(newlist->list[entry].AdapterDesc, __LPSTR(Adapter->Description), CKAHFW::ADAPTERDESCLEN);
                newlist->list[entry].AdapterDesc[CKAHFW::ADAPTERDESCLEN - 1] = 0;

                memset(newlist->list[entry].Phys, 0, CKAHFW::PHYSLEN);
                memcpy(newlist->list[entry].Phys, Adapter->PhysicalAddress, min(Adapter->PhysicalAddressLength, CKAHFW::PHYSLEN));

                memcpy(newlist->list[entry].Zones, Adapter->ZoneIndices, sizeof(Adapter->ZoneIndices));

                bool  HasIPv4 = false;
                DWORD IPv4 = 0;
                DWORD Maskv4 = 0;

                bool  HasIPv6 = false;
                CKAHUM::IPv6 IPv6;   IPv6.SetZero();
                CKAHUM::IPv6 Maskv6; Maskv6.SetZero();

                IP_ADAPTER_UNICAST_ADDRESS* UnicastAddress = Adapter->FirstUnicastAddress;
                while (UnicastAddress)
                {
                    if (UnicastAddress->Address.lpSockaddr->sa_family == AF_INET)
                    {
                        if (!HasIPv4)
                        {
                            DWORD ipv4 = ntohl(((sockaddr_in*)UnicastAddress->Address.lpSockaddr)->sin_addr.S_un.S_addr);

                            DWORD maxmaskv4 = CKAHUM::IPv4Mask(32);
                            DWORD maxlength = 32;

                            IP_ADAPTER_PREFIX* Prefix = Adapter->FirstPrefix;
                            while (Prefix)
                            {
                                if (Prefix->Address.lpSockaddr->sa_family == AF_INET &&
                                    Prefix->PrefixLength > 0 &&
                                    Prefix->PrefixLength < maxlength)
                                {
                                    DWORD netv4 = ntohl(((sockaddr_in*)Prefix->Address.lpSockaddr)->sin_addr.S_un.S_addr);
                                    DWORD maskv4 = CKAHUM::IPv4Mask( Prefix->PrefixLength );
                                    if ((netv4 & maskv4) == (ipv4 & maskv4))
                                    {
                                        maxmaskv4 = maskv4;
                                        maxlength = Prefix->PrefixLength;
                                    }
                                }

                                Prefix = Prefix->Next;
                            }
                            HasIPv4 = TRUE;
                            IPv4 = ipv4;
                            Maskv4 = maxmaskv4;
                        }
                    }
                    else if (UnicastAddress->Address.lpSockaddr->sa_family == AF_INET6 )
                    {
                        if (!IPv6.IsValid())
                        {
                            CKAHUM::IPv6 ipv6;
                            ipv6.Set( ((CKAHUM::OWord*)((sockaddr_in6*)UnicastAddress->Address.lpSockaddr)->sin6_addr.u.Byte)->ntoh(),
                                      ((sockaddr_in6*)UnicastAddress->Address.lpSockaddr)->sin6_scope_id);

                            CKAHUM::IPv6::Scope scope = ipv6.GetScope();

                            if (ipv6.GetScope() == CKAHUM::IPv6::ScopeGlobal)
                            {
                                CKAHUM::IPv6 maxmaskv6; 

                                maxmaskv6.SetMask(128, 0);
                                DWORD maxlength = 128;

                                IP_ADAPTER_PREFIX* Prefix = Adapter->FirstPrefix;
                                while (Prefix)
                                {
                                    if (Prefix->Address.lpSockaddr->sa_family == AF_INET6 &&
                                        Prefix->PrefixLength > 0 &&
                                        Prefix->PrefixLength < maxlength)
                                    {
                                        CKAHUM::IPv6 netv6;
                                        CKAHUM::IPv6 maskv6;

                                        netv6.Set( ((CKAHUM::OWord*)((sockaddr_in6*)Prefix->Address.lpSockaddr)->sin6_addr.u.Byte)->ntoh(),
                                                   ((sockaddr_in6*)Prefix->Address.lpSockaddr)->sin6_scope_id );
                                        maskv6.SetMask(Prefix->PrefixLength, 0);

                                        if ((netv6 & maskv6) == (ipv6 & maskv6))
                                        {
                                            maxmaskv6= maskv6;
                                            maxlength = Prefix->PrefixLength;
                                        }
                                    }

                                    Prefix = Prefix->Next;
                                }
                                IPv6 = ipv6;
                                Maskv6 = maxmaskv6;
                            }
                        }

                        if (!HasIPv6)
                        {
                            HasIPv6 = TRUE;
                        }
                    }

                    UnicastAddress = UnicastAddress->Next;
                }

                newlist->list[entry].HasIPv4 = HasIPv4;
                newlist->list[entry].IPv4    = IPv4;
                newlist->list[entry].Maskv4  = Maskv4;
                newlist->list[entry].HasIPv6 = HasIPv6;
                newlist->list[entry].IPv6    = IPv6;
                newlist->list[entry].Maskv6  = Maskv6;

                Adapter = Adapter->Next;
                entry++;
            }
            newlist->size = entry;
        }

        if (AdapterAddresses != NULL) 
        {
            FREE(AdapterAddresses);
        }
    }
    else
    {
        // pre-IPv6 version (2K-)

        DWORD size = 0;

        DWORD err = ::GetIpAddrTable(0, &size, FALSE);

        BYTE * ipaddrbuffer = new BYTE[size];
        if (! ipaddrbuffer)
        {
	        //log.WriteFormat (_T("[CNetWatcher] GetNewStatus failed - no memory"), PEL_INFO);
            return false;
        }

        PMIB_IPADDRTABLE table = (PMIB_IPADDRTABLE) ipaddrbuffer;
        
        table->dwNumEntries = 0;

        err = ::GetIpAddrTable(table, &size, FALSE);
        if (err != NO_ERROR)
        {
            delete [] ipaddrbuffer;
	        //log.WriteFormat (_T("[CNetWatcher] GetNewStatus failed - GetIpAddrTable returned error"), PEL_INFO);
            return false;
        }

        int entries = 0;

	    DWORD i;
        for (i = 0; i < table->dwNumEntries; ++i)
        {
            if (table->table[i].dwAddr != 0) entries ++;
        }

        newlistsize = sizeof(CKAHFW::Network)*entries + sizeof(int);

        newlist = (NetworkList *) new unsigned char [ newlistsize ];
        memset(newlist, 0, newlistsize);

        newlist->size = entries;

        int entry = 0;
        for (i = 0; i < table->dwNumEntries && entry < entries; ++i)
        {
            if (table->table[i].dwAddr != 0)
            {
                newlist->list[entry].HasIPv4 = TRUE;
                newlist->list[entry].IPv4    = ntohl(table->table[i].dwAddr);
                newlist->list[entry].Maskv4  = ntohl(table->table[i].dwMask);
                newlist->list[entry].HasIPv6 = FALSE;

                int ifacenum = table->table[i].dwIndex;

                newlist->list[entry].PhysLength = 0;
                memset(newlist->list[entry].Phys, 0, CKAHFW::PHYSLEN);

                memset(newlist->list[entry].AdapterName, 0, CKAHFW::ADAPTERNAMELEN);
                memset(newlist->list[entry].AdapterDesc, 0, CKAHFW::ADAPTERDESCLEN);

                strcpy(newlist->list[entry].AdapterDesc, "Unknown");

                MIB_IFROW ifrow;
                memset(&ifrow, 0, sizeof(ifrow));

                ifrow.dwIndex = table->table[i].dwIndex;

                if (GetIfEntry(&ifrow) == NO_ERROR)
                {
                    memcpy(newlist->list[entry].Phys, ifrow.bPhysAddr, min(ifrow.dwPhysAddrLen, CKAHFW::PHYSLEN));

                    strncpy(newlist->list[entry].AdapterDesc, (char*)ifrow.bDescr, CKAHFW::ADAPTERDESCLEN);
                    newlist->list[entry].AdapterDesc[CKAHFW::ADAPTERDESCLEN - 1] = 0;
                }

                entry++;
            }
        }

        delete [] ipaddrbuffer;
    }

    if ( newlistsize && newlist &&
         newlistsize != m_listsize || 
         memcmp(m_list, newlist, newlistsize ) !=0 )
    {
        delete [] (unsigned char *) m_list;

        m_list     = newlist;
        m_listsize = newlistsize;

        //log.WriteFormat (_T("[CNetWatcher] GetNewStatus succeeded, list changed"), PEL_INFO);
        return true;
    }
    else
    {
        delete [] (unsigned char *) newlist;

        //log.WriteFormat (_T("[CNetWatcher] GetNewStatus succeeded, list not changed"), PEL_INFO);
        return false;
    }
}