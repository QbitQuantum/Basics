//
// Function: main
//
// Description:
//    Initialize Winsock and set up the WSAQUERYSET structure
//    for querying DNS. We use the special GUID 
//    SVCID_INET_HOSTADDRBYNAME for name resolution and we
//    query on the UDP and TCP protocols. The information
//    is returned as a BLOB so we must specify the LUP_RETURN_BLOB
//    flag. Once the call to WSALookupServiceBegin/Next is 
//    successful then decode the BLOB data into a real HOSTENT
//    and print the results.
//
int main(int argc, char **argv)
{
    WSADATA        wsd;
    WSAQUERYSET   *qs=NULL;
    char           buff[RNR_BUFFER_SIZE];
    GUID           HostnameGuid = SVCID_INET_HOSTADDRBYNAME;
    HANDLE         hRnr;
    AFPROTOCOLS    afproto[2] = { {AF_INET, IPPROTO_UDP}, 
                                  {AF_INET, IPPROTO_TCP} };
    DWORD          dwLength=RNR_BUFFER_SIZE;
    int            ret, i;
    LPBLOB         pvRet=NULL;
    HOSTENT       *hp=NULL;
    SOCKADDR_IN    addr;

    // Check for proper usage
    //
    if (argc != 2)
    {
        printf("usage: %s hostname\n", argv[0]);
        return -1;
    }
    // Load Winsock
    //
    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
    {
        printf("WSAStartup() failed: %d\n", GetLastError());
        return -1;
    }
    // Initalize the WSAQUERYSET structure for the query
    //
    qs = (WSAQUERYSET *)buff;

    memset(qs, 0, sizeof(*qs));
    qs->dwSize = sizeof(WSAQUERYSET);
    qs->lpszServiceInstanceName = argv[1]; // name to resolve
    qs->lpServiceClassId = &HostnameGuid;
    qs->dwNameSpace = NS_ALL;              // or ND_DNS
    qs->dwNumberOfProtocols = 2;           // TCP and UDP
    qs->lpafpProtocols = afproto;
    
    ret = WSALookupServiceBegin(qs, LUP_RETURN_BLOB | LUP_RETURN_NAME,
                &hRnr);
    if (ret == NO_ERROR)
    {
        // We only have to call WSALookupServiceNext once because
        // the BLOB HOSTENT return will contain multiple addresses
        // if there are mutliple IP addresses associated with the
        // given name
        //
        ret = WSALookupServiceNext(hRnr, 0, &dwLength, qs);
        if (ret != NO_ERROR)
        {
            if (WSAGetLastError() == WSASERVICE_NOT_FOUND)
            {
                printf("No such name found!\n");
                WSALookupServiceEnd(hRnr);
                return 0;
            }
            printf("WSALookupServiceNext() failed: %d\n",
                WSAGetLastError());
        }
        WSALookupServiceEnd(hRnr);
    }
    // Make sure we got something returned
    //
    if (qs->lpBlob == NULL)
        return -1;
    //
    // Create our own buffer to hold the blob data
    //
    hp = (HOSTENT *)LocalAlloc(LPTR, qs->lpBlob->cbSize);
    if (!hp)
    {
        printf("LocalAlloc() failed: %d\n", GetLastError());
        return -1;
    }
    memcpy(hp, qs->lpBlob->pBlobData, qs->lpBlob->cbSize);
    //
    // Unpack the BLOB data so its meaningful
    //
    UnpackHostEnt(hp);
    //
    // Print out the addresses
    //
    for(i=0; hp->h_addr_list[i] ;i++)
    {
        memcpy(&addr.sin_addr, hp->h_addr_list[i], hp->h_length);
        printf("%s IP: %s\n", argv[1], inet_ntoa(addr.sin_addr));
    }
    for(i=0; hp->h_aliases[i] ;i++)
        printf("Alias: %s\n", hp->h_aliases[i]);

    // Cleanup
    //
    LocalFree(hp);

    WSACleanup();
    return 0;
}