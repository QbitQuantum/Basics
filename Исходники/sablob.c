PDNS_BLOB
WINAPI
SaBlob_Query(IN LPWSTR Name,
             IN WORD DnsType,
             IN ULONG Flags,
             IN PVOID *Reserved,
             IN DWORD AddressFamily)
{
    PDNS_RECORD DnsRecord = NULL;
    INT ErrorCode;
    PDNS_BLOB DnsBlob = NULL;
    LPWSTR LocalName, LocalNameCopy;

    /* If they want reserved data back, clear it out in case we fail */
    if (Reserved) *Reserved = NULL;

    /* Query DNS */
    ErrorCode = DnsQuery_W(Name,
                           DnsType,
                           Flags,
                           NULL,
                           &DnsRecord,
                           Reserved);
    if (ErrorCode != ERROR_SUCCESS)
    {
        /* We failed... did the caller use reserved data? */
        if (Reserved && *Reserved)
        {
            /* He did, and it was valid. Free it */
            DnsApiFree(*Reserved);
            *Reserved = NULL;
        }

        /* Normalize error code */
        if (ErrorCode == RPC_S_SERVER_UNAVAILABLE) ErrorCode = WSATRY_AGAIN;
        goto Quickie;
    }

    /* Now create the Blob from the DNS Records */
    DnsBlob = SaBlob_CreateFromRecords(DnsRecord, TRUE, DnsType);
    if (!DnsBlob)
    {
        /* Failed, get error code */
        ErrorCode = GetLastError();
        goto Quickie;
    }

    /* Make sure it has a name */
    if (!DnsBlob->Name)
    {
        /* It doesn't, fail */
        ErrorCode = DNS_INFO_NO_RECORDS;
        goto Quickie;
    }

    /* Check if the name is local or loopback */
    if (!(DnsNameCompare_W(DnsBlob->Name, L"localhost")) &&
        !(DnsNameCompare_W(DnsBlob->Name, L"loopback")))
    {
        /* Nothing left to do, exit! */
        goto Quickie;
    }

    /* This is a local name...query it */
    LocalName = DnsQueryConfigAllocEx(DnsConfigFullHostName_W, NULL, NULL);
    if (LocalName)
    {
        /* Create a copy for the caller */
        LocalNameCopy = Dns_CreateStringCopy_W(LocalName);
        if (LocalNameCopy)
        {
            /* Overwrite the one in the blob */
            DnsBlob->Name = LocalNameCopy;
        }
        else
        {
            /* We failed to make a copy, free memory */
            DnsApiFree(LocalName);
        }
    }

Quickie:
    /* Free the DNS Record if we have one */
    if (DnsRecord) DnsRecordListFree(DnsRecord, DnsFreeRecordList);

    /* Check if this is a failure path with an active blob */
    if ((ErrorCode != ERROR_SUCCESS) && (DnsBlob))
    {
        /* Free the blob */
        SaBlob_Free(DnsBlob);
        DnsBlob = NULL;
    }

    /* Set the last error and return */
    SetLastError(ErrorCode);
    return DnsBlob;
}