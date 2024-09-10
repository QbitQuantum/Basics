NET_API_STATUS NET_API_FUNCTION
NetServerEnum(
    IN  LPCWSTR      servername OPTIONAL,
    IN  DWORD       level,
    OUT LPBYTE      *bufptr,
    IN  DWORD       prefmaxlen,
    OUT LPDWORD     entriesread,
    OUT LPDWORD     totalentries,
    IN  DWORD       servertype,
    IN  LPCWSTR      domain OPTIONAL,
    IN OUT LPDWORD  resume_handle OPTIONAL
    )
/*++

Routine Description:

    This is the DLL entrypoint for NetServerEnum.

Arguments:

    servername - Supplies the name of server to execute this function

    level - Supplies the requested level of information.

    bufptr - Returns a pointer to a buffer which contains the
        requested transport information.

    prefmaxlen - Supplies the number of bytes of information
        to return in the buffer.  If this value is MAXULONG, we will try
        to return all available information if there is enough memory
        resource.

    entriesread - Returns the number of entries read into the buffer.  This
        value is returned only if the return code is NERR_Success or
        ERROR_MORE_DATA.

    totalentries - Returns the total number of entries available.  This value
        is returned only if the return code is NERR_Success or ERROR_MORE_DATA.

    servertype - Supplies the type of server to enumerate.

    domain - Supplies the name of one of the active domains to enumerate the
        servers from.  If NULL, servers from the primary domain, logon domain
        and other domains are enumerated.

    resume_handle - Supplies and returns the point to continue with enumeration.

Return Value:

    NET_API_STATUS - NERR_Success or reason for failure.

--*/
{
    NET_API_STATUS NetStatus;


    //
    // NetServerEnum is simply a wrapper to NetServerEnumEx
    //

    NetStatus = NetServerEnumEx(
                    servername,
                    level,
                    bufptr,
                    prefmaxlen,
                    entriesread,
                    totalentries,
                    servertype,
                    domain,
                    NULL );     // NULL FirstNameToReturn

    if (ARGUMENT_PRESENT(resume_handle)) {
        *resume_handle = 0;
    }

    return NetStatus;

}