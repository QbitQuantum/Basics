VOID
BtrFreeLookaside(
	__in BTR_LOOKASIDE_TYPE Type,
	__in PVOID Ptr
	)
{
	PBTR_LOOKASIDE Lookaside;
	PSLIST_ENTRY ListEntry;
	USHORT Depth;

	if (!Ptr) {
		return;
	}

	Lookaside = &BtrLookaside[Type];
	InterlockedIncrement(&Lookaside->TotalFrees);

	Depth = QueryDepthSList(&Lookaside->ListHead);
	ListEntry = (PSLIST_ENTRY)((PUCHAR)Ptr - MEMORY_ALLOCATION_ALIGNMENT);

	if (Depth < Lookaside->MaximumDepth) {
		InterlockedPushEntrySList(&Lookaside->ListHead, ListEntry);
	} else {
		InterlockedIncrement(&Lookaside->FreeMisses);
		BtrAlignedFree(ListEntry);
	}
}