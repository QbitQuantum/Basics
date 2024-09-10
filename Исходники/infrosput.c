NTSTATUS
InfWriteFile(HINF InfHandle,
             PUNICODE_STRING FileName,
             PUNICODE_STRING HeaderComment)
{
  OBJECT_ATTRIBUTES ObjectAttributes;
  IO_STATUS_BLOCK IoStatusBlock;
  HANDLE FileHandle;
  NTSTATUS Status;
  INFSTATUS InfStatus;
  PWCHAR Buffer;
  ULONG BufferSize;
  PWCHAR HeaderBuffer;
  ULONG HeaderBufferSize;
  UINT Index;

  InfStatus = InfpBuildFileBuffer((PINFCACHE) InfHandle, &Buffer, &BufferSize);
  if (! INF_SUCCESS(InfStatus))
    {
      DPRINT("Failed to create buffer (Status 0x%lx)\n", InfStatus);
      return InfStatus;
    }

  /* Open the inf file */
  InitializeObjectAttributes(&ObjectAttributes,
                             FileName,
                             0,
                             NULL,
                             NULL);

  Status = NtOpenFile(&FileHandle,
                      GENERIC_WRITE | SYNCHRONIZE,
                      &ObjectAttributes,
                      &IoStatusBlock,
                      0,
                      FILE_SYNCHRONOUS_IO_NONALERT | FILE_NON_DIRECTORY_FILE);
  if (!INF_SUCCESS(Status))
    {
      DPRINT1("NtOpenFile() failed (Status %lx)\n", Status);
      FREE(Buffer);
      return Status;
    }

  DPRINT("NtOpenFile() successful\n");

  if (NULL != HeaderComment && 0 != HeaderComment->Length)
    {
      /* This is just a comment header, don't abort on errors here */
      HeaderBufferSize = HeaderComment->Length + 7 * sizeof(WCHAR);
      HeaderBuffer = MALLOC(HeaderBufferSize);
      if (NULL != HeaderBuffer)
        {
          strcpyW(HeaderBuffer, L"; ");
          for (Index = 0; Index < HeaderComment->Length / sizeof(WCHAR); Index++)
            {
              HeaderBuffer[2 + Index] = HeaderComment->Buffer[Index];
            }
          strcpyW(HeaderBuffer + (2 + HeaderComment->Length / sizeof(WCHAR)),
                  L"\r\n\r\n");
          NtWriteFile(FileHandle,
                      NULL,
                      NULL,
                      NULL,
                      &IoStatusBlock,
                      HeaderBuffer,
                      HeaderBufferSize,
                      NULL,
                      NULL);
          FREE(HeaderBuffer);
        }
    }

  /* Write main contents */
  Status = NtWriteFile(FileHandle,
                       NULL,
                       NULL,
                       NULL,
                       &IoStatusBlock,
                       Buffer,
                       BufferSize,
                       NULL,
                       NULL);

  NtClose(FileHandle);
  FREE(Buffer);

  if (!INF_SUCCESS(Status))
    {
      DPRINT1("NtWriteFile() failed (Status %lx)\n", Status);
      FREE(Buffer);
      return(Status);
    }

  return STATUS_SUCCESS;
}