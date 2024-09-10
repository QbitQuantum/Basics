// 取得所有网卡的信息 David 2010.6.2 add
PIP_ADAPTER_INFO GetAllAdaptersInfo()
{
	PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
	ASSERT(NULL != pAdapterInfo);
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	// 空间不够则重新分配空间
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen); 
	}

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR){
			
		return pAdapterInfo;
	}
	else
	{
		free(pAdapterInfo);
		return NULL;
	}
}