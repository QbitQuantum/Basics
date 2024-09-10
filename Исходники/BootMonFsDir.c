/**
  Set information about a file.

  @param[in]  Instance  A pointer to the description of the volume
                        the file belongs to.
  @param[in]  File      A pointer to the description of the file.
  @param[in]  Info      A pointer to the file information to write.

  @retval  EFI_SUCCESS           The information was set.
  @retval  EFI_ACCESS_DENIED     An attempt is being made to change the
                                 EFI_FILE_DIRECTORY Attribute.
  @retval  EFI_ACCESS_DENIED     The file was opened in read-only mode and an
                                 attempt is being made to modify a field other
                                 than Attribute.
  @retval  EFI_ACCESS_DENIED     An attempt is made to change the name of a file
                                 to a file that is already present.
  @retval  EFI_WRITE_PROTECTED   An attempt is being made to modify a read-only
                                 attribute.
  @retval  EFI_OUT_OF_RESOURCES  An allocation needed to process the request
                                 failed.

**/
STATIC
EFI_STATUS
SetFileInfo (
  IN BOOTMON_FS_INSTANCE  *Instance,
  IN BOOTMON_FS_FILE      *File,
  IN EFI_FILE_INFO        *Info
  )
{
  EFI_STATUS  Status;
  BOOLEAN     FileSizeIsDifferent;
  BOOLEAN     FileNameIsDifferent;
  BOOLEAN     TimeIsDifferent;

  //
  // A directory can not be changed to a file and a file can
  // not be changed to a directory.
  //
  if ((Info->Attribute & EFI_FILE_DIRECTORY)      !=
      (File->Info->Attribute & EFI_FILE_DIRECTORY)  ) {
    return EFI_ACCESS_DENIED;
  }

  FileSizeIsDifferent = (Info->FileSize != File->Info->FileSize);
  FileNameIsDifferent = (StrnCmp (
                           Info->FileName,
                           File->Info->FileName,
                           MAX_NAME_LENGTH - 1
                           ) != 0);
  //
  // Check if the CreateTime, LastAccess or ModificationTime
  // have been changed. The file system does not support file
  // timestamps thus the three times in "File->Info" are
  // always equal to zero. The following comparison actually
  // checks if all three times are still equal to 0 or not.
  //
  TimeIsDifferent = CompareMem (
                      &Info->CreateTime,
                      &File->Info->CreateTime,
                      3 * sizeof (EFI_TIME)
                      ) != 0;

  //
  // For a file opened in read-only mode, only the Attribute field can be
  // modified. The root directory open mode is forced to read-only at opening
  // thus the following test protects the root directory to be somehow modified.
  //
  if (File->OpenMode == EFI_FILE_MODE_READ) {
    if (FileSizeIsDifferent || FileNameIsDifferent || TimeIsDifferent) {
      return EFI_ACCESS_DENIED;
    }
  }

  if (TimeIsDifferent) {
    return EFI_WRITE_PROTECTED;
  }

  if (FileSizeIsDifferent) {
    Status = SetFileSize (Instance, File, Info->FileSize);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  //
  // Note down in RAM the Attribute field but we can not
  // ask to store it in flash for the time being.
  //
  File->Info->Attribute = Info->Attribute;

  if (FileNameIsDifferent) {
    Status = SetFileName (Instance, File, Info->FileName);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}