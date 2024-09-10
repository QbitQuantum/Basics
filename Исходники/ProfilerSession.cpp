void FRawProfilerSession::PrepareLoading()
{
	SCOPE_LOG_TIME_FUNC();

	const FString Filepath = DataFilepath + FStatConstants::StatsFileRawExtension;
	const int64 Size = IFileManager::Get().FileSize( *Filepath );
	if( Size < 4 )
	{
		UE_LOG( LogStats, Error, TEXT( "Could not open: %s" ), *Filepath );
		return;
	}
	TAutoPtr<FArchive> FileReader( IFileManager::Get().CreateFileReader( *Filepath ) );
	if( !FileReader )
	{
		UE_LOG( LogStats, Error, TEXT( "Could not open: %s" ), *Filepath );
		return;
	}

	if( !Stream.ReadHeader( *FileReader ) )
	{
		UE_LOG( LogStats, Error, TEXT( "Could not open, bad magic: %s" ), *Filepath );
		return;
	}

	const bool bIsFinalized = Stream.Header.IsFinalized();
	check( bIsFinalized );
	check( Stream.Header.Version == EStatMagicWithHeader::VERSION_5 );
	StatsThreadStats.MarkAsLoaded();

	TArray<FStatMessage> Messages;
	if( Stream.Header.bRawStatsFile )
	{
		// Read metadata.
		TArray<FStatMessage> MetadataMessages;
		Stream.ReadFNamesAndMetadataMessages( *FileReader, MetadataMessages );
		StatsThreadStats.ProcessMetaDataOnly( MetadataMessages );

		const FName F00245 = FName(245, 245, 0);
		
		const FName F11602 = FName(11602, 11602, 0);
		const FName F06394 = FName(6394, 6394, 0);

		const int64 CurrentFilePos = FileReader->Tell();

		// Update profiler's metadata.
		StatMetaData->UpdateFromStatsState( StatsThreadStats );
		const uint32 GameThreadID = GetMetaData()->GetGameThreadID();

		// Read frames offsets.
		Stream.ReadFramesOffsets( *FileReader );

		// Buffer used to store the compressed and decompressed data.
		TArray<uint8> SrcArray;
		TArray<uint8> DestArray;
		const bool bHasCompressedData = Stream.Header.HasCompressedData();
		check(bHasCompressedData);

		TMap<int64, FStatPacketArray> CombinedHistory;
		int64 TotalPacketSize = 0;
		int64 MaximumPacketSize = 0;
		// Read all packets sequentially, force by the memory profiler which is now a part of the raw stats.
		// !!CAUTION!! Frame number in the raw stats is pointless, because it is time based, not frame based.
		// Background threads usually execute time consuming operations, so the frame number won't be valid.
		// Needs to be combined by the thread and the time, not by the frame number.
		{
			int64 FrameOffset0 = Stream.FramesInfo[0].FrameFileOffset;
			FileReader->Seek( FrameOffset0 );

			const int64 FileSize = FileReader->TotalSize();

			while( FileReader->Tell() < FileSize )
			{
				// Read the compressed data.
				FCompressedStatsData UncompressedData( SrcArray, DestArray );
				*FileReader << UncompressedData;
				if( UncompressedData.HasReachedEndOfCompressedData() )
				{
					break;
				}

				FMemoryReader MemoryReader( DestArray, true );

				FStatPacket* StatPacket = new FStatPacket();
				Stream.ReadStatPacket( MemoryReader, *StatPacket );
				
				const int64 FrameNum = StatPacket->Frame;
				FStatPacketArray& Frame = CombinedHistory.FindOrAdd(FrameNum);
			
				// Check if we need to combine packets from the same thread.
				FStatPacket** CombinedPacket = Frame.Packets.FindByPredicate([&](FStatPacket* Item) -> bool
				{
					return Item->ThreadId == StatPacket->ThreadId;
				});
				
				if( CombinedPacket )
				{
					(*CombinedPacket)->StatMessages += StatPacket->StatMessages;
				}
				else
				{
					Frame.Packets.Add(StatPacket);
				}

				const int64 CurrentPos = FileReader->Tell();
				const int32 PctPos = int32(100.0f*CurrentPos/FileSize);

				UE_LOG( LogStats, Log, TEXT( "%3i Processing FStatPacket: Frame %5i for thread %5i with %6i messages (%.1f MB)" ), 
					PctPos, 
					StatPacket->Frame, 
					StatPacket->ThreadId, 
					StatPacket->StatMessages.Num(), 
					StatPacket->StatMessages.GetAllocatedSize()/1024.0f/1024.0f );

				const int64 PacketSize = StatPacket->StatMessages.GetAllocatedSize();
				TotalPacketSize += PacketSize;
				MaximumPacketSize = FMath::Max( MaximumPacketSize, PacketSize );
			}
		}

		UE_LOG( LogStats, Log, TEXT( "TotalPacketSize: %.1f MB, Max: %1f MB" ), 
			TotalPacketSize/1024.0f/1024.0f, 
			MaximumPacketSize/1024.0f/1024.0f );

		TArray<int64> Frames;
		CombinedHistory.GenerateKeyArray(Frames);
		Frames.Sort();
		const int64 MiddleFrame = Frames[Frames.Num()/2];


		// Remove all frames without the game thread messages.
		for (int32 FrameIndex = 0; FrameIndex < Frames.Num(); ++FrameIndex)
		{
			const int64 TargetFrame = Frames[FrameIndex];
			const FStatPacketArray& Frame = CombinedHistory.FindChecked( TargetFrame );

			const double GameThreadTimeMS = GetMetaData()->ConvertCyclesToMS( GetFastThreadFrameTimeInternal( Frame, EThreadType::Game ) );

			if (GameThreadTimeMS == 0.0f)
			{
				CombinedHistory.Remove( TargetFrame );
				Frames.RemoveAt( FrameIndex );
				FrameIndex--;
			}
		}
		
	
		StatMetaData->SecondsPerCycle = GetSecondsPerCycle( CombinedHistory.FindChecked(MiddleFrame) );
		check( StatMetaData->GetSecondsPerCycle() > 0.0 );

		//const int32 FirstGameThreadFrame = FindFirstFrameWithGameThread( CombinedHistory, Frames );

		// Prepare profiler frame.
		{
			SCOPE_LOG_TIME( TEXT( "Preparing profiler frames" ), nullptr );

			// Prepare profiler frames.
			double ElapsedTimeMS = 0;

			for( int32 FrameIndex = 0; FrameIndex < Frames.Num(); ++FrameIndex )
			{
				const int64 TargetFrame = Frames[FrameIndex];
				const FStatPacketArray& Frame = CombinedHistory.FindChecked(TargetFrame);

				const double GameThreadTimeMS = GetMetaData()->ConvertCyclesToMS( GetFastThreadFrameTimeInternal(Frame,EThreadType::Game) );

				if( GameThreadTimeMS == 0.0f )
				{
					continue;
				}

				const double RenderThreadTimeMS = GetMetaData()->ConvertCyclesToMS( GetFastThreadFrameTimeInternal(Frame,EThreadType::Renderer) );

				// Update mini-view, convert from cycles to ms.
				TMap<uint32, float> ThreadTimesMS;
				ThreadTimesMS.Add( GameThreadID, GameThreadTimeMS );
				ThreadTimesMS.Add( GetMetaData()->GetRenderThreadID()[0], RenderThreadTimeMS );

				// Pass the reference to the stats' metadata.
				OnAddThreadTime.ExecuteIfBound( FrameIndex, ThreadTimesMS, StatMetaData );

				// Create a new profiler frame and add it to the stream.
				ElapsedTimeMS += GameThreadTimeMS;
				FProfilerFrame* ProfilerFrame = new FProfilerFrame( TargetFrame, GameThreadTimeMS, ElapsedTimeMS );
				ProfilerFrame->ThreadTimesMS = ThreadTimesMS;
				ProfilerStream.AddProfilerFrame( TargetFrame, ProfilerFrame );
			}
		}
	
		// Process the raw stats data.
		{
			SCOPE_LOG_TIME( TEXT( "Processing the raw stats" ), nullptr );

			double CycleCounterAdjustmentMS = 0.0f;

			// Read the raw stats messages.
			for( int32 FrameIndex = 0; FrameIndex < Frames.Num()-1; ++FrameIndex )
			{
				const int64 TargetFrame = Frames[FrameIndex];
				const FStatPacketArray& Frame = CombinedHistory.FindChecked(TargetFrame);

				FProfilerFrame* ProfilerFrame = ProfilerStream.GetProfilerFrame( FrameIndex );

				UE_CLOG( FrameIndex % 8 == 0, LogStats, Log, TEXT( "Processing raw stats frame: %4i/%4i" ), FrameIndex, Frames.Num() );

				ProcessStatPacketArray( Frame, *ProfilerFrame, FrameIndex ); // or ProfilerFrame->TargetFrame

				// Find the first cycle counter for the game thread.
				if( CycleCounterAdjustmentMS == 0.0f )
				{
					CycleCounterAdjustmentMS = ProfilerFrame->Root->CycleCounterStartTimeMS;
				}

				// Update thread time and mark profiler frame as valid and ready for use.
				ProfilerFrame->MarkAsValid();
			}

			// Adjust all profiler frames.
			ProfilerStream.AdjustCycleCounters( CycleCounterAdjustmentMS );
		}
	}

	const int64 AllocatedSize = ProfilerStream.GetAllocatedSize();

	// We have the whole metadata and basic information about the raw stats file, start ticking the profiler session.
	//OnTickHandle = FTicker::GetCoreTicker().AddTicker( OnTick, 0.25f );

#if	0
	if( SessionType == EProfilerSessionTypes::OfflineRaw )
	{
		// Broadcast that a capture file has been fully processed.
		OnCaptureFileProcessed.ExecuteIfBound( GetInstanceID() );
	}
#endif // 0
}