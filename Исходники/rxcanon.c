NET_API_STATUS
RxNetpNameValidate(
    IN  LPTSTR  ServerName,
    IN  LPTSTR  Name,
    IN  DWORD   NameType,
    IN  DWORD   Flags
    )

/*++

Routine Description:

    Runs I_NetNameValidate on a down-level server

Arguments:

    ServerName  - down-level server where this routine is run
    Name        - name to validate
    NameType    - type of name expected
    Flags       - flags controlling server-side routine

Return Value:

    NET_API_STATUS
        Success - NERR_Success
        Failure -

--*/

{
    return RxRemoteApi(
        API_WI_NetNameValidate,     // API #
        ServerName,                 // where we're gonna do it
        REMSmb_I_NetNameValidate_P, // parameter descriptor
        NULL,                       // data descriptor 16-bit
        NULL,                       // data descriptor 32-bit
        NULL,                       // data descriptor SMB
        NULL,                       // aux data descriptor 16-bit
        NULL,                       // aux data descriptor 32-bit
        NULL,                       // aux data descriptor SMB
        FALSE,                      // can use NULL session
        Name,                       // args to remote routine
        NameType,                   // "
        Flags                       // "
        );
}