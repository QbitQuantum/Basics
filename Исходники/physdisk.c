BOOLEAN
OpenFile(
    PSZ     DriveNumber,
    PHANDLE Handle
    )
{
    OBJECT_ATTRIBUTES oa;
    STRING            ntDriveName;
    UNICODE_STRING    uniDriveName;
    IO_STATUS_BLOCK   ioStatusBlock;
    int               charsInName;
    char              driveName[50];
    NTSTATUS          nts;


    sprintf(driveName, "\\Device\\Harddisk%s\\Partition0", DriveNumber);

    charsInName = strlen(driveName);

    ntDriveName.Length = (USHORT)charsInName;
    ntDriveName.MaximumLength = (USHORT)charsInName;
    ntDriveName.Buffer = driveName;

    printf( "NT drive name = %s\n", ntDriveName.Buffer );

    RtlAnsiStringToUnicodeString(&uniDriveName, &ntDriveName, TRUE);

    memset(&oa, 0, sizeof(OBJECT_ATTRIBUTES));
    oa.Length = sizeof(OBJECT_ATTRIBUTES);
    oa.ObjectName = &uniDriveName;
    oa.Attributes = OBJ_CASE_INSENSITIVE;

    if (!NT_SUCCESS(nts = NtOpenFile(Handle,
                                     SYNCHRONIZE | FILE_READ_DATA | FILE_WRITE_DATA,
                                     &oa,
                                     &ioStatusBlock,
                                     FILE_SHARE_READ | FILE_SHARE_WRITE,
                                     FILE_SYNCHRONOUS_IO_ALERT))) {

        printf("NtOpenFile status %x\n", nts);
        return FALSE;
    }

    RtlFreeUnicodeString(&uniDriveName);

    return TRUE;
}