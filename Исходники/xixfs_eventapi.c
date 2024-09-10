NTSTATUS
xixfs_SendRenameLinkBC(
	IN BOOLEAN		Wait,
	IN uint32		SubCommand,
	IN uint8		* HostMac,
	IN uint64		LotNumber,
	IN uint8		* VolumeId,
	IN uint64		OldParentLotNumber,
	IN uint64		NewParentLotNumber
)
{
	NTSTATUS						RC = STATUS_UNSUCCESSFUL;
	PXIXFSDG_PKT						pPacket = NULL;
	PXIXFS_FILE_CHANGE_BROADCAST		pPacketData = NULL;
	XIFS_LOCK_CONTROL				LockControl;
	uint8							DstAddress[6] ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	
	DebugTrace(DEBUG_LEVEL_TRACE, (DEBUG_TARGET_RESOURCE| DEBUG_TARGET_FCB|DEBUG_TARGET_LOCK),
		("Enter XifsdSendRenameLinkBC \n"));

	ASSERT(Wait);
	
	// Changed by ILGU HONG
	//	chesung suggest
	/*
	if(FALSE ==xixfs_AllocDGPkt(&pPacket, HostMac, DstAddress, XIXFS_TYPE_FILE_CHANGE))
	{
		return FALSE;
	}
	*/
	if(FALSE ==xixfs_AllocDGPkt(&pPacket, HostMac, NULL, XIXFS_TYPE_FILE_CHANGE))
	{
		return FALSE;
	}

	pPacketData = &(pPacket->RawDataDG.FileChangeReq);
	// Changed by ILGU HONG
	RtlCopyMemory(pPacketData->VolumeId, VolumeId, 16);
	pPacketData->LotNumber = HTONLL(LotNumber);
	pPacketData->PrevParentLotNumber = HTONLL(OldParentLotNumber);
	pPacketData->NewParentLotNumber = HTONLL(NewParentLotNumber);
	pPacketData->SubCommand =HTONL(SubCommand);

	pPacket->TimeOut.QuadPart = xixcore_GetCurrentTime64() + DEFAULT_REQUEST_MAX_TIMEOUT;




	ExAcquireFastMutexUnsafe(&XiGlobalData.XifsComCtx.SendPktListMutex);
	InsertTailList(&(XiGlobalData.XifsComCtx.SendPktList),
								&(pPacket->PktListEntry) );
	ExReleaseFastMutexUnsafe(&XiGlobalData.XifsComCtx.SendPktListMutex);

	KeSetEvent(&(XiGlobalData.XifsComCtx.CliSendDataEvent),0, FALSE);
	

	
	DebugTrace(DEBUG_LEVEL_TRACE, (DEBUG_TARGET_RESOURCE| DEBUG_TARGET_FCB|DEBUG_TARGET_LOCK),
			("Exit XifsdSendRenameLinkBC \n"));

	return STATUS_SUCCESS;	
}