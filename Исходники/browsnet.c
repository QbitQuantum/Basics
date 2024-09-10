NET_API_STATUS
BrCreateNetwork(
    PUNICODE_STRING TransportName,
    IN BOOLEAN Wannish,
    IN BOOLEAN Ras,
    IN PUNICODE_STRING AlternateTransportName OPTIONAL
    )
/*++

Routine Description:

    This routine allocates memory to hold a network structure, and initializes
    all of its associated data structures.

Arguments:

    TransportName - The name of the transport to add.

Return Value:

    Status of operation (mostly status of allocations).

--*/
{
    NET_API_STATUS Status;
    PNETWORK Network;
    BOOLEAN NetworkLockInitialized = FALSE;
    BOOLEAN MasterFlagsInitialized = FALSE;
    BOOLEAN BackupBrowserTimerCreated = FALSE;
    BOOLEAN MasterBrowserTimerCreated =FALSE;
    BOOLEAN AnnouncementTimerCreated = FALSE;
    BOOLEAN ResponseCacheLockInitialized = FALSE;

    //
    // Check to see if the transport already exists.
    //

    if ((Network = BrFindNetwork(TransportName)) != NULL) {

        return NERR_AlreadyExists;
    }

    //
    // If this transport is explicitly on our list of transports to unbind,
    //  simply ignore the transport.
    //

    if (BrInfo.UnboundBindings != NULL) {
        LPTSTR_ARRAY TStrArray = BrInfo.UnboundBindings;

        while (!NetpIsTStrArrayEmpty(TStrArray)) {
            LPWSTR NewTransportName;

#define NAME_PREFIX L"\\Device\\"
#define NAME_PREFIX_LENGTH 8

            //
            // The transport name in the registry is only optionally prefixed with \device\
            //

            if ( _wcsnicmp( NAME_PREFIX, TStrArray, NAME_PREFIX_LENGTH) == 0 ) {
                NewTransportName = TransportName->Buffer;
            } else {
                NewTransportName = TransportName->Buffer + NAME_PREFIX_LENGTH;
            }

            if ( _wcsicmp( TStrArray, NewTransportName ) == 0 ) {
                dprintf(INIT, ("Binding is marked as unbound: %s (Silently ignoring)\n", TransportName->Buffer ));
                return NERR_Success;
            }

            TStrArray = NetpNextTStrArrayEntry(TStrArray);

        }

    }


    //
    // If this transport isn't bound to the SMB server,
    //  don't create the transport here.
    //  we do announcments through the SMB server.
    //

    Status = I_NetServerSetServiceBits(NULL, TransportName->Buffer, 0, TRUE);

    if (Status == ERROR_PATH_NOT_FOUND ) {
        dprintf(INIT, ("SMB Server doesn't have this transport: %s (Silently unbinding)\n", TransportName->Buffer ));
        return NERR_Success;
    }


    //
    // Create the transport.
    //

    try {

        Network = MIDL_user_allocate(sizeof(NETWORK));

        if (Network == NULL) {
            try_return(Status = ERROR_NOT_ENOUGH_MEMORY);
        }

        RtlInitializeResource(&Network->Lock);

        NetworkLockInitialized = TRUE;

        Network->LockCount = 0;

        Network->ReferenceCount = 1;

        Network->Role = BrDefaultRole;

        Network->NumberOfFailedBackupTimers = 0;

        Network->NumberOfFailedPromotions = 0;

        Network->NumberOfPromotionEventsLogged = 0;

        Network->LastBackupBrowserReturned = 0;

        Network->LastDomainControllerBrowserReturned = 0;

        Network->TimeStoppedBackup = 0;

        Network->BackupServerList = NULL;
        Network->BackupDomainList = NULL;

        Network->TotalBackupServerListEntries = 0;
        Network->TotalBackupDomainListEntries = 0;

        Network->NetworkName.Buffer = MIDL_user_allocate(TransportName->MaximumLength);

        if (Network->NetworkName.Buffer == NULL) {
            try_return(Status = ERROR_NOT_ENOUGH_MEMORY);
        }

        Network->NetworkName.MaximumLength = TransportName->MaximumLength;

        RtlCopyUnicodeString(&Network->NetworkName, TransportName);

        Network->Flags = 0;

        if (ARGUMENT_PRESENT(AlternateTransportName)) {
            PNETWORK AlternateNetwork = BrFindNetwork(AlternateTransportName);

            //
            //  If we didn't find an alternate network, or if that network
            //  already has an alternate network, return an error.
            //

            if (AlternateNetwork == NULL ||
                AlternateNetwork->AlternateNetwork != NULL) {

                try_return(Status = NERR_InternalError);
            }

            Network->Flags |= NETWORK_IPX;

            //
            //  Link the two networks together.
            //

            Network->AlternateNetwork = AlternateNetwork;

            AlternateNetwork->AlternateNetwork = Network;

        } else {
            Network->AlternateNetwork = NULL;
        }

        //
        //  Null terminate the network name buffer.
        //

        Network->NetworkName.Buffer[Network->NetworkName.Length/sizeof(WCHAR)] = UNICODE_NULL;

        RtlInitUnicodeString(&Network->MasterBrowserName, NULL);

        if (Wannish) {
            Network->Flags |= NETWORK_WANNISH;
        }

        if (Ras) {
            Network->Flags |= NETWORK_RAS;
        }

        Network->LastBowserServerQueried = 0;

        RtlInitializeCriticalSection(&Network->MasterFlagsLock);

        MasterFlagsInitialized = TRUE;

        Network->MasterFlags = 0;

        InitializeInterimServerList(&Network->BrowseTable,
                                    BrBrowseTableInsertRoutine,
                                    BrBrowseTableUpdateRoutine,
                                    BrBrowseTableDeleteRoutine,
                                    BrBrowseTableAgeRoutine);

        Network->LastBowserDomainQueried = 0;

        InitializeInterimServerList(&Network->DomainList,
                                    BrDomainTableInsertRoutine,
                                    BrDomainTableUpdateRoutine,
                                    BrDomainTableDeleteRoutine,
                                    BrDomainTableAgeRoutine);

        InitializeListHead(&Network->OtherDomainsList);

        Status = BrCreateTimer(&Network->BackupBrowserTimer);

        if (Status != NERR_Success) {

            try_return(Status);
        }

        BackupBrowserTimerCreated = TRUE;

        Status = BrCreateTimer(&Network->MasterBrowserTimer);

        if (Status != NERR_Success) {
            try_return(Status);
        }

        MasterBrowserTimerCreated = TRUE;

        Status = BrCreateTimer(&Network->MasterBrowserAnnouncementTimer);

        if (Status != NERR_Success) {

            try_return(Status);
        }

        AnnouncementTimerCreated = TRUE;

        InitializeCriticalSection(&Network->ResponseCacheLock);

        ResponseCacheLockInitialized = TRUE;

        InitializeListHead(&Network->ResponseCache);

        Network->TimeCacheFlushed = 0;

        Network->NumberOfCachedResponses = 0;

        Status = RtlEnterCriticalSection(&NetworkLock);

        if (!NT_SUCCESS(Status)) {

            try_return(Status = BrMapStatus(Status));
        }

        InsertHeadList(&ServicedNetworks, &Network->NextNet);

        Status = RtlLeaveCriticalSection(&NetworkLock);

        if (!NT_SUCCESS(Status)) {
            InternalError(("Unable to release browser critical section\n"));
        }

try_exit:NOTHING;
    } finally {
        if (Status != NERR_Success) {

            if (Network != NULL) {
                if (ResponseCacheLockInitialized) {
                    DeleteCriticalSection(&Network->ResponseCacheLock);
                }

                if (MasterFlagsInitialized) {
                    RtlDeleteCriticalSection(&Network->MasterFlagsLock);
                }

                if (NetworkLockInitialized) {
                    RtlDeleteResource(&Network->Lock);
                }

                if (AnnouncementTimerCreated) {
                    BrDestroyTimer(&Network->MasterBrowserAnnouncementTimer);
                }

                if (MasterBrowserTimerCreated) {
                    BrDestroyTimer(&Network->MasterBrowserTimer);
                }

                if (BackupBrowserTimerCreated) {
                    BrDestroyTimer(&Network->BackupBrowserTimer);
                }

                if (Network->NetworkName.Buffer != NULL) {
                    MIDL_user_free(Network->NetworkName.Buffer);
                }

                MIDL_user_free(Network);

            }

        }
    }

    return Status;
}