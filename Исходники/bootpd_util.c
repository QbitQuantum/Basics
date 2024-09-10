/*
 *
 * Takes an internet address and an optional interface address as
 * arguments and checks their validity.
 * Add the interface number and IP to an MIB_IPNETROW structure
 * and remove the entry from the ARP cache.
 * Code adapted from ReactOS 
 */
int ArpDeleteHost(struct in_addr addr)
{
PMIB_IPNETTABLE pIpNetTable = NULL;
ULONG Size = 0;
DWORD dwIpAddr = 0;
INT iRet;
MIB_IPNETROW DelHost;
DWORD Ark;

    /* check IP address */
    dwIpAddr = addr.s_addr;

    /* We need the IpNetTable to get the adapter index */
    /* Return required buffer size */
    GetIpNetTable(NULL, &Size, 0);

    /* allocate memory for ARP address table */
    pIpNetTable = (PMIB_IPNETTABLE) calloc (Size, 1);
    if (		pIpNetTable == NULL 
		||   (iRet = GetIpNetTable(pIpNetTable, &Size, TRUE)) != NO_ERROR )
        goto cleanup;

     /* we need to read the ARP table in order to get the right interface table */
	for ( Ark=0 ; 
		  Ark<pIpNetTable->dwNumEntries && pIpNetTable->table[Ark].dwAddr != dwIpAddr ; 
		  Ark++) ;
	if ( Ark<pIpNetTable->dwNumEntries )
	{
        DelHost.dwAddr = dwIpAddr;
        DelHost.dwIndex = pIpNetTable->table[Ark].dwIndex;
		iRet = DeleteIpNetEntry (& DelHost);
		if (iRet != NO_ERROR) LOG (5, "IP address %s flushed from ARP table", inet_ntoa (addr));
    }

cleanup:
    if (pIpNetTable != NULL) free (pIpNetTable);
    return 0;
} // ArpDeleteHost 