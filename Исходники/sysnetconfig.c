int system_getdns(const char* name, char primary[40], char secondary[40])
{
	ULONG idx = 0;
	DWORD dwRetVal = 0;
	ULONG outBufLen = 0;
	WCHAR wAdapterName[256] = {0};
	PIP_PER_ADAPTER_INFO pPerAdapterInfo;
	
	MultiByteToWideChar(CP_ACP, 0, name, -1, wAdapterName, 256);
	if(NO_ERROR!=GetAdapterIndex(wAdapterName, &idx))
		return -1;

	outBufLen = sizeof(IP_PER_ADAPTER_INFO);
	pPerAdapterInfo = (PIP_PER_ADAPTER_INFO)malloc(outBufLen);
	if(ERROR_BUFFER_OVERFLOW==GetPerAdapterInfo(idx, pPerAdapterInfo, &outBufLen))
	{
		free(pPerAdapterInfo);
		pPerAdapterInfo = (PIP_PER_ADAPTER_INFO)malloc(outBufLen);
	}

	if ((dwRetVal = GetPerAdapterInfo(idx, pPerAdapterInfo, &outBufLen)) == ERROR_SUCCESS)
	{
		secondary[0] = '\0';
		strncpy(primary, pPerAdapterInfo->DnsServerList.IpAddress.String, 39);
		if(pPerAdapterInfo->DnsServerList.Next)
			strncpy(secondary, pPerAdapterInfo->DnsServerList.Next->IpAddress.String, 39);
	}

	free(pPerAdapterInfo);
	return dwRetVal==ERROR_SUCCESS?0:-(int)dwRetVal;
}