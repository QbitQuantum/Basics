static BOOLEAN
IsValidNTOSInstallation_UStr(
    IN PUNICODE_STRING SystemRootPath)
{
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    HANDLE SystemRootDirectory;
    BOOLEAN Success;

    /* Open SystemRootPath */
    InitializeObjectAttributes(&ObjectAttributes,
                               SystemRootPath,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    Status = NtOpenFile(&SystemRootDirectory,
                        FILE_LIST_DIRECTORY | SYNCHRONIZE,
                        &ObjectAttributes,
                        &IoStatusBlock,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        FILE_SYNCHRONOUS_IO_NONALERT | FILE_DIRECTORY_FILE);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to open SystemRoot '%wZ', Status 0x%08lx\n", SystemRootPath, Status);
        return FALSE;
    }

    Success = IsValidNTOSInstallationByHandle(SystemRootDirectory);

    /* Done! */
    NtClose(SystemRootDirectory);
    return Success;
}