/**
 *  get the device path and file path based on the loaded image name.
 *  @param Name the iamge file name such as framework.efi
 *  @param DevicePath the Device path of this file is loaded from.
 *  @param FilePath the file path of this file.
 *  @return EFI_SUCCESS the device path and file path was found successfully.
 *  @return EFI_INVALID_PARAMETER the Parameter is invalid
 */
EFI_STATUS
GetFilePathByName (
  IN CHAR16                       *Name,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **FilePath
  )
{
  EFI_STATUS                  Status;
  UINTN                       Index;
  EFI_LOADED_IMAGE_PROTOCOL   *Image;
  EFI_HANDLE                  *HandleBuffer;
  UINTN                       HandleNum;
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL    *TempDeviceNode;
  CHAR16                      *TempFilePath;
  CHAR16                      FullFilePath[MAX_FILE_PATH];
  BOOLEAN                     Found;

  //
  //verify parameters.
  //
  if (Name == NULL || DevicePath == NULL || FilePath == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (StrLen (Name) == 0) {
    return EFI_INVALID_PARAMETER;
  }

  //
  //get all the load image protocol instance.
  //
  Found        = FALSE;
  HandleNum    = 0;
  HandleBuffer = NULL;

  Status  = LibLocateHandle(
                  ByProtocol,
                  &gEfiLoadedImageProtocolGuid,
                  NULL,
                  &HandleNum,
                  &HandleBuffer
                  );

  if (EFI_ERROR(Status) || HandleNum == 0) {
    return EFI_ABORTED;
  }

  //
  //for all the LoadedImage protocol found the image file name to match the
  //given file name.
  //
  TempDevicePath = NULL;
  for (Index = 0; Index < HandleNum; Index ++ ) {

    FullFilePath[0] = '\0';

    //
    // Get the image instance from the image handle
    //
    Status = tBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gEfiLoadedImageProtocolGuid,
                     &Image
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }

    if (Image->FilePath == NULL) {
      continue;
    }

    //
    //get the file path and parse the file name.
    //
    TempDevicePath = UnpackDevicePath (Image->FilePath);
    TempFilePath   = NULL;
    TempDeviceNode = TempDevicePath;

    while (!IsDevicePathEnd(TempDeviceNode)) {
      if ((DevicePathType(TempDeviceNode) == MEDIA_DEVICE_PATH) &&
          (DevicePathSubType(TempDeviceNode) == MEDIA_FILEPATH_DP)) {
        StrCat(FullFilePath, L"\\");
        TempFilePath = ((FILEPATH_DEVICE_PATH *)TempDeviceNode)->PathName;

        if (StrLen (TempFilePath) == 1 && TempFilePath[0] == '\\') {
          //
          //if this the "\\" path then we need not append it,or else there will
          //have 3 '\\' in the device path.
          //
          ;
        } else {
          StrCat(FullFilePath, TempFilePath);
        }
      }
      TempDeviceNode = NextDevicePathNode (TempDeviceNode);
    }

    tBS->FreePool (TempDevicePath);

    if (StrLen (FullFilePath) <= StrLen (Name)) {
      continue;
    }

    TempFilePath = FullFilePath + (StrLen(FullFilePath) - StrLen(Name));

    if ((*(TempFilePath - 1)) == L'\\' && StriCmp (TempFilePath, Name) == 0) {

      TempFilePath[0] = '\0';
      //
      // Get the device instance from the device handle
      //
      Status = tBS->HandleProtocol (
                     Image->DeviceHandle,
                     &gEfiDevicePathProtocolGuid,
                     &TempDevicePath
                     );
      if (EFI_ERROR(Status)) {
        return Status;
      }

      Found = TRUE;
      break;
    }
  }

  if (HandleBuffer != NULL) {
    tBS->FreePool (HandleBuffer);
  }

  if (!Found) {
    return EFI_NOT_FOUND;
  }


  //
  // If the file path is only a root directory "\\", remove it
  //
  if (StrLen(FullFilePath) > 1) {
    if (FullFilePath[StrLen(FullFilePath) - 1] == L'\\') {
     FullFilePath[StrLen(FullFilePath) - 1] = '\0';
    }
  }

  *DevicePath = DuplicateDevicePath (TempDevicePath);
  if (*DevicePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //skip the first '\\'.
  //
  *FilePath = StrDuplicate (FullFilePath + 1);
  if (*FilePath == NULL) {
    tBS->FreePool (*DevicePath);
    *DevicePath = NULL;
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;

}