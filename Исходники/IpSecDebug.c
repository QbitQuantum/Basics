/**
  Print the IKE Packet.

  @param[in]  Packet      Point to IKE packet to be printed.
  @param[in]  Direction   Point to the IKE packet is inbound or outbound.
  @param[in]  IpVersion   Specified IP Version.

**/
VOID
IpSecDumpPacket (
  IN IKE_PACKET            *Packet,
  IN EFI_IPSEC_TRAFFIC_DIR Direction,
  IN UINT8                 IpVersion
  )
{
  CHAR8                     *TypeStr;
  UINTN                     PacketSize;
  UINT64                    InitCookie;
  UINT64                    RespCookie;

  ASSERT (Packet != NULL);

  PacketSize = Packet->PayloadTotalSize + sizeof (IKE_HEADER);
  InitCookie = (Direction == EfiIPsecOutBound) ? HTONLL (Packet->Header->InitiatorCookie) : Packet->Header->InitiatorCookie;
  RespCookie = (Direction == EfiIPsecOutBound) ? HTONLL (Packet->Header->ResponderCookie) : Packet->Header->ResponderCookie;

  switch (Packet->Header->ExchangeType) {
  case IKE_XCG_TYPE_IDENTITY_PROTECT:
    TypeStr = mExchangeStr[0];
    break;

  case IKE_XCG_TYPE_INFO:
    TypeStr = mExchangeStr[1];
    break;

  case IKE_XCG_TYPE_QM:
    TypeStr = mExchangeStr[2];
    break;
    
  case IKE_XCG_TYPE_SA_INIT:
    TypeStr = mExchangeStr[3];
    break;

  case IKE_XCG_TYPE_AUTH:
    TypeStr = mExchangeStr[4];
    break;

  case IKE_XCG_TYPE_CREATE_CHILD_SA:
    TypeStr = mExchangeStr[5];
    break;

  case IKE_XCG_TYPE_INFO2:
    TypeStr = mExchangeStr[6];
    break;
    
  default:
    TypeStr = mExchangeStr[7];
    break;
  }

  if (Direction == EfiIPsecOutBound) {
    DEBUG ((DEBUG_INFO, "\n>>>Sending %d bytes %a to ", PacketSize, TypeStr));
  } else {
    DEBUG ((DEBUG_INFO, "\n>>>Receiving %d bytes %a from ", PacketSize, TypeStr));
  }

  IpSecDumpAddress (DEBUG_INFO, &Packet->RemotePeerIp, IpVersion);

  DEBUG ((DEBUG_INFO, "   InitiatorCookie:0x%lx ResponderCookie:0x%lx\n", InitCookie, RespCookie));
  DEBUG (
    (DEBUG_INFO,
    "   Version: 0x%x Flags:0x%x ExchangeType:0x%x\n",
    Packet->Header->Version,
    Packet->Header->Flags,
    Packet->Header->ExchangeType)
    );
  DEBUG (
    (DEBUG_INFO,
    "   MessageId:0x%x NextPayload:0x%x\n",
    Packet->Header->MessageId,
    Packet->Header->NextPayload)
    );

}