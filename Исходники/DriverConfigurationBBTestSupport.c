EFI_STATUS
GatherConfigHandles (
  IN EFI_HANDLE         SupportHandle,
  OUT UINTN             *NoConfigHandles,
  OUT EFI_HANDLE        **ConfigHandleBuffer
  )
{
  EFI_STATUS                          Status;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  CHAR16                              *FilePath;
  CHAR16                              *ConfigFilePath;
  EFI_INI_FILE_HANDLE                 IniFile;
  UINT32                              Order;
  UINT32                              OrderNum;
  CHAR16                              Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  UINTN                               Index;
  UINTN                               NoHandles;
  EFI_HANDLE                          *HandleBuffer;
  CHAR16                              *DevicePathStr;

  //
  // Locate test profile library protocol
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   &ProfileLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &DevicePath,
                         &FilePath
                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ConfigFilePath = PoolPrint (L"%s\\%s", FilePath, EFI_SCT_FILE_DEVICE_CONFIG);
  if (ConfigFilePath == NULL) {
    gtBS->FreePool (DevicePath);
    gtBS->FreePool (FilePath);
    return EFI_OUT_OF_RESOURCES;
  }

  gtBS->FreePool (FilePath);

  //
  // Open the device configuration file
  //
  Status = ProfileLib->EfiIniOpen (
                         ProfileLib,
                         DevicePath,
                         ConfigFilePath,
                         &IniFile
                         );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (DevicePath);
    gtBS->FreePool (ConfigFilePath);
    return Status;
  }

  gtBS->FreePool (DevicePath);
  gtBS->FreePool (ConfigFilePath);

  //
  // Get the number of device configuration data
  //
  Status = DeviceConfigGetOrderNum (
             IniFile,
             &OrderNum
             );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    return Status;
  }

  //
  // Get all handles
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    return Status;
  }

  //
  // Initialize the output variables
  //
  *NoConfigHandles = 0;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_HANDLE) * NoHandles,
                   (VOID **)ConfigHandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    gtBS->FreePool (HandleBuffer);
    return Status;
  }

  //
  // Scan each device configuration data
  //
  for (Order = 0; Order < OrderNum; Order++) {
    //
    // Here, need to check the setting in configuration file and find the
    // matched device path in the system
    //
    Status = DeviceConfigGetString (
               IniFile,
               Order,
               L"DriverConfiguration",
               Buffer
               );
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (StriCmp (Buffer, L"Yes") != 0) {
      continue;
    }

    Status = DeviceConfigGetString (
               IniFile,
               Order,
               L"DevicePath",
               Buffer
               );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Search the matched device path in the system
    //
    for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gEfiDevicePathProtocolGuid,
                       &DevicePath
                       );
      if (EFI_ERROR (Status)) {
        continue;
      }

      DevicePathStr = DevicePathToStr (DevicePath);

      if (StrCmp (Buffer, DevicePathStr) == 0) {
        gtBS->FreePool (DevicePathStr);
        break;
      }

      gtBS->FreePool (DevicePathStr);
    }

    //
    // Found it?
    //
    if (Index < NoHandles) {
      InsertChildHandles (
        NoConfigHandles,
        *ConfigHandleBuffer,
        HandleBuffer[Index],
        FALSE                       // Only for the handles on this controller
        );
    }
  }

  //
  // Free resources
  //
  gtBS->FreePool (HandleBuffer);

  //
  // Close the device configuration file
  //
  ProfileLib->EfiIniClose (ProfileLib, IniFile);

  //
  // Done
  //
  return EFI_SUCCESS;
}