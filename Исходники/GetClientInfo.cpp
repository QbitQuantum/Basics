int __cdecl main(void)
{
    DHCP_SEARCH_INFO              *pSearchInfo = NULL;         //SearchInfo
    LPDHCPV4_FAILOVER_CLIENT_INFO  pClientInfo = NULL;         // ClientInfo
    DWORD                          dwError    = ERROR_SUCCESS; // Variable that holds the error code
    LPWSTR                         pwszServer = NULL;          //Server IP Address

    pSearchInfo = (DHCP_SEARCH_INFO *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,sizeof(DHCP_SEARCH_INFO));
    if(pSearchInfo == NULL)
    {
        wprintf(L"HeapAlloc failed. Not Enough memory\n");
        goto cleanup;
    }
    pSearchInfo->SearchType = DhcpClientIpAddress;
    pSearchInfo->SearchInfo.ClientIpAddress=0xa000033; // Client with IP Address 10.0.0.51
    dwError = DhcpV4FailoverGetClientInfo(
                    pwszServer,  // Server IP Address
                    pSearchInfo, // Search Info on the basis of which clients will be fetched
                    &pClientInfo // ClientInfo obtained from the server
                    );
    if(ERROR_SUCCESS != dwError)
    {
        wprintf(L"DhcpV4FailoverGetClientInfo failed with Error = %d\n", dwError);
    }
    HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, pSearchInfo);
    pSearchInfo = NULL;
    FreeClientInfoMemory(pClientInfo);
    pClientInfo = NULL;
cleanup:
    return 0;
}