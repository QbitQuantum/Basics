NTSTATUS
NTAPI
CmpOpenHiveFiles(IN PCUNICODE_STRING BaseName,
                 IN PCWSTR Extension OPTIONAL,
                 OUT PHANDLE Primary,
                 OUT PHANDLE Log,
                 OUT PULONG PrimaryDisposition,
                 OUT PULONG LogDisposition,
                 IN BOOLEAN CreateAllowed,
                 IN BOOLEAN MarkAsSystemHive,
                 IN BOOLEAN NoBuffering,
                 OUT PULONG ClusterSize OPTIONAL)
{
    HANDLE EventHandle;
    PKEVENT Event;
    NTSTATUS Status;
    UNICODE_STRING FullName, ExtensionName;
    PWCHAR NameBuffer;
    USHORT Length;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    ULONG AttributeFlags, ShareMode, DesiredAccess, CreateDisposition, IoFlags;
    USHORT CompressionState;
    FILE_STANDARD_INFORMATION FileInformation;
    FILE_FS_SIZE_INFORMATION FsSizeInformation;

    /* Create event */
    Status = CmpCreateEvent(NotificationEvent, &EventHandle, &Event);
    if (!NT_SUCCESS(Status)) return Status;

    /* Initialize the full name */
    RtlInitEmptyUnicodeString(&FullName, NULL, 0);
    Length = BaseName->Length;

    /* Check if we have an extension */
    if (Extension)
    {
        /* Update the name length */
        Length += (USHORT)wcslen(Extension) * sizeof(WCHAR) + sizeof(UNICODE_NULL);

        /* Allocate the buffer for the full name */
        NameBuffer = ExAllocatePoolWithTag(PagedPool, Length, TAG_CM);
        if (!NameBuffer)
        {
            /* Fail */
            ObDereferenceObject(Event);
            ZwClose(EventHandle);
            return STATUS_NO_MEMORY;
        }

        /* Build the full name */
        FullName.Buffer = NameBuffer;
        FullName.MaximumLength = Length;
        RtlAppendUnicodeStringToString(&FullName, BaseName);
    }
    else
    {
        /* The base name is the full name */
        FullName = *BaseName;
        NameBuffer = NULL;
    }

    /* Initialize the attributes */
    InitializeObjectAttributes(&ObjectAttributes,
                               &FullName,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);

    /* Check if we can create the hive */
    if ((CreateAllowed) && !(CmpShareSystemHives))
    {
        /* Open only or create */
        CreateDisposition = FILE_OPEN_IF;
    }
    else
    {
        /* Open only */
        CreateDisposition = FILE_OPEN;
    }

    /* Setup the flags */
    // FIXME : FILE_OPEN_FOR_BACKUP_INTENT is unimplemented and breaks 3rd stage boot
    IoFlags = //FILE_OPEN_FOR_BACKUP_INTENT |
              FILE_NO_COMPRESSION |
              FILE_RANDOM_ACCESS |
              (NoBuffering ? FILE_NO_INTERMEDIATE_BUFFERING : 0);

    /* Set share and access modes */
    if ((CmpMiniNTBoot) && (CmpShareSystemHives))
    {
        /* We're on Live CD or otherwise sharing */
        DesiredAccess = FILE_READ_DATA;
        ShareMode = FILE_SHARE_READ;
    }
    else
    {
        /* We want to write exclusively */
        ShareMode = 0;
        DesiredAccess = FILE_READ_DATA | FILE_WRITE_DATA;
    }

    /* Default attributes */
    AttributeFlags = FILE_ATTRIBUTE_NORMAL;

    /* Now create the file */
    Status = ZwCreateFile(Primary,
                          DesiredAccess | SYNCHRONIZE,
                          &ObjectAttributes,
                          &IoStatusBlock,
                          NULL,
                          AttributeFlags,
                          ShareMode,
                          CreateDisposition,
                          FILE_SYNCHRONOUS_IO_NONALERT | IoFlags,
                          NULL,
                          0);
    /* Check if anything failed until now */
    if (!NT_SUCCESS(Status))
    {
        /* Close handles and free buffers */
        if (NameBuffer) ExFreePoolWithTag(NameBuffer, TAG_CM);
        ObDereferenceObject(Event);
        ZwClose(EventHandle);
        DPRINT1("ZwCreateFile failed : %lx.\n", Status);
        *Primary = NULL;
        return Status;
    }
                          
    if (MarkAsSystemHive)
    {
        /* We opened it, mark it as a system hive */
        Status = ZwFsControlFile(*Primary,
                                 EventHandle,
                                 NULL,
                                 NULL,
                                 &IoStatusBlock,
                                 FSCTL_MARK_AS_SYSTEM_HIVE,
                                 NULL,
                                 0,
                                 NULL,
                                 0);
        if (Status == STATUS_PENDING)
        {
            /* Wait for completion */
            KeWaitForSingleObject(Event,
                                  Executive,
                                  KernelMode,
                                  FALSE,
                                  NULL);
            Status = IoStatusBlock.Status;
        }

        /* If we don't support it, ignore the failure */
        if (Status == STATUS_INVALID_DEVICE_REQUEST) Status = STATUS_SUCCESS;

        if (!NT_SUCCESS(Status))
        {
            /* Close handles and free buffers */
            if (NameBuffer) ExFreePoolWithTag(NameBuffer, TAG_CM);
            ObDereferenceObject(Event);
            ZwClose(EventHandle);
            ZwClose(*Primary);
            *Primary = NULL;
            return Status;
        }
    }

    /* Disable compression */
    CompressionState = 0;
    Status = ZwFsControlFile(*Primary,
                             EventHandle,
                             NULL,
                             NULL,
                             &IoStatusBlock,
                             FSCTL_SET_COMPRESSION,
                             &CompressionState,
                             sizeof(CompressionState),
                             NULL,
                             0);
    if (Status == STATUS_PENDING)
    {
        /* Wait for completion */
        KeWaitForSingleObject(Event,
                              Executive,
                              KernelMode,
                              FALSE,
                              NULL);
    }

    /* Get the disposition */
    *PrimaryDisposition = (ULONG)IoStatusBlock.Information;
    if (IoStatusBlock.Information != FILE_CREATED)
    {
        /* Check how large the file is */
        Status = ZwQueryInformationFile(*Primary,
                                        &IoStatusBlock,
                                        &FileInformation,
                                        sizeof(FileInformation),
                                        FileStandardInformation);
        if (NT_SUCCESS(Status))
        {
            /* Check if it's 0 bytes */
            if (!FileInformation.EndOfFile.QuadPart)
            {
                /* Assume it's a new file */
                *PrimaryDisposition = FILE_CREATED;
            }
        }
    }

    /* Check if the caller wants cluster size returned */
    if (ClusterSize)
    {
        /* Query it */
        Status = ZwQueryVolumeInformationFile(*Primary,
                                              &IoStatusBlock,
                                              &FsSizeInformation,
                                              sizeof(FsSizeInformation),
                                              FileFsSizeInformation);
        if (!NT_SUCCESS(Status))
        {
            /* Close handles and free buffers */
            if (NameBuffer) ExFreePoolWithTag(NameBuffer, TAG_CM);
            ObDereferenceObject(Event);
            ZwClose(EventHandle);
            return Status;
        }

        /* Check if the sector size is invalid */
        if (FsSizeInformation.BytesPerSector > HBLOCK_SIZE)
        {
            /* Close handles and free buffers */
            if (NameBuffer) ExFreePoolWithTag(NameBuffer, TAG_CM);
            ObDereferenceObject(Event);
            ZwClose(EventHandle);
            return STATUS_CANNOT_LOAD_REGISTRY_FILE;
        }

        /* Return cluster size */
        *ClusterSize = max(1, FsSizeInformation.BytesPerSector / HSECTOR_SIZE);
    }

    /* Check if we don't need to create a log file */
    if (!Extension)
    {
        /* We're done, close handles */
        ObDereferenceObject(Event);
        ZwClose(EventHandle);
        return STATUS_SUCCESS;
    }

    /* Check if we can create the hive */
    CreateDisposition = CmpShareSystemHives ? FILE_OPEN : FILE_OPEN_IF;
    if (*PrimaryDisposition == FILE_CREATED)
    {
        /* Over-write the existing log file, since this is a new hive */
        CreateDisposition = FILE_SUPERSEDE;
    }

    /* Setup the name */
    RtlInitUnicodeString(&ExtensionName, Extension);
    RtlAppendUnicodeStringToString(&FullName, &ExtensionName);

    /* Initialize the attributes */
    InitializeObjectAttributes(&ObjectAttributes,
                               &FullName,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);

    /* Setup the flags */
    IoFlags = FILE_NO_COMPRESSION | FILE_NO_INTERMEDIATE_BUFFERING;

    /* Check if this is a log file */
    if (!_wcsnicmp(Extension, L".log", 4))
    {
        /* Hide log files */
        AttributeFlags |= FILE_ATTRIBUTE_HIDDEN;
    }

    /* Now create the file */
    Status = ZwCreateFile(Log,
                          DesiredAccess,
                          &ObjectAttributes,
                          &IoStatusBlock,
                          NULL,
                          AttributeFlags,
                          ShareMode,
                          CreateDisposition,
                          IoFlags,
                          NULL,
                          0);
    if ((NT_SUCCESS(Status)) && (MarkAsSystemHive))
    {
        /* We opened it, mark it as a system hive */
        Status = ZwFsControlFile(*Log,
                                 EventHandle,
                                 NULL,
                                 NULL,
                                 &IoStatusBlock,
                                 FSCTL_MARK_AS_SYSTEM_HIVE,
                                 NULL,
                                 0,
                                 NULL,
                                 0);
        if (Status == STATUS_PENDING)
        {
            /* Wait for completion */
            KeWaitForSingleObject(Event,
                                  Executive,
                                  KernelMode,
                                  FALSE,
                                  NULL);
            Status = IoStatusBlock.Status;
        }

        /* If we don't support it, ignore the failure */
        if (Status == STATUS_INVALID_DEVICE_REQUEST) Status = STATUS_SUCCESS;

        /* If we failed, close the handle */
        if (!NT_SUCCESS(Status)) ZwClose(*Log);
    }

    /* Check if anything failed until now */
    if (!NT_SUCCESS(Status))
    {
        /* Clear the handle */
        *Log = NULL;
    }
    else
    {
        /* Disable compression */
        Status = ZwFsControlFile(*Log,
                                 EventHandle,
                                 NULL,
                                 NULL,
                                 &IoStatusBlock,
                                 FSCTL_SET_COMPRESSION,
                                 &CompressionState,
                                 sizeof(CompressionState),
                                 NULL,
                                 0);
        if (Status == STATUS_PENDING)
        {
            /* Wait for completion */
            KeWaitForSingleObject(Event,
                                  Executive,
                                  KernelMode,
                                  FALSE,
                                  NULL);
        }

        /* Return the disposition */
        *LogDisposition = (ULONG)IoStatusBlock.Information;
    }

    /* We're done, close handles and free buffers */
    if (NameBuffer) ExFreePoolWithTag(NameBuffer, TAG_CM);
    ObDereferenceObject(Event);
    ZwClose(EventHandle);
    return STATUS_SUCCESS;
}