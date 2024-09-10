/**
  Configure a UDP IO port to receive the multicast.

  @param  McastIo               The UDP IO to configure
  @param  Context               The opaque parameter to the function which is the
                                MTFTP session.

  @retval EFI_SUCCESS           The UDP child is successfully configured.
  @retval Others                Failed to configure the UDP child.

**/
EFI_STATUS
EFIAPI
Mtftp4RrqConfigMcastPort (
  IN UDP_IO                 *McastIo,
  IN VOID                   *Context
  )
{
  MTFTP4_PROTOCOL           *Instance;
  EFI_MTFTP4_CONFIG_DATA    *Config;
  EFI_UDP4_CONFIG_DATA      UdpConfig;
  EFI_IPv4_ADDRESS          Group;
  EFI_STATUS                Status;
  IP4_ADDR                  Ip;

  Instance                     = (MTFTP4_PROTOCOL *) Context;
  Config                       = &Instance->Config;

  UdpConfig.AcceptBroadcast    = FALSE;
  UdpConfig.AcceptPromiscuous  = FALSE;
  UdpConfig.AcceptAnyPort      = FALSE;
  UdpConfig.AllowDuplicatePort = FALSE;
  UdpConfig.TypeOfService      = 0;
  UdpConfig.TimeToLive         = 64;
  UdpConfig.DoNotFragment      = FALSE;
  UdpConfig.ReceiveTimeout     = 0;
  UdpConfig.TransmitTimeout    = 0;
  UdpConfig.UseDefaultAddress  = Config->UseDefaultSetting;
  UdpConfig.StationAddress     = Config->StationIp;
  UdpConfig.SubnetMask         = Config->SubnetMask;
  UdpConfig.StationPort        = Instance->McastPort;
  UdpConfig.RemotePort         = 0;

  Ip = HTONL (Instance->ServerIp);
  CopyMem (&UdpConfig.RemoteAddress, &Ip, sizeof (EFI_IPv4_ADDRESS));

  Status = McastIo->Protocol.Udp4->Configure (McastIo->Protocol.Udp4, &UdpConfig);

  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (!Config->UseDefaultSetting && 
      !EFI_IP4_EQUAL (&mZeroIp4Addr, &Config->GatewayIp)) {
    //
    // The station IP address is manually configured and the Gateway IP is not 0.
    // Add the default route for this UDP instance.
    //
    Status = McastIo->Protocol.Udp4->Routes (
                                       McastIo->Protocol.Udp4, 
                                       FALSE,
                                       &mZeroIp4Addr,
                                       &mZeroIp4Addr,
                                       &Config->GatewayIp
                                       );
                             
    if (EFI_ERROR (Status)) {
      McastIo->Protocol.Udp4->Configure (McastIo->Protocol.Udp4, NULL);
      return Status;
    }
  }

  //
  // join the multicast group
  //
  Ip = HTONL (Instance->McastIp);
  CopyMem (&Group, &Ip, sizeof (EFI_IPv4_ADDRESS));

  return McastIo->Protocol.Udp4->Groups (McastIo->Protocol.Udp4, TRUE, &Group);
}