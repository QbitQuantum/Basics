int getAdaptersInfo()
{
        char MacAddressStr[256]; //mac address converted to a string
        char MacOneByteStr[10]; //used to hold one byte of mac address
        int retval = 0; //return -1 if no adapters found

        if (isIPHLPAvail())  //inits iphlpapi and returns true if dll loaded
        {
                //just return count if we already did this before
                if (AdapterCount)
                        return AdapterCount;

                IP_ADAPTER_INFO  *pAdapterInfo; //points to buffer hold linked list adapter info

                DWORD dwSize = (sizeof(IP_ADAPTER_INFO) * MAX_ADAPTERS) + sizeof(DWORD); //size for lots of adapters
                char *buffer = new char[dwSize];  //allocate space for lots of adapters
                if (buffer)
                {
                        pAdapterInfo = (IP_ADAPTER_INFO *)buffer;  //point to buffer
                        if (GetAdaptersInfo(
                                pAdapterInfo,  // buffer for mapping table
                                &dwSize) == NO_ERROR)                     // sort the table
                        {
                                while (pAdapterInfo)
                                {
                                        strcpy(adapters[AdapterCount].AdapterName, pAdapterInfo->Description);
                                        strcpy(adapters[AdapterCount].IpAddress, (const char *)pAdapterInfo->IpAddressList.IpAddress.String);

                                        //build mac address as a string
                                        *MacAddressStr = '\0';
                                        for (unsigned int loop = 0; loop < pAdapterInfo->AddressLength; loop++)
                                        {
                                                if (strlen(MacAddressStr))
                                                        strcat(MacAddressStr,"-");
                                                sprintf(MacOneByteStr,"%02X",pAdapterInfo->Address[loop]);
                                                strcat(MacAddressStr,MacOneByteStr);
                                        }
                                        strcpy((char *)adapters[AdapterCount].MacAddress, MacAddressStr);

                                        AdapterCount++;
                                        pAdapterInfo = pAdapterInfo->Next;
                                }

                                retval = AdapterCount;
                        }

                        delete [] buffer;
                }
        }

        return retval;
}