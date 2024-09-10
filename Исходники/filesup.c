NTSTATUS
SetupCopyFile(
    PWCHAR SourceFileName,
    PWCHAR DestinationFileName)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    HANDLE FileHandleSource;
    HANDLE FileHandleDest;
    static IO_STATUS_BLOCK IoStatusBlock;
    FILE_STANDARD_INFORMATION FileStandard;
    FILE_BASIC_INFORMATION FileBasic;
    ULONG RegionSize;
    UNICODE_STRING FileName;
    NTSTATUS Status;
    PVOID SourceFileMap = 0;
    HANDLE SourceFileSection;
    SIZE_T SourceSectionSize = 0;
    LARGE_INTEGER ByteOffset;

#ifdef __REACTOS__
    RtlInitUnicodeString(&FileName,
                         SourceFileName);

    InitializeObjectAttributes(&ObjectAttributes,
                               &FileName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = NtOpenFile(&FileHandleSource,
                        GENERIC_READ,
                        &ObjectAttributes,
                        &IoStatusBlock,
                        FILE_SHARE_READ,
                        FILE_SEQUENTIAL_ONLY);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtOpenFile failed: %x, %wZ\n", Status, &FileName);
        goto done;
    }
#else
    FileHandleSource = CreateFileW(SourceFileName,
                                   GENERIC_READ,
                                   FILE_SHARE_READ,
                                   NULL,
                                   OPEN_EXISTING,
                                   0,
                                   NULL);
    if (FileHandleSource == INVALID_HANDLE_VALUE)
    {
        Status = STATUS_UNSUCCESSFUL;
        goto done;
    }
#endif

    Status = NtQueryInformationFile(FileHandleSource,
                                    &IoStatusBlock,
                                    &FileStandard,
                                    sizeof(FILE_STANDARD_INFORMATION),
                                    FileStandardInformation);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtQueryInformationFile failed: %x\n", Status);
        goto closesrc;
    }

    Status = NtQueryInformationFile(FileHandleSource,
                                    &IoStatusBlock,&FileBasic,
                                    sizeof(FILE_BASIC_INFORMATION),
                                    FileBasicInformation);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtQueryInformationFile failed: %x\n", Status);
        goto closesrc;
    }

    Status = NtCreateSection(&SourceFileSection,
                             SECTION_MAP_READ,
                             NULL,
                             NULL,
                             PAGE_READONLY,
                             SEC_COMMIT,
                             FileHandleSource);
    if (!NT_SUCCESS(Status))
    {
      DPRINT1("NtCreateSection failed: %x, %S\n", Status, SourceFileName);
      goto closesrc;
    }

    Status = NtMapViewOfSection(SourceFileSection,
                                NtCurrentProcess(),
                                &SourceFileMap,
                                0,
                                0,
                                NULL,
                                &SourceSectionSize,
                                ViewUnmap,
                                0,
                                PAGE_READONLY );
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtMapViewOfSection failed: %x, %S\n", Status, SourceFileName);
        goto closesrcsec;
    }

    RtlInitUnicodeString(&FileName,
                         DestinationFileName);

    InitializeObjectAttributes(&ObjectAttributes,
                               &FileName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = NtCreateFile(&FileHandleDest,
                          GENERIC_WRITE | SYNCHRONIZE,
                          &ObjectAttributes,
                          &IoStatusBlock,
                          NULL,
                          FILE_ATTRIBUTE_NORMAL,
                          0,
                          FILE_OVERWRITE_IF,
                          FILE_NO_INTERMEDIATE_BUFFERING |
                          FILE_SEQUENTIAL_ONLY |
                          FILE_SYNCHRONOUS_IO_NONALERT,
                          NULL,
                          0);
    if (!NT_SUCCESS(Status))
    {
        /* Open may have failed because the file to overwrite
         * is in readonly mode
         */
        if (Status == STATUS_ACCESS_DENIED)
        {
            FILE_BASIC_INFORMATION FileBasicInfo;

            /* Reattempt to open it with limited access */
            Status = NtCreateFile(&FileHandleDest,
                                  FILE_WRITE_ATTRIBUTES | SYNCHRONIZE,
                                  &ObjectAttributes,
                                  &IoStatusBlock,
                                  NULL,
                                  FILE_ATTRIBUTE_NORMAL,
                                  0,
                                  FILE_OPEN,
                                  FILE_NO_INTERMEDIATE_BUFFERING |
                                  FILE_SEQUENTIAL_ONLY |
                                  FILE_SYNCHRONOUS_IO_NONALERT,
                                  NULL,
                                  0);
            /* Fail for real if we cannot open it that way */
            if (!NT_SUCCESS(Status))
            {
                DPRINT1("NtCreateFile failed: %x, %wZ\n", Status, &FileName);
                goto unmapsrcsec;
            }

            /* Zero our basic info, just to set attributes */
            RtlZeroMemory(&FileBasicInfo, sizeof(FileBasicInfo));
            /* Reset attributes to normal, no read-only */
            FileBasicInfo.FileAttributes = FILE_ATTRIBUTE_NORMAL;
            /* We basically don't care about whether it succeed:
             * if it didn't, later open will fail
             */
            NtSetInformationFile(FileHandleDest, &IoStatusBlock, &FileBasicInfo,
                                 sizeof(FileBasicInfo), FileBasicInformation);

            /* Close file */
            NtClose(FileHandleDest);

            /* And re-attempt overwrite */
            Status = NtCreateFile(&FileHandleDest,
                                  GENERIC_WRITE | SYNCHRONIZE,
                                  &ObjectAttributes,
                                  &IoStatusBlock,
                                  NULL,
                                  FILE_ATTRIBUTE_NORMAL,
                                  0,
                                  FILE_OVERWRITE_IF,
                                  FILE_NO_INTERMEDIATE_BUFFERING |
                                  FILE_SEQUENTIAL_ONLY |
                                  FILE_SYNCHRONOUS_IO_NONALERT,
                                  NULL,
                                  0);
        }

        /* We failed */
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("NtCreateFile failed: %x, %wZ\n", Status, &FileName);
            goto unmapsrcsec;
        }
    }

    RegionSize = (ULONG)PAGE_ROUND_UP(FileStandard.EndOfFile.u.LowPart);
    IoStatusBlock.Status = 0;
    ByteOffset.QuadPart = 0ULL;
    Status = NtWriteFile(FileHandleDest,
                         NULL,
                         NULL,
                         NULL,
                         &IoStatusBlock,
                         SourceFileMap,
                         RegionSize,
                         &ByteOffset,
                         NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtWriteFile failed: %x:%x, iosb: %p src: %p, size: %x\n", Status, IoStatusBlock.Status, &IoStatusBlock, SourceFileMap, RegionSize);
        goto closedest;
    }

    /* Copy file date/time from source file */
    Status = NtSetInformationFile(FileHandleDest,
                                  &IoStatusBlock,
                                  &FileBasic,
                                  sizeof(FILE_BASIC_INFORMATION),
                                  FileBasicInformation);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtSetInformationFile failed: %x\n", Status);
        goto closedest;
    }

    /* shorten the file back to it's real size after completing the write */
    Status = NtSetInformationFile(FileHandleDest,
                                  &IoStatusBlock,
                                  &FileStandard.EndOfFile,
                                  sizeof(FILE_END_OF_FILE_INFORMATION),
                                  FileEndOfFileInformation);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtSetInformationFile failed: %x\n", Status);
    }

closedest:
    NtClose(FileHandleDest);

unmapsrcsec:
    NtUnmapViewOfSection(NtCurrentProcess(), SourceFileMap);

closesrcsec:
    NtClose(SourceFileSection);

closesrc:
    NtClose(FileHandleSource);

done:
    return Status;
}