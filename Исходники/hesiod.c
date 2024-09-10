WINAPI
hes_resolve(LPSTR HesiodName, LPSTR HesiodNameType)
{
    register char  *cp;
    LPSTR* retvec;
    DNS_STATUS status; 
    
    PDNS_RECORD pDnsRecord; 
    PDNS_RECORD pR;
    DNS_FREE_TYPE freetype ;
    int i = 0;
    freetype =  DnsFreeRecordListDeep;
    

    cp = hes_to_bind(HesiodName, HesiodNameType);
    if (cp == NULL) return(NULL);
    errno = 0;

    
    status = DnsQuery_A(cp,                 //pointer to OwnerName 
                        DNS_TYPE_TEXT,         //Type of the record to be queried
                        DNS_QUERY_STANDARD,     // Bypasses the resolver cache on the lookup. 
                        NULL,                   //contains DNS server IP address
                        &pDnsRecord,                //Resource record comprising the response
                        NULL);                     //reserved for future use
    
    if (status) {
        errno = status;
        Hes_Errno = HES_ER_NOTFOUND;
        return  NULL;
    }
     
    pR = pDnsRecord;
    while (pR)
    {   
        if (pR->wType == DNS_TYPE_TEXT)
            i++;
        pR = pR->pNext;
    }
    i++;
    retvec = LocalAlloc(LPTR, i*sizeof(LPSTR));
    pR = pDnsRecord;
    i = 0;
    while (pR)
    {   
        if (pR->wType == DNS_TYPE_TEXT){
            SIZE_T l = strlen(((pR->Data).Txt.pStringArray)[0]);
            retvec[i] = LocalAlloc(LPTR, l+1);
            strcpy(retvec[i], ((pR->Data).Txt.pStringArray)[0]);
            i++;
        }
        pR = pR->pNext;
    }
    retvec[i] = NULL;
    DnsRecordListFree(pDnsRecord, freetype);
    return retvec;
         
}