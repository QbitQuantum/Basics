DWORD
WSAAPI
WsTcFindIfsProviderForSocket(IN PTCATALOG Catalog,
                             IN SOCKET Handle)
{
    PTPROVIDER Provider;
    IN SOCKET NewHandle;
    INT Error;
    DWORD OptionLength;
    PLIST_ENTRY Entry;
    WSAPROTOCOL_INFOW ProtocolInfo;
    DWORD UniqueId;
    INT ErrorCode;
    PTCATALOG_ENTRY CatalogEntry;

    /* Get the catalog lock */
    WsTcLock();

    /* Loop as long as the catalog changes */
CatalogChanged:

    /* Loop every provider */
    Entry = Catalog->ProtocolList.Flink;
    while (Entry != &Catalog->ProtocolList)
    {
        /* Get the catalog entry */
        CatalogEntry = CONTAINING_RECORD(Entry, TCATALOG_ENTRY, CatalogLink);

        /* Move to the next entry */
        Entry = Entry->Flink;

        /* Skip it if it doesn't support IFS */
        if (!(CatalogEntry->ProtocolInfo.dwServiceFlags1 & XP1_IFS_HANDLES)) continue;

        /* Check if we need to load it */
        if (!(Provider = CatalogEntry->Provider))
        {
            /* Load it */
            ErrorCode = WsTcLoadProvider(Catalog, CatalogEntry);
            
            /* Skip it if we failed to load it */
            if (ErrorCode != ERROR_SUCCESS) continue;

            /* Get the provider again */
            Provider = CatalogEntry->Provider;
        }

        /* Reference the entry and get our unique id */
        InterlockedIncrement(&CatalogEntry->RefCount);
        UniqueId = Catalog->UniqueId;

        /* Release the lock now */
        WsTcUnlock();

        /* Get the catalog entry ID */
        OptionLength = sizeof(ProtocolInfo);
        ErrorCode = Provider->Service.lpWSPGetSockOpt(Handle,
                                                      SOL_SOCKET,
                                                      SO_PROTOCOL_INFOW,
                                                      (PCHAR)&ProtocolInfo,
                                                      (LPINT)&OptionLength,
                                                      &Error);

        /* Dereference the entry and check the result */
        WsTcEntryDereference(CatalogEntry);
        if (ErrorCode != ERROR_SUCCESS)
        {
            /* Lock and make sure this provider is still valid */
            WsTcLock();
            if (UniqueId == Catalog->UniqueId) continue;

            /* It changed! We need to start over */
            goto CatalogChanged;
        }

        /* Now get the IFS handle */
        NewHandle = WPUModifyIFSHandle(ProtocolInfo.dwCatalogEntryId,
                                       Handle,
                                       &Error);
        
        /* Check if the socket is invalid */
        if (NewHandle == INVALID_SOCKET) return WSAENOTSOCK;

        /* We suceeded, get out of here */
        return ERROR_SUCCESS;
    }

    /* Unrecognized socket if we get here: note, we still have the lock */
    WsTcUnlock();
    return WSAENOTSOCK;
}