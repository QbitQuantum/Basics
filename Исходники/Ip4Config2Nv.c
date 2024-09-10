/**
  Convert the IFR data into the network configuration data and set the IP
  configure parameters for the NIC.

  @param[in]       IfrFormNvData     The IFR NV data.
  @param[in, out]  Instance          The IP4 config2 instance.

  @retval EFI_SUCCESS            The configure parameter for this NIC was
                                 set successfully.
  @retval EFI_INVALID_PARAMETER  The address information for setting is invalid.
  @retval Others                 Other errors as indicated.

**/
EFI_STATUS
Ip4Config2ConvertIfrNvDataToConfigNvData (
  IN     IP4_CONFIG2_IFR_NVDATA     *IfrFormNvData,
  IN OUT IP4_CONFIG2_INSTANCE       *Instance
  )
{
  EFI_STATUS                       Status;
  EFI_IP4_CONFIG2_PROTOCOL         *Ip4Cfg2;
  IP4_CONFIG2_NVDATA               *Ip4NvData;

  EFI_IP_ADDRESS                   StationAddress;
  EFI_IP_ADDRESS                   SubnetMask;
  EFI_IP_ADDRESS                   Gateway;
  IP4_ADDR                         Ip;
  EFI_IPv4_ADDRESS                 *DnsAddress;
  UINTN                            DnsCount;
  UINTN                            Index;

  EFI_EVENT                        TimeoutEvent;
  EFI_EVENT                        SetAddressEvent;
  BOOLEAN                          IsAddressOk;
  UINTN                            DataSize;
  EFI_INPUT_KEY                    Key;

  Status          = EFI_SUCCESS;
  Ip4Cfg2         = &Instance->Ip4Config2;
  Ip4NvData       = &Instance->Ip4NvData;

  DnsCount        = 0;
  DnsAddress      = NULL;

  TimeoutEvent    = NULL;
  SetAddressEvent = NULL;



  if (Instance == NULL || IfrFormNvData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (IfrFormNvData->Configure != TRUE) {
    return EFI_SUCCESS;
  }

  if (IfrFormNvData->DhcpEnable == TRUE) {
    Ip4NvData->Policy = Ip4Config2PolicyDhcp;

    Status = Ip4Cfg2->SetData (
                        Ip4Cfg2,
                        Ip4Config2DataTypePolicy,
                        sizeof (EFI_IP4_CONFIG2_POLICY),
                        &Ip4NvData->Policy
                        );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  } else {
    //
    // Get Ip4NvData from IfrFormNvData if it is valid.
    //
    Ip4NvData->Policy = Ip4Config2PolicyStatic;

    Status = Ip4Config2StrToIp (IfrFormNvData->SubnetMask, &SubnetMask.v4);
    if (EFI_ERROR (Status) || ((SubnetMask.Addr[0] != 0) && (GetSubnetMaskPrefixLength (&SubnetMask.v4) == 0))) {
      CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Invalid Subnet Mask!", NULL);
      return EFI_INVALID_PARAMETER;
    }

    Status = Ip4Config2StrToIp (IfrFormNvData->StationAddress, &StationAddress.v4);
    if (EFI_ERROR (Status) ||
        (SubnetMask.Addr[0] != 0 && !NetIp4IsUnicast (NTOHL (StationAddress.Addr[0]), NTOHL (SubnetMask.Addr[0]))) ||
        !Ip4StationAddressValid (NTOHL (StationAddress.Addr[0]), NTOHL (SubnetMask.Addr[0]))) {
      CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Invalid IP address!", NULL);
      return EFI_INVALID_PARAMETER;
    }

    Status = Ip4Config2StrToIp (IfrFormNvData->GatewayAddress, &Gateway.v4);
    if (EFI_ERROR (Status) ||
        (Gateway.Addr[0] != 0 && SubnetMask.Addr[0] != 0 && !NetIp4IsUnicast (NTOHL (Gateway.Addr[0]), NTOHL (SubnetMask.Addr[0])))) {
      CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Invalid Gateway!", NULL);
      return EFI_INVALID_PARAMETER;
    }

    Status = Ip4Config2StrToIpList (IfrFormNvData->DnsAddress, &DnsAddress, &DnsCount);
    if (!EFI_ERROR (Status) && DnsCount > 0) {
      for (Index = 0; Index < DnsCount; Index ++) {
        CopyMem (&Ip, &DnsAddress[Index], sizeof (IP4_ADDR));
        if (IP4_IS_UNSPECIFIED (NTOHL (Ip)) || IP4_IS_LOCAL_BROADCAST (NTOHL (Ip))) {
          CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Invalid Dns Server!", NULL);
          FreePool(DnsAddress);
          return EFI_INVALID_PARAMETER;
        }
      }
    } else {
      if (EFI_ERROR (Status)) {
        CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Invalid Dns Server!", NULL);
      }
    }

    if (Ip4NvData->ManualAddress != NULL) {
      FreePool(Ip4NvData->ManualAddress);
    }
    Ip4NvData->ManualAddressCount = 1;
    Ip4NvData->ManualAddress = AllocateZeroPool(sizeof(EFI_IP4_CONFIG2_MANUAL_ADDRESS));
    if (Ip4NvData->ManualAddress == NULL) {
      if (DnsAddress != NULL) {
        FreePool(DnsAddress);
      }

      return EFI_OUT_OF_RESOURCES;
    }
    CopyMem(&Ip4NvData->ManualAddress->Address, &StationAddress.v4, sizeof(EFI_IPv4_ADDRESS));
    CopyMem(&Ip4NvData->ManualAddress->SubnetMask, &SubnetMask.v4, sizeof(EFI_IPv4_ADDRESS));

    if (Ip4NvData->GatewayAddress != NULL) {
      FreePool(Ip4NvData->GatewayAddress);
    }
    Ip4NvData->GatewayAddressCount = 1;
    Ip4NvData->GatewayAddress = AllocateZeroPool(sizeof(EFI_IPv4_ADDRESS));
    if (Ip4NvData->GatewayAddress == NULL) {
      if (DnsAddress != NULL) {
        FreePool(DnsAddress);
      }
      return EFI_OUT_OF_RESOURCES;
    }
    CopyMem(Ip4NvData->GatewayAddress, &Gateway.v4, sizeof(EFI_IPv4_ADDRESS));

    if (Ip4NvData->DnsAddress != NULL) {
      FreePool(Ip4NvData->DnsAddress);
    }
    Ip4NvData->DnsAddressCount = (UINT32) DnsCount;
    Ip4NvData->DnsAddress      = DnsAddress;

    //
    // Setting Ip4NvData.
    //
    Status = Ip4Cfg2->SetData (
                        Ip4Cfg2,
                        Ip4Config2DataTypePolicy,
                        sizeof (EFI_IP4_CONFIG2_POLICY),
                        &Ip4NvData->Policy
                        );
    if (EFI_ERROR(Status)) {
      return Status;
    }

    //
    // Create events & timers for asynchronous settings.
    //
    Status = gBS->CreateEvent (
                    EVT_TIMER,
                    TPL_CALLBACK,
                    NULL,
                    NULL,
                    &TimeoutEvent
                    );
    if (EFI_ERROR (Status)) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    Ip4Config2ManualAddressNotify,
                    &IsAddressOk,
                    &SetAddressEvent
                    );
    if (EFI_ERROR (Status)) {
      goto Exit;
    }

    IsAddressOk = FALSE;

    Status = Ip4Cfg2->RegisterDataNotify (
                        Ip4Cfg2,
                        Ip4Config2DataTypeManualAddress,
                        SetAddressEvent
                        );
    if (EFI_ERROR (Status)) {
      goto Exit;
    }

    //
    // Set ManualAddress.
    //
    DataSize = Ip4NvData->ManualAddressCount * sizeof (EFI_IP4_CONFIG2_MANUAL_ADDRESS);
    Status = Ip4Cfg2->SetData (
                        Ip4Cfg2,
                        Ip4Config2DataTypeManualAddress,
                        DataSize,
                        (VOID *) Ip4NvData->ManualAddress
                        );

    if (Status == EFI_NOT_READY) {
      gBS->SetTimer (TimeoutEvent, TimerRelative, 50000000);
      while (EFI_ERROR (gBS->CheckEvent (TimeoutEvent))) {
        if (IsAddressOk) {
          Status = EFI_SUCCESS;
          break;
        }
      }
    }

    Ip4Cfg2->UnregisterDataNotify (
               Ip4Cfg2,
               Ip4Config2DataTypeManualAddress,
               SetAddressEvent
               );
    if (EFI_ERROR (Status)) {
      goto Exit;
    }

    //
    // Set gateway.
    //
    DataSize = Ip4NvData->GatewayAddressCount * sizeof (EFI_IPv4_ADDRESS);
    Status = Ip4Cfg2->SetData (
                        Ip4Cfg2,
                        Ip4Config2DataTypeGateway,
                        DataSize,
                        Ip4NvData->GatewayAddress
                        );
    if (EFI_ERROR (Status)) {
      goto Exit;
    }

    //
    // Set DNS addresses.
    //
    if (Ip4NvData->DnsAddressCount > 0 && Ip4NvData->DnsAddress != NULL) {
      DataSize = Ip4NvData->DnsAddressCount * sizeof (EFI_IPv4_ADDRESS);
      Status = Ip4Cfg2->SetData (
                          Ip4Cfg2,
                          Ip4Config2DataTypeDnsServer,
                          DataSize,
                          Ip4NvData->DnsAddress
                          );

      if (EFI_ERROR (Status)) {
        goto Exit;
      }
    }
  }

Exit:
  if (SetAddressEvent != NULL) {
    gBS->CloseEvent (SetAddressEvent);
  }

  if (TimeoutEvent != NULL) {
    gBS->CloseEvent (TimeoutEvent);
  }

  return Status;
}