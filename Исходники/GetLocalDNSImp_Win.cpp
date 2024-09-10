/*
Note: Ancient PSDK required in order to build a W98 target.
*/
bool GetDNSNetworkParams(std::vector<std::string> &vecLocalDnsIp)
{
	bool bResult = false;
	FIXED_INFO *pFixdInfo = NULL;
	ULONG ulOutBufLen;
	DWORD dwRetVal;
	IP_ADDR_STRING *pIPAddr = NULL;
	do 
	{
		dwRetVal = GetNetworkParams(pFixdInfo, &ulOutBufLen);
		if(ERROR_BUFFER_OVERFLOW != dwRetVal && ERROR_SUCCESS != dwRetVal)
			break;

		if(ERROR_BUFFER_OVERFLOW == dwRetVal)
		{
			pFixdInfo = (PFIXED_INFO)malloc(ulOutBufLen);
			if(NULL == pFixdInfo)
				break;
		}

		dwRetVal = GetNetworkParams(pFixdInfo, &ulOutBufLen);

		if(ERROR_SUCCESS == dwRetVal)
		{
			for(pIPAddr = &pFixdInfo->DnsServerList; pIPAddr; pIPAddr = pIPAddr->Next)
			{
				vecLocalDnsIp.push_back(pIPAddr->IpAddress.String);
			}
		}

		if(!vecLocalDnsIp.empty())
			bResult = true;
	} while (false);

	if(NULL != pFixdInfo)
	{
		free(pFixdInfo);
		pFixdInfo = NULL;
	}

	return bResult;
}