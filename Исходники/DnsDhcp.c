/**
  Parse the DHCP ACK to get Dns4 server information.

  @param  Instance         The DNS instance.
  @param  DnsServerCount   Retrieved Dns4 server Ip count.
  @param  DnsServerList    Retrieved Dns4 server Ip list.

  @retval EFI_SUCCESS           The Dns4 information is got from the DHCP ACK.
  @retval EFI_OUT_OF_RESOURCES  Failed to allocate memory.
  @retval EFI_NO_MEDIA          There was a media error.
  @retval Others                Other errors as indicated.

**/
EFI_STATUS
GetDns4ServerFromDhcp4 (
  IN  DNS_INSTANCE               *Instance,
  OUT UINT32                     *DnsServerCount,
  OUT EFI_IPv4_ADDRESS           **DnsServerList
  )
{
  EFI_STATUS                          Status;
  EFI_HANDLE                          Image;
  EFI_HANDLE                          Controller;
  BOOLEAN                             MediaPresent;
  EFI_HANDLE                          MnpChildHandle;  
  EFI_MANAGED_NETWORK_PROTOCOL        *Mnp;
  EFI_MANAGED_NETWORK_CONFIG_DATA     MnpConfigData;
  EFI_HANDLE                          Dhcp4Handle;  
  EFI_DHCP4_PROTOCOL                  *Dhcp4;
  EFI_IP4_CONFIG2_PROTOCOL            *Ip4Config2;
  UINTN                               DataSize;
  VOID                                *Data;
  EFI_IP4_CONFIG2_INTERFACE_INFO      *InterfaceInfo;
  EFI_DHCP4_PACKET                    SeedPacket;
  EFI_DHCP4_PACKET_OPTION             *ParaList[2];
  DNS4_SERVER_INFOR                   DnsServerInfor;

  EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN    Token;
  BOOLEAN                             IsDone;
  UINTN                               Index;
  
  Image                      = Instance->Service->ImageHandle;
  Controller                 = Instance->Service->ControllerHandle;

  MnpChildHandle             = NULL;
  Mnp                        = NULL;
  
  Dhcp4Handle                = NULL;
  Dhcp4                      = NULL;

  Ip4Config2                 = NULL;
  DataSize                   = 0;
  Data                       = NULL;
  InterfaceInfo              = NULL;

  ZeroMem ((UINT8 *) ParaList, sizeof (ParaList));

  ZeroMem (&MnpConfigData, sizeof (EFI_MANAGED_NETWORK_CONFIG_DATA));
  
  ZeroMem (&DnsServerInfor, sizeof (DNS4_SERVER_INFOR));
  
  ZeroMem (&Token, sizeof (EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN));
  
  DnsServerInfor.ServerCount = DnsServerCount;

  IsDone = FALSE;

  //
  // Check media.
  //
  MediaPresent = TRUE;
  NetLibDetectMedia (Controller, &MediaPresent);
  if (!MediaPresent) {
    return EFI_NO_MEDIA;
  }

  //
  // Start the auto configuration if UseDefaultSetting.
  //
  if (Instance->Dns4CfgData.UseDefaultSetting) {
    Status = DnsStartIp4 (Controller, Image);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }
  
  //
  // Create a Mnp child instance, get the protocol and config for it.
  //
  Status = NetLibCreateServiceChild (
             Controller,
             Image,
             &gEfiManagedNetworkServiceBindingProtocolGuid,
             &MnpChildHandle
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->OpenProtocol (
                  MnpChildHandle,
                  &gEfiManagedNetworkProtocolGuid,
                  (VOID **) &Mnp,
                  Image,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }
  
  MnpConfigData.ReceivedQueueTimeoutValue = 0;
  MnpConfigData.TransmitQueueTimeoutValue = 0;
  MnpConfigData.ProtocolTypeFilter        = IP4_ETHER_PROTO;
  MnpConfigData.EnableUnicastReceive      = TRUE;
  MnpConfigData.EnableMulticastReceive    = TRUE;
  MnpConfigData.EnableBroadcastReceive    = TRUE;
  MnpConfigData.EnablePromiscuousReceive  = FALSE;
  MnpConfigData.FlushQueuesOnReset        = TRUE;
  MnpConfigData.EnableReceiveTimestamps   = FALSE;
  MnpConfigData.DisableBackgroundPolling  = FALSE;

  Status = Mnp->Configure(Mnp, &MnpConfigData);
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }
  
  //
  // Create a DHCP4 child instance and get the protocol.
  //
  Status = NetLibCreateServiceChild (
             Controller,
             Image,
             &gEfiDhcp4ServiceBindingProtocolGuid,
             &Dhcp4Handle
             );
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }

  Status = gBS->OpenProtocol (
                  Dhcp4Handle,
                  &gEfiDhcp4ProtocolGuid,
                  (VOID **) &Dhcp4,
                  Image,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }

  //
  // Get Ip4Config2 instance info.
  //
  Status = gBS->HandleProtocol (Controller, &gEfiIp4Config2ProtocolGuid, (VOID **) &Ip4Config2);
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }
  
  Status = Ip4Config2->GetData (Ip4Config2, Ip4Config2DataTypeInterfaceInfo, &DataSize, Data);
  if (EFI_ERROR (Status) && Status != EFI_BUFFER_TOO_SMALL) {
    goto ON_EXIT;
  }

  Data = AllocateZeroPool (DataSize);
  if (Data == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  Status = Ip4Config2->GetData (Ip4Config2, Ip4Config2DataTypeInterfaceInfo, &DataSize, Data);
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }

  InterfaceInfo = (EFI_IP4_CONFIG2_INTERFACE_INFO *)Data;
  
  //
  // Build required Token.
  //
  Status = gBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  DhcpCommonNotify,
                  &IsDone,
                  &Token.CompletionEvent
                  );
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }
  
  SetMem (&Token.RemoteAddress, sizeof (EFI_IPv4_ADDRESS), 0xff);
  
  Token.RemotePort = 67;

  Token.ListenPointCount = 1;
  
  Token.ListenPoints = AllocateZeroPool (Token.ListenPointCount * sizeof (EFI_DHCP4_LISTEN_POINT));
  if (Token.ListenPoints == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  if (Instance->Dns4CfgData.UseDefaultSetting) {
    CopyMem (&(Token.ListenPoints[0].ListenAddress), &(InterfaceInfo->StationAddress), sizeof (EFI_IPv4_ADDRESS));
    CopyMem (&(Token.ListenPoints[0].SubnetMask), &(InterfaceInfo->SubnetMask), sizeof (EFI_IPv4_ADDRESS));
  } else {
    CopyMem (&(Token.ListenPoints[0].ListenAddress), &(Instance->Dns4CfgData.StationIp), sizeof (EFI_IPv4_ADDRESS));
    CopyMem (&(Token.ListenPoints[0].SubnetMask), &(Instance->Dns4CfgData.SubnetMask), sizeof (EFI_IPv4_ADDRESS));
  }
  
  Token.ListenPoints[0].ListenPort = 68;
  
  Token.TimeoutValue = DNS_TIME_TO_GETMAP;

  DnsInitSeedPacket (&SeedPacket, InterfaceInfo);

  ParaList[0] = AllocateZeroPool (sizeof (EFI_DHCP4_PACKET_OPTION));
  if (ParaList[0] == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }
  
  ParaList[0]->OpCode  = DHCP4_TAG_TYPE;
  ParaList[0]->Length  = 1;
  ParaList[0]->Data[0] = DHCP4_MSG_INFORM;
  
  ParaList[1] = AllocateZeroPool (sizeof (EFI_DHCP4_PACKET_OPTION));
  if (ParaList[1] == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }
  
  ParaList[1]->OpCode  = DHCP4_TAG_PARA_LIST;
  ParaList[1]->Length  = 1;
  ParaList[1]->Data[0] = DHCP4_TAG_DNS_SERVER;

  Status = Dhcp4->Build (Dhcp4, &SeedPacket, 0, NULL, 2, ParaList, &Token.Packet); 

  Token.Packet->Dhcp4.Header.Xid      = HTONL(NET_RANDOM (NetRandomInitSeed ()));
  
  Token.Packet->Dhcp4.Header.Reserved = HTONS ((UINT16)0x8000);
  
  if (Instance->Dns4CfgData.UseDefaultSetting) {
    CopyMem (&(Token.Packet->Dhcp4.Header.ClientAddr), &(InterfaceInfo->StationAddress), sizeof (EFI_IPv4_ADDRESS));
  } else {
    CopyMem (&(Token.Packet->Dhcp4.Header.ClientAddr), &(Instance->Dns4CfgData.StationIp), sizeof (EFI_IPv4_ADDRESS));
  }
  
  CopyMem (Token.Packet->Dhcp4.Header.ClientHwAddr, &(InterfaceInfo->HwAddress), InterfaceInfo->HwAddressSize); 
  
  Token.Packet->Dhcp4.Header.HwAddrLen = (UINT8)(InterfaceInfo->HwAddressSize);

  //
  // TransmitReceive Token
  //
  Status = Dhcp4->TransmitReceive (Dhcp4, &Token);
  if (EFI_ERROR (Status)) {
    goto ON_EXIT;
  }

  //
  // Poll the packet
  //
  do {
    Status = Mnp->Poll (Mnp);
  } while (!IsDone);
  
  //
  // Parse the ACK to get required information if received done.
  //
  if (IsDone && !EFI_ERROR (Token.Status)) {
    for (Index = 0; Index < Token.ResponseCount; Index++) {
      Status = ParseDhcp4Ack (Dhcp4, &Token.ResponseList[Index], &DnsServerInfor);
      if (!EFI_ERROR (Status)) {
        break;
      }
    }

    *DnsServerList = DnsServerInfor.ServerList;
  } else {
    Status = Token.Status;
  }
  
ON_EXIT:

  if (Data != NULL) {
    FreePool (Data);
  }

  for (Index = 0; Index < 2; Index++) {
    if (ParaList[Index] != NULL) {
      FreePool (ParaList[Index]);
    }
  }

  if (Token.ListenPoints) {
    FreePool (Token.ListenPoints);
  }

  if (Token.Packet) {
    FreePool (Token.Packet);
  }
  
  if (Token.ResponseList != NULL) {
    FreePool (Token.ResponseList);
  }
  
  if (Token.CompletionEvent != NULL) {
    gBS->CloseEvent (Token.CompletionEvent);
  }
  
  if (Dhcp4 != NULL) {
    Dhcp4->Stop (Dhcp4);
    Dhcp4->Configure (Dhcp4, NULL);

    gBS->CloseProtocol (
           Dhcp4Handle,
           &gEfiDhcp4ProtocolGuid,
           Image,
           Controller
           );
  }
  
  if (Dhcp4Handle != NULL) {
    NetLibDestroyServiceChild (
      Controller,
      Image,
      &gEfiDhcp4ServiceBindingProtocolGuid,
      Dhcp4Handle
      );
  }

  if (Mnp != NULL) {
    Mnp->Configure (Mnp, NULL);

    gBS->CloseProtocol (
           MnpChildHandle,
           &gEfiManagedNetworkProtocolGuid,
           Image,
           Controller
           );
  }
  
  NetLibDestroyServiceChild (
    Controller,
    Image,
    &gEfiManagedNetworkServiceBindingProtocolGuid,
    MnpChildHandle
    );
  
  return Status;
}