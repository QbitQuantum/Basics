NET_API_STATUS
RxpCopyAndConvertSessions(
    IN LPSESSION_SUPERSET_INFO InStructureArray,
    IN DWORD InEntryCount,
    IN DWORD LevelWanted,
    IN LPTSTR ClientName OPTIONAL,
    IN LPTSTR UserName OPTIONAL,
    OUT LPVOID * OutStructureArrayPtr,  // alloc'ed by this routine
    OUT LPDWORD OutEntryCountPtr OPTIONAL
    )

{
    LPSESSION_SUPERSET_INFO InEntry = InStructureArray;
    DWORD InEntriesLeft;
    const DWORD InFixedSize = sizeof(SESSION_SUPERSET_INFO);

    LPVOID OutEntry;                    // Buffer to be returned to caller.
    DWORD OutEntryCount;
    LPBYTE OutFixedDataEnd;
    DWORD OutFixedSize;
    DWORD OutMaxSize;
    LPTSTR OutStringLocation;
    DWORD OutStringSize;
    LPVOID OutStructureArray;

    BOOL AnyMatchFound = FALSE;         // not yet.
    NET_API_STATUS Status;

    NetpAssert( InEntryCount > 0 );
    NetpAssert( InStructureArray != NULL );

    *OutStructureArrayPtr = NULL;
    NetpSetOptionalArg(OutEntryCountPtr, 0);

    IF_DEBUG(SESSION) {
        NetpKdPrint(( "RxpCopyAndConvertSessions: starting...\n" ));
        NetpDbgDisplaySessionArray(
                SESSION_SUPERSET_LEVEL,
                (LPVOID) InStructureArray,
                InEntryCount);
    }

    //
    // Learn about info level that caller wants.
    //
    Status = NetpSessionStructureInfo (
            LevelWanted,                // level to learn about
            PARMNUM_ALL,                // No parmnum with this.
            TRUE,                       // Need native sizes.
            NULL,                       // don't need data desc 16
            NULL,                       // don't need data desc 32
            NULL,                       // don't need data desc SMB
            & OutMaxSize,               // max buffer size (native)
            & OutFixedSize,             // fixed size.
            & OutStringSize             // string size.
            );
    if (Status != NERR_Success) {
        return (Status);
    }

    //
    // Allocate memory for 32-bit version of caller's info level.
    // BUGBUG: Optimize by scanning input array first.
    //
    Status = NetApiBufferAllocate(
            InEntryCount * OutMaxSize,
            & OutStructureArray);
    if (Status != NERR_Success) {
        return (Status);
    }
    OutEntry = OutStructureArray;
    IF_DEBUG(SESSION) {
        NetpKdPrint(( "RxpCopyAndConvertSessions: allocated output buffer at "
                FORMAT_LPVOID "\n", (LPVOID) OutStructureArray ));
    }


    OutEntryCount = 0;
    OutStringLocation = (LPTSTR) NetpPointerPlusSomeBytes(
            OutStructureArray, InEntryCount * OutMaxSize);
    for (InEntriesLeft=InEntryCount; InEntriesLeft > 0; --InEntriesLeft) {

        OutFixedDataEnd = NetpPointerPlusSomeBytes(
                OutEntry, OutFixedSize);

        if (RxpSessionMatches(
                (LPSESSION_SUPERSET_INFO) InEntry,     // candidate structure
                ClientName,
                UserName)) {

            // Match!
            AnyMatchFound = TRUE;
            ++OutEntryCount;
            RxpConvertSessionInfo (
                    InEntry,
                    LevelWanted,
                    OutEntry,
                    OutFixedDataEnd,
                    & OutStringLocation);       // string area top (updated)

            OutEntry = (LPVOID) NetpPointerPlusSomeBytes(OutEntry,OutFixedSize);
        }

        InEntry = (LPVOID) NetpPointerPlusSomeBytes(InEntry, InFixedSize);

    }

    if (AnyMatchFound == FALSE) {

        (void) NetApiBufferFree( OutStructureArray );
        OutStructureArray = NULL;

        Status = RxpSessionMissingErrorCode( ClientName, UserName);

    } else {
        Status = NERR_Success;

        IF_DEBUG(SESSION) {
            NetpKdPrint(( "RxpCopyAndConvertSessions: ending...\n" ));
            NetpDbgDisplaySessionArray(
                    LevelWanted,
                    (LPVOID) OutStructureArray,
                    OutEntryCount);
        }
    }

    //
    // Tell caller how things went.
    //
    *OutStructureArrayPtr = OutStructureArray;
    NetpSetOptionalArg(OutEntryCountPtr, OutEntryCount);
    return (Status);

}