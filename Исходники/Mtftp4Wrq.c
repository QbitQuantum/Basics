/**
  Function to handle received ACK packet. 
  
  If the ACK number matches the expected block number, and there are more 
  data pending, send the next block. Otherwise tell the caller that we are done.

  @param  Instance              The MTFTP upload session
  @param  Packet                The MTFTP packet received
  @param  Len                   The packet length
  @param  Completed             Return whether the upload has finished.

  @retval EFI_SUCCESS           The ACK is successfully processed.
  @retval EFI_TFTP_ERROR        The block number loops back.
  @retval Others                Failed to transmit the next data packet.

**/
EFI_STATUS
Mtftp4WrqHandleAck (
  IN     MTFTP4_PROTOCOL       *Instance,
  IN     EFI_MTFTP4_PACKET     *Packet,
  IN     UINT32                Len,
     OUT BOOLEAN               *Completed
  )
{
  UINT16                    AckNum;
  INTN                      Expected;
  UINT64                    TotalBlock;
 
  *Completed  = FALSE;
  AckNum      = NTOHS (Packet->Ack.Block[0]);
  Expected    = Mtftp4GetNextBlockNum (&Instance->Blocks);

  ASSERT (Expected >= 0);

  //
  // Get an unwanted ACK, return EFI_SUCCESS to let Mtftp4WrqInput
  // restart receive.
  //
  if (Expected != AckNum) {
    return EFI_SUCCESS;
  }

  //
  // Remove the acked block number, if this is the last block number,
  // tell the Mtftp4WrqInput to finish the transfer. This is the last
  // block number if the block range are empty..
  //
  Mtftp4RemoveBlockNum (&Instance->Blocks, AckNum, *Completed,&TotalBlock);

  Expected = Mtftp4GetNextBlockNum (&Instance->Blocks);

  if (Expected < 0) {
  
    //
    // The block range is empty. It may either because the the last
    // block has been ACKed, or the sequence number just looped back,
    // that is, there is more than 0xffff blocks.
    //
    if (Instance->LastBlock == AckNum) {
      ASSERT (Instance->LastBlock >= 1);
      *Completed = TRUE;
      return EFI_SUCCESS;

    } else {
      Mtftp4SendError (
        Instance,
        EFI_MTFTP4_ERRORCODE_REQUEST_DENIED,
        (UINT8 *) "Block number rolls back, not supported, try blksize option"
        );

      return EFI_TFTP_ERROR;
    }
  }

  return Mtftp4WrqSendBlock (Instance, (UINT16) Expected);
}