/**

  Check whether current FileName point to a valid
  Efi Image File.

  @param FileName  File need to be checked.

  @retval TRUE  Is Efi Image
  @retval FALSE Not a valid Efi Image

**/
BOOLEAN
LibIsSupportedFileType (
  IN UINT16  *FileName
  )
{
  CHAR16     *InputFileType;
  CHAR16     *TmpStr;
  BOOLEAN    IsSupported;

  if (gFileExplorerPrivate.FileType == NULL) {
    return TRUE;
  }

  InputFileType = LibGetTypeFromName (FileName);
  //
  // If the file not has *.* style, always return TRUE.
  //
  if (InputFileType == NULL) {
    return TRUE;
  }

  TmpStr = AllocateCopyPool (StrSize (InputFileType), InputFileType);
  ASSERT(TmpStr != NULL);
  LibToLowerString(TmpStr);

  IsSupported = (StrStr (gFileExplorerPrivate.FileType, TmpStr) == NULL ? FALSE : TRUE);

  FreePool (TmpStr);
  return IsSupported;
}