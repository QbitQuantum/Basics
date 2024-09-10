/**
  Set information about a file.

  @param[in]  Fcb   A pointer to the description of the open file.
  @param[in]  Info  A pointer to the file information to write.

  @retval  EFI_SUCCESS           The information was set.
  @retval  EFI_ACCESS_DENIED     An attempt is made to change the name of a file
                                 to a file that is already present.
  @retval  EFI_ACCESS_DENIED     An attempt is being made to change the
                                 EFI_FILE_DIRECTORY Attribute.
  @retval  EFI_ACCESS_DENIED     The file is a read-only file or has been
                                 opened in read-only mode and an attempt is
                                 being made to modify a field other than
                                 Attribute.
  @retval  EFI_WRITE_PROTECTED   An attempt is being made to modify a
                                 read-only attribute.
  @retval  EFI_DEVICE_ERROR      The last issued semi-hosting operation failed.
  @retval  EFI_OUT_OF_RESOURCES  A allocation needed to process the request failed.

**/
STATIC
EFI_STATUS
SetFileInfo (
  IN  SEMIHOST_FCB   *Fcb,
  IN  EFI_FILE_INFO  *Info
  )
{
  EFI_STATUS     Status;
  RETURN_STATUS  Return;
  BOOLEAN        FileSizeIsDifferent;
  BOOLEAN        FileNameIsDifferent;
  BOOLEAN        ReadOnlyIsDifferent;
  CHAR8          *AsciiFileName;
  UINTN          FileSize;
  UINTN          Length;
  UINTN          SemihostHandle;

  //
  // A directory can not be changed to a file and a file can
  // not be changed to a directory.
  //
  if (((Info->Attribute & EFI_FILE_DIRECTORY) != 0) != Fcb->IsRoot) {
    return EFI_ACCESS_DENIED;
  }

  AsciiFileName = AllocatePool (StrLen (Info->FileName) + 1);
  if (AsciiFileName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  UnicodeStrToAsciiStr (Info->FileName, AsciiFileName);

  FileSizeIsDifferent = (Info->FileSize != Fcb->Info.FileSize);
  FileNameIsDifferent = (AsciiStrCmp (AsciiFileName, Fcb->FileName) != 0);
  ReadOnlyIsDifferent = CompareMem (
                          &Info->CreateTime,
                          &Fcb->Info.CreateTime,
                          3 * sizeof (EFI_TIME)
                          ) != 0;

  //
  // For a read-only file or a file opened in read-only mode, only
  // the Attribute field can be modified. As the root directory is
  // read-only (i.e. VolumeOpen()), this protects the root directory
  // description.
  //
  if ((Fcb->OpenMode == EFI_FILE_MODE_READ)     ||
      (Fcb->Info.Attribute & EFI_FILE_READ_ONLY)  ) {
    if (FileSizeIsDifferent || FileNameIsDifferent || ReadOnlyIsDifferent) {
      Status = EFI_ACCESS_DENIED;
      goto Error;
    }
  }

  if (ReadOnlyIsDifferent) {
    Status = EFI_WRITE_PROTECTED;
    goto Error;
  }

  Status = EFI_DEVICE_ERROR;

  if (FileSizeIsDifferent) {
    FileSize = Info->FileSize;
    if (Fcb->Info.FileSize < FileSize) {
      Status = ExtendFile (Fcb, FileSize - Fcb->Info.FileSize);
      if (EFI_ERROR (Status)) {
        goto Error;
      }
      //
      // The read/write position from the host file system point of view
      // is at the end of the file. If the position from this module
      // point of view is smaller than the new file size, then
      // ask the host file system to move to that position.
      //
      if (Fcb->Position < FileSize) {
        FileSetPosition (&Fcb->File, Fcb->Position);
      }
    }
    Fcb->Info.FileSize = FileSize;

    Return = SemihostFileLength (Fcb->SemihostHandle, &Length);
    if (RETURN_ERROR (Return)) {
      goto Error;
    }
    Fcb->Info.PhysicalSize = Length;
  }

  //
  // Note down in RAM the Attribute field but we can not ask
  // for its modification to the host file system as the
  // semi-host interface does not provide this feature.
  //
  Fcb->Info.Attribute = Info->Attribute;

  if (FileNameIsDifferent) {
    Return = SemihostFileOpen (
               AsciiFileName,
               SEMIHOST_FILE_MODE_READ | SEMIHOST_FILE_MODE_BINARY,
               &SemihostHandle
               );
    if (!RETURN_ERROR (Return)) {
      SemihostFileClose (SemihostHandle);
      Status = EFI_ACCESS_DENIED;
      goto Error;
    }

    Return = SemihostFileRename (Fcb->FileName, AsciiFileName);
    if (RETURN_ERROR (Return)) {
      goto Error;
    }
    FreePool (Fcb->FileName);
    Fcb->FileName = AsciiFileName;
    AsciiFileName = NULL;
  }

  Status = EFI_SUCCESS;

Error:
  if (AsciiFileName != NULL) {
    FreePool (AsciiFileName);
  }

  return Status;
}