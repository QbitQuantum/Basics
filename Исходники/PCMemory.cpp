void	TLMemory::Platform::MemOuputAllocations()
{
	DWORD LastError;
	PROCESS_HEAP_ENTRY Entry;

	TChar buffer[256] = {0};

    // Lock the heap to prevent other threads from accessing the heap 
    // during enumeration.
    if (HeapLock(g_MemHeap) == FALSE) {
        _stprintf(&buffer[0], TEXT("Failed to lock heap with LastError %d.\n"),
                 GetLastError());

		OutputDebugString(buffer);
        return;
    }

    _stprintf(&buffer[0], TEXT("Walking heap %#p...\n\n"), g_MemHeap);
	OutputDebugString(buffer);

    Entry.lpData = NULL;
    while (HeapWalk(g_MemHeap, &Entry) != FALSE) 
	{
        if ((Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0) 
		{
            _stprintf(&buffer[0], TEXT("Allocated block"));
			OutputDebugString(buffer);

            if ((Entry.wFlags & PROCESS_HEAP_ENTRY_MOVEABLE) != 0) 
			{
                _stprintf(&buffer[0], TEXT(", movable with HANDLE %#p"), Entry.Block.hMem);
				OutputDebugString(buffer);
            }

            if ((Entry.wFlags & PROCESS_HEAP_ENTRY_DDESHARE) != 0) 
			{
                _stprintf(&buffer[0], TEXT(", DDESHARE"));
				OutputDebugString(buffer);
            }
        }
        else if ((Entry.wFlags & PROCESS_HEAP_REGION) != 0) 
		{
            _stprintf(&buffer[0], TEXT("Region\n  %d bytes committed\n") \
                     TEXT("  %d bytes uncommitted\n  First block address: %#p\n") \
                     TEXT("  Last block address: %#p\n"),
                     Entry.Region.dwCommittedSize,
                     Entry.Region.dwUnCommittedSize,
                     Entry.Region.lpFirstBlock,
                     Entry.Region.lpLastBlock);
			OutputDebugString(buffer);
        }
        else if ((Entry.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) != 0) 
		{
            _stprintf(&buffer[0], TEXT("Uncommitted range\n"));
			OutputDebugString(buffer);
        }
        else 
		{
            _stprintf(&buffer[0], TEXT("Block\n"));
			OutputDebugString(buffer);
        }

        _stprintf(&buffer[0], TEXT("  Data portion begins at: %#p\n  Size: %d bytes\n") \
                 TEXT("  Overhead: %d bytes\n  Region index: %d\n\n"),
                 Entry.lpData,
                 Entry.cbData,
                 Entry.cbOverhead,
                 Entry.iRegionIndex);
		OutputDebugString(buffer);
    }
    LastError = GetLastError();
    if (LastError != ERROR_NO_MORE_ITEMS) 
	{
        _stprintf(&buffer[0], TEXT("HeapWalk failed with LastError %d.\n"), LastError);
		OutputDebugString(buffer);
    }

    //
    // Unlock the heap to allow other threads to access the heap after 
    // enumeration has completed.
    //
    if (HeapUnlock(g_MemHeap) == FALSE) 
	{
        _stprintf(&buffer[0], TEXT("Failed to unlock heap with LastError %d.\n"),
                 GetLastError());
		OutputDebugString(buffer);
    }
}