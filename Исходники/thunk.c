NTSTATUS
openfile (
    IN PHANDLE  filehandle,
    IN PUCHAR   BasePath,
    IN PUCHAR   Name
)
{
    ANSI_STRING    AscBasePath, AscName;
    UNICODE_STRING UniPathName, UniName;
    NTSTATUS                    status;
    OBJECT_ATTRIBUTES           ObjA;
    IO_STATUS_BLOCK             IOSB;
    UCHAR                       StringBuf[500];

    //
    // Build name
    //

    UniPathName.Buffer = (PWCHAR)StringBuf;
    UniPathName.Length = 0;
    UniPathName.MaximumLength = sizeof( StringBuf );

    RtlInitString(&AscBasePath, BasePath);
    RtlAnsiStringToUnicodeString( &UniPathName, &AscBasePath, FALSE );

    RtlInitString(&AscName, Name);
    RtlAnsiStringToUnicodeString( &UniName, &AscName, TRUE );

    RtlAppendUnicodeStringToString (&UniPathName, &UniName);

    InitializeObjectAttributes(
            &ObjA,
            &UniPathName,
            OBJ_CASE_INSENSITIVE,
            0,
            0 );

    //
    // open file
    //

    status = NtOpenFile (
            filehandle,                         // return handle
            SYNCHRONIZE | FILE_READ_DATA,       // desired access
            &ObjA,                              // Object
            &IOSB,                              // io status block
            FILE_SHARE_READ | FILE_SHARE_WRITE, // share access
            FILE_SYNCHRONOUS_IO_ALERT           // open options
            );

    RtlFreeUnicodeString (&UniName);
    return status;
}