NTSTATUS
LfsSvrDatagramRecvHandler (
	IN PVOID	TdiEventContext,
	IN LONG		SourceAddressLength,
	IN PVOID	SourceAddress,
	IN LONG		OptionsLength,
	IN PVOID	Options,
	IN ULONG	ReceiveDatagramFlags,
	IN ULONG	BytesIndicated,
	IN ULONG	BytesAvailable,
	OUT ULONG   *BytesTaken,
	IN PVOID	Tsdu,
	OUT PIRP	*IoRequestPacket
	)
{
	PLFSDGRAMSVR_CTX	SvrCtx = (PLFSDGRAMSVR_CTX)TdiEventContext;
	PTRANSPORT_ADDRESS	ClientAddr = (PTRANSPORT_ADDRESS)SourceAddress;
	PLPX_ADDRESS		ClientLpxAddr = (PLPX_ADDRESS)ClientAddr->Address[0].Address;
	PLFSDG_PKT			Pkt;
	BOOLEAN				bRet;
	static UCHAR		Protocol[4] = NDFT_PROTOCOL;

	UNREFERENCED_PARAMETER( SourceAddressLength );
	UNREFERENCED_PARAMETER( OptionsLength );
	UNREFERENCED_PARAMETER( Options );
	UNREFERENCED_PARAMETER( ReceiveDatagramFlags );
	UNREFERENCED_PARAMETER( BytesTaken );
	UNREFERENCED_PARAMETER( IoRequestPacket );

#if !DBG
	UNREFERENCED_PARAMETER(BytesIndicated);
#endif

	// BytesIndicated, BytesAvailable, BytesTaken
	
	SPY_LOG_PRINT( LFS_DEBUG_LIB_NOISE, 
				   ("[LFS] LfsSvrDatagramRecvHandler: BytesIndicated : %d BytesAvailable : %d\n",
					BytesIndicated, BytesAvailable) );

	if (BytesAvailable < sizeof(NDFT_HEADER) ) {
		
		SPY_LOG_PRINT( LFS_DEBUG_LIB_INFO, ( "[LFS] LfsSvrDatagramRecvHandler: too small bytes.\n" ) );
		goto not_accepted;
	}

	bRet = LfsAllocDGPkt( &Pkt, MAX_DATAGRAM_DATA_SIZE );
	
	if (FALSE == bRet) {
	
		SPY_LOG_PRINT( LFS_DEBUG_LIB_INFO, ( "[LFS] LfsSvrDatagramRecvHandler: LfsAllocDGPkt() failed.\n") );
		goto not_accepted;
	}

	//	read the head

	RtlCopyMemory( &Pkt->RawHeadDG, Tsdu, sizeof(Pkt->RawHeadDG) );

	//	validation check

	SPY_LOG_PRINT( LFS_DEBUG_LIB_NOISE, 
					("[LFS] LfsSvrDatagramRecvHandler: Protocol:%lx Ver:%x.%x TotalSize:%ld"
					 " Type:%x\n",
					 *((ULONG *)Pkt->RawHeadDG.Protocol), 
					 NTOHS(Pkt->RawHeadDG.NdfsMajorVersion2), 
					 NTOHS(Pkt->RawHeadDG.NdfsMinorVersion2),
					 NTOHL(Pkt->RawHeadDG.MessageSize4), 
					 NTOHS(Pkt->RawHeadDG.Type2)) );

	if (RtlCompareMemory(Pkt->RawHeadDG.Protocol, Protocol, 4) != 4 ||
		NTOHS(Pkt->RawHeadDG.NdfsMajorVersion2) != NDFT_MAJVER		||
		NTOHS(Pkt->RawHeadDG.NdfsMinorVersion2) != NDFT_MINVER		||
		(NTOHS(Pkt->RawHeadDG.Type2) & LFSPKTTYPE_PREFIX) != (LFSPKTTYPE_DATAGRAM | LFSPKTTYPE_REQUEST) ) {

		LfsDereferenceDGPkt(Pkt);

		SPY_LOG_PRINT( LFS_DEBUG_LIB_NOISE, ("[LFS] LfsSvrDatagramRecvHandler: Invalid reply header.\n") );
		goto not_accepted;
	}

	Pkt->PacketSize	= NTOHL(Pkt->RawHeadDG.MessageSize4);
	Pkt->DataSize	= NTOHL(Pkt->RawHeadDG.MessageSize4) - sizeof(NDFT_HEADER);

	if (Pkt->PacketSize != sizeof(NDFT_HEADER) + Pkt->DataSize ) {

		LfsDereferenceDGPkt(Pkt);
		SPY_LOG_PRINT( LFS_DEBUG_LIB_INFO, ("[LFS] LfsSvrDatagramRecvHandler: Invalid reply packet size.\n") );
		goto not_accepted;
	}

	if (BytesAvailable < Pkt->PacketSize) {
	
		LfsDereferenceDGPkt(Pkt);
		SPY_LOG_PRINT( LFS_DEBUG_LIB_INFO, ("[LFS] LfsSvrDatagramRecvHandler: wrong message size contained.\n") );
		goto not_accepted;
	}

	//	retrieve the source address.
	//	Do not trust Owner's address in the packet.

	RtlCopyMemory(&Pkt->SourceAddr, ClientLpxAddr, sizeof(LPX_ADDRESS));

	SPY_LOG_PRINT( LFS_DEBUG_LIB_NOISE, 
				  ("[LFS] LfsSvrDatagramRecvHandler:"
				   " received a datagram packet from %02X:%02X:%02X:%02X:%02X:%02X/%d\n",
				   ClientLpxAddr->Node[0],ClientLpxAddr->Node[1],ClientLpxAddr->Node[2],
				   ClientLpxAddr->Node[3],ClientLpxAddr->Node[4],ClientLpxAddr->Node[5],
				   (int)ClientLpxAddr->Port) );

	//	read the data

	RtlCopyMemory( &Pkt->RawDataDG, (PUCHAR)Tsdu + sizeof(Pkt->RawHeadDG), Pkt->DataSize );

	//	insert to the packet queue

	InitializeListHead( &Pkt->PktListEntry );

	ExInterlockedInsertTailList( &SvrCtx->RecvDGPktQueue,
								 &Pkt->PktListEntry,
								 &SvrCtx->RecvDGPktQSpinLock );

	KeSetEvent( &SvrCtx->DatagramRecvEvent, IO_NO_INCREMENT, FALSE );

	return STATUS_SUCCESS;

not_accepted:

	SPY_LOG_PRINT( LFS_DEBUG_LIB_NOISE, 
				   ("[LFS] LfsSvrDatagramRecvHandler: a datagram packet rejected.\n") );

	return STATUS_DATA_NOT_ACCEPTED;
}