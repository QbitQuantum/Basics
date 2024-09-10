/**
  Command entry point.

  @param[in] RomBar       The Rom Base address.
  @param[in] RomSize      The Rom size.
  @param[in] FileName     The file name.

  @retval EFI_SUCCESS             The command completed successfully.
  @retval EFI_INVALID_PARAMETER   Command usage error.
  @retval EFI_UNSUPPORTED         Protocols unsupported.
  @retval EFI_OUT_OF_RESOURCES    Out of memory.
  @retval Other value             Unknown error.
**/
EFI_STATUS
EFIAPI
LoadEfiDriversFromRomImage (
  VOID                      *RomBar,
  UINTN                     RomSize,
  CONST CHAR16              *FileName
  )

{
  EFI_PCI_EXPANSION_ROM_HEADER  *EfiRomHeader;
  PCI_DATA_STRUCTURE            *Pcir;
  UINTN                         ImageIndex;
  UINTN                         RomBarOffset;
  UINT32                        ImageSize;
  UINT16                        ImageOffset;
  EFI_HANDLE                    ImageHandle;
  EFI_STATUS                    Status;
  EFI_STATUS                    ReturnStatus;
  CHAR16                        RomFileName[280];
  EFI_DEVICE_PATH_PROTOCOL      *FilePath;
  BOOLEAN                       SkipImage;
  UINT32                        DestinationSize;
  UINT32                        ScratchSize;
  UINT8                         *Scratch;
  VOID                          *ImageBuffer;
  VOID                          *DecompressedImageBuffer;
  UINT32                        ImageLength;
  EFI_DECOMPRESS_PROTOCOL       *Decompress;
  UINT32                        InitializationSize;

  ImageIndex    = 0;
  ReturnStatus     = EFI_NOT_FOUND;
  RomBarOffset  = (UINTN) RomBar;

  do {

    EfiRomHeader = (EFI_PCI_EXPANSION_ROM_HEADER *) (UINTN) RomBarOffset;

    if (EfiRomHeader->Signature != PCI_EXPANSION_ROM_HEADER_SIGNATURE) {
      ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_LOADPCIROM_CORRUPT), gShellDebug1HiiHandle, FileName, ImageIndex);
//      PrintToken (STRING_TOKEN (STR_LOADPCIROM_IMAGE_CORRUPT), HiiHandle, ImageIndex);
      return ReturnStatus;
    }

    //
    // If the pointer to the PCI Data Structure is invalid, no further images can be located. 
    // The PCI Data Structure must be DWORD aligned. 
    //
    if (EfiRomHeader->PcirOffset == 0 ||
        (EfiRomHeader->PcirOffset & 3) != 0 ||
        RomBarOffset - (UINTN)RomBar + EfiRomHeader->PcirOffset + sizeof (PCI_DATA_STRUCTURE) > RomSize) {
      break;
    }

    Pcir      = (PCI_DATA_STRUCTURE *) (UINTN) (RomBarOffset + EfiRomHeader->PcirOffset);
    //
    // If a valid signature is not present in the PCI Data Structure, no further images can be located.
    //
    if (Pcir->Signature != PCI_DATA_STRUCTURE_SIGNATURE) {
      break;
    }
    ImageSize = Pcir->ImageLength * 512;
    if (RomBarOffset - (UINTN)RomBar + ImageSize > RomSize) {
      break;
    }

    if ((Pcir->CodeType == PCI_CODE_TYPE_EFI_IMAGE) &&
        (EfiRomHeader->EfiSignature == EFI_PCI_EXPANSION_ROM_HEADER_EFISIGNATURE) &&
        ((EfiRomHeader->EfiSubsystem == EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER) ||
         (EfiRomHeader->EfiSubsystem == EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER))) {

      ImageOffset             = EfiRomHeader->EfiImageHeaderOffset;
      InitializationSize      = EfiRomHeader->InitializationSize * 512;

      if (InitializationSize <= ImageSize && ImageOffset < InitializationSize) {

        ImageBuffer             = (VOID *) (UINTN) (RomBarOffset + ImageOffset);
        ImageLength             = InitializationSize - ImageOffset;
        DecompressedImageBuffer = NULL;

        //
        // decompress here if needed
        //
        SkipImage = FALSE;
        if (EfiRomHeader->CompressionType > EFI_PCI_EXPANSION_ROM_HEADER_COMPRESSED) {
          SkipImage = TRUE;
        }

        if (EfiRomHeader->CompressionType == EFI_PCI_EXPANSION_ROM_HEADER_COMPRESSED) {
          Status = gBS->LocateProtocol (&gEfiDecompressProtocolGuid, NULL, (VOID**)&Decompress);
          ASSERT_EFI_ERROR(Status);
          if (EFI_ERROR (Status)) {
            SkipImage = TRUE;
          } else {
            SkipImage = TRUE;
            Status = Decompress->GetInfo (
                                  Decompress,
                                  ImageBuffer,
                                  ImageLength,
                                  &DestinationSize,
                                  &ScratchSize
                                 );
            if (!EFI_ERROR (Status)) {
              DecompressedImageBuffer = AllocateZeroPool (DestinationSize);
              if (ImageBuffer != NULL) {
                Scratch = AllocateZeroPool (ScratchSize);
                if (Scratch != NULL) {
                  Status = Decompress->Decompress (
                                        Decompress,
                                        ImageBuffer,
                                        ImageLength,
                                        DecompressedImageBuffer,
                                        DestinationSize,
                                        Scratch,
                                        ScratchSize
                                       );
                  if (!EFI_ERROR (Status)) {
                    ImageBuffer = DecompressedImageBuffer;
                    ImageLength = DestinationSize;
                    SkipImage   = FALSE;
                  }

                  FreePool (Scratch);
                }
              }
            }
          }
        }

        if (!SkipImage) {
          //
          // load image and start image
          //
          UnicodeSPrint (RomFileName, sizeof (RomFileName), L"%s[%d]", FileName, ImageIndex);
          FilePath = FileDevicePath (NULL, RomFileName);

          Status = gBS->LoadImage (
                        TRUE,
                        gImageHandle,
                        FilePath,
                        ImageBuffer,
                        ImageLength,
                        &ImageHandle
                       );
          if (EFI_ERROR (Status)) {
            ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_LOADPCIROM_LOAD_FAIL), gShellDebug1HiiHandle, FileName, ImageIndex, Status);
//            PrintToken (STRING_TOKEN (STR_LOADPCIROM_LOAD_IMAGE_ERROR), HiiHandle, ImageIndex, Status);
          } else {
            Status = gBS->StartImage (ImageHandle, NULL, NULL);
            if (EFI_ERROR (Status)) {
              ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_LOADPCIROM_START_FAIL), gShellDebug1HiiHandle, FileName, ImageIndex, Status);
//              PrintToken (STRING_TOKEN (STR_LOADPCIROM_START_IMAGE), HiiHandle, ImageIndex, Status);
            } else {
              ReturnStatus = Status;
            }
          }
        }

        if (DecompressedImageBuffer != NULL) {
          FreePool (DecompressedImageBuffer);
        }

      }
    }

    RomBarOffset = RomBarOffset + ImageSize;
    ImageIndex++;
  } while (((Pcir->Indicator & 0x80) == 0x00) && ((RomBarOffset - (UINTN) RomBar) < RomSize));

  return ReturnStatus;
}