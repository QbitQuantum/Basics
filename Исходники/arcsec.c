NTSTATUS
IopApplySystemPartitionProt(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock
    )

/*++

Routine Description:

    This routine applies protection to the system partition that
    prevents all users except administrators from accessing the
    partition.


    This routine is only used during system initialization.
    As such, all memory allocations are expected to succeed.
    Success is tested only with assertions.


Arguments:

    LoaderBlock - Supplies a pointer to the loader parameter block that was
        created by the OS Loader.

Return Value:

    The function value is the final status from attempting to set the system
    partition protection.


--*/

{
    NTSTATUS status;
    PACL dacl;
    SECURITY_DESCRIPTOR securityDescriptor;
    OBJECT_ATTRIBUTES objectAttributes;
    ULONG length;
    CHAR ArcNameFmt[12];

    ArcNameFmt[0] = '\\';
    ArcNameFmt[1] = 'A';
    ArcNameFmt[2] = 'r';
    ArcNameFmt[3] = 'c';
    ArcNameFmt[4] = 'N';
    ArcNameFmt[5] = 'a';
    ArcNameFmt[6] = 'm';
    ArcNameFmt[7] = 'e';
    ArcNameFmt[8] = '\\';
    ArcNameFmt[9] = '%';
    ArcNameFmt[10] = 's';
    ArcNameFmt[11] = '\0';

    ASSERT( ARGUMENT_PRESENT( LoaderBlock ) );
    ASSERT( ARGUMENT_PRESENT( LoaderBlock->ArcHalDeviceName ) );

    //
    // Build an appropriate discretionary ACL.
    //

    length = (ULONG) sizeof( ACL ) +
             ( 2 * ((ULONG) sizeof( ACCESS_ALLOWED_ACE ))) +
             SeLengthSid( SeLocalSystemSid ) +
             SeLengthSid( SeAliasAdminsSid ) +
             8; // The 8 is just for good measure

    dacl = (PACL) ExAllocatePool( PagedPool, length );
    if (!dacl) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    status = RtlCreateAcl( dacl, length, ACL_REVISION2 );
    if (NT_SUCCESS( status )) {

        status = RtlAddAccessAllowedAce( dacl,
                                         ACL_REVISION2,
                                         GENERIC_ALL,
                                         SeLocalSystemSid );
        if (NT_SUCCESS( status )) {

            status = RtlAddAccessAllowedAce( dacl,
                                             ACL_REVISION2,
                                             GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE | READ_CONTROL,
                                             SeAliasAdminsSid );
            if (NT_SUCCESS( status )) {

                //
                // Put it in a security descriptor so that it may be applied to
                // the system partition device.
                //

                status = RtlCreateSecurityDescriptor( &securityDescriptor,
                                                      SECURITY_DESCRIPTOR_REVISION );
                if (NT_SUCCESS( status )) {

                    status = RtlSetDaclSecurityDescriptor( &securityDescriptor,
                                                           TRUE,
                                                           dacl,
                                                           FALSE );
                }
            }
        }
    }

    if (!NT_SUCCESS( status )) {
        ExFreePool( dacl );
        return status;
    }

    //
    // Open the ARC boot device and apply the ACL.
    //

    {
        NTSTATUS tmpStatus;
        UCHAR deviceNameBuffer[256];
        STRING deviceNameString;
        UNICODE_STRING deviceNameUnicodeString;
        HANDLE deviceHandle;
        IO_STATUS_BLOCK ioStatusBlock;

        //
        // Begin by formulating the ARC name of the boot device in the ARC
        // name space.
        //

        sprintf( deviceNameBuffer,
                 ArcNameFmt,
                 LoaderBlock->ArcHalDeviceName );

        RtlInitAnsiString( &deviceNameString, deviceNameBuffer );

        status = RtlAnsiStringToUnicodeString( &deviceNameUnicodeString,
                                               &deviceNameString,
                                               TRUE );

        if (NT_SUCCESS( status )) {

            InitializeObjectAttributes( &objectAttributes,
                                        &deviceNameUnicodeString,
                                        OBJ_CASE_INSENSITIVE,
                                        NULL,
                                        NULL );

            status = ZwOpenFile( &deviceHandle,
                                 WRITE_DAC,
                                 &objectAttributes,
                                 &ioStatusBlock,
                                 TRUE,
                                 0 );

            RtlFreeUnicodeString( &deviceNameUnicodeString );

            if (NT_SUCCESS( status )) {


                //
                // Apply the ACL built above to the system partition device
                // object.
                //

                status = ZwSetSecurityObject( deviceHandle,
                                              DACL_SECURITY_INFORMATION,
                                              &securityDescriptor );

                tmpStatus = NtClose( deviceHandle );
            }
        }
    }

    //
    // Free the memory used to hold the ACL.
    //

    ExFreePool( dacl );

    return status;
}