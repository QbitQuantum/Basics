NTSTATUS
NdasFatSecondaryUserFsCtrl (
    IN PIRP_CONTEXT IrpContext,
    IN PIRP Irp
    )

/*++

Routine Description:

    This is the common routine for implementing the user's requests made
    through NtFsControlFile.

Arguments:

    Irp - Supplies the Irp being processed

Return Value:

    NTSTATUS - The return status for the operation

--*/

{
    NTSTATUS Status;
    ULONG FsControlCode;

    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation( Irp );

	PVOLUME_DEVICE_OBJECT		volDo = CONTAINING_RECORD( IrpContext->Vcb, VOLUME_DEVICE_OBJECT, Vcb );
	BOOLEAN						secondarySessionResourceAcquired = FALSE;

	TYPE_OF_OPEN				typeOfOpen;
	PVCB						vcb;
	PFCB						fcb;
	PCCB						ccb;

	PSECONDARY_REQUEST			secondaryRequest = NULL;

	PNDFS_REQUEST_HEADER		ndfsRequestHeader;
	PNDFS_WINXP_REQUEST_HEADER	ndfsWinxpRequestHeader;
	PNDFS_WINXP_REPLY_HEADER	ndfsWinxpReplytHeader;
	UINT8						*ndfsWinxpRequestData;

	LARGE_INTEGER				timeOut;

	struct FileSystemControl	fileSystemControl;

	PVOID						inputBuffer = NULL;
	ULONG						inputBufferLength;
	PVOID						outputBuffer = NULL;
	ULONG						outputBufferLength;
	ULONG						bufferLength;


    //
    //  Save some references to make our life a little easier
    //

    FsControlCode = IrpSp->Parameters.FileSystemControl.FsControlCode;

    DebugTrace(+1, Dbg,"FatUserFsCtrl...\n", 0);
    DebugTrace( 0, Dbg,"FsControlCode = %08lx\n", FsControlCode);

    //
    //  Some of these Fs Controls use METHOD_NEITHER buffering.  If the previous mode
    //  of the caller was userspace and this is a METHOD_NEITHER, we have the choice
    //  of realy buffering the request through so we can possibly post, or making the
    //  request synchronous.  Since the former was not done by design, do the latter.
    //

    if (Irp->RequestorMode != KernelMode && (FsControlCode & 3) == METHOD_NEITHER) {

        SetFlag( IrpContext->Flags, IRP_CONTEXT_FLAG_WAIT);
    }

    //
    //  Case on the control code.
    //

    switch ( FsControlCode ) {

    case FSCTL_REQUEST_OPLOCK_LEVEL_1:
    case FSCTL_REQUEST_OPLOCK_LEVEL_2:
    case FSCTL_REQUEST_BATCH_OPLOCK:
    case FSCTL_OPLOCK_BREAK_ACKNOWLEDGE:
    case FSCTL_OPBATCH_ACK_CLOSE_PENDING:
    case FSCTL_OPLOCK_BREAK_NOTIFY:
    case FSCTL_OPLOCK_BREAK_ACK_NO_2:
    case FSCTL_REQUEST_FILTER_OPLOCK :

		//ASSERT( FALSE );

		//Status = STATUS_SUCCESS;
		//break;

        Status = FatOplockRequest( IrpContext, Irp );
		return Status;

    case FSCTL_LOCK_VOLUME:

		FatCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace2( -1, Dbg, ("NdasFatSecondaryUserFsCtrl -> %08lx\n", Status) );
		return Status;

		//Status = FatLockVolume( IrpContext, Irp );
        break;

    case FSCTL_UNLOCK_VOLUME:

		FatCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace2( -1, Dbg, ("NdasFatSecondaryUserFsCtrl -> %08lx\n", Status) );
		return Status;

		//Status = FatUnlockVolume( IrpContext, Irp );
        break;

    case FSCTL_DISMOUNT_VOLUME:

		FatCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace2( -1, Dbg, ("NdasFatSecondaryUserFsCtrl -> %08lx\n", Status) );
		return Status;

        //Status = FatDismountVolume( IrpContext, Irp );
        break;

    case FSCTL_MARK_VOLUME_DIRTY:

		FatCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace2( -1, Dbg, ("NdasFatSecondaryUserFsCtrl -> %08lx\n", Status) );
		return Status;

		//Status = FatDirtyVolume( IrpContext, Irp );
        break;

    case FSCTL_IS_VOLUME_DIRTY:

        Status = FatIsVolumeDirty( IrpContext, Irp );
        break;

    case FSCTL_IS_VOLUME_MOUNTED:

        Status = FatIsVolumeMounted( IrpContext, Irp );

		DebugTrace2( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		break;

    case FSCTL_IS_PATHNAME_VALID:

		Status = FatIsPathnameValid( IrpContext, Irp );
		
		DebugTrace2( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		break;

    case FSCTL_QUERY_RETRIEVAL_POINTERS:
        Status = FatQueryRetrievalPointers( IrpContext, Irp );
        break;

    case FSCTL_QUERY_FAT_BPB:

		Status = FatQueryBpb( IrpContext, Irp );

		DebugTrace2( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		break;

    case FSCTL_FILESYSTEM_GET_STATISTICS:
        Status = FatGetStatistics( IrpContext, Irp );
        break;

    case FSCTL_GET_VOLUME_BITMAP:
        Status = FatGetVolumeBitmap( IrpContext, Irp );
        break;

    case FSCTL_GET_RETRIEVAL_POINTERS:
        Status = FatGetRetrievalPointers( IrpContext, Irp );
        break;

    case FSCTL_MOVE_FILE:

		FatCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace2( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;
		
		//Status = FatMoveFile( IrpContext, Irp );
        break;

    case FSCTL_ALLOW_EXTENDED_DASD_IO:
        Status = FatAllowExtendedDasdIo( IrpContext, Irp );
        break;

    default :

        DebugTrace(0, Dbg, "Invalid control code -> %08lx\n", FsControlCode );

        FatCompleteRequest( IrpContext, Irp, STATUS_INVALID_DEVICE_REQUEST );
        Status = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

	ASSERT( !ExIsResourceAcquiredSharedLite(&volDo->Vcb.Resource) );	

	if (Status != STATUS_SUCCESS) {

		DebugTrace2( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;
	}

	inputBuffer = IrpContext->InputBuffer;
	outputBuffer = IrpContext->outputBuffer;

	ASSERT( IrpSp->Parameters.FileSystemControl.InputBufferLength ? (inputBuffer != NULL) : (inputBuffer == NULL) );
	ASSERT( IrpSp->Parameters.FileSystemControl.OutputBufferLength ? (outputBuffer != NULL) : (outputBuffer == NULL) );

	ASSERT( KeGetCurrentIrql() == PASSIVE_LEVEL );

	if (!FlagOn(IrpContext->Flags, IRP_CONTEXT_FLAG_WAIT)) {

		return FatFsdPostRequest( IrpContext, Irp );
	}

	try {

		secondarySessionResourceAcquired 
			= SecondaryAcquireResourceExclusiveLite( IrpContext, 
													 &volDo->SessionResource, 
													 BooleanFlagOn(IrpContext->Flags, IRP_CONTEXT_FLAG_WAIT) );

		if (FlagOn(volDo->Secondary->Thread.Flags, SECONDARY_THREAD_FLAG_REMOTE_DISCONNECTED) ) {

			PrintIrp( Dbg2, "SECONDARY_THREAD_FLAG_REMOTE_DISCONNECTED", NULL, IrpContext->OriginatingIrp );
			NDAS_ASSERT( FlagOn(IrpContext->Flags, IRP_CONTEXT_FLAG_WAIT) );
			SetFlag( IrpContext->NdasFatFlags, NDAS_FAT_IRP_CONTEXT_FLAG_DONT_POST_REQUEST );
			FatRaiseStatus( IrpContext, STATUS_CANT_WAIT );	
		}

		ASSERT( IS_SECONDARY_FILEOBJECT(IrpSp->FileObject) );
		
		typeOfOpen = FatDecodeFileObject( IrpSp->FileObject, &vcb, &fcb, &ccb );

		if (FlagOn(ccb->NdasFatFlags, ND_FAT_CCB_FLAG_UNOPENED)) {

			ASSERT( FlagOn(ccb->NdasFatFlags, ND_FAT_CCB_FLAG_CORRUPTED) );

			try_return( Status = STATUS_FILE_CORRUPT_ERROR );
		}
		
		fileSystemControl.FsControlCode			= IrpSp->Parameters.FileSystemControl.FsControlCode;
		fileSystemControl.InputBufferLength		= IrpSp->Parameters.FileSystemControl.InputBufferLength;
		fileSystemControl.OutputBufferLength	= IrpSp->Parameters.FileSystemControl.OutputBufferLength;

		if (inputBuffer == NULL)
			fileSystemControl.InputBufferLength = 0;
		if (outputBuffer == NULL)
			fileSystemControl.OutputBufferLength = 0;

		outputBufferLength	= fileSystemControl.OutputBufferLength;
		
		if (fileSystemControl.FsControlCode == FSCTL_MOVE_FILE) {			// 29
		
			inputBufferLength = 0;			
		
		} else if (fileSystemControl.FsControlCode == FSCTL_MARK_HANDLE) {		// 63
		
			inputBufferLength = 0;			
		
		} else {
		
			inputBufferLength  = fileSystemControl.InputBufferLength;
		}
		
		bufferLength = (inputBufferLength >= outputBufferLength) ? inputBufferLength : outputBufferLength;

		secondaryRequest = AllocateWinxpSecondaryRequest( volDo->Secondary, 
														  IRP_MJ_FILE_SYSTEM_CONTROL,
														  bufferLength );

		if (secondaryRequest == NULL) {

			NDAS_ASSERT( NDAS_ASSERT_INSUFFICIENT_RESOURCES );
			Status = Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
			Irp->IoStatus.Information = 0;
			try_return( Status );
		}

		ndfsRequestHeader = &secondaryRequest->NdfsRequestHeader;
		INITIALIZE_NDFS_REQUEST_HEADER(	ndfsRequestHeader, 
										NDFS_COMMAND_EXECUTE, 
										volDo->Secondary, 
										IRP_MJ_FILE_SYSTEM_CONTROL, 
										inputBufferLength );

		ndfsWinxpRequestHeader = (PNDFS_WINXP_REQUEST_HEADER)(ndfsRequestHeader+1);
		ASSERT( ndfsWinxpRequestHeader == (PNDFS_WINXP_REQUEST_HEADER)secondaryRequest->NdfsRequestData );
		INITIALIZE_NDFS_WINXP_REQUEST_HEADER( ndfsWinxpRequestHeader, Irp, IrpSp, ccb->PrimaryFileHandle );

		ndfsWinxpRequestHeader->FileSystemControl.OutputBufferLength	= fileSystemControl.OutputBufferLength;
		ndfsWinxpRequestHeader->FileSystemControl.InputBufferLength		= fileSystemControl.InputBufferLength;
		ndfsWinxpRequestHeader->FileSystemControl.FsControlCode			= fileSystemControl.FsControlCode;

#if 0
		if (fileSystemControl.FsControlCode == FSCTL_MOVE_FILE) {		// 29
				
			PMOVE_FILE_DATA	moveFileData = inputBuffer;	
			PFILE_OBJECT	moveFileObject;
			PCCB			moveCcb;

			Status = ObReferenceObjectByHandle( moveFileData->FileHandle,
												FILE_READ_DATA,
												0,
												KernelMode,
												&moveFileObject,
												NULL );

			if (Status != STATUS_SUCCESS) {

				ASSERT( FALSE );
				try_return( Status );
			}
	
			ObDereferenceObject( moveFileObject );

			moveCcb = moveFileObject->FsContext2;

			ndfsWinxpRequestHeader->FileSystemControl.FscMoveFileData.FileHandle	= moveCcb->PrimaryFileHandle;
			ndfsWinxpRequestHeader->FileSystemControl.FscMoveFileData.StartingVcn	= moveFileData->StartingVcn.QuadPart;
			ndfsWinxpRequestHeader->FileSystemControl.FscMoveFileData.StartingLcn	= moveFileData->StartingLcn.QuadPart;
			ndfsWinxpRequestHeader->FileSystemControl.FscMoveFileData.ClusterCount	= moveFileData->ClusterCount;
		
		} else
#endif
		if (fileSystemControl.FsControlCode == FSCTL_MARK_HANDLE) {	// 63
		
			PMARK_HANDLE_INFO	markHandleInfo = inputBuffer;	
			PFILE_OBJECT		volumeFileObject;
			PCCB				volumeCcb;

			Status = ObReferenceObjectByHandle( markHandleInfo->VolumeHandle,
												FILE_READ_DATA,
												0,
												KernelMode,
												&volumeFileObject,
												NULL );

			if (Status != STATUS_SUCCESS) {

				try_return( Status );
			}
	
			ObDereferenceObject( volumeFileObject );

			volumeCcb = volumeFileObject->FsContext2;

			ndfsWinxpRequestHeader->FileSystemControl.FscMarkHandleInfo.UsnSourceInfo	= markHandleInfo->UsnSourceInfo;
			ndfsWinxpRequestHeader->FileSystemControl.FscMarkHandleInfo.VolumeHandle	= volumeCcb->PrimaryFileHandle;
			ndfsWinxpRequestHeader->FileSystemControl.FscMarkHandleInfo.HandleInfo		= markHandleInfo->HandleInfo;
		
		} else {

			ndfsWinxpRequestData = (UINT8 *)(ndfsWinxpRequestHeader+1);

			if (inputBufferLength)
				RtlCopyMemory( ndfsWinxpRequestData, inputBuffer, inputBufferLength );
		}

		ASSERT( !ExIsResourceAcquiredSharedLite(&IrpContext->Vcb->Resource) );	

		secondaryRequest->RequestType = SECONDARY_REQ_SEND_MESSAGE;
		QueueingSecondaryRequest( volDo->Secondary, secondaryRequest );

		timeOut.QuadPart = -NDASFAT_TIME_OUT;		
		Status = KeWaitForSingleObject( &secondaryRequest->CompleteEvent, Executive, KernelMode, FALSE, &timeOut );

		if (Status != STATUS_SUCCESS) {

			secondaryRequest = NULL;
			try_return( Status = STATUS_IO_DEVICE_ERROR );
		}

		KeClearEvent( &secondaryRequest->CompleteEvent );

		if (secondaryRequest->ExecuteStatus != STATUS_SUCCESS) {

			if (IrpContext->OriginatingIrp)
				PrintIrp( Dbg2, "secondaryRequest->ExecuteStatus != STATUS_SUCCESS", NULL, IrpContext->OriginatingIrp );

			DebugTrace2( 0, Dbg2, ("secondaryRequest->ExecuteStatus != STATUS_SUCCESS file = %s, line = %d\n", __FILE__, __LINE__) );

			NDAS_ASSERT( FlagOn(IrpContext->Flags, IRP_CONTEXT_FLAG_WAIT) );
			SetFlag( IrpContext->NdasFatFlags, NDAS_FAT_IRP_CONTEXT_FLAG_DONT_POST_REQUEST );
			FatRaiseStatus( IrpContext, STATUS_CANT_WAIT );
		}

		ndfsWinxpReplytHeader = (PNDFS_WINXP_REPLY_HEADER)secondaryRequest->NdfsReplyData;
		Status = Irp->IoStatus.Status = NTOHL(ndfsWinxpReplytHeader->Status4);
		Irp->IoStatus.Information = NTOHL(ndfsWinxpReplytHeader->Information32);

		if (FsControlCode == FSCTL_GET_NTFS_VOLUME_DATA && Status != STATUS_SUCCESS)
			DebugTrace2( 0, Dbg2, ("FSCTL_GET_NTFS_VOLUME_DATA: Status = %x, Irp->IoStatus.Information = %d\n", Status, Irp->IoStatus.Information) );

		if (NTOHL(secondaryRequest->NdfsReplyHeader.MessageSize4) - sizeof(NDFS_REPLY_HEADER) - sizeof(NDFS_WINXP_REPLY_HEADER)) {

			ASSERT( Irp->IoStatus.Status == STATUS_SUCCESS || Irp->IoStatus.Status == STATUS_BUFFER_OVERFLOW );
			ASSERT( Irp->IoStatus.Information );
			ASSERT( Irp->IoStatus.Information <= outputBufferLength );
			ASSERT( outputBuffer );

			RtlCopyMemory( outputBuffer,
						   (UINT8 *)(ndfsWinxpReplytHeader+1),
						   Irp->IoStatus.Information );
		}

		if (fileSystemControl.FsControlCode == FSCTL_MOVE_FILE && Status != STATUS_SUCCESS)
			DebugTrace2( 0, Dbg2, ("NtfsDefragFile: status = %x\n", Status) );

#if 0
		if (Status == STATUS_SUCCESS && fileSystemControl.FsControlCode == FSCTL_MOVE_FILE) {		// 29
				
			PMOVE_FILE_DATA	moveFileData = inputBuffer;	
			PFILE_OBJECT	moveFileObject;

			TYPE_OF_OPEN	typeOfOpen;
			PVCB			vcb;
			PFCB			moveFcb;
			PSCB			moveScb;
			PCCB			moveCcb;


			Status = ObReferenceObjectByHandle( moveFileData->FileHandle,
												FILE_READ_DATA,
												0,
												KernelMode,
												&moveFileObject,
												NULL );

			if (Status != STATUS_SUCCESS) {

				try_return( Status );
			}
	
			ObDereferenceObject( moveFileObject );
				
			typeOfOpen = NtfsDecodeFileObject( IrpContext, moveFileObject, &vcb, &moveFcb, &moveScb, &moveCcb, TRUE );
		
			if (typeOfOpen == UserFileOpen && FlagOn(volDo->NdasFatFlags, ND_FAT_DEVICE_FLAG_DIRECT_RW) && ndfsWinxpReplytHeader->FileInformationSet && NTOHLL(ndfsWinxpReplytHeader->AllocationSize8)) {

				PNDFS_FAT_MCB_ENTRY	mcbEntry;
				ULONG			index;
				VCN				testVcn;

			
				SetFlag( IrpContext->Flags, IRP_CONTEXT_FLAG_ACQUIRE_PAGING );
				NtfsAcquireFcbWithPaging( IrpContext, moveFcb, 0 );
				NtfsAcquireNtfsMcbMutex( &moveScb->Mcb );

				mcbEntry = (PNDFS_FAT_MCB_ENTRY)( ndfsWinxpReplytHeader+1 );

				if (moveScb->Header.AllocationSize.QuadPart) {

					NtfsRemoveNtfsMcbEntry( &moveScb->Mcb, 0, 0xFFFFFFFF );
				}

				for (index=0, testVcn=0; index < NTOHL(ndfsWinxpReplytHeader->NumberOfMcbEntry4); index++) {

					ASSERT( mcbEntry[index].Vcn == testVcn );
					testVcn += (LONGLONG)mcbEntry[index].ClusterCount;

					NtfsAddNtfsMcbEntry( &moveScb->Mcb, 
										 mcbEntry[index].Vcn, 
										 (mcbEntry[index].Lcn << vcb->AllocationSupport.LogOfBytesPerSector), 
										 (LONGLONG)mcbEntry[index].ClusterCount, 
										 TRUE );
				}
					
				ASSERT( LlBytesFromClusters(vcb, testVcn) == NTOHLL(ndfsWinxpReplytHeader->AllocationSize8) );

				if (moveScb->Header.AllocationSize.QuadPart != NTOHLL(ndfsWinxpReplytHeader->AllocationSize8))
					SetFlag( moveScb->ScbState, SCB_STATE_TRUNCATE_ON_CLOSE );		

				moveScb->Header.FileSize.LowPart = NTOHLL(ndfsWinxpReplytHeader->FileSize8);
				moveScb->Header.AllocationSize.QuadPart = NTOHLL(ndfsWinxpReplytHeader->AllocationSize8);
				ASSERT( moveScb->Header.AllocationSize.QuadPart >= moveScb->Header.FileSize.LowPart );

				if (moveFileObject->SectionObjectPointer->DataSectionObject != NULL && moveFileObject->PrivateCacheMap == NULL) {

					CcInitializeCacheMap( moveFileObject,
										  (PCC_FILE_SIZES)&moveScb->Header.AllocationSize,
										  FALSE,
										  &NtfsData.CacheManagerCallbacks,
										  moveScb );

					//CcSetAdditionalCacheAttributes( fileObject, TRUE, TRUE );
				}

				if (CcIsFileCached(moveFileObject)) {

					NtfsSetBothCacheSizes( moveFileObject,
										   (PCC_FILE_SIZES)&scb->Header.AllocationSize,
										   moveScb );
				}

				NtfsReleaseNtfsMcbMutex( &moveScb->Mcb );
				NtfsReleaseFcb( IrpContext, moveFcb );
			}
		}

#endif
try_exit:  NOTHING;

	} finally {

		if (secondarySessionResourceAcquired == TRUE) {

			SecondaryReleaseResourceLite( IrpContext, &volDo->SessionResource );		
		}

		if (secondaryRequest)
			DereferenceSecondaryRequest( secondaryRequest );
	}

	FatCompleteRequest( IrpContext, Irp, Status );

    DebugTrace(-1, Dbg, "FatUserFsCtrl -> %08lx\n", Status );
    return Status;
}