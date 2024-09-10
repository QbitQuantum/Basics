VOID
EFIAPI
WinNtIoProtocolNotifyFunction (
  IN EFI_EVENT                Event,
  IN VOID                     *Context
  )
/*++

Routine Description:
  This function will log memory size data to data hub.

Arguments:
Event        - Event whose notification function is being invoked.
Context      - Pointer to the notification function's context.

Returns:
    EFI_STATUS.

--*/
{
  EFI_STATUS                      Status;
  EFI_MEMORY_SUBCLASS_DRIVER_DATA MemorySubClassData;
  EFI_DATA_RECORD_HEADER          *Record;
  EFI_SUBCLASS_TYPE1_HEADER       *DataHeader;
  UINTN                           HandleCount;
  UINTN                           HandleIndex;
  UINT64                          MonotonicCount;
  BOOLEAN                         RecordFound;
  EFI_HANDLE                      *HandleBuffer;
  EFI_WIN_NT_IO_PROTOCOL          *WinNtIo;
  EFI_DATA_HUB_PROTOCOL           *DataHub;
  UINT64                          TotalMemorySize;

  DataHub         = NULL;
  MonotonicCount  = 0;
  RecordFound     = FALSE;

  //
  // Retrieve the list of all handles from the handle database.
  //
  Status = gBS->LocateHandleBuffer (
                  AllHandles,
                  &gEfiWinNtIoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }
  //
  // Locate DataHub protocol.
  //
  Status = gBS->LocateProtocol (&gEfiDataHubProtocolGuid, NULL, &DataHub);
  if (EFI_ERROR (Status)) {
    return ;
  }
  //
  // Search the Handle array to find the meory size information.
  //
  for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
    Status = gBS->OpenProtocol (
                    HandleBuffer[HandleIndex],
                    &gEfiWinNtIoProtocolGuid,
                    &WinNtIo,
                    Context,
                    NULL,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (EFI_ERROR (Status)) {
      continue;
    }

    if ((WinNtIo->WinNtThunk->Signature == EFI_WIN_NT_THUNK_PROTOCOL_SIGNATURE) &&
        EfiCompareGuid (WinNtIo->TypeGuid, &gEfiWinNtMemoryGuid)
          ) {
      //
      // Check if this record has been stored in data hub.
      //
      do {
        Status = DataHub->GetNextRecord (DataHub, &MonotonicCount, NULL, &Record);
        if (Record->DataRecordClass == EFI_DATA_RECORD_CLASS_DATA) {
          DataHeader = (EFI_SUBCLASS_TYPE1_HEADER *) (Record + 1);
          if (EfiCompareGuid (&Record->DataRecordGuid, &gProcessorSubClassName) &&
              (DataHeader->RecordType == EFI_MEMORY_ARRAY_START_ADDRESS_RECORD_NUMBER)
              ) {
            RecordFound = TRUE;
          }
        }
      } while (MonotonicCount != 0);

      if (RecordFound) {
        RecordFound = FALSE;
        continue;
      }
      //
      // Initialize data record.
      //
      MemorySubClassData.Header.Instance    = 1;
      MemorySubClassData.Header.SubInstance = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;
      MemorySubClassData.Header.RecordType  = EFI_MEMORY_ARRAY_START_ADDRESS_RECORD_NUMBER;

      TotalMemorySize                       = (UINT64) Atoi (WinNtIo->EnvString);

      MemorySubClassData.Record.ArrayStartAddress.MemoryArrayStartAddress               = 0;
      MemorySubClassData.Record.ArrayStartAddress.MemoryArrayEndAddress                 = LShiftU64 (TotalMemorySize, 20) - 1;
      MemorySubClassData.Record.ArrayStartAddress.PhysicalMemoryArrayLink.ProducerName  = gMemoryProducerGuid;
      MemorySubClassData.Record.ArrayStartAddress.PhysicalMemoryArrayLink.Instance      = 1;
      MemorySubClassData.Record.ArrayStartAddress.PhysicalMemoryArrayLink.SubInstance = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;
      MemorySubClassData.Record.ArrayStartAddress.MemoryArrayPartitionWidth = 0;

      //
      // Store memory size data record to data hub.
      //
      Status = DataHub->LogData (
                          DataHub,
                          &gEfiMemorySubClassGuid,
                          &gMemoryProducerGuid,
                          EFI_DATA_RECORD_CLASS_DATA,
                          &MemorySubClassData,
                          sizeof (EFI_SUBCLASS_TYPE1_HEADER) + sizeof (EFI_MEMORY_ARRAY_START_ADDRESS)
                          );
    }

    gBS->CloseProtocol (
          HandleBuffer[HandleIndex],
          &gEfiWinNtIoProtocolGuid,
          Context,
          NULL
          );
  }
}