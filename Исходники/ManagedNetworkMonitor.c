EFI_STATUS
MnpSendPacketOut (
  IN CHAR8     *Buffer,
  IN UINT32    Sequence,
  IN UINTN     Size
  )
/*++

Routine Description:

  This func is to send a data packet out to managed network.

Arguments:

  Buffer    - A buffer for writing.
  Sequence  - The Sequence Id of the packet to send.
  Size      - The size of the buffer to send.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.

--*/
{
  BOOLEAN           IsOver;
  EAS_MNP_FRAG_FLAG FragFlag;
  EAS_APP_FLAG      AppFlag;
  UINTN             BufferSize;
  UINT32            PacketLength;
  UINT32            PacketStartPoint;
  EFI_STATUS        Status;
  UINT8             *FragmentBuffer;

  if (0 == Size) {
    return EFI_SUCCESS;
  }

  IsOver = FALSE;
  FragFlag.LLFlag ^= FragFlag.LLFlag;
  FragFlag.Flag.SeqId   = HTONL (Sequence);
  FragFlag.Flag.OpCode  = LINK_OPERATION_DATA;
  BufferSize            = Size;
  PacketStartPoint      = 0;
  FragmentBuffer        = NULL;

  while (!IsOver) {
    //
    // Build Fragment Flag
    //
    if (BufferSize <= MAX_PACKET_LENGTH) {
      IsOver = TRUE;
      CLR_FLAG_MF (FragFlag.LLFlag);
      PacketLength          = (UINT32) BufferSize;
      FragFlag.Flag.Offset  = HTONS (PacketStartPoint);
    } else {
      //
      // Need more fragement
      //
      IsOver = FALSE;
      SET_FLAG_MF (FragFlag.LLFlag);
      PacketLength          = MAX_PACKET_LENGTH;
      FragFlag.Flag.Offset  = HTONS (PacketStartPoint);
      BufferSize -= MAX_PACKET_LENGTH;
    }
    //
    // Build App Flag
    //
    AppFlag.LLFlag ^= AppFlag.LLFlag;
    AppSequence = AppSequenceSavedForResend;
    AppFlag.Flag.SeqId = HTONL(AppSequence);
    //
    // Build data
    //
   	FragmentBuffer = EntsAllocatePool (PacketLength + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG));
	if(NULL == FragmentBuffer) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"EntsAllocatePool Error"));
      return EFI_OUT_OF_RESOURCES;
    }

    EntsCopyMem (&TxData, &mMnpTxDataTemplate, sizeof (EFI_MANAGED_NETWORK_TRANSMIT_DATA));
    TxData.DataLength = (UINT32) (PacketLength + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG));
    TxData.FragmentTable[0].FragmentLength = (UINT32) (PacketLength + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG));
    TxData.FragmentTable[0].FragmentBuffer = FragmentBuffer;

    EntsCopyMem (
      (UINT8 *) TxData.FragmentTable[0].FragmentBuffer + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG),
      (CHAR8 *) Buffer + PacketStartPoint,
      PacketLength
      );
    EntsCopyMem (
      (UINT8 *) TxData.FragmentTable[0].FragmentBuffer + sizeof (EAS_MNP_FRAG_FLAG),
      &AppFlag.LLFlag,
      sizeof (EAS_APP_FLAG)
      );
    EntsCopyMem (
      TxData.FragmentTable[0].FragmentBuffer,
      &FragFlag.LLFlag,
      sizeof (EAS_MNP_FRAG_FLAG)
      );
    PacketStartPoint += PacketLength;

    TxToken.Packet.TxData = &TxData;

    //
    // Ready to send buffer
    //
    Context = 0;
    Status  = Mnp->Transmit (Mnp, &TxToken);
    if (EFI_ERROR (Status)) {
      RecycleTxBuffer(FragmentBuffer);
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Mnp->Transmit Error"));
      return Status;
    }
    //
    // Check the event ( Omitted...)
    //
    RecycleTxBuffer(FragmentBuffer);
  }

  return EFI_SUCCESS;
}