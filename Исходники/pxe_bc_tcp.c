//
// //////////////////////////////////////////////////////////////////////
//
//  Tcp Write Routine - called by base code - e.g. TFTP - already locked
//
EFI_STATUS
TcpWrite (
  IN PXE_BASECODE_DEVICE            *Private,
  IN UINT16                         OpFlags,
  IN UINT16                         *UrgentPointer,
  IN UINT32                         *SequenceNumber,
  IN UINT32                         *AckNumber,
  IN UINT16                         *HlenResCode,
  IN UINT16                         *Window,
  IN EFI_IP_ADDRESS                 *DestIpPtr,
  IN EFI_PXE_BASE_CODE_TCP_PORT     *DestPortPtr,
  IN EFI_IP_ADDRESS                 *GatewayIpPtr, OPTIONAL
  IN EFI_IP_ADDRESS                 *SrcIpPtr,
  IN OUT EFI_PXE_BASE_CODE_TCP_PORT *SrcPortPtr,
  IN UINTN                          *HeaderSizePtr,
  IN VOID                           *HeaderPtr,
  IN UINTN                          *BufferSizePtr,
  IN VOID                           *BufferPtr
  )
/*++
Routine description:
  Write buffer to TCP sesion.

Parameters:
  Private := Pointer to PxeBc interface
  OpFlags := 
  UrgentPointer := 
  SequenceNumber := 
  AckNumber := 
  HlenResCode := 
  Window := 
  DestIpPtr := Destination IP address
  DestPortPtr := Destination TCP port
  GatewayIpPtr := Gateway IP address or NULL
  SrcIpPtr := Source IP address
  SrcPortPtr := Source TCP port
  HeaderSizePtr := Size of packet header
  HeaderPtr := Pointer to header buffer
  BufferSizePtr := Size of packet data
  BufferPtr := Pointer to data buffer

Returns:
  EFI_SUCCESS := 
  EFI_INVALID_PARAMETER := 
  EFI_BAD_BUFFER_SIZE := 
  other := 
--*/
{
  EFI_PXE_BASE_CODE_TCP_PORT  DefaultSrcPort;
  UINTN                       TotalLength;
  UINT8                       CodeBits;

  DefaultSrcPort = 23;

  //
  // check parameters
  //
  if (BufferSizePtr == NULL ||
      BufferPtr == NULL ||
      DestIpPtr == NULL ||
      DestPortPtr == NULL ||
      HeaderPtr == NULL ||
      (OpFlags &~(EFI_PXE_BASE_CODE_UDP_OPFLAGS_MAY_FRAGMENT | EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT))
      ) {
    DEBUG (
      (EFI_D_WARN,
      "\nTcpWrite()  Exit #1  %xh (%r)",
      EFI_INVALID_PARAMETER,
      EFI_INVALID_PARAMETER)
      );

    return EFI_INVALID_PARAMETER;
  }
  //
  // Derive header size.
  //
  TotalLength = *BufferSizePtr + sizeof (TCPV4_HEADER);

  if (TotalLength > 0x0000ffff) {
    DEBUG (
      (EFI_D_WARN,
      "\nTcpWrite()  Exit #2  %xh (%r)",
      EFI_BAD_BUFFER_SIZE,
      EFI_BAD_BUFFER_SIZE)
      );

    return EFI_BAD_BUFFER_SIZE;
  }

  if (SrcIpPtr == NULL) {
    SrcIpPtr = &Private->EfiBc.Mode->StationIp;
  }

  if (SrcPortPtr == NULL) {
    SrcPortPtr = &DefaultSrcPort;
    OpFlags |= EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT;
  }

  if (OpFlags & EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT) {
    *SrcPortPtr = Private->RandomPort;

    if (++Private->RandomPort == 0) {
      Private->RandomPort = PXE_RND_PORT_LOW;
    }
  }

#define IpTxBuffer  ((IPV4_BUFFER *) Private->TransmitBufferPtr)
  //
  // build pseudo header and tcp header in transmit buffer
  //
#define Tcpv4Base ((TCPV4_HEADERS *) (IpTxBuffer->u.Data - sizeof (TCPV4_PSEUDO_HEADER)))

  Tcpv4Base->Tcpv4PseudoHeader.SrcAddr.L    = SrcIpPtr->Addr[0];
  Tcpv4Base->Tcpv4PseudoHeader.DestAddr.L   = DestIpPtr->Addr[0];
  Tcpv4Base->Tcpv4PseudoHeader.Zero         = 0;
  Tcpv4Base->Tcpv4PseudoHeader.Protocol     = PROT_TCP;
  Tcpv4Base->Tcpv4PseudoHeader.TotalLength  = HTONS (TotalLength);
  Tcpv4Base->Tcpv4Header.SrcPort            = HTONS (*SrcPortPtr);
  Tcpv4Base->Tcpv4Header.DestPort           = HTONS (*DestPortPtr);
  Tcpv4Base->Tcpv4Header.SeqNumber          = HTONL (*SequenceNumber);
  Tcpv4Base->Tcpv4Header.AckNumber          = HTONL (*AckNumber);
  Tcpv4Base->Tcpv4Header.HlenResCode        = HTONS (*HlenResCode);
  Tcpv4Base->Tcpv4Header.Window             = HTONS (*Window);
  Tcpv4Base->Tcpv4Header.UrgentPointer      = HTONS (*UrgentPointer);
  Tcpv4Base->Tcpv4Header.Checksum           = 0;

  Tcpv4Base->Tcpv4Header.Checksum = IpChecksum2 (
                                      (UINT16 *) Tcpv4Base,
                                      sizeof (TCPV4_HEADER) + sizeof (TCPV4_PSEUDO_HEADER),
                                      (UINT16 *) BufferPtr,
                                      (UINT16) *BufferSizePtr
                                      );

  if (Tcpv4Base->Tcpv4Header.Checksum == 0) {
    //
    // transmit zero checksum as ones complement
    //
    Tcpv4Base->Tcpv4Header.Checksum = 0xffff;
  }

  DEBUG (
    (EFI_D_NET,
    "\nTcpWrite()  DestIP is:  %d.%d.%d.%d SrcIP is:  %d.%d.%d.%d\n",
    Tcpv4Base->Tcpv4PseudoHeader.DestAddr.B[0],
    Tcpv4Base->Tcpv4PseudoHeader.DestAddr.B[1],
    Tcpv4Base->Tcpv4PseudoHeader.DestAddr.B[2],
    Tcpv4Base->Tcpv4PseudoHeader.DestAddr.B[3],
    Tcpv4Base->Tcpv4PseudoHeader.SrcAddr.B[0],
    Tcpv4Base->Tcpv4PseudoHeader.SrcAddr.B[1],
    Tcpv4Base->Tcpv4PseudoHeader.SrcAddr.B[2],
    Tcpv4Base->Tcpv4PseudoHeader.SrcAddr.B[3])
    );

  DEBUG (
    (EFI_D_NET,
    "\nSrcPort=%d, DstPort=%d, SeqNum=%x, AckNum=%x\n",
    NTOHS (Tcpv4Base->Tcpv4Header.SrcPort),
    NTOHS (Tcpv4Base->Tcpv4Header.DestPort),
    NTOHL (Tcpv4Base->Tcpv4Header.SeqNumber),
    NTOHL (Tcpv4Base->Tcpv4Header.AckNumber))
    );

  CodeBits = (UINT8) (NTOHS (Tcpv4Base->Tcpv4Header.HlenResCode) & 0x3f);

  return Ip4Send (
          Private,
          OpFlags,
          PROT_TCP,
          Tcpv4Base->Tcpv4PseudoHeader.SrcAddr.L,
          Tcpv4Base->Tcpv4PseudoHeader.DestAddr.L,
          (GatewayIpPtr) ? GatewayIpPtr->Addr[0] : 0,
          sizeof (TCPV4_HEADER),
          BufferPtr,
          *BufferSizePtr
          );
}