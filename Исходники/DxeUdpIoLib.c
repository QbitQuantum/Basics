/**
  The event handle for UDP receive request.

  It will build a NET_BUF from the recieved UDP data, then deliver it
  to the receiver.

  @param[in]  Context               The UDP RX token.

**/
VOID
EFIAPI
UdpIoOnDgramRcvdDpc (
  IN VOID                   *Context
  )
{
  EFI_STATUS                Status;
  VOID                      *Token;
  VOID                      *RxData;
  VOID                      *Session;
  UDP_RX_TOKEN              *RxToken;
  UDP_END_POINT             EndPoint;
  NET_BUF                   *Netbuf;

  RxToken = (UDP_RX_TOKEN *) Context;

  ZeroMem (&EndPoint, sizeof(UDP_END_POINT));

  ASSERT ((RxToken->Signature == UDP_IO_RX_SIGNATURE) &&
          (RxToken == RxToken->UdpIo->RecvRequest));

  ASSERT ((RxToken->UdpIo->UdpVersion == UDP_IO_UDP4_VERSION) ||
          (RxToken->UdpIo->UdpVersion == UDP_IO_UDP6_VERSION));

  //
  // Clear the receive request first in case that the caller
  // wants to restart the receive in the callback.
  //
  RxToken->UdpIo->RecvRequest = NULL;

  if (RxToken->UdpIo->UdpVersion == UDP_IO_UDP4_VERSION) {
    Token  = &RxToken->Token.Udp4;
    RxData = ((EFI_UDP4_COMPLETION_TOKEN *) Token)->Packet.RxData;
    Status = ((EFI_UDP4_COMPLETION_TOKEN *) Token)->Status;
  } else {
    Token  = &RxToken->Token.Udp6;
    RxData = ((EFI_UDP6_COMPLETION_TOKEN *) Token)->Packet.RxData;
    Status = ((EFI_UDP6_COMPLETION_TOKEN *) Token)->Status;
  }

  if (EFI_ERROR (Status) || RxData == NULL) {
    if (Status != EFI_ABORTED) {
      //
      // Invoke the CallBack only if the reception is not actively aborted.
      //
      RxToken->CallBack (NULL, NULL, Status, RxToken->Context);
    }

    UdpIoFreeRxToken (RxToken);
    return;
  }

  //
  // Build a NET_BUF from the UDP receive data, then deliver it up.
  //
  if (RxToken->UdpIo->UdpVersion == UDP_IO_UDP4_VERSION) {
    if (((EFI_UDP4_RECEIVE_DATA *) RxData)->DataLength == 0) {
      //
      // Discard zero length data payload packet.
      //
      goto Resume;
    }

    Netbuf = NetbufFromExt (
               (NET_FRAGMENT *)((EFI_UDP4_RECEIVE_DATA *) RxData)->FragmentTable,
               ((EFI_UDP4_RECEIVE_DATA *) RxData)->FragmentCount,
               0,
               (UINT32) RxToken->HeadLen,
               UdpIoRecycleDgram,
               RxToken
               );

    if (Netbuf == NULL) {
      gBS->SignalEvent (((EFI_UDP4_RECEIVE_DATA *) RxData)->RecycleSignal);
      RxToken->CallBack (NULL, NULL, EFI_OUT_OF_RESOURCES, RxToken->Context);

      UdpIoFreeRxToken (RxToken);
      return;
    }

    Session             = &((EFI_UDP4_RECEIVE_DATA *) RxData)->UdpSession;
    EndPoint.LocalPort  = ((EFI_UDP4_SESSION_DATA *) Session)->DestinationPort;
    EndPoint.RemotePort = ((EFI_UDP4_SESSION_DATA *) Session)->SourcePort;

    CopyMem (
      &EndPoint.LocalAddr,
      &((EFI_UDP4_SESSION_DATA *) Session)->DestinationAddress,
      sizeof (EFI_IPv4_ADDRESS)
      );

    CopyMem (
      &EndPoint.RemoteAddr,
      &((EFI_UDP4_SESSION_DATA *) Session)->SourceAddress,
      sizeof (EFI_IPv4_ADDRESS)
      );

    EndPoint.LocalAddr.Addr[0]  = NTOHL (EndPoint.LocalAddr.Addr[0]);
    EndPoint.RemoteAddr.Addr[0] = NTOHL (EndPoint.RemoteAddr.Addr[0]);
  } else {
    if (((EFI_UDP6_RECEIVE_DATA *) RxData)->DataLength == 0) {
      //
      // Discard zero length data payload packet.
      //
      goto Resume;
    }

    Netbuf = NetbufFromExt (
               (NET_FRAGMENT *)((EFI_UDP6_RECEIVE_DATA *) RxData)->FragmentTable,
               ((EFI_UDP6_RECEIVE_DATA *) RxData)->FragmentCount,
               0,
               (UINT32) RxToken->HeadLen,
               UdpIoRecycleDgram,
               RxToken
               );

    if (Netbuf == NULL) {
      gBS->SignalEvent (((EFI_UDP6_RECEIVE_DATA *) RxData)->RecycleSignal);
      RxToken->CallBack (NULL, NULL, EFI_OUT_OF_RESOURCES, RxToken->Context);

      UdpIoFreeRxToken (RxToken);
      return;
    }

    Session             = &((EFI_UDP6_RECEIVE_DATA *) RxData)->UdpSession;
    EndPoint.LocalPort  = ((EFI_UDP6_SESSION_DATA *) Session)->DestinationPort;
    EndPoint.RemotePort = ((EFI_UDP6_SESSION_DATA *) Session)->SourcePort;

    CopyMem (
      &EndPoint.LocalAddr,
      &((EFI_UDP6_SESSION_DATA *) Session)->DestinationAddress,
      sizeof (EFI_IPv6_ADDRESS)
      );

    CopyMem (
      &EndPoint.RemoteAddr,
      &((EFI_UDP6_SESSION_DATA *) Session)->SourceAddress,
      sizeof (EFI_IPv6_ADDRESS)
      );

    Ip6Swap128 (&EndPoint.LocalAddr.v6);
    Ip6Swap128 (&EndPoint.RemoteAddr.v6);
  }

  RxToken->CallBack (Netbuf, &EndPoint, EFI_SUCCESS, RxToken->Context);
  return;

Resume:
  if (RxToken->UdpIo->UdpVersion == UDP_IO_UDP4_VERSION) {
    gBS->SignalEvent (((EFI_UDP4_RECEIVE_DATA *) RxData)->RecycleSignal);
    RxToken->UdpIo->Protocol.Udp4->Receive (RxToken->UdpIo->Protocol.Udp4, &RxToken->Token.Udp4);
  } else {
    gBS->SignalEvent (((EFI_UDP6_RECEIVE_DATA *) RxData)->RecycleSignal);
    RxToken->UdpIo->Protocol.Udp6->Receive (RxToken->UdpIo->Protocol.Udp6, &RxToken->Token.Udp6);
  }
}