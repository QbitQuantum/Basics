/**
  Dump FMP protocol info.
**/
VOID
DumpFmpData (
  VOID
  )
{
  EFI_STATUS                                    Status;
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *Fmp;
  EFI_HANDLE                                    *HandleBuffer;
  UINTN                                         NumberOfHandles;
  UINTN                                         Index;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                 *FmpImageInfoBuf;
  UINTN                                         ImageInfoSize;
  UINT32                                        FmpImageInfoDescriptorVer;
  UINT8                                         FmpImageInfoCount;
  UINTN                                         DescriptorSize;
  UINT32                                        PackageVersion;
  CHAR16                                        *PackageVersionName;
  UINT32                                        PackageVersionNameMaxLen;
  UINT64                                        AttributesSupported;
  UINT64                                        AttributesSetting;

  Print(L"############\n");
  Print(L"# FMP DATA #\n");
  Print(L"############\n");
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareManagementProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) {
    Print(L"FMP protocol - %r\n", EFI_NOT_FOUND);
    return;
  }

  for (Index = 0; Index < NumberOfHandles; Index++) {
    Status = gBS->HandleProtocol(
                    HandleBuffer[Index],
                    &gEfiFirmwareManagementProtocolGuid,
                    (VOID **)&Fmp
                    );
    if (EFI_ERROR(Status)) {
      continue;
    }

    ImageInfoSize = 0;
    Status = Fmp->GetImageInfo (
                    Fmp,
                    &ImageInfoSize,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                    );
    if (Status != EFI_BUFFER_TOO_SMALL) {
      continue;
    }

    FmpImageInfoBuf = NULL;
    FmpImageInfoBuf = AllocateZeroPool (ImageInfoSize);
    if (FmpImageInfoBuf == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto EXIT;
    }

    PackageVersionName = NULL;
    Status = Fmp->GetImageInfo (
                    Fmp,
                    &ImageInfoSize,               // ImageInfoSize
                    FmpImageInfoBuf,              // ImageInfo
                    &FmpImageInfoDescriptorVer,   // DescriptorVersion
                    &FmpImageInfoCount,           // DescriptorCount
                    &DescriptorSize,              // DescriptorSize
                    &PackageVersion,              // PackageVersion
                    &PackageVersionName           // PackageVersionName
                    );

    //
    // If FMP GetInformation interface failed, skip this resource
    //
    if (EFI_ERROR(Status)) {
      Print(L"FMP (%d) ImageInfo - %r\n", Index, Status);
      FreePool(FmpImageInfoBuf);
      continue;
    }

    Print(L"FMP (%d) ImageInfo:\n", Index);
    DumpFmpImageInfo(
      ImageInfoSize,               // ImageInfoSize
      FmpImageInfoBuf,             // ImageInfo
      FmpImageInfoDescriptorVer,   // DescriptorVersion
      FmpImageInfoCount,           // DescriptorCount
      DescriptorSize,              // DescriptorSize
      PackageVersion,              // PackageVersion
      PackageVersionName           // PackageVersionName
      );

    if (PackageVersionName != NULL) {
      FreePool(PackageVersionName);
    }
    FreePool(FmpImageInfoBuf);

    //
    // Get package info
    //
    PackageVersionName = NULL;
    Status = Fmp->GetPackageInfo (
                    Fmp,
                    &PackageVersion,              // PackageVersion
                    &PackageVersionName,          // PackageVersionName
                    &PackageVersionNameMaxLen,    // PackageVersionNameMaxLen
                    &AttributesSupported,         // AttributesSupported
                    &AttributesSetting            // AttributesSetting
                    );
    if (EFI_ERROR(Status)) {
      Print(L"FMP (%d) PackageInfo - %r\n", Index, Status);
    } else {
      Print(L"FMP (%d) ImageInfo:\n", Index);
      DumpFmpPackageInfo(
        PackageVersion,              // PackageVersion
        PackageVersionName,          // PackageVersionName
        PackageVersionNameMaxLen,    // PackageVersionNameMaxLen
        AttributesSupported,         // AttributesSupported
        AttributesSetting            // AttributesSetting
        );

      if (PackageVersionName != NULL) {
        FreePool(PackageVersionName);
      }
    }
  }
  Print(L"\n");

EXIT:
  FreePool(HandleBuffer);
}