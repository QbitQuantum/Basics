void GetNetConfig::PrintDNSAddress(void)
{
	if ((m_nOptions & pt_dns) != pt_dns) {
		return;
	}

	if (m_pAdapter->Index <= 0) {
		return;
	}
	ULONG outBufLen = 0;
    GetPerAdapterInfo(m_pAdapter->Index, NULL, &outBufLen);
	if (outBufLen <= 0) {
		return;
	}
	IP_PER_ADAPTER_INFO* pPerAdapterInfo = (IP_PER_ADAPTER_INFO*) malloc(outBufLen);
    DWORD dwResult = GetPerAdapterInfo(m_pAdapter->Index, pPerAdapterInfo, &outBufLen);
	if (dwResult != ERROR_SUCCESS) {
		free(pPerAdapterInfo);
		return;
	}

    if (m_bTitle == TRUE) {
	    printf("\tDNS Address: \t");
	}

	IP_ADDR_STRING* pDns = &pPerAdapterInfo->DnsServerList;

    // loop through all DNS IPs
	int i = 0;
    while (pDns) {
		if (i > 0) {
			printf(", ");
		}
		printf("%s",
				pDns->IpAddress.String);

        pDns = pDns->Next;
		i++;
	}
	printf("\n");

	free(pPerAdapterInfo);
}