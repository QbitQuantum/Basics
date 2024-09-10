unsigned long OsSocket::initDefaultAdapterID(UtlString &interface_id)
{
    mInitializeSem.acquire();
    UtlString address = "";
    unsigned long retip = htonl(INADDR_ANY);

#ifdef WIN32
    // Under windows it is possible for many network devices to be present.
    // in this case we will either return an empty string
    // or if the configuration parameter  PHONESET_BIND_MAC_ADDRESS is defined
    // we will look up the mac address against the windows adapters
    // and then return the correct ip address for that adapter
    int numAdapters = getAdaptersInfo();  //fills in the structure with the adapter info
    if (numAdapters < 2)
    {
        retip = htonl(INADDR_ANY);
    }
    else
    {
        char ipaddress[20];
        char adapter_id[30];

        *ipaddress = '\0';
        *adapter_id = '\0';

        strcpy(adapter_id, interface_id.data());

        //if this fails, then we need to choose any address
        if (strlen(adapter_id) == 0 ||
                lookupIpAddressByMacAddress(adapter_id, ipaddress) == -1)
        {
            retip = htonl(INADDR_ANY);
        }
        else
        {
            address = ipaddress;
        }
    }

    //now convert if it has a string ip address
    if (address != "")
    {
        struct in_addr  ipAddr;
        ipAddr.s_addr = inet_addr (address.data());
        retip = ipAddr.s_addr;
    }

#endif

    mInitializeSem.release();
    return retip;
}