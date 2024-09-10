NET_API_STATUS
NetrReplImportDirEnum (
    IN LPTSTR UncServerName OPTIONAL,
    // IN DWORD Level,
    IN OUT LPIMPORT_ENUM_STRUCT EnumContainer,
    // OUT LPIMPORT_CONTAINER BufPtr,      // RPC container (union)
    IN DWORD PrefMaxSize,
    // OUT LPDWORD EntriesRead,
    OUT LPDWORD TotalEntries,
    IN OUT LPDWORD ResumeHandle OPTIONAL
    )

/*++

Routine Description:

    Same as NetReplImportDirEnum.

Arguments:

    Same as NetReplImportDirEnum.

Return Value:

    Same as NetReplImportDirEnum.

--*/

{
    LPVOID ApiArray = NULL;
    LPVOID ApiEntry;
    NET_API_STATUS ApiStatus;
    LPCLIENT_LIST_REC ClientRecord;
    DWORD EntryCount = 0;
    DWORD FixedSize;
    DWORD Level;
    BOOL LockedClientList = FALSE;
    BOOL LockedConfigData = FALSE;
    DWORD OutputSize;
    LPVOID StringLocation;

    UNREFERENCED_PARAMETER(PrefMaxSize);
    UNREFERENCED_PARAMETER(UncServerName);

#define SET_ENTRIES_READ( value ) \
    { \
        /* Pretend level 0, to make life easy. */ \
        EnumContainer->ImportInfo.Level0->EntriesRead = (value); \
    }

#define SET_BUFFER_POINTER( value ) \
    { \
        /* Pretend level 0, to make life easy. */ \
        EnumContainer->ImportInfo.Level0->Buffer = (value); \
    }

    //
    // Check for caller errors.
    //
    NetpAssert( EnumContainer != NULL );
    NetpAssert( EnumContainer->ImportInfo.Level0 != NULL );
    Level = EnumContainer->Level;

    SET_BUFFER_POINTER( NULL ); // Don't confuse caller about possible alloc.

    if (TotalEntries == NULL) {
        return (ERROR_INVALID_PARAMETER);
    }

    // Test for memory faults before we lock anything.
    SET_ENTRIES_READ( 0 );
    * TotalEntries = 0;

    // This version only supports 1 call to enumerate, so resume handle
    // should never be set to nonzero.  But let's check, so caller finds out
    // they have a buggy program.
    if (ResumeHandle != NULL) {
        if (*ResumeHandle != 0) {
            return (ERROR_INVALID_PARAMETER);
        }
    }

    //
    // Check role and handle call if import half of service is not running.
    //
    ACQUIRE_LOCK_SHARED( ReplConfigLock );
    LockedConfigData = TRUE;

    if ( !ReplRoleIncludesImport( ReplConfigRole  ) ) {

        ApiStatus = ImportDirEnumApiRecords(
                UncServerName,
                Level,
                (LPBYTE *) (LPVOID) &ApiArray,
                PrefMaxSize,
                & EntryCount,
                TotalEntries );
        goto Cleanup;
    }

    //
    // Import side of service is running...
    // Compute size of output area (and check caller's Level too).
    //
    ApiStatus = NetpReplImportDirStructureInfo (
            Level,
            PARMNUM_ALL,
            TRUE,  // want native sizes
            NULL,  // don't need DataDesc16
            NULL,  // don't need DataDesc32
            NULL,  // don't need DataDescSmb
            & OutputSize,  // need max size of structure
            & FixedSize,
            NULL); // don't need StringSize
    if (ApiStatus != NO_ERROR) {
        goto Cleanup;  // don't forget to unlock...
    }

    //
    // Get read-only lock on client list.
    //
    ACQUIRE_LOCK_SHARED( RCGlobalClientListLock );
    LockedClientList = TRUE;

    //
    // Find out how many entries there are.
    //
    EntryCount = RCGlobalClientListCount;

    IF_DEBUG( IMPAPI ) {
        NetpKdPrint(( "NetrReplImportDirEnum: there are " FORMAT_DWORD
                " client records.\n", EntryCount ));
    }

    if (EntryCount > 0) {

        //
        // Allocate the output area.
        //
        ApiStatus = NetApiBufferAllocate(
                OutputSize * EntryCount,
                (LPVOID *) & ApiArray);
        if (ApiStatus != NO_ERROR) {

            // ApiStatus is already set to return error to caller.
            // Don't forget to release lock...

        } else {

            NetpAssert( ApiArray != NULL );

            //
            // Loop for each entry in client list.
            //
            ApiEntry = ApiArray;
            ClientRecord = RCGlobalClientListHeader;
            StringLocation = NetpPointerPlusSomeBytes(
                    ApiArray,
                    OutputSize * EntryCount );

            while (ClientRecord != NULL) {

                //
                // Build an array entry for this client record.
                //
                ApiStatus = ImportDirBuildApiRecord (
                        Level,
                        ClientRecord->dir_name,
                        ClientRecord->state,
                        ClientRecord->master,
                        ClientRecord->timestamp, // Last update, secs since '70.
                        ClientRecord->lockcount,
                        ClientRecord->time_of_first_lock, // Seconds since 1970.
                        ApiEntry,
                        (LPBYTE *) (LPVOID) & StringLocation);
                IF_DEBUG( IMPAPI ) {
                    NetpKdPrint(( "NetrReplImportDirEnum: build status is "
                            FORMAT_API_STATUS ".\n", ApiStatus ));
                }
                NetpAssert( ApiStatus == NO_ERROR );  // We checked all parms.

                ClientRecord = ClientRecord->next_p;
                ApiEntry = NetpPointerPlusSomeBytes( ApiEntry, FixedSize );

            }

        }

        // Don't forget to release lock...

    } else {