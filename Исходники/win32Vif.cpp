bool Win32Vif::FindIPAddr(ProtoAddress vifAddr)
{
    // Iterate through addresses looking for an address match
    ULONG bufferSize = 0;
    ULONG index = 0;
    if (ERROR_INSUFFICIENT_BUFFER == GetIpAddrTable(NULL, &bufferSize, FALSE))
    {
        char* tableBuffer = new char[bufferSize];
        if (NULL == tableBuffer)
        {   
            PLOG(PL_ERROR, "ProtoSocket::GetInterfaceName() new tableBuffer error: %s\n", ::GetErrorString());
            return false;
        }
        MIB_IPADDRTABLE* addrTable = (MIB_IPADDRTABLE*)tableBuffer;
        if (ERROR_SUCCESS == GetIpAddrTable(addrTable, &bufferSize, FALSE))
        {
            for (DWORD i = 0; i < addrTable->dwNumEntries; i++)
            {
                MIB_IPADDRROW* entry = &(addrTable->table[i]);
                ProtoAddress tempAddress;
                tempAddress.SetRawHostAddress(ProtoAddress::IPv4, (char*)&entry->dwAddr, 4);
                if (tempAddress.HostIsEqual(vifAddr))
                {
                    return true; // ljt fix me
                    MIB_IFROW ifEntry;  
                    index = entry->dwIndex;
                    if (NO_ERROR != GetIfEntry(&ifEntry))
                    {   
                        PLOG(PL_ERROR, "ProtoSocket::GetInterfaceName() GetIfEntry(%d) error: %s\n", i, ::GetErrorString());
                        return false;
                    }
                    delete[] tableBuffer;
                    break;
                }
            }
        }
        else
        {
            PLOG(PL_WARN, "ProtoSocket::GetInterfaceName(%s) warning GetIpAddrTable() error: %s\n", vifAddr.GetHostString(), GetErrorString());
        }
        delete[] tableBuffer;
    }

    if (index)
    {
        // we found one - add another address
        // ljt need to check if this is a vif etc
        // maybe don't do this at all? just fail
        // if we've found one?

        ULONG status = TRUE;
        UINT tmpIPAddr;
        UINT tmpIPMask;
        ULONG NTEContext = 0;
        ULONG NTEInstance = 0;
        tmpIPAddr = inet_addr(vifAddr.GetHostString());
        tmpIPMask = inet_addr("255.255.255.0");
        if ((status = AddIPAddress(tmpIPAddr,
                                   tmpIPMask,
                                   index,
                                   &NTEContext,
                                   &NTEInstance)) != NO_ERROR)
        {
            PLOG(PL_ERROR,"Win32Vif::Open() AddIPAddress call failed with %d\n",status);
            return false;
        }
        return true;
    }
    return false;
} // end Win32Vif::FindIPAddr()