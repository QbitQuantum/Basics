char *macAddress(void)
{
	IP_ADAPTER_INFO *adapterInfo;
	ULONG adapterInfoSize = 0;

	if (GetAdaptersInfo(NULL, &adapterInfoSize) != ERROR_SUCCESS)
	{
		adapterInfo = (IP_ADAPTER_INFO *) malloc(adapterInfoSize);
	}

	if (GetAdaptersInfo(adapterInfo, &adapterInfoSize) != ERROR_SUCCESS)
	{
		return NULL;
	}

	{
		char *mac = String_asHex(adapterInfo->Address, adapterInfo->AddressLength);
		free(adapterInfo);
		return mac;
	}
}