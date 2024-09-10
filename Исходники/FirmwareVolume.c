EFI_STATUS
FindApplicationMatchingUiSection (
  IN  CHAR16      *UiString,
  OUT EFI_HANDLE  *FvHandle,
  OUT EFI_GUID    *NameGuid
  )
{
  EFI_STATUS                    Status;
  EFI_STATUS                    NextStatus;
  UINTN                         NoHandles;
  EFI_HANDLE                    *Buffer;
  UINTN                         Index;
  EFI_FV_FILETYPE               FileType;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
  VOID                          *Key;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINTN                         Size;
  UINTN                         UiStringLen;
  CHAR16                        *UiSection;
  UINT32                        Authentication;


  UiStringLen = 0;
  if (UiString != NULL) {
    DEBUG ((DEBUG_ERROR, "UiString %s\n", UiString));
    UiStringLen = StrLen (UiString);
  }

  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiFirmwareVolume2ProtocolGuid, NULL, &NoHandles, &Buffer);
  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < NoHandles; Index++) {
      Status = gBS->HandleProtocol (Buffer[Index], &gEfiFirmwareVolume2ProtocolGuid, (VOID **)&Fv);
      if (!EFI_ERROR (Status)) {
        Key = AllocatePool (Fv->KeySize);
        ASSERT (Key != NULL);
        ZeroMem (Key, Fv->KeySize);

        FileType = EFI_FV_FILETYPE_APPLICATION;

        do {
          NextStatus = Fv->GetNextFile (Fv, Key, &FileType, NameGuid, &Attributes, &Size);
          if (!EFI_ERROR (NextStatus)) {
            if (UiString == NULL) {
              //
              // If UiString is NULL match first application we find.
              //
              *FvHandle = Buffer[Index];
              FreePool (Key);
              return Status;
            }

            UiSection = NULL;
            Status = Fv->ReadSection (
                          Fv,
                          NameGuid,
                          EFI_SECTION_USER_INTERFACE,
                          0,
                          (VOID **)&UiSection,
                          &Size,
                          &Authentication
                          );
            if (!EFI_ERROR (Status)) {
              if (StrnCmp (UiString, UiSection, UiStringLen) == 0) {
                //
                // We found a UiString match.
                //
                *FvHandle = Buffer[Index];
                FreePool (Key);
                FreePool (UiSection);
                return Status;
              }
              FreePool (UiSection);
            }
          }
        } while (!EFI_ERROR (NextStatus));

        FreePool (Key);
      }
    }

    FreePool (Buffer);
   }

  return EFI_NOT_FOUND;
}