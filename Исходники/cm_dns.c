int getAFSServerW(cm_unichar_t *cellName, int *cellHostAddrs,
                  cm_unichar_t cellHostNames[][MAXHOSTCHARS], 
                  int *numServers, int *ttl)
{
#ifdef DNSAPI_ENV
    PDNS_RECORDW pDnsCell, pDnsIter, pDnsVol,pDnsVolIter, pDnsCIter;
    int i;
    struct sockaddr_in vlSockAddr;
    cm_unichar_t query[1024];

#ifdef AFS_FREELANCE_CLIENT
    if ( cm_stricmp_utf16(cellName, L"Freelance.Local.Root") == 0 )
        return -1;
#endif /* AFS_FREELANCE_CLIENT */

    *numServers = 0; 
    *ttl = 0;

    /* query the AFSDB records of cell */
    StringCbCopyW(query, sizeof(query), cellName);
    if (query[wcslen(query)-1] != L'.') {
        StringCbCatW(query, sizeof(query), L".");
    }

    if (DnsQuery_W(query, DNS_TYPE_AFSDB, DNS_QUERY_STANDARD, NULL, (PDNS_RECORD *) &pDnsCell,
                   NULL) == ERROR_SUCCESS) {
        memset((void*) &vlSockAddr, 0, sizeof(vlSockAddr));

        /* go through the returned records */
        for (pDnsIter = pDnsCell;pDnsIter; pDnsIter = pDnsIter->pNext) {
            /* if we find an AFSDB record with Preference set to 1, we found a volserver */
            if (pDnsIter->wType == DNS_TYPE_AFSDB && pDnsIter->Data.Afsdb.wPreference == 1) {
                StringCbCopyW(cellHostNames[*numServers], sizeof(cellHostNames[*numServers]),
                              pDnsIter->Data.Afsdb.pNameExchange);
                (*numServers)++;
                
                if (!*ttl) 
                    *ttl = pDnsIter->dwTtl;
                if (*numServers == AFSMAXCELLHOSTS) 
                    break;
            }
        }

        for (i=0;i<*numServers;i++) 
            cellHostAddrs[i] = 0;

        /* now check if there are any A records in the results */
        for (pDnsIter = pDnsCell; pDnsIter; pDnsIter = pDnsIter->pNext) {
            if(pDnsIter->wType == DNS_TYPE_A)
                /* check if its for one of the volservers */
                for (i=0;i<*numServers;i++)
                    if(cm_stricmp_utf16(pDnsIter->pName, cellHostNames[i]) == 0)
                        cellHostAddrs[i] = pDnsIter->Data.A.IpAddress;
        }

        for (i=0;i<*numServers;i++) {
            /* if we don't have an IP yet, then we should try resolving the volserver hostname
               in a separate query. */
            if (!cellHostAddrs[i]) {
                if (DnsQuery_W(cellHostNames[i], DNS_TYPE_A, DNS_QUERY_STANDARD, NULL,
                               (PDNS_RECORD *) &pDnsVol, NULL) == ERROR_SUCCESS) {
                    for (pDnsVolIter = pDnsVol; pDnsVolIter; pDnsVolIter=pDnsVolIter->pNext) {
                        /* if we get an A record, keep it */
                        if (pDnsVolIter->wType == DNS_TYPE_A && cm_stricmp_utf16(cellHostNames[i], pDnsVolIter->pName)==0) {
                            cellHostAddrs[i] = pDnsVolIter->Data.A.IpAddress;
                            break;
                        }
                        /* if we get a CNAME, look for a corresponding A record */
                        if (pDnsVolIter->wType == DNS_TYPE_CNAME && cm_stricmp_utf16(cellHostNames[i], pDnsVolIter->pName)==0) {
                            for (pDnsCIter=pDnsVolIter; pDnsCIter; pDnsCIter=pDnsCIter->pNext) {
                                if (pDnsCIter->wType == DNS_TYPE_A && cm_stricmp_utf16(pDnsVolIter->Data.CNAME.pNameHost, pDnsCIter->pName)==0) {
                                    cellHostAddrs[i] = pDnsCIter->Data.A.IpAddress;
                                    break;
                                }
                            }
                            if (cellHostAddrs[i]) 
                                break;
                            /* TODO: if the additional section is missing, then do another lookup for the CNAME */
                        }
                    }
                    /* we are done with the volserver lookup */
                    DnsRecordListFree((PDNS_RECORD) pDnsVol, DnsFreeRecordListDeep);
                }
            }
        }
        DnsRecordListFree((PDNS_RECORD) pDnsCell, DnsFreeRecordListDeep);
    }

    if ( *numServers > 0 )
        return 0;
    else        
#endif  /* DNSAPI_ENV */
        return -1;
}