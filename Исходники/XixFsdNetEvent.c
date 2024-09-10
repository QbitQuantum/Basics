NTSTATUS
XixFsdSendFileChangeRC(
	IN BOOLEAN		Wait,
	IN uint8		* HostMac,
	IN uint64		LotNumber,
	IN uint8		* DiskId,
	IN uint32		PartitionId,
	IN uint64		FileLength,
	IN uint64		AllocationLength,
	IN uint64		UpdateStartOffset
)
{
	NTSTATUS							RC = STATUS_UNSUCCESSFUL;
	PXIFSDG_PKT							pPacket = NULL;
	PXIFS_FILE_LENGTH_CHANGE_BROADCAST	pPacketData = NULL;
	uint8								DstAddress[6] ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	
	DebugTrace(DEBUG_LEVEL_TRACE, (DEBUG_TARGET_RESOURCE| DEBUG_TARGET_FCB|DEBUG_TARGET_LOCK),
		("Enter XixFsdSendFileChangeRC \n"));

	ASSERT(Wait);
	
	// Changed by ILGU HONG
	//	chesung suggest
	/*
	if(FALSE ==LfsAllocDGPkt(&pPacket, HostMac, DstAddress, XIFS_TYPE_FILE_LENGTH_CHANGE))
	{
		return FALSE;
	}
	*/
	
	if(FALSE ==LfsAllocDGPkt(&pPacket, HostMac, DstAddress, XIFS_TYPE_FILE_LENGTH_CHANGE))
	{
		return FALSE;
	}



	pPacketData = &(pPacket->RawDataDG.FileLenChangeReq);
	// Changed by ILGU HONG
	//	RtlCopyMemory(pPacketData->DiskId, DiskId, 6);
	RtlCopyMemory(pPacketData->DiskId, DiskId, 16);
	pPacketData->PartionId = HTONL(PartitionId);
	pPacketData->LotNumber = HTONLL(LotNumber);
	pPacketData->FileLength = HTONLL(FileLength);
	pPacketData->AllocationLength = HTONLL(AllocationLength);
	pPacketData->WriteStartOffset =	HTONLL(UpdateStartOffset);
	pPacket->TimeOut.QuadPart = XixGetSystemTime().QuadPart + DEFAULT_REQUEST_MAX_TIMEOUT;




	ExAcquireFastMutex(&XiGlobalData.XifsComCtx.SendPktListMutex);
	InsertTailList(&(XiGlobalData.XifsComCtx.SendPktList),
								&(pPacket->PktListEntry) );
	ExReleaseFastMutex(&XiGlobalData.XifsComCtx.SendPktListMutex);

	KeSetEvent(&(XiGlobalData.XifsComCtx.CliSendDataEvent),0, FALSE);
	

	
	DebugTrace(DEBUG_LEVEL_TRACE, (DEBUG_TARGET_RESOURCE| DEBUG_TARGET_FCB|DEBUG_TARGET_LOCK),
			("Exit XixFsdSendFileChangeRC \n"));

	return STATUS_SUCCESS;	
}