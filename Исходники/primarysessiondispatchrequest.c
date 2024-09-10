static VOID
DispatchWinXpRequestWorker (
	IN  PPRIMARY_SESSION	PrimarySession,
	IN  UINT16				Mid
    )
{
	PNDFS_REQUEST_HEADER		ndfsRequestHeader = (PNDFS_REQUEST_HEADER)PrimarySession->Thread.SessionSlot[Mid].RequestMessageBuffer;
	PNDFS_REPLY_HEADER			ndfsReplyHeader = (PNDFS_REPLY_HEADER)PrimarySession->Thread.SessionSlot[Mid].ReplyMessageBuffer; 
	PNDFS_WINXP_REQUEST_HEADER	ndfsWinxpRequestHeader = PrimarySession->Thread.SessionSlot[Mid].NdfsWinxpRequestHeader;
	
	UINT32						replyDataSize;

	
	ASSERT(Mid == NTOHS(ndfsRequestHeader->Mid2));
	
    DebugTrace2( 0, Dbg, ("DispatchWinXpRequestWorker: entered PrimarySession = %p, ndfsRequestHeader->Command = %d\n", 
						  PrimarySession, ndfsRequestHeader->Command));

	ASSERT( PrimarySession->Thread.SessionSlot[Mid].State == SLOT_EXECUTING );


	replyDataSize = CaculateReplyDataLength(PrimarySession, ndfsWinxpRequestHeader);

	if (replyDataSize <= (ULONG)(PrimarySession->SessionContext.SecondaryMaxDataSize || 
	    sizeof(PrimarySession->Thread.SessionSlot[Mid].ReplyMessageBuffer) - sizeof(NDFS_REPLY_HEADER) - sizeof(NDFS_WINXP_REQUEST_HEADER))) {

		if (ndfsRequestHeader->MessageSecurity == 1) {

			if (ndfsWinxpRequestHeader->IrpMajorFunction == IRP_MJ_READ && PrimarySession->SessionContext.RwDataSecurity == 0)
				PrimarySession->Thread.SessionSlot[Mid].NdfsWinxpReplyHeader = (PNDFS_WINXP_REPLY_HEADER)(ndfsReplyHeader+1);
			else
				PrimarySession->Thread.SessionSlot[Mid].NdfsWinxpReplyHeader = (PNDFS_WINXP_REPLY_HEADER)PrimarySession->Thread.SessionSlot[Mid].CryptWinxpMessageBuffer;
		}
		else
			PrimarySession->Thread.SessionSlot[Mid].NdfsWinxpReplyHeader = (PNDFS_WINXP_REPLY_HEADER)(ndfsReplyHeader+1);
	
	} else {

		PrimarySession->Thread.SessionSlot[Mid].ExtendWinxpReplyMessagePoolLength = 
			ADD_ALIGN8(sizeof(NDFS_WINXP_REPLY_HEADER) + replyDataSize);
		PrimarySession->Thread.SessionSlot[Mid].ExtendWinxpReplyMessagePool = 
			ExAllocatePoolWithTag( NonPagedPool,
								   PrimarySession->Thread.SessionSlot[Mid].ExtendWinxpReplyMessagePoolLength,
								   PRIMARY_SESSION_BUFFERE_TAG );

		ASSERT( PrimarySession->Thread.SessionSlot[Mid].ExtendWinxpReplyMessagePool );

		if (PrimarySession->Thread.SessionSlot[Mid].ExtendWinxpReplyMessagePool == NULL) {
	
			DebugTrace2( 0, Dbg, ("failed to allocate ExtendWinxpReplyMessagePool\n"));
			goto fail_replypoolalloc;
		}

		PrimarySession->Thread.SessionSlot[Mid].NdfsWinxpReplyHeader 
			= (PNDFS_WINXP_REPLY_HEADER)PrimarySession->Thread.SessionSlot[Mid].ExtendWinxpReplyMessagePool;
	}
	
    DebugTrace2( 0, Dbg,
				 ("DispatchWinXpRequestWorker: PrimarySession = %p, ndfsRequestHeader->Command = %d\n", 
				  PrimarySession, ndfsRequestHeader->Command) );

	PrimarySession->Thread.SessionSlot[Mid].Status = 
		DispatchWinXpRequest( PrimarySession, 
							  ndfsWinxpRequestHeader,
							  PrimarySession->Thread.SessionSlot[Mid].NdfsWinxpReplyHeader,
							  NTOHL(ndfsRequestHeader->MessageSize4) - sizeof(NDFS_REQUEST_HEADER) - sizeof(NDFS_WINXP_REQUEST_HEADER),
							  &PrimarySession->Thread.SessionSlot[Mid].ReplyDataSize );

    DebugTrace2( 0, Dbg, ("DispatchWinXpRequestWorker: Return PrimarySession = %p, ndfsRequestHeader->Command = %d\n", 
						  PrimarySession, ndfsRequestHeader->Command) );

fail_replypoolalloc:
	PrimarySession->Thread.SessionSlot[Mid].State = SLOT_FINISH;

	KeSetEvent( &PrimarySession->Thread.WorkCompletionEvent, IO_NO_INCREMENT, FALSE );

	return;
}