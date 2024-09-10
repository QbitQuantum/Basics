EFI_STATUS
ProcessOpRomImage (
  PCI_IO_DEVICE   *PciDevice
  )
/*++

Routine Description:

  Process the oprom image.
  
Arguments:
  PciDevice       A pointer to a pci device.

Returns:

  EFI Status.
  
--*/
{
  UINT8                         Indicator;
  UINT32                        ImageSize;
  UINT16                        ImageOffset;
  VOID                          *RomBar;
  UINT8                         *RomBarOffset;
  EFI_HANDLE                    ImageHandle;
  EFI_STATUS                    Status;
  EFI_STATUS                    retStatus;
  BOOLEAN                       SkipImage;
  UINT32                        DestinationSize;
  UINT32                        ScratchSize;
  UINT8                         *Scratch;
  VOID                          *ImageBuffer;
  VOID                          *DecompressedImageBuffer;
  UINT32                        ImageLength;
  EFI_DECOMPRESS_PROTOCOL       *Decompress;
  EFI_PCI_EXPANSION_ROM_HEADER  *EfiRomHeader;
  PCI_DATA_STRUCTURE            *Pcir;
  UINT32                        InitializationSize;

  Indicator = 0;

  //
  // Get the Address of the Rom image
  //
  RomBar        = PciDevice->PciIo.RomImage;
  RomBarOffset  = (UINT8 *) RomBar;
  retStatus     = EFI_NOT_FOUND;

  if (RomBarOffset == NULL) {
    return retStatus;
  }
  ASSERT (((EFI_PCI_EXPANSION_ROM_HEADER *) RomBarOffset)->Signature == PCI_EXPANSION_ROM_HEADER_SIGNATURE);

  do {
    EfiRomHeader = (EFI_PCI_EXPANSION_ROM_HEADER *) RomBarOffset;
    if (EfiRomHeader->Signature != PCI_EXPANSION_ROM_HEADER_SIGNATURE) {
      RomBarOffset = RomBarOffset + 512;
      continue;
    }

    Pcir        = (PCI_DATA_STRUCTURE *) (RomBarOffset + EfiRomHeader->PcirOffset);
    ASSERT (Pcir->Signature == PCI_DATA_STRUCTURE_SIGNATURE);
    ImageSize   = (UINT32) (Pcir->ImageLength * 512);
    Indicator   = Pcir->Indicator;

    if ((Pcir->CodeType == PCI_CODE_TYPE_EFI_IMAGE) &&
        (EfiRomHeader->EfiSignature == EFI_PCI_EXPANSION_ROM_HEADER_EFISIGNATURE) &&
        ((EfiRomHeader->EfiSubsystem == EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER) ||
         (EfiRomHeader->EfiSubsystem == EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER))) {

      ImageOffset             = EfiRomHeader->EfiImageHeaderOffset;
      InitializationSize      = EfiRomHeader->InitializationSize * 512;

      if (InitializationSize <= ImageSize && ImageOffset < InitializationSize) {

        ImageBuffer             = (VOID *) (RomBarOffset + ImageOffset);
        ImageLength             =  InitializationSize - (UINT32)ImageOffset;
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
          Status = gBS->LoadImage (
                          FALSE,
                          gPciBusDriverBinding.DriverBindingHandle,
                          NULL,
                          ImageBuffer,
                          ImageLength,
                          &ImageHandle
                          );
          if (!EFI_ERROR (Status)) {
            Status = gBS->StartImage (ImageHandle, NULL, NULL);
            if (!EFI_ERROR (Status)) {
              AddDriver (PciDevice, ImageHandle);
              retStatus = EFI_SUCCESS;
            }
          }
        }

        RomBarOffset = RomBarOffset + ImageSize;
      } else {
        RomBarOffset = RomBarOffset + ImageSize;
      }
    } else {
      RomBarOffset = RomBarOffset + ImageSize;
    }

  } while (((Indicator & 0x80) == 0x00) && ((UINTN) (RomBarOffset - (UINT8 *) RomBar) < PciDevice->RomSize));

  return retStatus;

}