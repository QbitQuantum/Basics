/**
  Extract filename from device path. The returned buffer is allocated using AllocateCopyPool.
  The caller is responsible for freeing the allocated buffer using FreePool().

  @param DevicePath       Device path.

  @return                 A new allocated string that represents the file name.

**/
CHAR16 *
ExtractFileNameFromDevicePath (
  IN   EFI_DEVICE_PATH_PROTOCOL *DevicePath
  )
{
  CHAR16          *String;
  CHAR16          *MatchString;
  CHAR16          *LastMatch;
  CHAR16          *FileName;
  UINTN           Length;

  ASSERT(DevicePath != NULL);

  String = UiDevicePathToStr(DevicePath);
  MatchString = String;
  LastMatch   = String;

  while(MatchString != NULL){
    LastMatch   = MatchString + 1;
    MatchString = StrStr(LastMatch,L"\\");
  }

  Length = StrLen(LastMatch);
  FileName = AllocateCopyPool ((Length + 1) * sizeof(CHAR16), LastMatch);
  *(FileName + Length) = 0;

  FreePool(String);

  return FileName;
}