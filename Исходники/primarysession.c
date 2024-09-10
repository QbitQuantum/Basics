NTSTATUS
SendNdfsWinxpMessage (
	IN PPRIMARY_SESSION			PrimarySession,
	IN PNDFS_REPLY_HEADER		NdfsReplyHeader, 
	IN PNDFS_WINXP_REPLY_HEADER	NdfsWinxpReplyHeader,
	IN UINT32						ReplyDataSize,
	IN UINT16						Mid
	)
{
	NTSTATUS	tdiStatus;
	UINT32		remaninigDataSize;		



	//
	//	If the replying data is less than max data size for the secondary,
	//	Send header and body at a time and return to the caller
	//

	if (ReplyDataSize <= PrimarySession->SessionContext.SecondaryMaxDataSize) {

		//int desResult;
		UINT8 *cryptWinxpRequestMessage = PrimarySession->Thread.SessionSlot[Mid].CryptWinxpMessageBuffer;

		//
		//	Set up reply NDFS header
		//

		RtlCopyMemory( NdfsReplyHeader->Protocol, NDFS_PROTOCOL, sizeof(NdfsReplyHeader->Protocol) );

		NdfsReplyHeader->Status		= NDFS_SUCCESS;
		NdfsReplyHeader->Flags	    = PrimarySession->SessionContext.Flags;
		NdfsReplyHeader->Uid2		= HTONS(PrimarySession->SessionContext.Uid);
		NdfsReplyHeader->Tid2		= HTONS(PrimarySession->SessionContext.Tid);
		NdfsReplyHeader->Mid2		= HTONS(Mid);
		NdfsReplyHeader->MessageSize4 = sizeof(NDFS_REPLY_HEADER) + 
									   (PrimarySession->SessionContext.MessageSecurity ? 
									    ADD_ALIGN8(sizeof(NDFS_WINXP_REPLY_HEADER) + ReplyDataSize) : (sizeof(NDFS_WINXP_REPLY_HEADER) + ReplyDataSize));

		NdfsReplyHeader->MessageSize4 = HTONL(NdfsReplyHeader->MessageSize4);

		ASSERT( HTONL(NdfsReplyHeader->MessageSize4) <= PrimarySession->Thread.SessionSlot[Mid].ReplyMessageBufferLength );

		tdiStatus = SendMessage( PrimarySession->ConnectionFileObject,
								 &PrimarySession->SendNdasFcStatistics,
								 NULL,
								 (UINT8 *)NdfsReplyHeader,
								 sizeof(NDFS_REPLY_HEADER) );

		if (tdiStatus != STATUS_SUCCESS) {

			return tdiStatus;
		}
		

		//
		//	If message security is not set,
		//	send a header and body in raw, and return to the caller.
		//

		if (PrimarySession->SessionContext.MessageSecurity == 0) {

			tdiStatus = SendMessage( PrimarySession->ConnectionFileObject,
									 &PrimarySession->SendNdasFcStatistics,
									 NULL,
									 (UINT8 *)NdfsWinxpReplyHeader,
									 NTOHL(NdfsReplyHeader->MessageSize4) - sizeof(NDFS_REPLY_HEADER) );

			return tdiStatus;
		}

		ASSERT( FALSE );

#if 0

		if(NdfsWinxpReplyHeader->IrpMajorFunction == IRP_MJ_READ)
				SPY_LOG_PRINT( LFS_DEBUG_PRIMARY_NOISE,
					("DispatchRequest: PrimarySession->SessionContext.RwDataSecurity = %d\n", PrimarySession->SessionContext.RwDataSecurity));

		if(NdfsWinxpReplyHeader->IrpMajorFunction == IRP_MJ_READ && PrimarySession->SessionContext.RwDataSecurity == 0)
			{
			RtlCopyMemory(cryptWinxpRequestMessage, NdfsWinxpReplyHeader, sizeof(NDFS_WINXP_REPLY_HEADER));
			RtlZeroMemory(&PrimarySession->DesCbcContext, sizeof(PrimarySession->DesCbcContext));
			RtlZeroMemory(PrimarySession->Iv, sizeof(PrimarySession->Iv));
			DES_CBCInit(&PrimarySession->DesCbcContext, PrimarySession->NetdiskPartition->NetdiskPartitionInformation.NetdiskInformation.Password, PrimarySession->Iv, DES_ENCRYPT);
			desResult = DES_CBCUpdate(&PrimarySession->DesCbcContext, (UINT8 *)NdfsWinxpReplyHeader, cryptWinxpRequestMessage, sizeof(NDFS_WINXP_REPLY_HEADER));
			ASSERT(desResult == IDOK);

			tdiStatus = SendMessage(
							PrimarySession->ConnectionFileObject,
							(UINT8 *)NdfsWinxpReplyHeader,
							NdfsReplyHeader->MessageSize - sizeof(NDFS_REPLY_HEADER),
							NULL,
							&PrimarySession->Thread.TransportCtx
							);
			}
			else
			{
			RtlZeroMemory(&PrimarySession->DesCbcContext, sizeof(PrimarySession->DesCbcContext));
			RtlZeroMemory(PrimarySession->Iv, sizeof(PrimarySession->Iv));
			DES_CBCInit(&PrimarySession->DesCbcContext, PrimarySession->NetdiskPartition->NetdiskPartitionInformation.NetdiskInformation.Password, PrimarySession->Iv, DES_ENCRYPT);
			desResult = DES_CBCUpdate(&PrimarySession->DesCbcContext, cryptWinxpRequestMessage, (UINT8 *)NdfsWinxpReplyHeader, NdfsReplyHeader->MessageSize-sizeof(NDFS_REPLY_HEADER));
			ASSERT(desResult == IDOK);

			tdiStatus = SendMessage(
							PrimarySession->ConnectionFileObject,
							cryptWinxpRequestMessage,
							NdfsReplyHeader->MessageSize - sizeof(NDFS_REPLY_HEADER),
							NULL,
							&PrimarySession->Thread.TransportCtx
							);
		}

		//
		//	Return to the caller
		//

		return tdiStatus;

#endif

	}


	ASSERT( (UINT8 *)NdfsWinxpReplyHeader == PrimarySession->Thread.SessionSlot[Mid].ExtendWinxpReplyMessagePool );
	ASSERT( ReplyDataSize > PrimarySession->SessionContext.SecondaryMaxDataSize );

	RtlCopyMemory( NdfsReplyHeader->Protocol, NDFS_PROTOCOL, sizeof(NdfsReplyHeader->Protocol) );
	NdfsReplyHeader->Status		= NDFS_SUCCESS;
	NdfsReplyHeader->Flags	    = PrimarySession->SessionContext.Flags;
	NdfsReplyHeader->Splitted	= 1;	// indicate the split.
	NdfsReplyHeader->Uid2		= HTONS(PrimarySession->SessionContext.Uid);
	NdfsReplyHeader->Tid2		= HTONS(PrimarySession->SessionContext.Tid);
	NdfsReplyHeader->Mid2		= 0;
	NdfsReplyHeader->MessageSize4 = sizeof(NDFS_REPLY_HEADER) + 
								   (PrimarySession->SessionContext.MessageSecurity ? 
									ADD_ALIGN8(sizeof(NDFS_WINXP_REPLY_HEADER) + ReplyDataSize) : (sizeof(NDFS_WINXP_REPLY_HEADER) + ReplyDataSize) );

	NdfsReplyHeader->MessageSize4 = HTONL(NdfsReplyHeader->MessageSize4);

	//
	//	Send reply NDFS header
	//

	tdiStatus = SendMessage( PrimarySession->ConnectionFileObject,
							 &PrimarySession->SendNdasFcStatistics,
							 NULL,
							 (UINT8 *)NdfsReplyHeader,
							 sizeof(NDFS_REPLY_HEADER) );

	if (tdiStatus != STATUS_SUCCESS) {

		return tdiStatus;
	} 

	//
	//	Send reply WinXp header
	//

#if 0

	if(PrimarySession->SessionContext.MessageSecurity)
	{
		int desResult;
		UINT8 *cryptWinxpRequestMessage = PrimarySession->Thread.SessionSlot[Mid].CryptWinxpMessageBuffer;

		RtlZeroMemory(&PrimarySession->DesCbcContext, sizeof(PrimarySession->DesCbcContext));
		RtlZeroMemory(PrimarySession->Iv, sizeof(PrimarySession->Iv));
		DES_CBCInit(&PrimarySession->DesCbcContext,
					PrimarySession->NetdiskPartition->NetdiskPartitionInformation.NetdiskInformation.Password, 
					PrimarySession->Iv, DES_ENCRYPT);
		desResult = DES_CBCUpdate(&PrimarySession->DesCbcContext,
								cryptWinxpRequestMessage,
								(UINT8 *)NdfsWinxpReplyHeader,
								sizeof(NDFS_WINXP_REPLY_HEADER));
		ASSERT(desResult == IDOK);
	
		tdiStatus = SendMessage(
					PrimarySession->ConnectionFileObject,
					cryptWinxpRequestMessage,
					sizeof(NDFS_WINXP_REPLY_HEADER),
					NULL,
					&PrimarySession->Thread.TransportCtx
					);
	}
	else
#endif
	{

		tdiStatus = SendMessage( PrimarySession->ConnectionFileObject,
								 &PrimarySession->SendNdasFcStatistics,
								 NULL,
								 (UINT8 *)NdfsWinxpReplyHeader,
								 sizeof(NDFS_WINXP_REPLY_HEADER) );
	} 

	if (tdiStatus != STATUS_SUCCESS) {
	
		return tdiStatus;
	}


	//
	//	Send data body
	//

	remaninigDataSize = ReplyDataSize;

	while(1)
	{

		//
		//	Set up reply NDFS header
		//

		RtlCopyMemory(NdfsReplyHeader->Protocol, NDFS_PROTOCOL, sizeof(NdfsReplyHeader->Protocol));
		NdfsReplyHeader->Status		= NDFS_SUCCESS;
		NdfsReplyHeader->Flags	    = PrimarySession->SessionContext.Flags;
		NdfsReplyHeader->Uid2		= HTONS(PrimarySession->SessionContext.Uid);
		NdfsReplyHeader->Tid2		= HTONS(PrimarySession->SessionContext.Tid);
		NdfsReplyHeader->Mid2		= 0;
		NdfsReplyHeader->MessageSize4 
				= sizeof(NDFS_REPLY_HEADER) 
					+ (PrimarySession->SessionContext.MessageSecurity ?
					ADD_ALIGN8(remaninigDataSize) : remaninigDataSize);

		NdfsReplyHeader->MessageSize4 = HTONL(NdfsReplyHeader->MessageSize4);

		if(remaninigDataSize > PrimarySession->SessionContext.SecondaryMaxDataSize)
			NdfsReplyHeader->Splitted = 1;
		else
			NdfsReplyHeader->Splitted = 0;

		//
		//	Send NDFS reply header
		//

		tdiStatus = SendMessage( PrimarySession->ConnectionFileObject,
								 &PrimarySession->SendNdasFcStatistics,
								 NULL,
								 (UINT8 *)NdfsReplyHeader,
								 sizeof(NDFS_REPLY_HEADER) );

		if(tdiStatus != STATUS_SUCCESS)
		{
			return tdiStatus;
		}
		//
		//	Send a part of data body
		//

#if 0

		if(PrimarySession->SessionContext.MessageSecurity)
		{
			int desResult;
			UINT8 *cryptNdfsWinxpReplyHeader = PrimarySession->Thread.SessionSlot[Mid].CryptWinxpMessageBuffer;

			desResult = DES_CBCUpdate(
							&PrimarySession->DesCbcContext, 
							cryptNdfsWinxpReplyHeader, 
							(UINT8 *)(NdfsWinxpReplyHeader+1) + (ReplyDataSize - remaninigDataSize), 
							NdfsReplyHeader->Splitted ?
								PrimarySession->SessionContext.SecondaryMaxDataSize :
								(NdfsReplyHeader->MessageSize - sizeof(NDFS_REPLY_HEADER))
							);
			ASSERT(desResult == IDOK);

			tdiStatus = SendMessage(
							PrimarySession->ConnectionFileObject,
							cryptNdfsWinxpReplyHeader,
							NdfsReplyHeader->Splitted ?
								PrimarySession->SessionContext.SecondaryMaxDataSize :
								(NdfsReplyHeader->MessageSize - sizeof(NDFS_REPLY_HEADER)),
							NULL,
							&PrimarySession->Thread.TransportCtx
							);
		}
		else
#endif
		{	

		tdiStatus = SendMessage( PrimarySession->ConnectionFileObject,
								 &PrimarySession->SendNdasFcStatistics,
								 NULL,
								 (UINT8 *)(NdfsWinxpReplyHeader+1) + (ReplyDataSize - remaninigDataSize),
								 NdfsReplyHeader->Splitted ? 
									PrimarySession->SessionContext.SecondaryMaxDataSize :
									(NTOHL(NdfsReplyHeader->MessageSize4) - sizeof(NDFS_REPLY_HEADER)) );
		}

		if(tdiStatus != STATUS_SUCCESS)
		{
			return tdiStatus;
		}

		//
		//	Decrease remaining bytes
		//

		if(NdfsReplyHeader->Splitted)
			remaninigDataSize -= PrimarySession->SessionContext.SecondaryMaxDataSize;
		else
			return STATUS_SUCCESS;


		ASSERT((INT32)remaninigDataSize > 0);
	}
}