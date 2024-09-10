NET_API_STATUS
RxNetErrorLogClear (
    IN LPTSTR UncServerName,
    IN LPTSTR BackupFile OPTIONAL,
    IN LPBYTE Reserved OPTIONAL
    )
{
    NetpAssert(UncServerName != NULL);
    NetpAssert(*UncServerName != '\0');

    return (RxRemoteApi(
            API_WErrorLogClear,         // API number
            UncServerName,
            REMSmb_NetErrorLogClear_P,  // parm desc
            NULL,                       // no data desc 16
            NULL,                       // no data desc 32
            NULL,                       // no data desc SMB
            NULL,                       // no aux desc 16
            NULL,                       // no aux desc 32
            NULL,                       // no aux desc SMB
            0,                          // flags: not a null session API
            // rest of API's arguments, in 32-bit LM2.x format:
            BackupFile,
            Reserved));

} // RxNetErrorLogClear