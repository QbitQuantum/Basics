/**
 * Retrieve the MAC address of the system
 */
unsigned pixie_get_mac_address(unsigned char macaddr[6])
{
	memset(macaddr, 0, 6);
#ifdef WIN32
	{
		DWORD dwStatus;
		IP_ADAPTER_INFO *p;
		IP_ADAPTER_INFO AdapterInfo[16];
		DWORD dwBufLen = sizeof(AdapterInfo);
		DWORD interface_index = -1;

		GetBestInterface(0x01010101, &interface_index);
		
		dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
		if (dwStatus != ERROR_SUCCESS)
			  return 1;

		for (p=AdapterInfo; p; p = p->Next) {

			if (p->Index == interface_index || interface_index == -1) {
				memcpy(macaddr, p->Address, 6);
				return 0;
			}
			/*(
			printf("[%02x:%02x:%02x:%02x:%02x:%02x]\n",
			mac_address[0], mac_address[1], mac_address[2], 
			mac_address[3], mac_address[4], mac_address[5]
			);
			printf("    %s\n", p->AdapterName);
			printf("    %s\n", p->Description);
			printf("    IP: ");
			for (a = &p->IpAddressList; a; a = a->Next) {
				printf("%s ", a->IpAddress.String);
			}
			printf("\n");
			*/
		}
	}
#else
	return -1;
#endif
	return -1;
}