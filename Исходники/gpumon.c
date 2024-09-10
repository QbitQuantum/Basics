static VOID NTAPI ProcessesUpdatedCallback(
	_In_opt_ PVOID Parameter,
	_In_opt_ PVOID Context
	)
{
	static ULONG runCount = 0; // MUST keep in sync with runCount in process provider

	DOUBLE elapsedTime; // total GPU node elapsed time in micro-seconds
	ULONG i;
	PLIST_ENTRY listEntry;
	FLOAT maxNodeValue = 0;
	PET_PROCESS_BLOCK maxNodeBlock = NULL;

	// Update global statistics.

	EtpUpdateSegmentInformation(NULL);
	EtpUpdateNodeInformation(NULL);

	elapsedTime = (DOUBLE)EtClockTotalRunningTimeDelta.Delta * 10000000 / EtClockTotalRunningTimeFrequency.QuadPart;

	if (elapsedTime != 0)
		EtGpuNodeUsage = (FLOAT)(EtGpuTotalRunningTimeDelta.Delta / (elapsedTime * EtGpuNodeBitMapBitsSet));
	else
		EtGpuNodeUsage = 0;

	if (EtGpuNodeUsage > 1)
		EtGpuNodeUsage = 1;

	// Do the update of the node bitmap if needed.
	if (EtGpuNewNodeBitMapBuffer)
	{
		PULONG newBuffer;

		newBuffer = _InterlockedExchangePointer(&EtGpuNewNodeBitMapBuffer, NULL);

		if (newBuffer)
		{
			PhFree(EtGpuNodeBitMap.Buffer);
			EtGpuNodeBitMap.Buffer = newBuffer;
			EtGpuNodeBitMapBuffer = newBuffer;
			EtGpuNodeBitMapBitsSet = RtlNumberOfSetBits(&EtGpuNodeBitMap);
			EtSaveGpuMonitorSettings();
		}
	}

	// Update per-process statistics.
	// Note: no lock is needed because we only ever modify the list on this same thread.

	//@@HTK
	listEntry = EtProcessBlockListHead.Flink;

	while (listEntry != &EtProcessBlockListHead)
	{
	    PET_PROCESS_BLOCK block;

	    block = CONTAINING_RECORD(listEntry, ET_PROCESS_BLOCK, ListEntry);

	    EtpUpdateSegmentInformation(block);
	    EtpUpdateNodeInformation(block);

	    if (elapsedTime != 0)
	    {
	        block->GpuNodeUsage = (FLOAT)(block->GpuRunningTimeDelta.Delta / (elapsedTime * EtGpuNodeBitMapBitsSet));

	        if (block->GpuNodeUsage > 1)
	            block->GpuNodeUsage = 1;
	    }

	    if (maxNodeValue < block->GpuNodeUsage)
	    {
	        maxNodeValue = block->GpuNodeUsage;
	        maxNodeBlock = block;
	    }

	    listEntry = listEntry->Flink;
	}

	// Update history buffers.

	if (runCount != 0)
	{
		PhAddItemCircularBuffer_FLOAT(&EtGpuNodeHistory, EtGpuNodeUsage);
		PhAddItemCircularBuffer_ULONG(&EtGpuDedicatedHistory, (ULONG)(EtGpuDedicatedUsage / PAGE_SIZE));
		PhAddItemCircularBuffer_ULONG(&EtGpuSharedHistory, (ULONG)(EtGpuSharedUsage / PAGE_SIZE));

		for (i = 0; i < EtGpuTotalNodeCount; i++)
		{
			FLOAT usage;

			usage = (FLOAT)(EtGpuNodesTotalRunningTimeDelta[i].Delta / elapsedTime);

			if (usage > 1)
				usage = 1;

			PhAddItemCircularBuffer_FLOAT(&EtGpuNodesHistory[i], usage);
		}

		if (maxNodeBlock)
		{
			PhAddItemCircularBuffer_ULONG(&EtMaxGpuNodeHistory, HandleToUlong(maxNodeBlock->ProcessItem->ProcessId));
			PhAddItemCircularBuffer_FLOAT(&EtMaxGpuNodeUsageHistory, maxNodeBlock->GpuNodeUsage);
			PhReferenceProcessRecordForStatistics(maxNodeBlock->ProcessItem->Record);
		}
		else
		{
			PhAddItemCircularBuffer_ULONG(&EtMaxGpuNodeHistory, 0);
			PhAddItemCircularBuffer_FLOAT(&EtMaxGpuNodeUsageHistory, 0);
		}
	}

	runCount++;
}