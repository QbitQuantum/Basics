/**

  Convert the UEFI DevicePath to full text representation with DevPathToText,
  then match the UEFI device path fragment in Translated against it.

  @param[in] Translated        UEFI device path fragment, translated from
                               OpenFirmware format, to search for.

  @param[in] TranslatedLength  The length of Translated in CHAR16's.

  @param[in] DevicePath        Boot option device path whose textual rendering
                               to search in.

  @param[in] DevPathToText  Binary-to-text conversion protocol for DevicePath.


  @retval TRUE   If Translated was found at the beginning of DevicePath after
                 converting the latter to text.

  @retval FALSE  If DevicePath was NULL, or it could not be converted, or there
                 was no match.

**/
STATIC
BOOLEAN
Match (
  IN  CONST CHAR16                           *Translated,
  IN  UINTN                                  TranslatedLength,
  IN  CONST EFI_DEVICE_PATH_PROTOCOL         *DevicePath
  )
{
  CHAR16  *Converted;
  BOOLEAN Result;

  Converted = ConvertDevicePathToText (
                DevicePath,
                FALSE, // DisplayOnly
                FALSE  // AllowShortcuts
                );
  if (Converted == NULL) {
    return FALSE;
  }

  //
  // Attempt to expand any relative UEFI device path starting with HD() to an
  // absolute device path first. The logic imitates BdsLibBootViaBootOption().
  // We don't have to free the absolute device path,
  // BdsExpandPartitionPartialDevicePathToFull() has internal caching.
  //
  Result = FALSE;
  if (DevicePathType (DevicePath) == MEDIA_DEVICE_PATH &&
      DevicePathSubType (DevicePath) == MEDIA_HARDDRIVE_DP) {
    EFI_DEVICE_PATH_PROTOCOL *AbsDevicePath;
    CHAR16                   *AbsConverted;

    AbsDevicePath = BdsExpandPartitionPartialDevicePathToFull (
                      (HARDDRIVE_DEVICE_PATH *) DevicePath);
    if (AbsDevicePath == NULL) {
      goto Exit;
    }
    AbsConverted = ConvertDevicePathToText (AbsDevicePath, FALSE, FALSE);
    if (AbsConverted == NULL) {
      goto Exit;
    }
    DEBUG ((DEBUG_VERBOSE,
      "%a: expanded relative device path \"%s\" for prefix matching\n",
      __FUNCTION__, Converted));
    FreePool (Converted);
    Converted = AbsConverted;
  }

  //
  // Is Translated a prefix of Converted?
  //
  Result = (BOOLEAN)(StrnCmp (Converted, Translated, TranslatedLength) == 0);
  DEBUG ((
    DEBUG_VERBOSE,
    "%a: against \"%s\": %a\n",
    __FUNCTION__,
    Converted,
    Result ? "match" : "no match"
    ));
Exit:
  FreePool (Converted);
  return Result;
}