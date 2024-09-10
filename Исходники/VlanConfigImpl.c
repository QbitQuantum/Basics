/**
  This function publish the VLAN configuration Form for a network device. The
  HII Config Access protocol will be installed on a child handle of the network
  device.

  @param[in, out]  PrivateData   Points to VLAN configuration private data.

  @retval EFI_SUCCESS            HII Form is installed for this network device.
  @retval EFI_OUT_OF_RESOURCES   Not enough resource for HII Form installation.
  @retval Others                 Other errors as indicated.

**/
EFI_STATUS
InstallVlanConfigForm (
  IN OUT VLAN_CONFIG_PRIVATE_DATA    *PrivateData
  )
{
  EFI_STATUS                      Status;
  EFI_HII_HANDLE                  HiiHandle;
  EFI_HANDLE                      DriverHandle;
  CHAR16                          Str[26 + sizeof (EFI_MAC_ADDRESS) * 2 + 1];
  CHAR16                          *MacString;
  EFI_DEVICE_PATH_PROTOCOL        *ChildDevicePath;
  EFI_HII_CONFIG_ACCESS_PROTOCOL  *ConfigAccess;
  EFI_VLAN_CONFIG_PROTOCOL        *VlanConfig;

  //
  // Create child handle and install HII Config Access Protocol
  //
  ChildDevicePath = AppendDevicePathNode (
                      PrivateData->ParentDevicePath,
                      (CONST EFI_DEVICE_PATH_PROTOCOL *) &mHiiVendorDevicePathNode
                      );
  if (ChildDevicePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  PrivateData->ChildDevicePath = ChildDevicePath;

  DriverHandle = NULL;
  ConfigAccess = &PrivateData->ConfigAccess;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  ChildDevicePath,
                  &gEfiHiiConfigAccessProtocolGuid,
                  ConfigAccess,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PrivateData->DriverHandle = DriverHandle;

  //
  // Establish the parent-child relationship between the new created
  // child handle and the ControllerHandle.
  //
  Status = gBS->OpenProtocol (
                  PrivateData->ControllerHandle,
                  &gEfiVlanConfigProtocolGuid,
                  (VOID **)&VlanConfig,
                  PrivateData->ImageHandle,
                  PrivateData->DriverHandle,
                  EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Publish the HII package list
  //
  HiiHandle = HiiAddPackages (
                &gVlanConfigFormSetGuid,
                DriverHandle,
                VlanConfigDxeStrings,
                VlanConfigBin,
                NULL
                );
  if (HiiHandle == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  PrivateData->HiiHandle = HiiHandle;

  //
  // Update formset title help string.
  //
  MacString = NULL;
  Status = NetLibGetMacString (PrivateData->ControllerHandle, PrivateData->ImageHandle, &MacString);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PrivateData->MacString = MacString;

  StrCpy (Str, L"VLAN Configuration (MAC:");
  StrnCat (Str, MacString, sizeof (EFI_MAC_ADDRESS) * 2);
  StrCat (Str, L")");
  HiiSetString (
    HiiHandle,
    STRING_TOKEN (STR_VLAN_FORM_SET_TITLE_HELP),
    Str,
    NULL
    );

  //
  // Update form title help string.
  //
  HiiSetString (
    HiiHandle,
    STRING_TOKEN (STR_VLAN_FORM_HELP),
    Str,
    NULL
    );

  return EFI_SUCCESS;
}