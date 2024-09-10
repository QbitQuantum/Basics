void FAsyncIOSystemBase::InternalRead( IFileHandle* FileHandle, int64 Offset, int64 Size, void* Dest )
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("FAsyncIOSystemBase::InternalRead"), STAT_AsyncIOSystemBase_InternalRead, STATGROUP_AsyncIO_Verbose);

	FScopeLock ScopeLock( ExclusiveReadCriticalSection );

	STAT(double ReadTime = 0);
	{	
		SCOPE_SECONDS_COUNTER(ReadTime);
		PlatformReadDoNotCallDirectly( FileHandle, Offset, Size, Dest );
	}	
	INC_FLOAT_STAT_BY(STAT_AsyncIO_PlatformReadTime,(float)ReadTime);

	// The platform might actually read more than Size due to aligning and internal min read sizes
	// though we only really care about throttling requested bandwidth as it's not very accurate
	// to begin with.
	STAT(ConstrainBandwidth(Size, ReadTime));
}