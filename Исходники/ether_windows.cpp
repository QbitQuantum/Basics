static bool tap_send_packet(
	LPADAPTER fd,
	LPPACKET lpPacket,
	BOOLEAN Sync,
	BOOLEAN RecyclingAllowed)
{
	BOOLEAN Result;

	lpPacket->OverLapped.Offset = 0;
	lpPacket->OverLapped.OffsetHigh = 0;
	lpPacket->bIoComplete = FALSE;

	if (Sync) {
		Result = WriteFile(fd->hFile,
						   lpPacket->Buffer,
						   lpPacket->Length,
						   &lpPacket->BytesReceived,
						   &lpPacket->OverLapped);
		if (Result) {
			GetOverlappedResult(fd->hFile,
								&lpPacket->OverLapped,
								&lpPacket->BytesReceived,
								TRUE);
		}
		lpPacket->bIoComplete = TRUE;
		if (RecyclingAllowed)
			PacketFreePacket(lpPacket);
	}
	else {
		Result = WriteFileEx(fd->hFile,
							 lpPacket->Buffer,
							 lpPacket->Length,
							 &lpPacket->OverLapped,
							 tap_write_completion);

		if (!Result && RecyclingAllowed)
			recycle_write_packet(lpPacket);
	}

	return Result;
}