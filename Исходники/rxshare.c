NET_API_STATUS
RxNetShareEnum(
    IN  LPTSTR  ServerName,
    IN  DWORD   Level,
    OUT LPBYTE* Buffer,
    IN  DWORD   PrefMaxLen,
    OUT LPDWORD EntriesRead,
    OUT LPDWORD EntriesLeft,
    IN OUT LPDWORD ResumeHandle OPTIONAL
    )

/*++

Routine Description:

    Performs NetShareEnum API at a remote down-level server. Any returned info
    will be in 32-bit LanMan format. Information returned in buffer sourced by
    this routine. Caller must use NetApiBufferFree when returned buffer no
    longer required

Arguments:

    ServerName  - where to perform the request
    Level       - of info to return. Can be 0, 1 or 2
    Buffer      - pointer to pointer to returned info buffer
    PrefMaxLen  - caller preferred maximum size of returned buffer
    EntriesRead - pointer to number of entries being returned from this call
    EntriesLeft - pointer to total number of share info structures which could be returned
    ResumeHandle- NOT Allowed on down level versions. Must Be NULL

Return Value:

    NET_API_STATUS
        Success = NERR_Success
        Failure = ERROR_INVALID_LEVEL
                    Level parameter not in range 0 <= Level <= 2
                  ERROR_INVALID_PARAMETER
                    Non-NULL ResumeHandle. ResumeHandle can be NULL or a
                    pointer to 0
                  (return code from NetApiBufferAllocate)
                  (return code from RxRemoteApi)
--*/

{
    NET_API_STATUS  rc;
    DWORD   array_size;
    LPDESC  pDesc16;
    LPDESC  pDesc32;
    LPDESC  pDescSmb;
    LPBYTE  ourbuf;
    DWORD   infolen;
    DWORD   entries_read, total_avail;


    UNREFERENCED_PARAMETER(PrefMaxLen);

#if DBG
    //
    // The ServerName parameter must be a non-NUL(L) string. We know this must
    // be so since (presumably) the server name was used as the criteria to get
    // here. Ensure that this is so (in the non-release version) so we trap
    // stupid mistakes early
    //

    NetpAssert(ServerName != NULL);
    NetpAssert(*ServerName);
#endif

    //
    // Set the number of entries read and total available to sensible defaults.
    // Side effect of testing writability of supplied parameters
    //

    //
    // I assume that:
    //  Buffer is a valid, non-NULL pointer
    //  EntriesRead is a valid, non-NULL pointer
    //  EntriesLeft is a valid, non-NULL pointer
    // since these should have been verified at the API level
    //

    *Buffer = NULL;
    *EntriesRead = 0;
    *EntriesLeft = 0;

    //
    // Check for invalid parameters.
    // NB Does Assume that DWORD is unsigned
    // Ensure that:
    //  Level is not >2
    //  ResumeHandle is NULL or a pointer to NULL
    //

    if ((ResumeHandle != NULL) && *ResumeHandle) {
        return ERROR_INVALID_PARAMETER;
    }

    if (Level > 2) {
        return ERROR_INVALID_LEVEL;
    }

    //
    // Decide which descriptors to use, based on the Level parameter
    //

    GetShareInfoDescriptors(Level, &pDesc16, &pDesc32, &pDescSmb, &infolen);
    ourbuf = NULL;

    //
    // here we used to let RxRemoteApi allocate a buffer (64K intermediate)
    // and do the transaction, returning us a buffer just large enough to
    // hold the returned information. WinBall server barfs if it gets a
    // request with a 64K buffer, so we have to solicit size info until we
    // get everything back. Unfortunately - as of writing - we have no way
    // of knowing the type of server we will make the transaction request to
    // so we may end up having to make >1 request to a LM 2.1 server where
    // we used to be able to get away with 1. On the other hand we can't risk
    // upsetting the WB server. Compromise time. Send a 'reasonable' sized
    // request to the other side (4K buffer). If it isn't sufficient then
    // we loop again, allocating the required buffer
    //

    //
    // what about a LRU cache which keeps the size of the buffer required
    // to satisfy an enum request to a particular down-level server?
    //

    //
    // Loop until we have enough memory or we die for some other reason.
    //

    array_size = INITIAL_BUFFER_SIZE;

    do {

        // Figure out how much memory we need.

        //
        // Remote the API, which will allocate the array for us.
        //

        rc = RxRemoteApi(API_WShareEnum,
                    ServerName,             // where it will run
                    REMSmb_NetShareEnum_P,  // parameter descriptor
                    pDesc16,                // Data descriptor/16-bit
                    pDesc32,                // Data descriptor/32-bit
                    pDescSmb,               // Data descriptor/SMB
                    NULL,                   // Aux descriptor/16-bit
                    NULL,                   // Aux descriptor/32-bit
                    NULL,                   // Aux descriptor/SMB
                    ALLOCATE_RESPONSE,      // allocate a buffer for us
                    Level,                  // level parameter
                    &ourbuf,                // pointer to allocated buffer
                    array_size,             // size of down-level buffer
                    &entries_read,          // pointer to entries read variable
                    &total_avail            // pointer to total entries variable
                    );

        if (rc == ERROR_MORE_DATA) {
            (void) NetApiBufferFree( ourbuf );
            ourbuf = NULL;

            if (array_size >= MAX_TRANSACT_RET_DATA_SIZE) {
                //
                // No point in trying with a larger buffer
                //
                break;
            }
#if DBG
            NetpAssert(array_size != total_avail * infolen);
#endif
            array_size = (total_avail * infolen);
            if (array_size > MAX_TRANSACT_RET_DATA_SIZE) {
                //
                // Try once more with the maximum-size buffer
                //
                array_size = MAX_TRANSACT_RET_DATA_SIZE;
            }
#if DBG
            NetpAssert( array_size != 0 );
#endif
        }
    } while (rc == ERROR_MORE_DATA);

    //
    // if we met with an error then free the allocated buffer and return the
    // error to the caller. If there was no error then we return the items
    // received from the down-level server
    //

    if (rc) {
        if (ourbuf != NULL) {
            (void) NetApiBufferFree(ourbuf);
        }
    } else {
        if (Level == 2) {
            ConvertMaxUsesField((LPSHARE_INFO_2)ourbuf, entries_read);
        }
        *Buffer = ourbuf;
        *EntriesRead = entries_read;
        *EntriesLeft = total_avail;
    }
    return rc;
}