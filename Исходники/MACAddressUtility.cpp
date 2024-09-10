inline long MACAddressUtility::GetMACAddressMSW(unsigned char * result)
{

#if defined(UNDER_CE)
	IP_ADAPTER_INFO AdapterInfo[16]; // Allocate information
	DWORD dwBufLen = sizeof(AdapterInfo); // Save memory size of buffer
	if(GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_SUCCESS)
	{
		memcpy(result, AdapterInfo->Address, 6);
	}
	else return -1;
#else
	UUID uuid;
	if(UuidCreateSequential(&uuid) == RPC_S_UUID_NO_ADDRESS) return -1;
	memcpy(result, (char*)(uuid.Data4+2), 6);
#endif
	return 0;
}