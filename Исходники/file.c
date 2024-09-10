NET_API_STATUS
FileEnumCommon (
    IN LPTSTR BasePath,
    IN LPTSTR UserName,
    IN DWORD Level,
    OUT LPBYTE *Buffer,
    IN DWORD PreferredMaximumLength,
    OUT LPDWORD EntriesRead,
    OUT LPDWORD TotalEntries,
    IN OUT LPDWORD ResumeHandle OPTIONAL,
    IN BOOLEAN IsGetInfo
    )

{
    NET_API_STATUS error;
    PSERVER_REQUEST_PACKET srp;

    //
    // Make sure that the level is valid.
    //

    if ( Level != 2 && Level != 3 ) {
        return ERROR_INVALID_LEVEL;
    }

    //
    // Set up the input parameters in the request buffer.
    //

    srp = SsAllocateSrp( );
    if ( srp == NULL ) {
        return ERROR_NOT_ENOUGH_MEMORY;
    }

#ifdef UNICODE
    RtlInitUnicodeString( &srp->Name1, BasePath );
    RtlInitUnicodeString( &srp->Name2, UserName );
#else
    {
        NTSTATUS status;
        OEM_STRING ansiString;
        RtlInitString( &ansiString, BasePath );
        status = RtlOemStringToUnicodeString( &srp->Name1, &ansiString, TRUE );
        RtlInitString( &ansiString, UserName );
        status = RtlOemStringToUnicodeString( &srp->Name2, &ansiString, TRUE );
    }
#endif

    srp->Level = Level;
    if ( IsGetInfo ) {
        srp->Flags = SRP_RETURN_SINGLE_ENTRY;
    }

    if ( ARGUMENT_PRESENT( ResumeHandle ) ) {
        srp->Parameters.Get.ResumeHandle = *ResumeHandle;
    } else {
        srp->Parameters.Get.ResumeHandle = 0;
    }

    //
    // Get the data from the server.  This routine will allocate the
    // return buffer and handle the case where PreferredMaximumLength ==
    // -1.
    //

    error = SsServerFsControlGetInfo(
                FSCTL_SRV_NET_FILE_ENUM,
                srp,
                (PVOID *)Buffer,
                PreferredMaximumLength
                );

    //
    // Set up return information.  Only change the resume handle if at
    // least one entry was returned.
    //

    *EntriesRead = srp->Parameters.Get.EntriesRead;
    *TotalEntries = srp->Parameters.Get.TotalEntries;
    if ( *EntriesRead > 0 && ARGUMENT_PRESENT( ResumeHandle ) ) {
        *ResumeHandle = srp->Parameters.Get.ResumeHandle;
    }

#ifndef UNICODE
    RtlFreeUnicodeString( &srp->Name1 );
    RtlFreeUnicodeString( &srp->Name2 );
#endif

    SsFreeSrp( srp );

    return error;

} // FileEnumCommon