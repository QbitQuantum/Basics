/* returns the subnet mask in network byte order */
static uint32_t getIpMaskForIpAddress(
    uint32_t ipAddress)
{
    /* Allocate information for up to 16 NICs */
    IP_ADAPTER_INFO AdapterInfo[16];
    /* Save memory size of buffer */
    DWORD dwBufLen = sizeof(AdapterInfo);
    uint32_t ipMask = INADDR_BROADCAST;
    bool found = false;

    PIP_ADAPTER_INFO pAdapterInfo;

    /* GetAdapterInfo:
       [out] buffer to receive data
       [in] size of receive data buffer */
    DWORD dwStatus = GetAdaptersInfo(AdapterInfo,
        &dwBufLen);
    if (dwStatus == ERROR_SUCCESS) {
        /* Verify return value is valid, no buffer overflow
           Contains pointer to current adapter info */
        pAdapterInfo = AdapterInfo;

        do {
            IP_ADDR_STRING *pIpAddressInfo = &pAdapterInfo->IpAddressList;
            do {
                unsigned long adapterAddress =
                    inet_addr(pIpAddressInfo->IpAddress.String);
                unsigned long adapterMask =
                    inet_addr(pIpAddressInfo->IpMask.String);
                if (adapterAddress == ipAddress) {
                    ipMask = adapterMask;
                    found = true;
                }
                pIpAddressInfo = pIpAddressInfo->Next;
            } while (pIpAddressInfo && !found);
            /* Progress through linked list */
            pAdapterInfo = pAdapterInfo->Next;
            /* Terminate on last adapter */
        } while (pAdapterInfo && !found);
    }

    return ipMask;
}