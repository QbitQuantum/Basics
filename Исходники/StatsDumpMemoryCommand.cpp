void FStatsMemoryDumpCommand::ProcessMemoryOperations( const TMap<int64, FStatPacketArray>& CombinedHistory )
{
	// This is only example code, no fully implemented, may sometimes crash.
	// This code is not optimized. 
	double PreviousSeconds = FPlatformTime::Seconds();
	uint64 NumMemoryOperations = 0;

	// Generate frames
	TArray<int64> Frames;
	CombinedHistory.GenerateKeyArray( Frames );
	Frames.Sort();

	// Raw stats callstack for this stat packet array.
	TMap<FName, FStackState> StackStates;

	// All allocation ordered by the sequence tag.
	// There is an assumption that the sequence tag will not turn-around.
	//TMap<uint32, FAllocationInfo> SequenceAllocationMap;
	TArray<FAllocationInfo> SequenceAllocationArray;

	// Pass 1.
	// Read all stats messages, parse all memory operations and decode callstacks.
	const int64 FirstFrame = 0;
	PreviousSeconds -= NumSecondsBetweenLogs;
	for( int32 FrameIndex = 0; FrameIndex < Frames.Num(); ++FrameIndex )
	{
        {
            const double CurrentSeconds = FPlatformTime::Seconds();
            if( CurrentSeconds > PreviousSeconds + NumSecondsBetweenLogs )
            {
                UE_LOG( LogStats, Warning, TEXT( "Processing frame %i/%i" ), FrameIndex+1, Frames.Num() );
                PreviousSeconds = CurrentSeconds;
            }
        }

		const int64 TargetFrame = Frames[FrameIndex];
		const int64 Diff = TargetFrame - FirstFrame;
		const FStatPacketArray& Frame = CombinedHistory.FindChecked( TargetFrame );

		bool bAtLeastOnePacket = false;
		for( int32 PacketIndex = 0; PacketIndex < Frame.Packets.Num(); PacketIndex++ )
		{
            {
                const double CurrentSeconds = FPlatformTime::Seconds();
                if( CurrentSeconds > PreviousSeconds + NumSecondsBetweenLogs )
                {
                    UE_LOG( LogStats, Log, TEXT( "Processing packet %i/%i" ), PacketIndex, Frame.Packets.Num() );
                    PreviousSeconds = CurrentSeconds;
                    bAtLeastOnePacket = true;
                }
            }

			const FStatPacket& StatPacket = *Frame.Packets[PacketIndex];
			const FName& ThreadFName = StatsThreadStats.Threads.FindChecked( StatPacket.ThreadId );
			const uint32 NewThreadID = ThreadIDtoStatID.FindChecked( StatPacket.ThreadId );

			FStackState* StackState = StackStates.Find( ThreadFName );
			if( !StackState )
			{
				StackState = &StackStates.Add( ThreadFName );
				StackState->Stack.Add( ThreadFName );
				StackState->Current = ThreadFName;
			}

			const FStatMessagesArray& Data = StatPacket.StatMessages;

			int32 LastPct = 0;
			const int32 NumDataElements = Data.Num();
			const int32 OnerPercent = FMath::Max( NumDataElements / 100, 1024 );
			bool bAtLeastOneMessage = false;
			for( int32 Index = 0; Index < NumDataElements; Index++ )
			{
				if( Index % OnerPercent )
				{
					const double CurrentSeconds = FPlatformTime::Seconds();
					if( CurrentSeconds > PreviousSeconds + NumSecondsBetweenLogs )
					{
						const int32 CurrentPct = int32( 100.0*(Index + 1) / NumDataElements );
						UE_LOG( LogStats, Log, TEXT( "Processing %3i%% (%i/%i) stat messages" ), CurrentPct, Index, NumDataElements );
						PreviousSeconds = CurrentSeconds;
						bAtLeastOneMessage = true;
					}
				}

				const FStatMessage& Item = Data[Index];

				const EStatOperation::Type Op = Item.NameAndInfo.GetField<EStatOperation>();
				const FName RawName = Item.NameAndInfo.GetRawName();

				if( Op == EStatOperation::CycleScopeStart || Op == EStatOperation::CycleScopeEnd || Op == EStatOperation::Memory )
				{
					if( Op == EStatOperation::CycleScopeStart )
					{
						StackState->Stack.Add( RawName );
						StackState->Current = RawName;
					}
					else if( Op == EStatOperation::Memory )
					{
						// Experimental code used only to test the implementation.
						// First memory operation is Alloc or Free
						const uint64 EncodedPtr = Item.GetValue_Ptr();
						const bool bIsAlloc = (EncodedPtr & (uint64)EMemoryOperation::Alloc) != 0;
						const bool bIsFree = (EncodedPtr & (uint64)EMemoryOperation::Free) != 0;
						const uint64 Ptr = EncodedPtr & ~(uint64)EMemoryOperation::Mask;
						if( bIsAlloc )
						{
							NumMemoryOperations++;
							// @see FStatsMallocProfilerProxy::TrackAlloc
							// After alloc ptr message there is always alloc size message and the sequence tag.
							Index++;
							const FStatMessage& AllocSizeMessage = Data[Index];
							const int64 AllocSize = AllocSizeMessage.GetValue_int64();

							// Read operation sequence tag.
							Index++;
							const FStatMessage& SequenceTagMessage = Data[Index];
							const uint32 SequenceTag = SequenceTagMessage.GetValue_int64();

							// Create a callstack.
							TArray<FName> StatsBasedCallstack;
							for( const auto& StackName : StackState->Stack )
							{
								StatsBasedCallstack.Add( StackName );
							}

							// Add a new allocation.
							SequenceAllocationArray.Add(
								FAllocationInfo(
								Ptr,
								AllocSize,
								StatsBasedCallstack,
								SequenceTag,
								EMemoryOperation::Alloc,
								StackState->bIsBrokenCallstack
								) );
						}
						else if( bIsFree )
						{
							NumMemoryOperations++;
							// Read operation sequence tag.
							Index++;
							const FStatMessage& SequenceTagMessage = Data[Index];
							const uint32 SequenceTag = SequenceTagMessage.GetValue_int64();

							// Create a callstack.
							/*
							TArray<FName> StatsBasedCallstack;
							for( const auto& RawName : StackState->Stack )
							{
								StatsBasedCallstack.Add( RawName );
							}
							*/

							// Add a new free.
							SequenceAllocationArray.Add(
								FAllocationInfo(
								Ptr,		
								0,
								TArray<FName>()/*StatsBasedCallstack*/,					
								SequenceTag,
								EMemoryOperation::Free,
								StackState->bIsBrokenCallstack
								) );
						}
						else
						{
							UE_LOG( LogStats, Warning, TEXT( "Pointer from a memory operation is invalid" ) );
						}
					}
					else if( Op == EStatOperation::CycleScopeEnd )
					{
						if( StackState->Stack.Num() > 1 )
						{
							const FName ScopeStart = StackState->Stack.Pop();
							const FName ScopeEnd = Item.NameAndInfo.GetRawName();

							check( ScopeStart == ScopeEnd );

							StackState->Current = StackState->Stack.Last();

							// The stack should be ok, but it may be partially broken.
							// This will happen if memory profiling starts in the middle of executing a background thread.
							StackState->bIsBrokenCallstack = false;
						}
						else
						{
							const FName ShortName = Item.NameAndInfo.GetShortName();

							UE_LOG( LogStats, Warning, TEXT( "Broken cycle scope end %s/%s, current %s" ),
									*ThreadFName.ToString(),
									*ShortName.ToString(),
									*StackState->Current.ToString() );

							// The stack is completely broken, only has the thread name and the last cycle scope.
							// Rollback to the thread node.
							StackState->bIsBrokenCallstack = true;
							StackState->Stack.Empty();
							StackState->Stack.Add( ThreadFName );
							StackState->Current = ThreadFName;
						}
					}
				}
			}
			if( bAtLeastOneMessage )
			{
				PreviousSeconds -= NumSecondsBetweenLogs;
			}
		}
		if( bAtLeastOnePacket )
		{
			PreviousSeconds -= NumSecondsBetweenLogs;
		}
	}

	UE_LOG( LogStats, Warning, TEXT( "NumMemoryOperations:   %llu" ), NumMemoryOperations );
	UE_LOG( LogStats, Warning, TEXT( "SequenceAllocationNum: %i" ), SequenceAllocationArray.Num() );

	// Pass 2.
	/*
	TMap<uint32,FAllocationInfo> UniqueSeq;
	TMultiMap<uint32,FAllocationInfo> OriginalAllocs;
	TMultiMap<uint32,FAllocationInfo> BrokenAllocs;
	for( const FAllocationInfo& Alloc : SequenceAllocationArray )
	{
		const FAllocationInfo* Found = UniqueSeq.Find(Alloc.SequenceTag);
		if( !Found )
		{
			UniqueSeq.Add(Alloc.SequenceTag,Alloc);
		}
		else
		{
			OriginalAllocs.Add(Alloc.SequenceTag, *Found);
			BrokenAllocs.Add(Alloc.SequenceTag, Alloc);
		}
	}
	*/

	// Sort all memory operation by the sequence tag, iterate through all operation and generate memory usage.
	SequenceAllocationArray.Sort( TLess<FAllocationInfo>() );

	// Alive allocations.
	TMap<uint64, FAllocationInfo> AllocationMap;
	TMultiMap<uint64, FAllocationInfo> FreeWithoutAllocMap;
	TMultiMap<uint64, FAllocationInfo> DuplicatedAllocMap;
	int32 NumDuplicatedMemoryOperations = 0;
	int32 NumFWAMemoryOperations = 0; // FreeWithoutAlloc

	UE_LOG( LogStats, Warning, TEXT( "Generating memory operations map" ) );
	const int32 NumSequenceAllocations = SequenceAllocationArray.Num();
	const int32 OnePercent = FMath::Max( NumSequenceAllocations / 100, 1024 );
	for( int32 Index = 0; Index < NumSequenceAllocations; Index++ )
	{
		if( Index % OnePercent )
		{
			const double CurrentSeconds = FPlatformTime::Seconds();
			if( CurrentSeconds > PreviousSeconds + NumSecondsBetweenLogs )
			{
				const int32 CurrentPct = int32( 100.0*(Index + 1) / NumSequenceAllocations );
				UE_LOG( LogStats, Log, TEXT( "Processing allocations %3i%% (%10i/%10i)" ), CurrentPct, Index + 1, NumSequenceAllocations );
				PreviousSeconds = CurrentSeconds;
			}
		}

		const FAllocationInfo& Alloc = SequenceAllocationArray[Index];
		const EMemoryOperation MemOp = Alloc.Op;
		const uint64 Ptr = Alloc.Ptr;
		const int64 Size = Alloc.Size;
		const uint32 SequenceTag = Alloc.SequenceTag;

		if( MemOp == EMemoryOperation::Alloc )
		{
			const FAllocationInfo* Found = AllocationMap.Find( Ptr );

			if( !Found )
			{
				AllocationMap.Add( Ptr, Alloc );
			}
			else
			{
				const FAllocationInfo* FoundAndFreed = FreeWithoutAllocMap.Find( Found->Ptr );
				const FAllocationInfo* FoundAndAllocated = FreeWithoutAllocMap.Find( Alloc.Ptr );

#if	_DEBUG
				if( FoundAndFreed )
				{
					const FString FoundAndFreedCallstack = GetCallstack( FoundAndFreed->EncodedCallstack );
				}

				if( FoundAndAllocated )
				{
					const FString FoundAndAllocatedCallstack = GetCallstack( FoundAndAllocated->EncodedCallstack );
				}

				NumDuplicatedMemoryOperations++;


				const FString FoundCallstack = GetCallstack( Found->EncodedCallstack );
				const FString AllocCallstack = GetCallstack( Alloc.EncodedCallstack );
#endif // _DEBUG

				// Replace pointer.
				AllocationMap.Add( Ptr, Alloc );
				// Store the old pointer.
				DuplicatedAllocMap.Add( Ptr, *Found );
			}
		}
		else if( MemOp == EMemoryOperation::Free )
		{
			const FAllocationInfo* Found = AllocationMap.Find( Ptr );
			if( Found )
			{
				const bool bIsValid = Alloc.SequenceTag > Found->SequenceTag;
				if( !bIsValid )
				{
					UE_LOG( LogStats, Warning, TEXT( "InvalidFree Ptr: %llu, Seq: %i/%i" ), Ptr, SequenceTag, Found->SequenceTag );
				}
				AllocationMap.Remove( Ptr );
			}
			else
			{
				FreeWithoutAllocMap.Add( Ptr, Alloc );
				NumFWAMemoryOperations++;
			}
		}
	}

	UE_LOG( LogStats, Warning, TEXT( "NumDuplicatedMemoryOperations: %i" ), NumDuplicatedMemoryOperations );
	UE_LOG( LogStats, Warning, TEXT( "NumFWAMemoryOperations:        %i" ), NumFWAMemoryOperations );

	// Dump problematic allocations
	DuplicatedAllocMap.ValueSort( FAllocationInfoGreater() );
	//FreeWithoutAllocMap

	uint64 TotalDuplicatedMemory = 0;
	for( const auto& It : DuplicatedAllocMap )
	{
		const FAllocationInfo& Alloc = It.Value;
		TotalDuplicatedMemory += Alloc.Size;
	}

	UE_LOG( LogStats, Warning, TEXT( "Dumping duplicated alloc map" ) );
	const float MaxPctDisplayed = 0.80f;
	uint64 DisplayedSoFar = 0;
	for( const auto& It : DuplicatedAllocMap )
	{
		const FAllocationInfo& Alloc = It.Value;
		const FString AllocCallstack = GetCallstack( Alloc.EncodedCallstack );
		UE_LOG( LogStats, Log, TEXT( "%lli (%.2f MB) %s" ), Alloc.Size, Alloc.Size / 1024.0f / 1024.0f, *AllocCallstack );

		DisplayedSoFar += Alloc.Size;

		const float CurrentPct = (float)DisplayedSoFar / (float)TotalDuplicatedMemory;
		if( CurrentPct > MaxPctDisplayed )
		{
			break;
		}
	}

	GenerateMemoryUsageReport( AllocationMap );
}