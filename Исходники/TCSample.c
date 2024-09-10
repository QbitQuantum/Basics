//******************************************************************************
// Routine: 
//      GetSockAddrFromString
//
// Arguments:
//      strAddress     - Address in the String format
//      pSocketAddress - Pointer to SOCKADDR_STORAGE structure where the 
//      address is returned
//
// Description:
//      Takes a string format address and returns a pointer to 
//      SOCKADDR_STORAGE structure containing the address.
//      Only resolves numeric addresses
//******************************************************************************
BOOL
GetSockAddrFromString(const WCHAR *strAddress, PSOCKADDR_STORAGE pSocketAddress)
{
    BOOL result = FALSE;    
    ADDRINFOW *pAddress = NULL;
    int wsaResult = 0;
    ADDRINFOW hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_NUMERICHOST;

    // Resolve the address
    wsaResult = GetAddrInfoW(strAddress, NULL, &hints, &pAddress);
    if (0 != wsaResult)
    {
        printf("Failed to resolve \"%S\". GetAddrInfoW() failed with 0x%x\n", strAddress, wsaResult);
        goto Exit;
    }

    // Make sure the address resolved to only one entry
    if (NULL != pAddress->ai_next)
    {
        printf("%S Resolved to more than one address. Please use a numeric Address\n", strAddress);
        goto Exit;
    }

    // Copy the address to the storage
    CopyMemory(pSocketAddress, pAddress->ai_addr, pAddress->ai_addrlen);

    result = TRUE;

Exit:
    // Cleanup
    if (NULL != pAddress)
    {
        
        FreeAddrInfoW(pAddress);
    }

    return result;
}