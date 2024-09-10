static BOOL
GetLSAPrincipalName(char * pszUser, DWORD dwUserSize)
{
    KERB_QUERY_TKT_CACHE_REQUEST CacheRequest;
    PKERB_RETRIEVE_TKT_RESPONSE pTicketResponse = NULL;
    ULONG ResponseSize;
    PKERB_EXTERNAL_NAME pClientName = NULL;
    PUNICODE_STRING     pDomainName = NULL;
    LSA_STRING Name;
    HANDLE hLogon = INVALID_HANDLE_VALUE;
    ULONG PackageId;
    NTSTATUS ntStatus;
    NTSTATUS ntSubStatus = 0;
    WCHAR * wchUser = NULL;
    DWORD   dwSize;
    SHORT   sCount;
    BOOL bRet = FALSE;

    ntStatus = LsaConnectUntrusted( &hLogon);
    if (FAILED(ntStatus))
        goto cleanup;

    Name.Buffer = MICROSOFT_KERBEROS_NAME_A;
    Name.Length = (USHORT)(sizeof(MICROSOFT_KERBEROS_NAME_A) - sizeof(char));
    Name.MaximumLength = Name.Length;

    ntStatus = LsaLookupAuthenticationPackage( hLogon, &Name, &PackageId);
    if (FAILED(ntStatus))
        goto cleanup;

    memset(&CacheRequest, 0, sizeof(KERB_QUERY_TKT_CACHE_REQUEST));
    CacheRequest.MessageType = KerbRetrieveTicketMessage;
    CacheRequest.LogonId.LowPart = 0;
    CacheRequest.LogonId.HighPart = 0;

    ntStatus = LsaCallAuthenticationPackage( hLogon,
                                             PackageId,
                                             &CacheRequest,
                                             sizeof(CacheRequest),
                                             &pTicketResponse,
                                             &ResponseSize,
                                             &ntSubStatus);
    if (FAILED(ntStatus) || FAILED(ntSubStatus))
        goto cleanup;

    /* We have a ticket in the response */
    pClientName = pTicketResponse->Ticket.ClientName;
    pDomainName = &pTicketResponse->Ticket.DomainName;

    /* We want to return ClientName @ DomainName */

    dwSize = 0;
    for ( sCount = 0; sCount < pClientName->NameCount; sCount++)
    {
        dwSize += pClientName->Names[sCount].Length;
    }
    dwSize += pDomainName->Length + sizeof(WCHAR);

    if ( dwSize / sizeof(WCHAR) > dwUserSize )
        goto cleanup;

    wchUser = malloc(dwSize);
    if (wchUser == NULL)
        goto cleanup;

    for ( sCount = 0, wchUser[0] = L'\0'; sCount < pClientName->NameCount; sCount++)
    {
        StringCbCatNW( wchUser, dwSize,
                       pClientName->Names[sCount].Buffer,
                       pClientName->Names[sCount].Length);
    }
    StringCbCatNW( wchUser, dwSize,
                   pDomainName->Buffer,
                   pDomainName->Length);

    if ( !UnicodeToANSI( wchUser, pszUser, dwUserSize) )
        goto cleanup;

    bRet = TRUE;

  cleanup:

    if (wchUser)
        free(wchUser);

    if ( hLogon != INVALID_HANDLE_VALUE)
        LsaDeregisterLogonProcess(hLogon);

    if ( pTicketResponse ) {
        SecureZeroMemory(pTicketResponse,ResponseSize);
        LsaFreeReturnBuffer(pTicketResponse);
    }

    return bRet;
}