NET_API_STATUS
RxNetSessionDel (
    IN  LPTSTR      UncServerName,
    IN  LPTSTR      ClientName OPTIONAL,
    IN  LPTSTR      UserName OPTIONAL
    )
{
    LPSESSION_SUPERSET_INFO ArrayPtr = NULL;
    DWORD EntryCount;
    NET_API_STATUS Status;
    DWORD TotalEntries;

    NetpAssert(UncServerName != NULL);
    NetpAssert(*UncServerName != '\0');

    //
    // In LM 2.0, there's no way to delete with UserName or delete all clients,
    // so we have to do an enum and find the sessions we want to delete.
    //
    Status = RxNetSessionEnum (
            UncServerName,
            ClientName,
            UserName,
            SESSION_SUPERSET_LEVEL,
            /*lint -save -e530 */  // (We know variable isn't initialized.)
            (LPBYTE *) (LPVOID *) & ArrayPtr,
            /*lint -restore */  // (Resume uninitialized variable checking.)
            1024,                       // prefered maximum (arbitrary)
            & EntryCount,
            & TotalEntries,
            NULL);                      // no resume handle

    if (Status == NERR_Success) {

        NetpAssert( EntryCount == TotalEntries );

        IF_DEBUG(SESSION) {
            NetpKdPrint(( PREFIX_NETAPI
                    "RxNetSessionDel: enum found " FORMAT_DWORD
                    " entries in array at " FORMAT_LPVOID ".\n",
                    EntryCount, (LPVOID) ArrayPtr ));
        }
        if (EntryCount > 0) {

            LPSESSION_SUPERSET_INFO EntryPtr = ArrayPtr;
            NET_API_STATUS WorstStatus = NERR_Success;

            for ( ; EntryCount > 0; --EntryCount) {

                IF_DEBUG(SESSION) {
                    NetpKdPrint(( PREFIX_NETAPI
                            "RxNetSessionDel: checking entry at "
                            FORMAT_LPVOID ", count is " FORMAT_DWORD ".\n",
                            (LPVOID) EntryPtr, EntryCount ));
                }

                if (RxpSessionMatches( EntryPtr, ClientName, UserName) ) {

                    Status = RxRemoteApi(
                            API_WSessionDel,            // API number
                            UncServerName,
                            REMSmb_NetSessionDel_P,     // parm desc
                            NULL,                       // no data desc 16
                            NULL,                       // no data desc 32
                            NULL,                       // no data desc SMB
                            NULL,                       // no aux desc 16
                            NULL,                       // no aux desc 32
                            NULL,                       // no aux desc SMB
                            0,                          // flags: normal
                            // rest of API's arguments, in 32-bit LM2.x format:
                            ClientName,                 // client computer name
                            (DWORD) 0);                 // reserved.
                    if (Status != NERR_Success) {
                        WorstStatus = Status;
                    }
                }

                ++EntryPtr;

            }

            Status = WorstStatus;

        } else {