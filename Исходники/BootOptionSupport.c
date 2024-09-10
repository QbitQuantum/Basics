EFI_STATUS
BdsLoadOptionFileSystemUpdateDevicePath (
  IN EFI_DEVICE_PATH            *OldDevicePath,
  IN CHAR16*                    FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL  **NewDevicePath
  )
{
  EFI_STATUS  Status;
  CHAR16      BootFilePath[BOOT_DEVICE_FILEPATH_MAX];
  UINTN       BootFilePathSize;
  FILEPATH_DEVICE_PATH* EndingDevicePath;
  FILEPATH_DEVICE_PATH* FilePathDevicePath;
  EFI_DEVICE_PATH*  DevicePath;

  DevicePath = DuplicateDevicePath (OldDevicePath);

  EndingDevicePath = (FILEPATH_DEVICE_PATH*)GetLastDevicePathNode (DevicePath);

  Print(L"File path of the %s: ", FileName);
  StrnCpy (BootFilePath, EndingDevicePath->PathName, BOOT_DEVICE_FILEPATH_MAX);
  Status = EditHIInputStr (BootFilePath, BOOT_DEVICE_FILEPATH_MAX);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BootFilePathSize = StrSize(BootFilePath);
  if (BootFilePathSize == 2) {
    *NewDevicePath = NULL;
    return EFI_NOT_FOUND;
  }

  // Create the FilePath Device Path node
  FilePathDevicePath = (FILEPATH_DEVICE_PATH*)AllocatePool(SIZE_OF_FILEPATH_DEVICE_PATH + BootFilePathSize);
  if (NULL == FilePathDevicePath)
  {
    return EFI_INVALID_PARAMETER;
  }
  FilePathDevicePath->Header.Type = MEDIA_DEVICE_PATH;
  FilePathDevicePath->Header.SubType = MEDIA_FILEPATH_DP;
  SetDevicePathNodeLength (FilePathDevicePath, SIZE_OF_FILEPATH_DEVICE_PATH + BootFilePathSize);
  CopyMem (FilePathDevicePath->PathName, BootFilePath, BootFilePathSize);

  // Generate the new Device Path by replacing the last node by the updated node
  SetDevicePathEndNode (EndingDevicePath);
  *NewDevicePath = AppendDevicePathNode (DevicePath, (CONST EFI_DEVICE_PATH_PROTOCOL *)FilePathDevicePath);
  FreePool(DevicePath);

  return EFI_SUCCESS;
}