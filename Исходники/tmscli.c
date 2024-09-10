BOOLEAN
OpenMailslot(
    PSZ Name,
    PHANDLE Handle
    )
{
    STRING ansiString;
    UNICODE_STRING nameString;
    NTSTATUS status;
    OBJECT_ATTRIBUTES objectAttributes;
    IO_STATUS_BLOCK ioStatusBlock;

    RtlInitString(&ansiString, Name );
    RtlOemStringToUnicodeString(&nameString, &ansiString, TRUE);

    //
    //  Open the mailslot
    //

    InitializeObjectAttributes(
        &objectAttributes,
        &nameString,
        OBJ_CASE_INSENSITIVE,
        NULL,
        NULL
        );

    printf( "Attempting to open mailslot \"%wZ\"\n", &nameString );

    status = NtOpenFile (
                Handle,
                FILE_WRITE_DATA | SYNCHRONIZE,
                &objectAttributes,
                &ioStatusBlock,
                FILE_SHARE_WRITE | FILE_SHARE_READ,
                0L
                );

    printf( "Status = %x\n", status );

    RtlFreeUnicodeString(&nameString);
    return ( (BOOLEAN) NT_SUCCESS( status ) );
}