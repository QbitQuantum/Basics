STATIC
EFI_STATUS
PciRomLoadEfiDriversFromRomImage (
  IN EFI_PHYSICAL_ADDRESS    Rom,
  IN UINTN                   RomSize
  )
{
  CHAR16                        *FileName;
  EFI_PCI_EXPANSION_ROM_HEADER  *EfiRomHeader;
  PCI_DATA_STRUCTURE            *Pcir;
  UINTN                         ImageIndex;
  UINTN                         RomOffset;
  UINT32                        ImageSize;
  UINT16                        ImageOffset;
  EFI_HANDLE                    ImageHandle;
  EFI_STATUS                    Status;
  EFI_STATUS                    retStatus;
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

  VBoxLogFlowFuncEnter();
  FileName = L"PciRomInMemory";

  //FileName = L"PciRom Addr=0000000000000000";
  //HexToString (&FileName[12], Rom, 16);

  ImageIndex    = 0;
  retStatus     = EFI_NOT_FOUND;
  RomOffset  = (UINTN) Rom;

  do {

    EfiRomHeader = (EFI_PCI_EXPANSION_ROM_HEADER *) (UINTN) RomOffset;

    if (EfiRomHeader->Signature != PCI_EXPANSION_ROM_HEADER_SIGNATURE) {
      return retStatus;
    }

    //
    // If the pointer to the PCI Data Structure is invalid, no further images can be located.
    // The PCI Data Structure must be DWORD aligned.
    //
    if (EfiRomHeader->PcirOffset == 0 ||
        (EfiRomHeader->PcirOffset & 3) != 0 ||
        RomOffset - (UINTN)Rom + EfiRomHeader->PcirOffset + sizeof (PCI_DATA_STRUCTURE) > RomSize) {
      break;
    }
    Pcir      = (PCI_DATA_STRUCTURE *) (UINTN) (RomOffset + EfiRomHeader->PcirOffset);
    //
    // If a valid signature is not present in the PCI Data Structure, no further images can be located.
    //
    if (Pcir->Signature != PCI_DATA_STRUCTURE_SIGNATURE) {
      break;
    }
    ImageSize = Pcir->ImageLength * 512;
    if (RomOffset - (UINTN)Rom + ImageSize > RomSize) {
      break;
    }

    if ((Pcir->CodeType == PCI_CODE_TYPE_EFI_IMAGE) &&
        (EfiRomHeader->EfiSignature == EFI_PCI_EXPANSION_ROM_HEADER_EFISIGNATURE) &&
        ((EfiRomHeader->EfiSubsystem == EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER) ||
         (EfiRomHeader->EfiSubsystem == EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER))) {

      ImageOffset             = EfiRomHeader->EfiImageHeaderOffset;
      InitializationSize      = EfiRomHeader->InitializationSize * 512;

      if (InitializationSize <= ImageSize && ImageOffset < InitializationSize) {

        ImageBuffer             = (VOID *) (UINTN) (RomOffset + ImageOffset);
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
          Status = gBS->LocateProtocol (&gEfiDecompressProtocolGuid, NULL, (VOID **) &Decompress);
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
              DecompressedImageBuffer = NULL;
              DecompressedImageBuffer = AllocatePool (DestinationSize);
              if (DecompressedImageBuffer != NULL) {
                Scratch = AllocatePool (ScratchSize);
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

                  gBS->FreePool (Scratch);
                }
              }
            }
          }
        }

        if (!SkipImage) {

          //
          // load image and start image
          //

          FilePath = FileDevicePath (NULL, FileName);

          Status = gBS->LoadImage (
                          FALSE,
                          gImageHandle,
                          FilePath,
                          ImageBuffer,
                          ImageLength,
                          &ImageHandle
                          );
          if (!EFI_ERROR (Status)) {
            Status = gBS->StartImage (ImageHandle, NULL, NULL);
            if (!EFI_ERROR (Status)) {
              retStatus = Status;
            }
          }
          if (FilePath != NULL) {
            gBS->FreePool (FilePath);
          }
        }

        if (DecompressedImageBuffer != NULL) {
          gBS->FreePool (DecompressedImageBuffer);
        }

      }
    }

    RomOffset = RomOffset + ImageSize;
    ImageIndex++;
  } while (((Pcir->Indicator & 0x80) == 0x00) && ((RomOffset - (UINTN) Rom) < RomSize));


  VBoxLogFlowFuncLeaveRC(retStatus);
  return retStatus;
}