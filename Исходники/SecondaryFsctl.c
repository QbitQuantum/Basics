static NTSTATUS
NdasNtfsSecondaryUserFsRequest (
    IN PIRP_CONTEXT IrpContext,
    IN PIRP			Irp
    )
{
    NTSTATUS			Status = STATUS_SUCCESS;
    ULONG				FsControlCode;
    ULONG				FsControlCodeFunction;
    PIO_STACK_LOCATION	IrpSp;

	PVOLUME_DEVICE_OBJECT		volDo = CONTAINING_RECORD( IrpContext->Vcb, VOLUME_DEVICE_OBJECT, Vcb );
	BOOLEAN						secondarySessionResourceAcquired = FALSE;

	TYPE_OF_OPEN				typeOfOpen;
	PVCB						vcb;
	PFCB						fcb;
	PSCB						scb;
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


    ASSERT_IRP_CONTEXT( IrpContext );
    ASSERT_IRP( Irp );

    PAGED_CODE();

	ASSERT( KeGetCurrentIrql() == PASSIVE_LEVEL );

    IrpSp = IoGetCurrentIrpStackLocation( Irp );

    FsControlCode = IrpSp->Parameters.FileSystemControl.FsControlCode;
	FsControlCodeFunction = (FsControlCode & 0x00003FFC) >> 2;

    DebugTrace( +1, Dbg, ("NtfsUserFsRequest, FsControlCode = %08lx, FsControlCodeFunction = %d\n", FsControlCode, FsControlCodeFunction) );

    switch ( FsControlCode ) {

    case FSCTL_REQUEST_OPLOCK_LEVEL_1:
    case FSCTL_REQUEST_OPLOCK_LEVEL_2:
    case FSCTL_REQUEST_BATCH_OPLOCK:
    case FSCTL_REQUEST_FILTER_OPLOCK:
    case FSCTL_OPLOCK_BREAK_ACKNOWLEDGE:
    case FSCTL_OPLOCK_BREAK_NOTIFY:
    case FSCTL_OPBATCH_ACK_CLOSE_PENDING :
    case FSCTL_OPLOCK_BREAK_ACK_NO_2:

		ASSERT( FALSE );
        //Status = NtfsOplockRequest( IrpContext, Irp );
        break;

	case FSCTL_LOCK_VOLUME: 
	
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		//Status = NtfsLockVolume( IrpContext, Irp );
        break;
	
    case FSCTL_UNLOCK_VOLUME:

		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		//Status = NtfsUnlockVolume( IrpContext, Irp );
        break;

	case FSCTL_DISMOUNT_VOLUME: {

#if 0
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;
#else

		BOOLEAN	secondaryCreateResourceAcquired = FALSE;

		ASSERT( IS_WINDOWSVISTA_OR_LATER() );

		do {
		
			BOOLEAN secondaryRecoveryResourceAcquired;

			DebugTrace( 0, Dbg, ("%s: IRP_MN_QUERY_REMOVE_DEVICE volDo = %p, NetdiskEnableMode = %d\n", 
								   __FUNCTION__, volDo, volDo->NetdiskEnableMode) );

			secondaryRecoveryResourceAcquired 
				= SecondaryAcquireResourceExclusiveLite( IrpContext, 
														 &volDo->RecoveryResource, 
														 FALSE );
			
			if (secondaryRecoveryResourceAcquired == FALSE) {

				Status = STATUS_ACCESS_DENIED;
				break;
			}

			SecondaryReleaseResourceLite( IrpContext, &volDo->RecoveryResource );

			ExAcquireFastMutex( &volDo->Secondary->FastMutex );	

			if (!volDo->Secondary->TryCloseActive) {
				
				volDo->Secondary->TryCloseActive = TRUE;
				ExReleaseFastMutex( &volDo->Secondary->FastMutex );
				Secondary_Reference( volDo->Secondary );
				//NtfsDebugTraceLevel |= DEBUG_TRACE_CLOSE;
				SecondaryTryClose( &IrpContext, volDo->Secondary );
				//NtfsDebugTraceLevel &= ~DEBUG_TRACE_CLOSE;
				
			} else {
				
				ExReleaseFastMutex( &volDo->Secondary->FastMutex );
			}

			if (volDo->Vcb.SecondaryCloseCount) {

				LARGE_INTEGER interval;

				// Wait all files closed
				interval.QuadPart = (-1 * NANO100_PER_SEC);      //delay 1 seconds
				KeDelayExecutionThread(KernelMode, FALSE, &interval);
			}

			CcWaitForCurrentLazyWriterActivity();

			secondaryCreateResourceAcquired 
				= SecondaryAcquireResourceExclusiveLite( IrpContext, 
														 &volDo->CreateResource, 
														 BooleanFlagOn(IrpContext->State, IRP_CONTEXT_STATE_WAIT) );

			if (secondaryCreateResourceAcquired == FALSE) {

				Status = STATUS_ACCESS_DENIED;
				break;
			}

			if (volDo->Vcb.SecondaryCloseCount) {

				LONG		ccbCount;
				PLIST_ENTRY	ccbListEntry;
				PVOID		restartKey;
				PFCB		fcb;

				ExAcquireFastMutex( &volDo->Secondary->RecoveryCcbQMutex );

			    for (ccbCount = 0, ccbListEntry = volDo->Secondary->RecoveryCcbQueue.Flink; 
					 ccbListEntry != &volDo->Secondary->RecoveryCcbQueue; 
					 ccbListEntry = ccbListEntry->Flink, ccbCount++);

				ExReleaseFastMutex( &volDo->Secondary->RecoveryCcbQMutex );

				ASSERT( !IsListEmpty(&volDo->Secondary->RecoveryCcbQueue) );
				ASSERT( ccbCount == volDo->Vcb.SecondaryCloseCount );

				DebugTrace( 0, Dbg, ("IRP_MN_QUERY_REMOVE_DEVICE: Vcb->SecondaryCloseCount = %d, Vcb->SecondaryCleanupCount = %d, Vcb->CloseCount = %d, ccbCount = %d\n",
			                          volDo->Vcb.SecondaryCloseCount, volDo->Vcb.SecondaryCleanupCount, volDo->Vcb.CloseCount, ccbCount) );

				restartKey = NULL;
				fcb = NdasNtfsGetNextFcbTableEntry( &volDo->Vcb, &restartKey );
				ASSERT( fcb != NULL || !IsListEmpty(&volDo->Secondary->DeletedFcbQueue) );

				Status = STATUS_ACCESS_DENIED;

				break;

			} else {

				Status = STATUS_SUCCESS;
				SetFlag( volDo->Secondary->Flags, SECONDARY_FLAG_DISMOUNTING );
			}
		
		} while(0);

		if (Status != STATUS_SUCCESS) {

			if (secondaryCreateResourceAcquired) {

				SecondaryReleaseResourceLite( IrpContext, &volDo->CreateResource );
				secondaryCreateResourceAcquired = FALSE;
			}

			NtfsCompleteRequest( IrpContext, Irp, Status );

			DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
			return Status;
		}

		Status = NtfsDismountVolume( IrpContext, Irp );

		SecondaryReleaseResourceLite( IrpContext, &volDo->CreateResource );

		return Status;

#endif
		break;
	}

    case FSCTL_IS_VOLUME_MOUNTED:

        Status = NtfsIsVolumeMounted( IrpContext, Irp );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;
		
        break;

    case FSCTL_MARK_VOLUME_DIRTY:

		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

        //Status = NtfsDirtyVolume( IrpContext, Irp );
        break;

    case FSCTL_IS_PATHNAME_VALID:
		
        NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_SUCCESS );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;
		
        break;

    case FSCTL_QUERY_RETRIEVAL_POINTERS:
        
		Status = NtfsQueryRetrievalPointers( IrpContext, Irp );
		break;

    case FSCTL_GET_COMPRESSION:
        
		//NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_INVALID_DEVICE_REQUEST );

		//DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		//return Status;

		Status = NtfsGetCompression( IrpContext, Irp );
		break;

    case FSCTL_SET_COMPRESSION:

		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_INVALID_DEVICE_REQUEST );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		Status = NtfsSetCompression( IrpContext, Irp );
        break;

    case FSCTL_MARK_AS_SYSTEM_HIVE:
        
		Status = NtfsMarkAsSystemHive( IrpContext, Irp );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		break;

    case FSCTL_FILESYSTEM_GET_STATISTICS:
        
		Status = NtfsGetStatistics( IrpContext, Irp );
        break;

    case FSCTL_GET_NTFS_VOLUME_DATA:
        
		Status = NtfsGetVolumeData( IrpContext, Irp );
        break;

    case FSCTL_GET_VOLUME_BITMAP:
        
		Status = NtfsGetVolumeBitmap( IrpContext, Irp );
        break;

    case FSCTL_GET_RETRIEVAL_POINTERS:
        
		Status = NtfsGetRetrievalPointers( IrpContext, Irp );
		break;

    case FSCTL_GET_NTFS_FILE_RECORD:
        
		Status = NtfsGetMftRecord( IrpContext, Irp );
		break;

	case FSCTL_MOVE_FILE: 

		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		Status = NtfsDefragFile( IrpContext, Irp );

		if (Status == STATUS_SUCCESS) {

			PMOVE_FILE_DATA	moveFileData = IrpContext->InputBuffer;	
			PFILE_OBJECT	moveFileObject;
			

			Status = ObReferenceObjectByHandle( moveFileData->FileHandle,
												FILE_READ_DATA,
												0,
												KernelMode,
												&moveFileObject,
												NULL );

			if (Status != STATUS_SUCCESS) {

				break;
			}
	
			ObDereferenceObject( moveFileObject );

			if (!IS_SECONDARY_FILEOBJECT(moveFileObject)) {

				ASSERT( FALSE );
				Status = STATUS_INVALID_PARAMETER;
			}
		} 

		if (Status != STATUS_SUCCESS)
			DebugTrace( 0, Dbg2, ("NtfsDefragFile: status = %x\n", Status) );

        break;

	case FSCTL_IS_VOLUME_DIRTY: 

		Status = NtfsIsVolumeDirty( IrpContext, Irp );
        break;

    case FSCTL_ALLOW_EXTENDED_DASD_IO:
        
		Status = NtfsSetExtendedDasdIo( IrpContext, Irp );
		break;

	case FSCTL_SET_REPARSE_POINT: 

		Status = NtfsSetReparsePoint( IrpContext, Irp );
        break;

    case FSCTL_GET_REPARSE_POINT:
        
		Status = NtfsGetReparsePoint( IrpContext, Irp );
		break;

    case FSCTL_DELETE_REPARSE_POINT:
        
		Status = NtfsDeleteReparsePoint( IrpContext, Irp );
        break;

    case FSCTL_SET_OBJECT_ID:
        
		Status = NtfsSetObjectId( IrpContext, Irp );                // In ObjIdSup.c
		break;

    case FSCTL_GET_OBJECT_ID:
        
		Status = NtfsGetObjectId( IrpContext, Irp );                // In ObjIdSup.c
		break;

    case FSCTL_DELETE_OBJECT_ID:
        
		Status = NtfsDeleteObjectId( IrpContext, Irp );             // In ObjIdSup.c
        break;

    case FSCTL_SET_OBJECT_ID_EXTENDED:
        
		Status = NtfsSetObjectIdExtendedInfo( IrpContext, Irp );    // In ObjIdSup.c
        break;

    case FSCTL_CREATE_OR_GET_OBJECT_ID:
        
		Status = NtfsCreateOrGetObjectId( IrpContext, Irp );

		if (IrpSp->Parameters.FileSystemControl.InputBufferLength)
			IrpContext->InputBuffer = Irp->AssociatedIrp.SystemBuffer;
		else
			IrpContext->InputBuffer = NULL;

        break;

    case FSCTL_READ_USN_JOURNAL:
        
		Status = NtfsReadUsnJournal( IrpContext, Irp, TRUE );     //  In UsnSup.c
        break;

    case FSCTL_CREATE_USN_JOURNAL:
        
		Status = NtfsCreateUsnJournal( IrpContext, Irp );
        break;

    case FSCTL_ENUM_USN_DATA:
        
		Status = NtfsReadFileRecordUsnData( IrpContext, Irp );
        break;

    case FSCTL_READ_FILE_USN_DATA:
        
		Status = NtfsReadFileUsnData( IrpContext, Irp );
        break;

    case FSCTL_WRITE_USN_CLOSE_RECORD:
        
		Status = NtfsWriteUsnCloseRecord( IrpContext, Irp );
        break;

    case FSCTL_QUERY_USN_JOURNAL:
        
		Status = NtfsQueryUsnJournal( IrpContext, Irp );
        break;

    case FSCTL_DELETE_USN_JOURNAL:
        
		Status = NtfsDeleteUsnJournal( IrpContext, Irp );
        break;

    case FSCTL_MARK_HANDLE:
        
		Status = NtfsMarkHandle( IrpContext, Irp );

		if (Status == STATUS_SUCCESS) {

			PMARK_HANDLE_INFO	markHandleInfo = inputBuffer;	
			PFILE_OBJECT		volumeFileObject;
			

			Status = ObReferenceObjectByHandle( markHandleInfo->VolumeHandle,
												FILE_READ_DATA,
												0,
												KernelMode,
												&volumeFileObject,
												NULL );

			if (Status != STATUS_SUCCESS) {

				break;
			}
	
			ObDereferenceObject( volumeFileObject );

			if (!IS_SECONDARY_FILEOBJECT(volumeFileObject)) {

				Status = STATUS_INVALID_PARAMETER;
			}
		}
		
		break;

    case FSCTL_SECURITY_ID_CHECK:
        
		Status = NtfsBulkSecurityIdCheck( IrpContext, Irp );
        break;

    case FSCTL_FIND_FILES_BY_SID:
        
		Status = NtfsFindFilesOwnedBySid( IrpContext, Irp );
        break;

    case FSCTL_SET_SPARSE :
        
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		//Status = NtfsSetSparse( IrpContext, Irp );
        break;

    case FSCTL_SET_ZERO_DATA :
        
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		Status = NtfsZeroRange( IrpContext, Irp );
        break;

    case FSCTL_QUERY_ALLOCATED_RANGES :
        
		Status = NtfsQueryAllocatedRanges( IrpContext, Irp );
        break;

    case FSCTL_ENCRYPTION_FSCTL_IO :
        
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		//Status = NtfsEncryptionFsctl( IrpContext, Irp );
        break;

    case FSCTL_SET_ENCRYPTION :
        
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		//Status = NtfsSetEncryption( IrpContext, Irp );
        break;

    case FSCTL_READ_RAW_ENCRYPTED:
        
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		//Status = NtfsReadRawEncrypted( IrpContext, Irp );
        break;

    case FSCTL_WRITE_RAW_ENCRYPTED:
        
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		//Status = NtfsWriteRawEncrypted( IrpContext, Irp );
        break;

    case FSCTL_EXTEND_VOLUME:
        
		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_ACCESS_DENIED );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		//Status = NtfsExtendVolume( IrpContext, Irp );
        break;

    case FSCTL_READ_FROM_PLEX:
        
		Status = NtfsReadFromPlex( IrpContext, Irp );

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;

		break;

    case FSCTL_FILE_PREFETCH:
        
		Status = NtfsPrefetchFile( IrpContext, Irp );
        break;

    default :
        
		DebugTrace( 0, DEBUG_TRACE_ALL, ("NtfsUserFsRequest: Invalid control code FsControlCode = %08lx, FsControlCodeFunction = %d\n", 
										  FsControlCode, FsControlCodeFunction) );

		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_INVALID_DEVICE_REQUEST );
        break;
    }

	ASSERT( !ExIsResourceAcquiredSharedLite(&volDo->Vcb.Resource) );	

	if (Status != STATUS_SUCCESS) {

		DebugTrace( -1, Dbg, ("NtfsUserFsRequest -> %08lx\n", Status) );
		return Status;
	}

	if (IrpSp->Parameters.FileSystemControl.InputBufferLength >= volDo->Secondary->Thread.SessionContext.SecondaryMaxDataSize ||
		IrpSp->Parameters.FileSystemControl.OutputBufferLength >= volDo->Secondary->Thread.SessionContext.PrimaryMaxDataSize) {

		ASSERT( FALSE );

		NtfsCompleteRequest( IrpContext, Irp, Status = STATUS_INVALID_DEVICE_REQUEST );
		return Status;
	}

	inputBuffer = IrpContext->InputBuffer;
	outputBuffer = IrpContext->outputBuffer;

	ASSERT( IrpSp->Parameters.FileSystemControl.InputBufferLength ? (inputBuffer != NULL) : (inputBuffer == NULL) );
	ASSERT( IrpSp->Parameters.FileSystemControl.OutputBufferLength ? (outputBuffer != NULL) : (outputBuffer == NULL) );

	ASSERT( KeGetCurrentIrql() == PASSIVE_LEVEL );

	if (!FlagOn(IrpContext->State, IRP_CONTEXT_STATE_WAIT)) {

		return NtfsPostRequest( IrpContext, Irp );
	}

	try {

		secondarySessionResourceAcquired 
			= SecondaryAcquireResourceExclusiveLite( IrpContext, 
													 &volDo->SessionResource, 
													 BooleanFlagOn(IrpContext->State, IRP_CONTEXT_STATE_WAIT) );

		if (FlagOn(volDo->Secondary->Thread.Flags, SECONDARY_THREAD_FLAG_REMOTE_DISCONNECTED) ) {

			PrintIrp( Dbg2, "SECONDARY_THREAD_FLAG_REMOTE_DISCONNECTED", NULL, IrpContext->OriginatingIrp );
			NtfsRaiseStatus( IrpContext, STATUS_CANT_WAIT, NULL, NULL );	
		}

		ASSERT( IS_SECONDARY_FILEOBJECT(IrpSp->FileObject) );
		
		typeOfOpen = NtfsDecodeFileObject( IrpContext, IrpSp->FileObject, &vcb, &fcb, &scb, &ccb, TRUE );

		if (FlagOn(ccb->NdasNtfsFlags, ND_NTFS_CCB_FLAG_UNOPENED)) {

			ASSERT( FlagOn(ccb->NdasNtfsFlags, ND_NTFS_CCB_FLAG_CORRUPTED) );

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
		
		} else if(fileSystemControl.FsControlCode == FSCTL_MARK_HANDLE) {		// 63
		
			inputBufferLength = 0;			
		
		} else {
		
			inputBufferLength  = fileSystemControl.InputBufferLength;
		}
		
		bufferLength = (inputBufferLength >= outputBufferLength) ? inputBufferLength : outputBufferLength;

		secondaryRequest = AllocateWinxpSecondaryRequest( volDo->Secondary, 
														  IRP_MJ_FILE_SYSTEM_CONTROL,
														  bufferLength );

		if (secondaryRequest == NULL) {

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
		
		} else if(fileSystemControl.FsControlCode == FSCTL_MARK_HANDLE) {	// 63
		
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

			if(inputBufferLength)
				RtlCopyMemory( ndfsWinxpRequestData, inputBuffer, inputBufferLength );
		}

		ASSERT( !ExIsResourceAcquiredSharedLite(&IrpContext->Vcb->Resource) );	

		secondaryRequest->RequestType = SECONDARY_REQ_SEND_MESSAGE;
		QueueingSecondaryRequest( volDo->Secondary, secondaryRequest );

		timeOut.QuadPart = -NDASNTFS_TIME_OUT;
		Status = KeWaitForSingleObject( &secondaryRequest->CompleteEvent, Executive, KernelMode, FALSE, &timeOut );

		if(Status != STATUS_SUCCESS) {

			secondaryRequest = NULL;
			try_return( Status = STATUS_IO_DEVICE_ERROR );
		}

		KeClearEvent( &secondaryRequest->CompleteEvent );

		if (secondaryRequest->ExecuteStatus != STATUS_SUCCESS) {

			if (IrpContext->OriginatingIrp)
				PrintIrp( Dbg2, "secondaryRequest->ExecuteStatus != STATUS_SUCCESS", NULL, IrpContext->OriginatingIrp );

			DebugTrace( 0, Dbg2, ("secondaryRequest->ExecuteStatus != STATUS_SUCCESS file = %s, line = %d\n", __FILE__, __LINE__) );

			NtfsRaiseStatus( IrpContext, STATUS_CANT_WAIT, NULL, NULL );
		}

		ndfsWinxpReplytHeader = (PNDFS_WINXP_REPLY_HEADER)secondaryRequest->NdfsReplyData;
		Status = Irp->IoStatus.Status = NTOHL(ndfsWinxpReplytHeader->Status4);
		Irp->IoStatus.Information = NTOHL(ndfsWinxpReplytHeader->Information32);

		if (FsControlCode == FSCTL_GET_NTFS_VOLUME_DATA && Status != STATUS_SUCCESS)
			DebugTrace( 0, Dbg2, ("FSCTL_GET_NTFS_VOLUME_DATA: Status = %x, Irp->IoStatus.Information = %d\n", Status, Irp->IoStatus.Information) );

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
			DebugTrace( 0, Dbg2, ("NtfsDefragFile: status = %x\n", Status) );

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

			if(Status != STATUS_SUCCESS) {

				try_return( Status );
			}
	
			ObDereferenceObject( moveFileObject );
				
			typeOfOpen = NtfsDecodeFileObject( IrpContext, moveFileObject, &vcb, &moveFcb, &moveScb, &moveCcb, TRUE );
		
			if (typeOfOpen == UserFileOpen && ndfsWinxpReplytHeader->FileInformationSet && NTOHLL(ndfsWinxpReplytHeader->AllocationSize8)) {

				PNDFS_NTFS_MCB_ENTRY	mcbEntry;
				ULONG			index;
				VCN				testVcn;

			
				SetFlag( IrpContext->Flags, IRP_CONTEXT_FLAG_ACQUIRE_PAGING );
				NtfsAcquireFcbWithPaging( IrpContext, moveFcb, 0 );
				NtfsAcquireNtfsMcbMutex( &moveScb->Mcb );

				mcbEntry = (PNDFS_NTFS_MCB_ENTRY)( ndfsWinxpReplytHeader+1 );

				if (moveScb->Header.AllocationSize.QuadPart) {

					NtfsRemoveNtfsMcbEntry( &moveScb->Mcb, 0, 0xFFFFFFFF );
				}

				for (index=0, testVcn=0; index < NTOHL(ndfsWinxpReplytHeader->NumberOfMcbEntry4); index++) {

					ASSERT( mcbEntry[index].Vcn == testVcn );
					testVcn += (LONGLONG)mcbEntry[index].ClusterCount;

					NtfsAddNtfsMcbEntry( &moveScb->Mcb, 
										 mcbEntry[index].Vcn, 
										 mcbEntry[index].Lcn, 
										 (LONGLONG)mcbEntry[index].ClusterCount, 
										 TRUE );
				}
					
				ASSERT( LlBytesFromClusters(vcb, testVcn) == NTOHLL(ndfsWinxpReplytHeader->AllocationSize8) );

				if (moveScb->Header.AllocationSize.QuadPart != NTOHLL(ndfsWinxpReplytHeader->AllocationSize8))
					SetFlag( moveScb->ScbState, SCB_STATE_TRUNCATE_ON_CLOSE );		

				moveScb->Header.FileSize.QuadPart = NTOHLL(ndfsWinxpReplytHeader->FileSize8);
				moveScb->Header.AllocationSize.QuadPart = NTOHLL(ndfsWinxpReplytHeader->AllocationSize8);
				ASSERT( moveScb->Header.AllocationSize.QuadPart >= moveScb->Header.FileSize.QuadPart );

				if (moveFileObject->SectionObjectPointer->DataSectionObject != NULL && moveFileObject->PrivateCacheMap == NULL) {

					CcInitializeCacheMap( moveFileObject,
										  (PCC_FILE_SIZES)&moveScb->Header.AllocationSize,
										  FALSE,
										  &NtfsData.CacheManagerCallbacks,
										  moveScb );
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

try_exit:  NOTHING;

	} finally {

		if (secondarySessionResourceAcquired == TRUE) {

			SecondaryReleaseResourceLite( IrpContext, &volDo->SessionResource );		
		}

		if (secondaryRequest)
			DereferenceSecondaryRequest( secondaryRequest );
	}

	NtfsCompleteRequest( IrpContext, Irp, Status );
	return Status;
}