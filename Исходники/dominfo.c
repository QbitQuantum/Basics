NTSTATUS
DfsOpen(
    IN  OUT PHANDLE DfsHandle,
    IN      PUNICODE_STRING DfsName OPTIONAL
)
{
    NTSTATUS status;
    OBJECT_ATTRIBUTES objectAttributes;
    IO_STATUS_BLOCK ioStatus;
    PUNICODE_STRING name;

    if (ARGUMENT_PRESENT(DfsName)) {
        name = DfsName;
    } else {
        name = &LocalDfsName;
    }

    InitializeObjectAttributes(
        &objectAttributes,
        name,
        OBJ_CASE_INSENSITIVE,
        NULL,
        NULL
    );

    status = NtCreateFile(
        DfsHandle,
        SYNCHRONIZE,
        &objectAttributes,
        &ioStatus,
        NULL,
        FILE_ATTRIBUTE_NORMAL,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        FILE_OPEN_IF,
        FILE_CREATE_TREE_CONNECTION | FILE_SYNCHRONOUS_IO_NONALERT,
        NULL,
        0);

    if (NT_SUCCESS(status))
        status = ioStatus.Status;

    return status;
}