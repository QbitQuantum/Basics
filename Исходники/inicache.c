NTSTATUS
IniCacheSave(
    PINICACHE Cache,
    PWCHAR FileName)
{
    UNICODE_STRING Name;
    PINICACHESECTION Section;
    PINICACHEKEY Key;
    ULONG BufferSize;
    PCHAR Buffer;
    PCHAR Ptr;
    ULONG Len;
    NTSTATUS Status;

    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    LARGE_INTEGER Offset;
    HANDLE FileHandle;


    /* Calculate required buffer size */
    BufferSize = 0;
    Section = Cache->FirstSection;
    while (Section != NULL)
    {
        BufferSize += (Section->Name ? wcslen(Section->Name) : 0)
                       + 4; /* "[]\r\n" */

        Key = Section->FirstKey;
        while (Key != NULL)
        {
            BufferSize += wcslen(Key->Name)
                          + (Key->Data ? wcslen(Key->Data) : 0)
                          + 3; /* "=\r\n" */
            Key = Key->Next;
        }

        Section = Section->Next;
        if (Section != NULL)
            BufferSize += 2; /* extra "\r\n" at end of each section */
    }
    BufferSize++; /* Null-terminator */

    DPRINT("BufferSize: %lu\n", BufferSize);

    /* Allocate file buffer */
    Buffer = (CHAR*)RtlAllocateHeap(ProcessHeap,
                                    HEAP_ZERO_MEMORY,
                                    BufferSize);
    if (Buffer == NULL)
    {
        DPRINT1("RtlAllocateHeap() failed\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Fill file buffer */
    Ptr = Buffer;
    Section = Cache->FirstSection;
    while (Section != NULL)
    {
        Len = sprintf(Ptr, "[%S]\r\n", Section->Name);
        Ptr += Len;

        Key = Section->FirstKey;
        while (Key != NULL)
        {
            Len = sprintf(Ptr, "%S=%S\r\n", Key->Name, Key->Data);
            Ptr += Len;
            Key = Key->Next;
        }

        Section = Section->Next;
        if (Section != NULL)
        {
            Len = sprintf(Ptr, "\r\n");
            Ptr += Len;
        }
    }

    /* Create ini file */
    RtlInitUnicodeString(&Name, FileName);

    InitializeObjectAttributes(&ObjectAttributes,
                               &Name,
                               0,
                               NULL,
                               NULL);

    Status = NtCreateFile(&FileHandle,
                          GENERIC_WRITE | SYNCHRONIZE,
                          &ObjectAttributes,
                          &IoStatusBlock,
                          NULL,
                          FILE_ATTRIBUTE_NORMAL,
                          0,
                          FILE_SUPERSEDE,
                          FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY,
                          NULL,
                          0);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtCreateFile() failed (Status %lx)\n", Status);
        RtlFreeHeap(ProcessHeap, 0, Buffer);
        return Status;
    }

    Offset.QuadPart = 0LL;
    Status = NtWriteFile(FileHandle,
                         NULL,
                         NULL,
                         NULL,
                         &IoStatusBlock,
                         Buffer,
                         BufferSize,
                         &Offset,
                         NULL);
    if (!NT_SUCCESS(Status))
    {
      DPRINT("NtWriteFile() failed (Status %lx)\n", Status);
      NtClose(FileHandle);
      RtlFreeHeap(ProcessHeap, 0, Buffer);
      return Status;
    }

    NtClose(FileHandle);

    RtlFreeHeap(ProcessHeap, 0, Buffer);

    return STATUS_SUCCESS;
}