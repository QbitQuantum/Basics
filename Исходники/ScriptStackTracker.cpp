/**
* Dumps capture stack trace summary to the passed in log.
*/
void FScriptStackTracker::DumpStackTraces( int32 StackThreshold, FOutputDevice& Ar )
{
	// Avoid distorting results while we log them.
	check( !bAvoidCapturing );
	bAvoidCapturing = true;

	// Make a copy as sorting causes index mismatch with TMap otherwise.
	TArray<FCallStack> SortedCallStacks = CallStacks;
	// Compare function, sorting callstack by stack count in descending order.
	struct FCompareStackCount
	{
		FORCEINLINE bool operator()( const FCallStack& A, const FCallStack& B ) const { return B.StackCount < A.StackCount; }
	};
	// Sort callstacks in descending order by stack count.
	SortedCallStacks.Sort( FCompareStackCount() );

	// Iterate over each callstack to get total stack count.
	uint64 TotalStackCount = 0;
	for( int32 CallStackIndex=0; CallStackIndex<SortedCallStacks.Num(); CallStackIndex++ )
	{
		const FCallStack& CallStack = SortedCallStacks[CallStackIndex];
		TotalStackCount += CallStack.StackCount;
	}

	// Calculate the number of frames we captured.
	int32 FramesCaptured = 0;
	if( bIsEnabled )
	{
		FramesCaptured = GFrameCounter - StartFrameCounter;
	}
	else
	{
		FramesCaptured = StopFrameCounter - StartFrameCounter;
	}

	// Log quick summary as we don't log each individual so totals in CSV won't represent real totals.
	Ar.Logf(TEXT("Captured %i unique callstacks totalling %i function calls over %i frames, averaging %5.2f calls/frame"), SortedCallStacks.Num(), (int32)TotalStackCount, FramesCaptured, (float) TotalStackCount / FramesCaptured);

	// Iterate over each callstack and write out info in human readable form in CSV format
	for( int32 CallStackIndex=0; CallStackIndex<SortedCallStacks.Num(); CallStackIndex++ )
	{
		const FCallStack& CallStack = SortedCallStacks[CallStackIndex];

		// Avoid log spam by only logging above threshold.
		if( CallStack.StackCount > StackThreshold )
		{
			// First row is stack count.
			FString CallStackString = FString::FromInt((int32)CallStack.StackCount);
			CallStackString += LINE_TERMINATOR;
			CallStackString += CallStack.StackTrace;

			// Finally log with ',' prefix so "Log:" can easily be discarded as row in Excel.
			Ar.Logf(TEXT(",%s"),*CallStackString);
		}
	}

	// Done logging.
	bAvoidCapturing = false;
}