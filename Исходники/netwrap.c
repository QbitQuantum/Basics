str_list_t DLLCALL getNameServerList(void)
{
#ifdef __unix__	/* Look up DNS server address */
	FILE*	fp;
	char*	p;
	char	str[128];
	str_list_t	list;

	if((list=strListInit())==NULL)
		return(NULL);
	if((fp=fopen("/etc/resolv.conf","r"))!=NULL) {
		while(!feof(fp)) {
			if(fgets(str,sizeof(str),fp)==NULL)
				break;
			truncsp(str);
			p=str;
			SKIP_WHITESPACE(p);
			if(strnicmp(p,"nameserver",10)!=0) /* no match */
				continue;
			FIND_WHITESPACE(p);	/* skip "nameserver" */
			SKIP_WHITESPACE(p);	/* skip more white-space */
			strListPush(&list,p);
		}
		fclose(fp);
	}
	return(list);

#elif defined(_WIN32)
	FIXED_INFO* FixedInfo=NULL;
	ULONG    	FixedInfoLen=0;
	IP_ADDR_STRING* ip;
	str_list_t	list;

	if((list=strListInit())==NULL)
		return(NULL);
	if(GetNetworkParams(FixedInfo,&FixedInfoLen) == ERROR_BUFFER_OVERFLOW) {
        FixedInfo=(FIXED_INFO*)malloc(FixedInfoLen);
		if(GetNetworkParams(FixedInfo,&FixedInfoLen) == ERROR_SUCCESS) {
			ip=&FixedInfo->DnsServerList;
			for(; ip!=NULL; ip=ip->Next)
				strListPush(&list,ip->IpAddress.String);
		}
        if(FixedInfo!=NULL)
            free(FixedInfo);
    }
	return(list);
#else
	#error "Need a get_nameserver() implementation for this platform"
#endif
}