NET_API_STATUS
RxNetErrorLogRead (
    IN LPTSTR UncServerName,
    IN LPTSTR Reserved1 OPTIONAL,
    IN LPHLOG ErrorLogHandle,
    IN DWORD Offset,
    IN LPDWORD Reserved2 OPTIONAL,
    IN DWORD Reserved3,
    IN DWORD OffsetFlag,
    OUT LPBYTE * BufPtr,
    IN DWORD PrefMaxSize,
    OUT LPDWORD BytesRead,
    OUT LPDWORD TotalBytes
    )
{
    const DWORD BufSize = 65535;
    NET_API_STATUS Status;
    LPBYTE UnconvertedBuffer;
    DWORD UnconvertedSize;

    UNREFERENCED_PARAMETER(PrefMaxSize);

    NetpAssert(UncServerName != NULL);
    NetpAssert(*UncServerName != '\0');

    *BufPtr = NULL;  // set in case of error, and GP fault if necessary.

    Status = RxRemoteApi(
            API_WErrorLogRead,             // API number
            UncServerName,
            REMSmb_NetErrorLogRead_P,      // parm desc

            REM16_ErrorLogReturnBuf,    // data desc 16
            REM16_ErrorLogReturnBuf,    // data desc 32 (same as 16)
            REMSmb_ErrorLogReturnBuf,   // data desc SMB

            NULL,                       // no aux desc 16
            NULL,                       // no aux desc 32
            NULL,                       // no aux desc SMB
            ALLOCATE_RESPONSE,          // flags: not a null session API
            // rest of API's arguments, in 32-bit LM2.x format:
            Reserved1,
            ErrorLogHandle,             // log handle (input)
            ErrorLogHandle,             // log handle (output)
            Offset,
            Reserved2,
            Reserved3,
            OffsetFlag,
            & UnconvertedBuffer,        // buffer (alloc for us)
            BufSize,
            & UnconvertedSize,
            TotalBytes);                // total available (approximate)
    if (Status != NO_ERROR) {
        return (Status);
    }

    if (UnconvertedSize > 0) {

        NetpAssert( UnconvertedBuffer != NULL );

        Status = RxpConvertErrorLogArray(
                UnconvertedBuffer,      // input array
                UnconvertedSize,        // input byte count
                BufPtr,                 // will be alloc'ed
                BytesRead);             // output byte count

        (void) NetApiBufferFree( UnconvertedBuffer );

        if (Status != NO_ERROR) {
            *BufPtr = NULL;
            *BytesRead = 0;
            *TotalBytes = 0;
            return (Status);
        }

    } else {

        *BytesRead = 0;
        *TotalBytes = 0;
        NetpAssert( *BufPtr == NULL );
        if (UnconvertedBuffer != NULL) {
            (void) NetApiBufferFree( UnconvertedBuffer );
        }

    }

    if ( *BytesRead == 0) {
        NetpAssert( *BufPtr == NULL );
    } else {
        NetpAssert( *BufPtr != NULL );
    }
    return (Status);

} // RxNetErrorLogRead