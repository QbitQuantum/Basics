/******************************************************************************
PacketFilter::StartFirewall - This public method starts firewall.
*******************************************************************************/
BOOL PacketFilter::StartFirewall()
{
    BOOL bStarted = FALSE;

	int tapadapter_index = -1;
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(sizeof(IP_ADAPTER_INFO));
	if (pAdapterInfo == NULL) {
		printf("Error allocating memory needed to call GetAdaptersinfo\n");
		return 1;
	}
	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into the ulOutBufLen variable
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
		FREE(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(ulOutBufLen);
		if (pAdapterInfo == NULL) {
			printf("Error allocating memory needed to call GetAdaptersinfo\n");
			return 2;
		}
	}

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
		pAdapter = pAdapterInfo;
		while (pAdapter) {
			if (strcmp(pAdapter->Description, "TAP-Windows Adapter V9") == 0) {
				tapadapter_index = pAdapter->Index;
				break;
			}
			pAdapter = pAdapter->Next;
		}
	}
	else {
		printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
	}
	if (pAdapterInfo)
		FREE(pAdapterInfo);


	NET_LUID tapluid;
	if (tapadapter_index < 0) {
		printf("Tap Adapter not found!\n");
		return 3;
	}
	if (ConvertInterfaceIndexToLuid(tapadapter_index, &tapluid) != NO_ERROR) {
		printf("Cant find LUID for TAP adapter!\n");
		return 4;
	}

	this->tapluid64 = tapluid.Value;

    try
    {
        // Create packet filter interface.
        if( ERROR_SUCCESS == CreateDeleteInterface( true ) )
        {
            // Bind to packet filter interface.
            if( ERROR_SUCCESS == BindUnbindInterface( true ) )
            {
                // Add filters.
                AddRemoveFilter( true );

                bStarted = TRUE;
            }
        }
    }
    catch(...)
    {
    }
    return bStarted;
}