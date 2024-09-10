/**
 * Dumps detailed information of bulk data usage.
 *
 * @param Log FOutputDevice to use for logging
 */
void FUntypedBulkData::DumpBulkDataUsage( FOutputDevice& Log )
{
#if TRACK_BULKDATA_USE
	// Arrays about to hold per object and per class size information.
	TArray<FObjectAndSize> PerObjectSizeArray;
	TArray<FObjectAndSize> PerClassSizeArray;

	{
		FScopeLock Lock(&FThreadSafeBulkDataToObjectMap::Get().GetLock());

		// Iterate over all "live" bulk data and add size to arrays if it is loaded.
		for( auto It(FThreadSafeBulkDataToObjectMap::Get().GetIterator()); It; ++It )
		{
			const FUntypedBulkData*	BulkData	= It.Key();
			const UObject*			Owner		= It.Value();
			// Only add bulk data that is consuming memory to array.
			if( Owner && BulkData->IsBulkDataLoaded() && BulkData->GetBulkDataSize() > 0 )
			{
				// Per object stats.
				PerObjectSizeArray.Add( FObjectAndSize( Owner, BulkData->GetBulkDataSize() ) );

				// Per class stats.
				bool bFoundExistingPerClassSize = false;
				// Iterate over array, trying to find existing entry.
				for( int32 PerClassIndex=0; PerClassIndex<PerClassSizeArray.Num(); PerClassIndex++ )
				{
					FObjectAndSize& PerClassSize = PerClassSizeArray[ PerClassIndex ];
					// Add to existing entry if found.
					if( PerClassSize.Object == Owner->GetClass() )
					{
						PerClassSize.Size += BulkData->GetBulkDataSize();
						bFoundExistingPerClassSize = true;
						break;
					}
				}
				// Add new entry if we didn't find an existing one.
				if( !bFoundExistingPerClassSize )
				{
					PerClassSizeArray.Add( FObjectAndSize( Owner->GetClass(), BulkData->GetBulkDataSize() ) );
				}
			}
		}
	}

	/** Compare operator, sorting by size in descending order */
	struct FCompareFObjectAndSize
	{
		FORCEINLINE bool operator()( const FObjectAndSize& A, const FObjectAndSize& B ) const
		{
			return B.Size < A.Size;
		}
	};

	// Sort by size.
	PerObjectSizeArray.Sort( FCompareFObjectAndSize() );
	PerClassSizeArray.Sort( FCompareFObjectAndSize() );

	// Log information.
	UE_LOG(LogSerialization, Log, TEXT(""));
	UE_LOG(LogSerialization, Log, TEXT("Per class summary of bulk data use:"));
	for( int32 PerClassIndex=0; PerClassIndex<PerClassSizeArray.Num(); PerClassIndex++ )
	{
		const FObjectAndSize& PerClassSize = PerClassSizeArray[ PerClassIndex ];
		Log.Logf( TEXT("  %5d KByte of bulk data for Class %s"), PerClassSize.Size / 1024, *PerClassSize.Object->GetPathName() );
	}
	UE_LOG(LogSerialization, Log, TEXT(""));
	UE_LOG(LogSerialization, Log, TEXT("Detailed per object stats of bulk data use:"));
	for( int32 PerObjectIndex=0; PerObjectIndex<PerObjectSizeArray.Num(); PerObjectIndex++ )
	{
		const FObjectAndSize& PerObjectSize = PerObjectSizeArray[ PerObjectIndex ];
		Log.Logf( TEXT("  %5d KByte of bulk data for %s"), PerObjectSize.Size / 1024, *PerObjectSize.Object->GetFullName() );
	}
	UE_LOG(LogSerialization, Log, TEXT(""));
#else
	UE_LOG(LogSerialization, Log, TEXT("Please recompiled with TRACK_BULKDATA_USE set to 1 in UnBulkData.cpp."));
#endif
}