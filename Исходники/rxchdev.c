NET_API_STATUS
RxNetCharDevGetInfo(
    IN  LPTSTR  ServerName,
    IN  LPTSTR  DeviceName,
    IN  DWORD   Level,
    OUT LPBYTE* Buffer
    )

/*++

Routine Description:

    Returns an information structure detailing a particular shared comms device
    at a down-level server

Arguments:

    ServerName  - Where to run the remoted API
    DeviceName  - Name of device for which to get info
    Level       - Of info required - 0 or 1
    Buffer      - Pointer to returned pointer to buffer containing info

Return Value:

    NET_API_STATUS
        Success - NERR_Success
        Failure - ERROR_INVALID_PARAMETER
                    DeviceName too long
                  ERROR_INVALID_LEVEL
                    Level parameter not allowed
                  (return code from remoted API)

--*/

{
    DWORD   buflen, total_avail;
    LPDESC  pDesc16, pDesc32, pDescSmb;
    LPBYTE  bufptr;
    NET_API_STATUS  rc;


    //
    // test out the caller supplied arguments. This should be done at the outer
    // level
    //

    *Buffer = NULL;

    if (STRLEN(DeviceName) > LM20_DEVLEN) {
        return ERROR_INVALID_PARAMETER;
    }

    switch (Level) {
    case 0:
        pDesc16 = REM16_chardev_info_0;
        pDesc32 = REM32_chardev_info_0;
        pDescSmb = REMSmb_chardev_info_0;
        buflen = sizeof(CHARDEV_INFO_0) + STRING_SPACE_REQD(DEVLEN + 1);
        break;

    case 1:
        pDesc16 = REM16_chardev_info_1;
        pDesc32 = REM32_chardev_info_1;
        pDescSmb = REMSmb_chardev_info_1;
        buflen = sizeof(CHARDEV_INFO_1) + STRING_SPACE_REQD(DEVLEN + 1) +
            STRING_SPACE_REQD(UNLEN + 1);
        break;

    default:
        return ERROR_INVALID_LEVEL;
    }

    //
    // In the GetInfo case we are content to pre-allocate the return buffer
    // because we know how large it should be (although we actually allocate
    // the maximum size for a particular GetInfo structure level)
    //

    if (rc = NetApiBufferAllocate(buflen, (LPVOID *) &bufptr)) {
        return rc;
    }
    rc = RxRemoteApi(API_NetCharDevGetInfo,     // API #
                    ServerName,                 // where to remote it
                    REMSmb_NetCharDevGetInfo_P, // parameter descriptor
                    pDesc16, pDesc32, pDescSmb, // primary structure descriptors
                    NULL, NULL, NULL,           // no aux data structures
                    FALSE,                      // can't use NULL session
                    DeviceName,                 // API parameters start here...
                    Level,
                    bufptr,
                    buflen,                     // supplied by us
                    &total_avail                // not used by 32-bit API
                    );
    if (rc) {
        (void) NetApiBufferFree(bufptr);
    } else {
        *Buffer = bufptr;
    }
    return rc;
}