DNS_STATUS 
do_res_search(const char *queryname, int qclass, int type, u_char *retanswer, int retanswerlen, int* anslen)
{
    PDNS_RECORD pDnsRecord; 
    PDNS_RECORD ptr;
    DNS_STATUS status; 
    DNS_FREE_TYPE freetype ;
    HEADER *hp;
    char *cp;
    int  n;
    int i;
    u_char  answer[MAX_MSG_SIZE];
    DWORD options = DNS_QUERY_STANDARD;
    freetype =  DnsFreeRecordListDeep;

    memset(answer, 0, MAX_MSG_SIZE);
    if (!(_res.options & RES_RECURSE))
	options = options | DNS_QUERY_NO_RECURSION;
    if (_res.options & RES_USEVC)
	options = options | DNS_QUERY_USE_TCP_ONLY;
    if (_res.options & RES_IGNTC)
	options = options | DNS_QUERY_ACCEPT_TRUNCATED_RESPONSE;

    status = DnsQuery_A(queryname,                 //pointer to OwnerName 
                        type,         //Type of the record to be queried
                        options,
                        NULL,                   //contains DNS server IP address
                        &pDnsRecord,                //Resource record comprising the response
                        NULL);                     //reserved for future use
    
    if (status) 
        return  status;
   

    hp = (HEADER *) answer;
    cp = answer + sizeof(HEADER);

    // populating the header
    hp->id = htons(++_res.id); // query id
    hp->qr = 1;  // 0 for query 1 for response
    hp->opcode = 0; // standard query
    hp->aa = 1; // authoritative answer
    hp->tc = 0; // no truncation
    hp->rd = (_res.options & RES_RECURSE) != 0; // resursion desired
    hp->ra = 1;  // recursion available
    hp->pr = (_res.options & RES_PRIMARY) != 0; // primary server required
    hp->rcode = NOERROR;
    hp->qdcount = htons(1); // number of question entries
    i = put_qname(cp, (char*)queryname);
    cp = cp + i;
    __putshort(type, (u_char *)cp);
    cp += sizeof(u_short);
    __putshort(qclass, (u_char *)cp);
    cp += sizeof(u_short);

    // get the answer
    for (n = 0, ptr = pDnsRecord; ptr; ptr = ptr->pNext)
    {
	if ((ptr->Flags).S.Section == DNSREC_ANSWER ||
	     (type == DNS_TYPE_PTR && (ptr->Flags).S.Section==DNSREC_QUESTION))
	{
	    i = build_rr(cp, ptr, qclass);
	    cp = cp + i;
	    //strcpy(cp, pDnsRecord->pName);
	    //cp += strlen(pDnsRecord->pName);
	    //cp++;

	    n++;
	}
    }
    hp->ancount = htons(n);

    // get the authority
    for (n = 0, ptr = pDnsRecord; ptr; ptr = ptr->pNext)
    {
	if ((ptr->Flags).S.Section == DNSREC_AUTHORITY )
	{
	    i = build_rr(cp, ptr, qclass);
	    cp = cp + i;

	    n++;
	}
    }
    hp->nscount = htons(n);

    // get the additional resource
    for (n = 0, ptr = pDnsRecord; ptr; ptr = ptr->pNext)
    {
	if ((ptr->Flags).S.Section == DNSREC_ADDITIONAL)
	{
	    i = build_rr(cp, ptr, qclass);
	    cp = cp + i;

	    n++;
	}

    }
    hp->arcount = htons(n);

    *anslen = (int)(cp - answer);
    if (*anslen > retanswerlen)
	memcpy(retanswer, answer, retanswerlen); // partial copy
    else
	memcpy(retanswer, answer, *anslen);
    DnsRecordListFree(pDnsRecord, freetype);
    return status;
}	