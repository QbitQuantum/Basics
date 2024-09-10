DWORD WINAPI CLuzj_ZTEDlg::IpconfigRenew()
{

	int i;
	DWORD ret;
	char  adaptername[MAX_ADAPTER_NAME];
	int count = 0;

	DWORD dwOutBufLen = sizeof(IP_INTERFACE_INFO);
	PIP_INTERFACE_INFO pIfTable = (PIP_INTERFACE_INFO)malloc(dwOutBufLen);
	if(pIfTable == NULL) return -1;
	
	ret = GetInterfaceInfo(pIfTable, &dwOutBufLen);
	if(ret == ERROR_INSUFFICIENT_BUFFER) {
		free(pIfTable); pIfTable = (PIP_INTERFACE_INFO)malloc(dwOutBufLen);
		if(pIfTable == NULL) return -2;
		ret = GetInterfaceInfo(pIfTable, &dwOutBufLen);
	}

	if(ret != NO_ERROR) return -3;

	for(i = 0; i < pIfTable->NumAdapters; i++) {
		wcstombs(adaptername, pIfTable->Adapter[i].Name, MAX_ADAPTER_NAME);

		if(stricmp(adaptername, ToTCPName(Config.m_csNetCard)) == 0) {

			EnableDHCP(GetGUID(adaptername), true);
			
			while(1) {
				if(count <= MAX_DHCP_TIMES) Log(I_INFO, "fetching IP address by DHCP...");	
				IpReleaseAddress(&pIfTable->Adapter[i]);
				ret = IpRenewAddress(&pIfTable->Adapter[i]);
				if(ret == NO_ERROR) break;	
				if(count <= MAX_DHCP_TIMES) {
					if(count == MAX_DHCP_TIMES) {
						count++;
						Log(I_INFO, "dhcp keep quiet.");
					} else {
						Log(I_WARN, "fetch IP address failed. (%d)", ret); count++;
					}
				} 
				Sleep(10000);
			}
			
			char *info = GetAdapterInfo((LPCSTR)Config.m_csNetCard);
			if(info == NULL) Log(I_INFO, "GetAdapterInfo: NULL");
			else Log(I_INFO, info);		

			break;
		}	
	}

	free(pIfTable);
	return 0;
}