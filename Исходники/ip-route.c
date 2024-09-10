int ip_route_get(const char* destination, char ip[40])
{
	DWORD index = ~(-1);
	struct sockaddr_in addrin;
	MIB_IPADDRTABLE *table = NULL;
	ULONG dwSize = 0;
	DWORD errcode = 0;
	DWORD i = 0;

	addrin.sin_family = AF_INET;
	addrin.sin_port = htons(0);
	inet_pton(AF_INET, destination, &addrin.sin_addr);
	if(NO_ERROR != GetBestInterfaceEx((struct sockaddr*)&addrin, &index))
		return -1;

	errcode = GetIpAddrTable( table, &dwSize, 0 );
	assert(ERROR_INSUFFICIENT_BUFFER == errcode);

	table = (MIB_IPADDRTABLE*)malloc(dwSize);
	errcode = GetIpAddrTable( table, &dwSize, 0 );
	if(!table || NO_ERROR != errcode)
	{
		free(table);
		return -1;
	}

	ip[0] = '\0';
	for(i = 0; i < table->dwNumEntries; i++)
	{
		if(table->table[i].dwIndex == index)
		{
			sprintf(ip, "%d.%d.%d.%d", 
				(table->table[i].dwAddr >> 0) & 0xFF,
				(table->table[i].dwAddr >> 8) & 0xFF,
				(table->table[i].dwAddr >> 16) & 0xFF,
				(table->table[i].dwAddr >> 24) & 0xFF);
			break;
		}
	}