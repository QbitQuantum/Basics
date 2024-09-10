BOOLEAN PacketSendPacket(
  LPADAPTER   AdapterObject,
  LPPACKET    lpPacket,
  BOOLEAN     Sync,
	BOOLEAN     RecyclingAllowed
)
{
  BOOLEAN  Result;

#if DEBUG_PACKETS
  D(bug("Packet32: PacketSendPacket bytes=%d, sync=%d\n",lpPacket->Length,Sync));
#endif

	lpPacket->OverLapped.Offset = 0;
	lpPacket->OverLapped.OffsetHigh = 0;
	lpPacket->bIoComplete = FALSE;

	if(Sync) {
		Result = WriteFile(
							AdapterObject->hFile,
							lpPacket->Buffer,
							lpPacket->Length,
							&lpPacket->BytesReceived,
							&lpPacket->OverLapped
							);
		if(Result) {
			Result = GetOverlappedResult(
									AdapterObject->hFile,
									&lpPacket->OverLapped,
									&lpPacket->BytesReceived,
									TRUE
									);
		} else {
			D(bug("Packet32: PacketSendPacket WriteFile failed, err=%d\n",(int)GetLastError()));
		}
		lpPacket->bIoComplete = TRUE;
		if(RecyclingAllowed) PacketFreePacket(lpPacket);
#if DEBUG_PACKETS
		D(bug("Packet32: PacketSendPacket result=%d, bytes=%d\n",(int)Result,(int)lpPacket->BytesReceived));
#endif
	} else {
		// don't care about the result
		Result = WriteFileEx(
			AdapterObject->hFile,
			lpPacket->Buffer,
			lpPacket->Length,
			&lpPacket->OverLapped,
			PacketSendCompletionRoutine
		);
#if DEBUG_PACKETS
		D(bug("Packet32: PacketSendPacket result=%d\n",(int)Result));
#endif
		if(!Result && RecyclingAllowed)	{
			recycle_write_packet(lpPacket);
		}
	}

  return Result;
}