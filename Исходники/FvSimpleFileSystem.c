/**
  Returns information about a file.

  @param  This            A pointer to the EFI_FILE_PROTOCOL instance that is the file
                          handle the requested information is for.
  @param  InformationType The type identifier for the information being requested.
  @param  BufferSize      On input, the size of Buffer. On output, the amount of data
                          returned in Buffer. In both cases, the size is measured in bytes.
  @param  Buffer          A pointer to the data buffer to return. The buffer's type is
                          indicated by InformationType.

  @retval EFI_SUCCESS          The information was returned.
  @retval EFI_UNSUPPORTED      The InformationType is not known.
  @retval EFI_NO_MEDIA         The device has no medium.
  @retval EFI_DEVICE_ERROR     The device reported an error.
  @retval EFI_VOLUME_CORRUPTED The file system structures are corrupted.
  @retval EFI_BUFFER_TOO_SMALL The BufferSize is too small to read the current directory entry.
                               BufferSize has been updated with the size needed to complete
                               the request.
**/
EFI_STATUS
EFIAPI
FvSimpleFileSystemGetInfo (
    IN     EFI_FILE_PROTOCOL    *This,
    IN     EFI_GUID             *InformationType,
    IN OUT UINTN                *BufferSize,
    OUT VOID                 *Buffer
)
{
    FV_FILESYSTEM_FILE           *File;
    EFI_FILE_SYSTEM_INFO         *FsInfoOut;
    EFI_FILE_SYSTEM_VOLUME_LABEL *FsVolumeLabel;
    FV_FILESYSTEM_INSTANCE       *Instance;
    UINTN                        Size;
    EFI_STATUS                   Status;

    File = FVFS_FILE_FROM_FILE_THIS (This);

    if (CompareGuid (InformationType, &gEfiFileSystemInfoGuid)) {
        //
        // Return filesystem info
        //
        Instance = File->Instance;

        Size = sizeof (EFI_FILE_SYSTEM_INFO) + StrSize (Instance->VolumeLabel) - sizeof (CHAR16);

        if (*BufferSize < Size) {
            *BufferSize = Size;
            return EFI_BUFFER_TOO_SMALL;
        }

        //
        // Cast output buffer for convenience
        //
        FsInfoOut = (EFI_FILE_SYSTEM_INFO *) Buffer;

        CopyMem (FsInfoOut, &mFsInfoTemplate, sizeof (EFI_FILE_SYSTEM_INFO));
        Status = StrnCpyS (FsInfoOut->VolumeLabel, (*BufferSize - OFFSET_OF (EFI_FILE_SYSTEM_INFO, VolumeLabel)) / sizeof (CHAR16), Instance->VolumeLabel, StrLen (Instance->VolumeLabel));
        ASSERT_EFI_ERROR (Status);
        FsInfoOut->Size = Size;
        return Status;
    } else if (CompareGuid (InformationType, &gEfiFileInfoGuid)) {
        //
        // Return file info
        //
        return FvFsGetFileInfo (File->FvFileInfo, BufferSize, (EFI_FILE_INFO *) Buffer);
    } else if (CompareGuid (InformationType, &gEfiFileSystemVolumeLabelInfoIdGuid)) {
        //
        // Return Volume Label
        //
        Instance = File->Instance;
        Size     = sizeof (EFI_FILE_SYSTEM_VOLUME_LABEL) + StrSize (Instance->VolumeLabel) - sizeof (CHAR16);;
        if (*BufferSize < Size) {
            *BufferSize = Size;
            return EFI_BUFFER_TOO_SMALL;
        }

        FsVolumeLabel = (EFI_FILE_SYSTEM_VOLUME_LABEL*) Buffer;
        Status        = StrnCpyS (FsVolumeLabel->VolumeLabel, (*BufferSize - OFFSET_OF (EFI_FILE_SYSTEM_VOLUME_LABEL, VolumeLabel)) / sizeof (CHAR16), Instance->VolumeLabel, StrLen (Instance->VolumeLabel));
        ASSERT_EFI_ERROR (Status);
        return Status;
    } else {
        return EFI_UNSUPPORTED;
    }
}