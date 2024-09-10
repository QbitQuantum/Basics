WINAPI
rgethostbyaddr(const char *addr, int len, int type)
{
    DNS_STATUS status;
    struct hostent* host;
#ifdef DEBUG
    char debstr[80];
#endif

    PDNS_RECORD pDnsRecord;
    DNS_FREE_TYPE freetype ;
    char qbuf[BUFSIZ];

    if (type != AF_INET)
        return ((struct hostent *) NULL);

    wsprintf(qbuf, "%u.%u.%u.%u.in-addr.arpa",
         ((unsigned)addr[3] & 0xff),
         ((unsigned)addr[2] & 0xff),
         ((unsigned)addr[1] & 0xff),
         ((unsigned)addr[0] & 0xff));


    freetype =  DnsFreeRecordListDeep;


    status = DnsQuery_A(qbuf,                 //pointer to OwnerName
                        DNS_TYPE_PTR,         //Type of the record to be queried
                        DNS_QUERY_STANDARD,
                        NULL,                   //contains DNS server IP address
                        &pDnsRecord,                //Resource record comprising the response
                        NULL);                     //reserved for future use

    if (status) {
#ifdef DEBUG
        if (_res.options & RES_DEBUG)
        {
            wsprintf(debstr, "res_query failed\n");
            OutputDebugString(debstr);
        }
#endif

        return  NULL;
    }

    host = (struct hostent*)(TlsGetValue(dwGhaIndex));
    if (host == NULL) {
	LPVOID lpvData = (LPVOID) LocalAlloc(LPTR, sizeof(struct hostent));
	if (lpvData != NULL) {
	    TlsSetValue(dwGhaIndex, lpvData);
	    host = (struct hostent*)lpvData;
	} else
	    return NULL;
    }

    if (host->h_name == NULL)
	host->h_name = LocalAlloc(LPTR, DNS_MAX_LABEL_BUFFER_LENGTH);
    if (host->h_aliases == NULL)
	host->h_aliases = LocalAlloc(LPTR, 1*sizeof(LPSTR));
    if (host->h_addr_list == NULL)
    {
	host->h_addr_list = LocalAlloc(LPTR, 2*sizeof(LPSTR));
	host->h_addr_list[0] = LocalAlloc(LPTR, DNS_MAX_LABEL_BUFFER_LENGTH);
    }

    strcpy(host->h_name, pDnsRecord->Data.Ptr.pNameHost);
    host->h_addrtype = type;
    host->h_length = len;
    host->h_aliases[0] = NULL;
    memcpy(host->h_addr_list[0], addr, sizeof(unsigned long));
    host->h_addr_list[1] = NULL;
    DnsRecordListFree(pDnsRecord, freetype);

    return host;

}