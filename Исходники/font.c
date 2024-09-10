NTSTATUS ExtractFont(UINT32 CodePage, PUCHAR FontBitField)
{
    BOOLEAN            bFoundFile = FALSE;
    HANDLE             Handle;
    NTSTATUS           Status;
    CHAR               FileName[20];
    IO_STATUS_BLOCK    IoStatusBlock;
    OBJECT_ATTRIBUTES  ObjectAttributes;
    UNICODE_STRING     LinkName;
    UNICODE_STRING     SourceName;
    CFHEADER           CabFileHeader;
    CFFILE             CabFile;
    ULONG              CabFileOffset = 0;
    LARGE_INTEGER      ByteOffset;
    WCHAR              SourceBuffer[MAX_PATH] = {L'\0'};
    ULONG              ReadCP;

    if(KeGetCurrentIrql() != PASSIVE_LEVEL)
        return STATUS_INVALID_DEVICE_STATE;

    RtlInitUnicodeString(&LinkName,
                         L"\\SystemRoot");

    InitializeObjectAttributes(&ObjectAttributes,
                               &LinkName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = ZwOpenSymbolicLinkObject(&Handle,
                                      SYMBOLIC_LINK_ALL_ACCESS,
                                      &ObjectAttributes);

    if (!NT_SUCCESS(Status))
        return(Status);

    SourceName.Length = 0;
    SourceName.MaximumLength = MAX_PATH * sizeof(WCHAR);
    SourceName.Buffer = SourceBuffer;

    Status = ZwQuerySymbolicLinkObject(Handle,
                                      &SourceName,
                                      NULL);
    ZwClose(Handle);

    Status = RtlAppendUnicodeToString(&SourceName, L"\\vgafonts.cab");
    InitializeObjectAttributes(&ObjectAttributes, &SourceName,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL, NULL);

    Status = ZwCreateFile(&Handle,
                          GENERIC_READ,
                          &ObjectAttributes, &IoStatusBlock, NULL,
                          FILE_ATTRIBUTE_NORMAL,
                          0,
                          FILE_OPEN, 
                          FILE_SYNCHRONOUS_IO_NONALERT,
                          NULL, 0);

    ByteOffset.LowPart = ByteOffset.HighPart = 0;

    if(NT_SUCCESS(Status))
    {
        Status = ZwReadFile(Handle, NULL, NULL, NULL, &IoStatusBlock,
                            &CabFileHeader, sizeof(CabFileHeader), &ByteOffset, NULL);

        if(NT_SUCCESS(Status))
        {
            if(CabFileHeader.Signature == CAB_SIGNATURE)
            {
                // We have a valid CAB file!
                // Read the file table now and decrement the file count on every file. When it's zero, we read the complete table.
                ByteOffset.LowPart = CabFileHeader.FileTableOffset;

                while(CabFileHeader.FileCount)
                {
                    Status = ZwReadFile(Handle, NULL, NULL, NULL, &IoStatusBlock,
                                        &CabFile, sizeof(CabFile), &ByteOffset, NULL);

                    if(NT_SUCCESS(Status))
                    {
                        ByteOffset.LowPart += sizeof(CabFile);

                        // We assume here that the file name is max. 19 characters (+ 1 NULL character) long.
                        // This should be enough for our purpose.
                        Status = ZwReadFile(Handle, NULL, NULL, NULL, &IoStatusBlock,
                                            FileName, sizeof(FileName), &ByteOffset, NULL);

                        if(NT_SUCCESS(Status))
                        {
                            if(!bFoundFile)
                            {
                                Status = RtlCharToInteger(FileName, 0, &ReadCP);
                                if (NT_SUCCESS(Status) && ReadCP == CodePage)
                                {
                                    // We got the correct file.
                                    // Save the offset and loop through the rest of the file table to find the position, where the actual data starts.
                                    CabFileOffset = CabFile.FileOffset;
                                    bFoundFile = TRUE;
                                }
                            }

                            ByteOffset.LowPart += strlen(FileName) + 1;
                        }
                    }

                    CabFileHeader.FileCount--;
                }

                // 8 = Size of a CFFOLDER structure (see cabman). As we don't need the values of that structure, just increase the offset here.
                ByteOffset.LowPart += 8;
                ByteOffset.LowPart += CabFileOffset;

                // ByteOffset now contains the offset of the actual data, so we can read the RAW font
                Status = ZwReadFile(Handle, NULL, NULL, NULL, &IoStatusBlock,
                                    FontBitField, 2048, &ByteOffset, NULL);
                ZwClose(Handle);
                return STATUS_SUCCESS;
            }
            else
            {
                DPRINT1("Error: CAB signature is missing!\n");
                Status = STATUS_UNSUCCESSFUL;
            }
        }
        else
            DPRINT1("Error: Cannot read from file\n");

        ZwClose(Handle);
        return Status;
    }
    else
    {
        DPRINT1("Error: Cannot open vgafonts.cab\n");
        return Status;
    }
}