/**
  Add new boot option for HTTP boot.

  @param[in]  Private             Pointer to the driver private data.
  @param[in]  UsingIpv6           Set to TRUE if creating boot option for IPv6.
  @param[in]  Description         The description text of the boot option.
  @param[in]  Uri                 The URI string of the boot file.
  
  @retval EFI_SUCCESS             The boot option is created successfully.
  @retval Others                  Failed to create new boot option.

**/
EFI_STATUS
HttpBootAddBootOption (
  IN   HTTP_BOOT_PRIVATE_DATA   *Private,
  IN   BOOLEAN                  UsingIpv6,
  IN   CHAR16                   *Description,
  IN   CHAR16                   *Uri
  )
{
  EFI_DEV_PATH               *Node;
  EFI_DEVICE_PATH_PROTOCOL   *TmpDevicePath;
  EFI_DEVICE_PATH_PROTOCOL   *NewDevicePath;
  UINTN                      Length;
  CHAR8                      AsciiUri[URI_STR_MAX_SIZE];
  CHAR16                     *CurrentOrder;
  EFI_STATUS                 Status;
  UINTN                      OrderCount;
  UINTN                      TargetLocation;
  BOOLEAN                    Found;
  UINT8                      *TempByteBuffer;
  UINT8                      *TempByteStart;
  UINTN                      DescSize;
  UINTN                      FilePathSize;
  CHAR16                     OptionStr[10];
  UINT16                     *NewOrder;
  UINTN                      Index;

  NewOrder      = NULL;
  TempByteStart = NULL;
  NewDevicePath = NULL;
  NewOrder      = NULL;
  Node          = NULL;
  TmpDevicePath = NULL;
  CurrentOrder  = NULL;

  if (StrLen (Description) == 0) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert the scheme to all lower case.
  //
  for (Index = 0; Index < StrLen (Uri); Index++) {
    if (Uri[Index] == L':') {
      break;
    }
    if (Uri[Index] >= L'A' && Uri[Index] <= L'Z') {
      Uri[Index] -= (CHAR16)(L'A' - L'a');
    }
  }

  //
  // Only accept http and https URI.
  //
  if ((StrnCmp (Uri, L"http://", 7) != 0) && (StrnCmp (Uri, L"https://", 7) != 0)) {
    return EFI_INVALID_PARAMETER;
  }
  
  //
  // Create a new device path by appending the IP node and URI node to
  // the driver's parent device path
  //
  if (!UsingIpv6) {
    Node = AllocateZeroPool (sizeof (IPv4_DEVICE_PATH));
    if (Node == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto ON_EXIT;
    }
    Node->Ipv4.Header.Type    = MESSAGING_DEVICE_PATH;
    Node->Ipv4.Header.SubType = MSG_IPv4_DP;
    SetDevicePathNodeLength (Node, sizeof (IPv4_DEVICE_PATH));
  } else {
    Node = AllocateZeroPool (sizeof (IPv6_DEVICE_PATH));
    if (Node == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto ON_EXIT;
    }
    Node->Ipv6.Header.Type     = MESSAGING_DEVICE_PATH;
    Node->Ipv6.Header.SubType  = MSG_IPv6_DP;
    SetDevicePathNodeLength (Node, sizeof (IPv6_DEVICE_PATH));
  }
  TmpDevicePath = AppendDevicePathNode (Private->ParentDevicePath, (EFI_DEVICE_PATH_PROTOCOL*) Node);
  FreePool (Node);
  if (TmpDevicePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // Update the URI node with the input boot file URI.
  //
  UnicodeStrToAsciiStr (Uri, AsciiUri);
  Length = sizeof (EFI_DEVICE_PATH_PROTOCOL) + AsciiStrSize (AsciiUri);
  Node = AllocatePool (Length);
  if (Node == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    FreePool (TmpDevicePath);
    goto ON_EXIT;
  }
  Node->DevPath.Type    = MESSAGING_DEVICE_PATH;
  Node->DevPath.SubType = MSG_URI_DP;
  SetDevicePathNodeLength (Node, Length);
  CopyMem ((UINT8*) Node + sizeof (EFI_DEVICE_PATH_PROTOCOL), AsciiUri, AsciiStrSize (AsciiUri));
  NewDevicePath = AppendDevicePathNode (TmpDevicePath, (EFI_DEVICE_PATH_PROTOCOL*) Node);
  FreePool (Node);
  FreePool (TmpDevicePath);
  if (NewDevicePath == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  //
  // Get current "BootOrder" variable and find a free target.
  //
  Length = 0;
  Status = GetVariable2 (
             L"BootOrder",
             &gEfiGlobalVariableGuid,
             (VOID **)&CurrentOrder,
             &Length 
             );
  if (EFI_ERROR (Status) && Status != EFI_NOT_FOUND) {
    goto ON_EXIT;
  }
  OrderCount = Length / sizeof (UINT16);
  Found = FALSE;
  for (TargetLocation=0; TargetLocation < 0xFFFF; TargetLocation++) {
    Found = TRUE;
    for (Index = 0; Index < OrderCount; Index++) {
      if (CurrentOrder[Index] == TargetLocation) {
        Found = FALSE;
        break;
      }
    }
    if (Found) {
      break;
    }
  }

  if (TargetLocation == 0xFFFF) {
    DEBUG ((EFI_D_ERROR, "Could not find unused target index.\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  } else {
    DEBUG ((EFI_D_INFO, "TargetIndex = %04x.\n", TargetLocation));
  }
  
  //
  // Construct and set the "Boot####" variable
  //
  DescSize = StrSize(Description);
  FilePathSize = GetDevicePathSize (NewDevicePath);
  TempByteBuffer = AllocateZeroPool(sizeof(EFI_LOAD_OPTION) + DescSize + FilePathSize);
  if (TempByteBuffer == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  TempByteStart = TempByteBuffer;
  *((UINT32 *) TempByteBuffer) = LOAD_OPTION_ACTIVE;      // Attributes
  TempByteBuffer += sizeof (UINT32);

  *((UINT16 *) TempByteBuffer) = (UINT16)FilePathSize;    // FilePathListLength
  TempByteBuffer += sizeof (UINT16);

  CopyMem (TempByteBuffer, Description, DescSize);
  TempByteBuffer += DescSize;
  CopyMem (TempByteBuffer, NewDevicePath, FilePathSize);

  UnicodeSPrint (OptionStr, sizeof(OptionStr), L"%s%04x", L"Boot", TargetLocation);
  Status = gRT->SetVariable (
                  OptionStr,
                  &gEfiGlobalVariableGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  sizeof(UINT32) + sizeof(UINT16) + DescSize + FilePathSize,
                  TempByteStart
                  );
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }

  //
  // Insert into the order list and set "BootOrder" variable
  //
  NewOrder = AllocateZeroPool ((OrderCount + 1) * sizeof (UINT16));
  if (NewOrder == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }
  CopyMem(NewOrder, CurrentOrder, OrderCount * sizeof(UINT16));
  NewOrder[OrderCount] = (UINT16) TargetLocation;
  Status = gRT->SetVariable (
                  L"BootOrder",
                  &gEfiGlobalVariableGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  ((OrderCount + 1) * sizeof (UINT16)),
                  NewOrder
                  );
  

ON_EXIT:

  if (CurrentOrder != NULL) {
    FreePool (CurrentOrder);
  }
  if (NewOrder != NULL) {
    FreePool (NewOrder);
  }
  if (TempByteStart != NULL) {
    FreePool (TempByteStart);
  }
  if (NewDevicePath != NULL) {
    FreePool (NewDevicePath);
  }

  return Status;
}