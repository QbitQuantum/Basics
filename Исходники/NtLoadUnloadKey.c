static NTSTATUS
OpenDirectoryByHandleOrPath(
    OUT PHANDLE RootPathHandle,
    IN HANDLE RootDirectory OPTIONAL,
    IN PUNICODE_STRING RootPath OPTIONAL)
{
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;

    *RootPathHandle = NULL;

    /*
     * RootDirectory and RootPath cannot be either both NULL
     * or both non-NULL, when being specified.
     */
    if ((!RootDirectory && !RootPath) ||
        ( RootDirectory &&  RootPath))
    {
        return STATUS_INVALID_PARAMETER;
    }

    if (!RootDirectory && RootPath)
    {
        /* Open the root directory path */
        InitializeObjectAttributes(&ObjectAttributes,
                                   RootPath,
                                   OBJ_CASE_INSENSITIVE,
                                   NULL,
                                   NULL);
        Status = NtOpenFile(RootPathHandle,
                            // FILE_TRAVERSE is needed to be able to use the handle as RootDirectory for future InitializeObjectAttributes calls.
                            FILE_LIST_DIRECTORY | FILE_ADD_FILE /* | FILE_ADD_SUBDIRECTORY */ | FILE_TRAVERSE | SYNCHRONIZE,
                            &ObjectAttributes,
                            &IoStatusBlock,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            FILE_SYNCHRONOUS_IO_NONALERT | FILE_DIRECTORY_FILE /* | FILE_OPEN_FOR_BACKUP_INTENT */);
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("NtOpenFile(%wZ) failed, Status 0x%08lx\n", RootPath, Status);
            return Status;
        }

        /* Mark the handle as being opened locally */
        *RootPathHandle = (HANDLE)((ULONG_PTR)*RootPathHandle | 1);
    }
    else if (RootDirectory && !RootPath)
    {
        *RootPathHandle = RootDirectory;
    }
    // No other cases possible

    return STATUS_SUCCESS;
}