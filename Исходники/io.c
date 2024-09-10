void fs_open(PUNICODE_STRING DriveRoot,int rw)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK Iosb;
    NTSTATUS Status;

    InitializeObjectAttributes(&ObjectAttributes,
        DriveRoot,
        0,
        NULL,
        NULL);

    Status = NtOpenFile(&fd,
        FILE_GENERIC_READ | (rw ? FILE_GENERIC_WRITE : 0),
        &ObjectAttributes,
        &Iosb,
        rw ? 0 : FILE_SHARE_READ,
        FILE_SYNCHRONOUS_IO_ALERT);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtOpenFile() failed with status 0x%.08x\n", Status);
        return;
    }

    // If rw is specified, then the volume should be exclusively locked
    if (rw) fs_lock(TRUE);

    // Query geometry and partition info, to have bytes per sector, etc

    CurrentOffset.QuadPart = 0LL;

    changes = last = NULL;
    did_change = 0;
}