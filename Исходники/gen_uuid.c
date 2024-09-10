static int get_node_id(unsigned char *byMAC)
{
    DWORD               i, dwSize;
    PMIB_IPADDRTABLE    pAddr = NULL;
    MIB_IFROW           iInfo;
    PFIXED_INFO         pFI = NULL;

    /* Get all IP addresses held by this machine; if it's connected to a network, there's at least one
       that's not localhost */
    dwSize = 0;
    GetIpAddrTable(NULL, &dwSize, TRUE);
    pAddr = (PMIB_IPADDRTABLE)malloc(sizeof(BYTE) * dwSize);
    if (!GetIpAddrTable(pAddr, &dwSize, TRUE))
    {
        for (i = 0; i < pAddr->dwNumEntries; ++i)
        {
            if (IP_LOCALHOST != pAddr->table[i].dwAddr)
            {
                /* Not localhost, so get the interface */
                memset(&iInfo, 0, sizeof(MIB_IFROW));
                iInfo.dwIndex = pAddr->table[i].dwIndex;
                GetIfEntry(&iInfo);

                if (MIB_IF_TYPE_ETHERNET == iInfo.dwType)
                {
                    /*iInfo.bPhysAddr contains the MAC address of this interface*/
                    memcpy(byMAC, iInfo.bPhysAddr, iInfo.dwPhysAddrLen);
                    free(pAddr);
                    return 1;
                }
            }
        }
    }
    free(pAddr);
    return 0;
}