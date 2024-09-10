void FStreamingWaveData::BeginPendingRequests(const TArray<uint32>& IndicesToLoad, const TArray<uint32>& IndicesToFree)
{
	if (UE_LOG_ACTIVE(LogAudio, Log) && IndicesToLoad.Num() > 0)
	{
		FString LogString = FString::Printf(TEXT("Requesting ASync load of chunk(s) %d"), IndicesToLoad[0]);
		for (int32 Index = 1; Index < IndicesToLoad.Num(); ++Index)
		{
			LogString += FString::Printf(TEXT(", %d"), IndicesToLoad[Index]);
		}
		LogString += FString::Printf(TEXT(" from SoundWave'%s'"), *SoundWave->GetName());
		UE_LOG(LogAudio, Log, TEXT("%s"), *LogString);
	}

	// Mark Chunks for removal in case they can be reused
	TArray<uint32> FreeChunkIndices;
	for (auto Index : IndicesToFree)
	{
		for (int32 ChunkIndex = 0; ChunkIndex < LoadedChunks.Num(); ++ChunkIndex)
		{
			if (LoadedChunks[ChunkIndex].Index == Index)
			{
				FreeChunkIndices.AddUnique(ChunkIndex);
				break;
			}
		}
	}

	if (IndicesToLoad.Num() > 0)
	{
		PendingChunkChangeRequestStatus.Set(AudioState_InProgress_Loading);

		// Set off all IO Requests
		for (auto Index : IndicesToLoad)
		{
			const FStreamedAudioChunk& Chunk = SoundWave->RunningPlatformData->Chunks[Index];
			int32 ChunkSize = Chunk.DataSize;

			FLoadedAudioChunk* ChunkStorage = NULL;

			for (auto FreeIndex : FreeChunkIndices)
			{
				if (LoadedChunks[FreeIndex].MemorySize >= ChunkSize)
				{
					FreeChunkIndices.Remove(FreeIndex);
					ChunkStorage = &LoadedChunks[FreeIndex];
					ChunkStorage->DataSize = ChunkSize;
					ChunkStorage->Index = Index;
					break;
				}
			}
			if (ChunkStorage == NULL)
			{
				ChunkStorage = AddNewLoadedChunk(ChunkSize);
				ChunkStorage->Index = Index;
			}

			// Pass the request on to the async io manager after increasing the request count. The request count 
			// has been pre-incremented before fielding the update request so we don't have to worry about file
			// I/O immediately completing and the game thread kicking off again before this function
			// returns.
			PendingChunkChangeRequestStatus.Increment();

			EAsyncIOPriority AsyncIOPriority = CurrentRequest.bPrioritiseRequest ? AIOP_BelowNormal : AIOP_Low;

			// Load and decompress async.
#if WITH_EDITORONLY_DATA
			if (Chunk.DerivedDataKey.IsEmpty() == false)
			{
				FAsyncStreamDerivedChunkTask* Task = new(PendingAsyncStreamDerivedChunkTasks)FAsyncStreamDerivedChunkTask(
					Chunk.DerivedDataKey,
					ChunkStorage->Data,
					ChunkSize,
					&PendingChunkChangeRequestStatus
					);
				Task->StartBackgroundTask();
			}
			else
#endif // #if WITH_EDITORONLY_DATA
			{
				check(Chunk.BulkData.GetFilename().Len());
				if (Chunk.BulkData.IsStoredCompressedOnDisk())
				{
					IORequestIndices.AddUnique(FIOSystem::Get().LoadCompressedData(
						Chunk.BulkData.GetFilename(),						// filename
						Chunk.BulkData.GetBulkDataOffsetInFile(),			// offset
						Chunk.BulkData.GetBulkDataSizeOnDisk(),				// compressed size
						Chunk.BulkData.GetBulkDataSize(),					// uncompressed size
						ChunkStorage->Data,									// dest pointer
						Chunk.BulkData.GetDecompressionFlags(),				// compressed data format
						&PendingChunkChangeRequestStatus,					// counter to decrement
						AsyncIOPriority										// priority
						)
						);
				}
				// Load async.
				else
				{
					IORequestIndices.AddUnique(FIOSystem::Get().LoadData(
						Chunk.BulkData.GetFilename(),						// filename
						Chunk.BulkData.GetBulkDataOffsetInFile(),			// offset
						Chunk.BulkData.GetBulkDataSize(),					// size
						ChunkStorage->Data,									// dest pointer
						&PendingChunkChangeRequestStatus,					// counter to decrement
						AsyncIOPriority										// priority
						)
						);
				}
				check(IORequestIndices[IORequestIndices.Num() - 1]);
			}
		}

		// Decrement the state to AudioState_InProgress_Loading + NumChunksCurrentLoading - 1.
		PendingChunkChangeRequestStatus.Decrement();
	}
	else
	{
		// Skip straight to finalisation
		PendingChunkChangeRequestStatus.Set(AudioState_ReadyFor_Finalization);
	}

	// Ensure indices are in order so we can step through backwards
	FreeChunkIndices.Sort();

	for (int32 FreeIndex = FreeChunkIndices.Num() - 1; FreeIndex >= 0; --FreeIndex)
	{
		FreeLoadedChunk(LoadedChunks[FreeChunkIndices[FreeIndex]]);
		LoadedChunks.RemoveAt(FreeChunkIndices[FreeIndex]);
	}
}