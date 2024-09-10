//////////////////////////////////////////////////////
	//Anti Cheat
	char* getMAC(){// By Yuri-BR
    PIP_ADAPTER_INFO AdapterInfo;
    DWORD dwBufLen = sizeof(AdapterInfo);
    char *mac_addr = (char*)malloc(17);

    AdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
    if (AdapterInfo == NULL) 
    {
        printf("Error allocating memory needed to call GetAdaptersinfo\n");
    }

    // Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen     variable
    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) 
    {

        AdapterInfo = (IP_ADAPTER_INFO *) malloc(dwBufLen);
        if (AdapterInfo == NULL) 
        {
             printf("Error allocating memory needed to call GetAdaptersinfo\n");
        }
     }

    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) 
    {
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;// Contains pointer to current adapter info
        do 
        {
            sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X", // By Yuri-BR
            pAdapterInfo->Address[0], pAdapterInfo->Address[1],
            pAdapterInfo->Address[2], pAdapterInfo->Address[3],
            pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

            return mac_addr;

            printf("\n");
            pAdapterInfo = pAdapterInfo->Next;        
        }
        while(pAdapterInfo);                        
        }
        free(AdapterInfo);
}