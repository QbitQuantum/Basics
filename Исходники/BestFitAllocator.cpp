/**
 * Dump allocation information.
 */
void FBestFitAllocator::DumpAllocs( FOutputDevice& Ar/*=*GLog*/ )
{		
	// Memory usage stats.
	INT				UsedSize		= 0;
	INT				FreeSize		= 0;
	INT				NumUsedChunks	= 0;
	INT				NumFreeChunks	= 0;
	
	// Fragmentation and allocation size visualization.
	INT				NumBlocks		= MemorySize / AllocationAlignment;
	INT				Dimension		= 1 + NumBlocks / appTrunc(appSqrt(NumBlocks));			
	TArray<FColor>	AllocationVisualization;
	AllocationVisualization.AddZeroed( Dimension * Dimension );
	INT				VisIndex		= 0;

	// Traverse linked list and gather allocation information.
	FMemoryChunk*	CurrentChunk	= FirstChunk;	
	while( CurrentChunk )
	{
		FColor VisColor;
		// Free chunk.
		if( CurrentChunk->bIsAvailable )
		{
			NumFreeChunks++;
			FreeSize += CurrentChunk->Size;
			VisColor = FColor(0,255,0);
		}
		// Allocated chunk.
		else
		{
			NumUsedChunks++;
			UsedSize += CurrentChunk->Size;
			
			// Slightly alternate coloration to also visualize allocation sizes.
			if( NumUsedChunks % 2 == 0 )
			{
				VisColor = FColor(255,0,0);
			}
			else
			{
				VisColor = FColor(192,0,0);
			}
		}

		for( INT i=0; i<(CurrentChunk->Size/AllocationAlignment); i++ )
		{
			AllocationVisualization(VisIndex++) = VisColor;
		}

		CurrentChunk = CurrentChunk->NextChunk;
	}

	check(UsedSize == AllocatedMemorySize);
	check(FreeSize == AvailableMemorySize);

	// Write out bitmap for visualization of fragmentation and allocation patterns.
	appCreateBitmap( TEXT("..\\..\\Binaries\\TextureMemory"), Dimension, Dimension, AllocationVisualization.GetTypedData() );
	Ar.Logf( TEXT("BestFitAllocator: Allocated %i KByte in %i chunks, leaving %i KByte in %i chunks."), UsedSize / 1024, NumUsedChunks, FreeSize / 1024, NumFreeChunks );
	Ar.Logf( TEXT("BestFitAllocator: %5.2f ms in allocator"), TimeSpentInAllocator * 1000 );
}