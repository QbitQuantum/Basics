NET_API_STATUS
RxpWkstaGetOldInfo (
    IN LPTSTR UncServerName,
    IN DWORD Level,
    OUT LPBYTE *BufPtr
    )

/*++

Routine Description:

    RxpWkstaGetOldInfo does a WkstaGetInfo to a downlevel server for an
    old info level.

Arguments:

    (Same as NetWkstaGetInfo, except UncServerName must not be null, and
    must not refer to the local computer.)

Return Value:

    (Same as NetWkstaGetInfo.)

--*/

{
    DWORD BufSize;
    LPDESC DataDesc16, DataDesc32, DataDescSmb;
    NET_API_STATUS Status;
    DWORD TotalAvail;

    IF_DEBUG(WKSTA) {
        NetpKdPrint(( PREFIX_NETAPI "RxpWkstaGetOldInfo: starting, server="
                FORMAT_LPTSTR ", lvl=" FORMAT_DWORD ".\n",
                UncServerName, Level));
    }

    //
    // Error check caller.
    //
    NetpAssert(UncServerName != NULL);
    if ( !NetpIsOldWkstaInfoLevel( Level )) {
        return (ERROR_INVALID_LEVEL);
    }
    if (BufPtr == NULL) {
        return (ERROR_INVALID_PARAMETER);
    }
    *BufPtr = NULL;  // assume error; it makes error handlers easy to code.
    // This also forces possible GP fault before we allocate memory.

    //
    // Learn about info level.
    //
    Status = NetpWkstaStructureInfo (
            Level,                      // level to learn about
            PARMNUM_ALL,                // No parmnum with this.
            TRUE,                       // Need native sizes.
            & DataDesc16,
            & DataDesc32,
            & DataDescSmb,
            & BufSize,                  // max buffer size
            NULL,                       // don't need fixed size.
            NULL                        // don't need string size.
            );
    if (Status != NERR_Success) {
        return (Status);
    }

    //
    // Actually remote the API, which will get back the (old) info level
    // data in native format.
    //
    Status = RxRemoteApi(
            API_WWkstaGetInfo,          // API number
            UncServerName,              // Required, with \\name.
            REMSmb_NetWkstaGetInfo_P,   // parm desc
            DataDesc16,
            DataDesc32,
            DataDescSmb,
            NULL,                       // no aux data desc 16
            NULL,                       // no aux data desc 32
            NULL,                       // no aux data desc SMB
            ALLOCATE_RESPONSE,          // flags: alloc buffer for us.
            // rest of API's arguments, in 32-bit LM 2.x format:
            Level,
            BufPtr,                     // alloc buffer & set this ptr
            BufSize,
            & TotalAvail);              // total size (BUGBUG meaningless?)

    NetpAssert( Status != ERROR_MORE_DATA );
    NetpAssert( Status != NERR_BufTooSmall );

    return (Status);

} // RxpWkstaGetOldInfo