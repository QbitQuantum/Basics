ADAPTER_LIST CSocketApp::GetMacInfo(void)
{
	USES_CONVERSION;
	ADAPTER_LIST AdapterList;
	
	PIP_ADAPTER_INFO pIpAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;

    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
    pIpAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof (IP_ADAPTER_INFO));
    if (pIpAdapterInfo == NULL) {
		AllocConsole();
        _cprintf("Error allocating memory needed to call GetAdaptersinfo\n");
        FreeConsole();
		return AdapterList;
    }
    if (GetAdaptersInfo(pIpAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pIpAdapterInfo);
        pIpAdapterInfo = (IP_ADAPTER_INFO *) malloc(ulOutBufLen);
        if (pIpAdapterInfo == NULL) {
			AllocConsole();
            _cprintf("Error allocating memory needed to call GetAdaptersinfo\n");
			FreeConsole();
            return AdapterList;
        }
    }

    if ((dwRetVal = GetAdaptersInfo(pIpAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pIpAdapterInfo;
        while (pAdapter) {
			ADAPTER_INFO AdapterInfo;

			AdapterInfo.sName = A2W(pAdapter->AdapterName);
			AdapterInfo.sDesc = A2W(pAdapter->Description);
			AdapterInfo.uType = pAdapter->Type;

			CString sMacAddr;
			CString sTemp;
			for (DWORD i = 0; i < pAdapter->AddressLength; i++)
			{
				sTemp.Format(_T("%02x"), pAdapter->Address[i]);
				sMacAddr += sTemp;
			}
			AdapterInfo.sMac = sMacAddr;

			IP_ADDR_STRING *pIpAddrString =&(pAdapter->IpAddressList);
			do 
			{
				AdapterInfo.sIPs.push_back(A2W(pIpAddrString->IpAddress.String));
				pIpAddrString = pIpAddrString->Next;
			} while (pIpAddrString);
			pAdapter = pAdapter->Next;

			AdapterList.push_back(AdapterInfo);
        }
    } else {
		AllocConsole();
        _cprintf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
		FreeConsole();
    }
    if (pIpAdapterInfo)
        free(pIpAdapterInfo);
	return AdapterList;
}