/**
  Get a human readable name for an image.
  The following methods will be tried orderly:
    1. Image PDB
    2. FFS UI section
    3. Image GUID

  @param[in] DriverInfo Pointer to memory profile driver info.

  @post The resulting Unicode name string is stored in the mNameString global array.

**/
VOID
GetDriverNameString (
 IN MEMORY_PROFILE_DRIVER_INFO  *DriverInfo
 )
{
  EFI_STATUS                  Status;
  CHAR8                       *PdbFileName;
  CHAR16                      *NameString;
  UINTN                       StringSize;

  //
  // Method 1: Get the name string from image PDB
  //
  if ((DriverInfo->ImageBase != 0) && (DriverInfo->FileType != EFI_FV_FILETYPE_SMM) && (DriverInfo->FileType != EFI_FV_FILETYPE_SMM_CORE)) {
    PdbFileName = PeCoffLoaderGetPdbPointer ((VOID *) (UINTN) DriverInfo->ImageBase);

    if (PdbFileName != NULL) {
      GetShortPdbFileName (PdbFileName, mNameString);
      return;
    }
  }

  if (!CompareGuid (&DriverInfo->FileName, &gZeroGuid)) {
    //
    // Try to get the image's FFS UI section by image GUID
    //
    NameString = NULL;
    StringSize = 0;
    Status = GetSectionFromAnyFv (
              &DriverInfo->FileName,
              EFI_SECTION_USER_INTERFACE,
              0,
              (VOID **) &NameString,
              &StringSize
              );
    if (!EFI_ERROR (Status)) {
      //
      // Method 2: Get the name string from FFS UI section
      //
      StrnCpy (mNameString, NameString, PROFILE_NAME_STRING_LENGTH);
      mNameString[PROFILE_NAME_STRING_LENGTH] = 0;
      FreePool (NameString);
      return;
    }
  }

  //
  // Method 3: Get the name string from image GUID
  //
  UnicodeSPrint (mNameString, sizeof (mNameString), L"%g", &DriverInfo->FileName);
}