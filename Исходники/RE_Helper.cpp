void __cdecl xf_dump()
{
	PROCESS_HEAP_ENTRY ent = {NULL};
	HeapLock(ghHeap);
	HeapCompact(ghHeap,0);
	char sBlockInfo[255];
	while (HeapWalk(ghHeap, &ent))
	{
		if (ent.wFlags & PROCESS_HEAP_ENTRY_BUSY) {
			xf_mem_block* p = (xf_mem_block*)ent.lpData;
			if (p->bBlockUsed==TRUE && p->nBlockSize==ent.cbData)
			{
#ifndef _WIN64
				wsprintfA(sBlockInfo, "!!! Lost memory block at 0x%08X, size %u\n    Allocated from: %s\n", ent.lpData, ent.cbData,
					p->sCreatedFrom);
#else
				wsprintfA(sBlockInfo, "!!! Lost memory block at 0x%I64X, size %u\n    Allocated from: %s\n", ent.lpData, ent.cbData,
					p->sCreatedFrom);
#endif
			} else {
#ifndef _WIN64
				wsprintfA(sBlockInfo, "!!! Lost memory block at 0x%08X, size %u\n    Allocated from: %s\n", ent.lpData, ent.cbData,
					"<Header information broken!>");
#else
				wsprintfA(sBlockInfo, "!!! Lost memory block at 0x%I64X, size %u\n    Allocated from: %s\n", ent.lpData, ent.cbData,
					"<Header information broken!>");
#endif
			}
			OutputDebugStringA(sBlockInfo);
		}
	}
	HeapUnlock(ghHeap);
}