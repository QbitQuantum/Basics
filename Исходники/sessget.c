NET_API_STATUS
RxNetSessionGetInfo (
    IN LPTSTR UncServerName,
    IN LPTSTR UncClientName,
    IN LPTSTR UserName,
    IN DWORD LevelWanted,
    OUT LPBYTE *BufPtr
    )

/*++

Routine Description:

    RxNetSessionGetInfo performs the same function as NetSessionGetInfo,
    except that the server name is known to refer to a downlevel server.

Arguments:

    (Same as NetSessionGetInfo, except UncServerName must not be null, and
    must not refer to the local computer.)

Return Value:

    (Same as NetSessionGetInfo.)

--*/

{
    NET_API_STATUS ApiStatus;
    LPBYTE TempBuffer;               // Buffer we'll use.
    DWORD TempBufferSize;
    LPDESC TempDataDesc16, TempDataDesc32, TempDataDescSmb;
    NET_API_STATUS TempStatus;
    DWORD TotalAvail;

    IF_DEBUG(SESSION) {
        NetpKdPrint(("RxNetSessionGetInfo: starting, server=" FORMAT_LPTSTR
                ", lvl=" FORMAT_DWORD ".\n", UncServerName, LevelWanted));
    }

    //
    // Update pointers if they point to null chars.
    //
    ChangeNullCharToNullPtr( UncClientName );
    ChangeNullCharToNullPtr( UserName );

    //
    // Error check DLL stub and the app.
    //
    NetpAssert(UncServerName != NULL);
    if (BufPtr == NULL) {
        return (ERROR_INVALID_PARAMETER);
    }
    *BufPtr = NULL;  // assume error; it makes error handlers easy to code.
    // This also forces possible GP fault before we allocate memory.

    if ( (UncClientName == NULL) || (UserName == NULL) ) {
        return (ERROR_INVALID_PARAMETER);
    }

    //
    // Learn about temp info level (max superset of all levels).
    //
    TempStatus = NetpSessionStructureInfo (
            SESSION_SUPERSET_LEVEL,     // level to learn about
            PARMNUM_ALL,                // No parmnum with this.
            TRUE,                       // Need native sizes.
            & TempDataDesc16,
            & TempDataDesc32,
            & TempDataDescSmb,
            & TempBufferSize,           // max buffer size (native)
            NULL,                       // don't need fixed size.
            NULL                        // don't need string size.
            );
    NetpAssert(TempStatus == NERR_Success);

    //
    // Allocate memory for 32-bit version of superset info level.
    //
    TempStatus = NetApiBufferAllocate(
            TempBufferSize,
            (LPVOID *) & TempBuffer);
    if (TempStatus != NERR_Success) {
        return (TempStatus);
    }
    IF_DEBUG(SESSION) {
        NetpKdPrint(( "RxNetSessionGetInfo: allocated temp buffer at "
                FORMAT_LPVOID "\n", (LPVOID) TempBuffer ));
    }

    //
    // Actually remote the API, which will get back the superset
    // data in native format.
    //
    ApiStatus = RxRemoteApi(
            API_WSessionGetInfo,        // API number
            UncServerName,              // Required, with \\name.
            REMSmb_NetSessionGetInfo_P, // parm desc
            TempDataDesc16,
            TempDataDesc32,
            TempDataDescSmb,
            NULL,                       // no aux data desc 16
            NULL,                       // no aux data desc 32
            NULL,                       // no aux data desc SMB
            0,                          // Flags: normal
            // rest of API's arguments, in 32-bit LM 2.x format:
            UncClientName,
            SESSION_SUPERSET_LEVEL,     // level with all possible fields
            TempBuffer,
            TempBufferSize,
            & TotalAvail);              // total size (BUGBUG meaningless?)

    NetpAssert( ApiStatus != ERROR_MORE_DATA );
    NetpAssert( ApiStatus != NERR_BufTooSmall );

    if (ApiStatus == NERR_Success) {

        DWORD EntriesSelected;

        //
        // Copy and convert from temp info level to level the caller wants.
        // Check for match on UncClientName and UserName first.
        //
        TempStatus = RxpCopyAndConvertSessions(
                (LPSESSION_SUPERSET_INFO) TempBuffer,  // input "array"
                1,                      // only one "entry" this time
                LevelWanted,
                UncClientName,
                UserName,
                (LPVOID *) BufPtr,      // alloc'ed (may be NULL if no match)
                & EntriesSelected);     // output entry count
        NetpAssert(TempStatus == NERR_Success);

        if (EntriesSelected == 0) {

            ApiStatus = RxpSessionMissingErrorCode( UncClientName, UserName );
            NetpAssert( ApiStatus != NERR_Success );
        }
    }
    (void) NetApiBufferFree( TempBuffer );
    return (ApiStatus);

} // RxNetSessionGetInfo