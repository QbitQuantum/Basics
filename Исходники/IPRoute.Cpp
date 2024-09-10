void DoDeleteIpForwardEntry(char* pszDest)
{
    DWORD dwStatus, dwDelStatus, i;
    PMIB_IPFORWARDTABLE pIpRouteTab = NULL; // Ip routing table
    MIB_IPFORWARDROW routeEntry;            // Ip routing table row entry
    DWORD dwForwardDest = 0;
    bool fDeleted = FALSE;
    

    memset(&routeEntry, 0, sizeof(MIB_IPFORWARDROW));
    dwForwardDest = inet_addr(pszDest); // convert dotted ip addr. to ip addr.
    if (dwForwardDest == INADDR_NONE)
    {
        printf("IpRoute: Bad Destination %s\n", pszDest);
        return;
    }


    if ( (dwStatus = MyGetIpForwardTable(pIpRouteTab, TRUE)) == NO_ERROR)
    {
        for (i = 0; i < pIpRouteTab->dwNumEntries; i++)
        {
            if (dwForwardDest == pIpRouteTab->table[i].dwForwardDest)
            {
                memcpy(&routeEntry, &(pIpRouteTab->table[i]), sizeof(MIB_IPFORWARDROW));
                dwDelStatus = DeleteIpForwardEntry(&routeEntry); 
                if (dwDelStatus != NO_ERROR)
                {
                    printf("IpRoute: couldn't delete (%s), dwStatus = %lu.\n",
                            pszDest, dwDelStatus);
                    return;
                }
                else
                    fDeleted = TRUE;
            }
        }
        free(pIpRouteTab);
        if (! fDeleted)
            printf("IpRoute: The route specified was not found.\n");
        return;
    }
    else if ( dwStatus == ERROR_NO_DATA)
    {
        printf("IpRoute: No entries in route table.\n");
        if (pIpRouteTab)
            free (pIpRouteTab);
        return;
    }
    else
    {
        if (pIpRouteTab)
            free (pIpRouteTab);
        printf("IpRoute returned 0x%x\n", dwStatus);
        return;
    }

}