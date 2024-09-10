STATIC
NET_API_STATUS
WsGetSystemInfo(
    IN  DWORD Level,
    OUT LPBYTE *BufferPointer
    )

/*++

Routine Description:

    This function calls the Redirector FSD, the LSA subsystem and the
    MSV1_0 authentication package, and the Datagram Receiver DD to get
    the system wide information returned by NetWkstaGetInfo API.

Arguments:

    Level - Supplies the requested level of information.

    BufferPointer - Returns a pointer to a buffer which contains the
        requested workstation information.


Return Value:

    NET_API_STATUS - NERR_Success or reason for failure.

--*/
{
    NET_API_STATUS status;
    DWORD NumberOfLoggedOnUsers = 1;

    //
    // Get number of logged on users from the MSV1_0 authentication package
    // if Level == 102.
    //
    if (Level == 102) {

        PMSV1_0_ENUMUSERS_RESPONSE EnumUsersResponse;

        //
        // Ask authentication package to enumerate users who are physically
        // logged to the local machine.
        //
        if ((status = WsLsaEnumUsers(
                          (LPBYTE *) &EnumUsersResponse
                          )) != NERR_Success) {
            return status;
        }

        NumberOfLoggedOnUsers = EnumUsersResponse->NumberOfLoggedOnUsers;

        (VOID) LsaFreeReturnBuffer(EnumUsersResponse);
    }

    //
    // Put all the data collected into output buffer allocated by this routine.
    //
    return WsFillSystemBufferInfo(
               Level,
               NumberOfLoggedOnUsers,
               BufferPointer
               );
}