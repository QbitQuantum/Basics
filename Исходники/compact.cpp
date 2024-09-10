// Perform a compacting GC
size_t ObjectMemory::compact(Oop* const sp)
{
	TRACE("Compacting OT, size %d, free %d, ...\n", m_nOTSize, m_pOT + m_nOTSize - m_pFreePointerList);
	EmptyZct(sp);

	// First perform a normal GC
	reclaimInaccessibleObjects(GCNormal);

	Interpreter::freePools();

	// Walk the OT from the bottom to locate free entries, and from the top to locate candidates to move
	// 

	size_t moved = 0;
	OTE* last = m_pOT + m_nOTSize - 1;
	OTE* first = m_pOT;
#pragma warning(push)
#pragma warning(disable : 4127)
	while(true)
#pragma warning(pop)
	{
		// Look for a tail ender
		while (last > first && last->isFree())
			last--;
		// Look for a free slot
		while (first < last && !first->isFree())
			first++;
		if (first == last)
			break;	// Met in the middle, we're done
		
		HARDASSERT(first->isFree());
		HARDASSERT(!last->isFree());

		// Copy the tail ender over the free slot
		*first = *last;
		moved++;
		// Leave forwarding pointer in the old slot
		last->m_location = reinterpret_cast<POBJECT>(first);
		last->beFree();
		last->m_count = 0;
		// Advance last as we've moved this slot
		last--;
	}

	HARDASSERT(last == first);
	// At this point, last == first, and the first free slot will be that after last

	TRACE("%d OTEs compacted\n", moved);

	// Now we can update the objects using the forwarding pointers in the old slots

	// We must remove the const. spaces memory protect for the duration of the pointer update
	ProtectConstSpace(PAGE_READWRITE);

	// New head of free list is first OTE after the single contiguous block of used OTEs
	// Need to set this before compacting as 
	m_pFreePointerList = last+1;

	// Now run through the new OT and update the Oops in the objects
	OTE* pOTE = m_pOT;
	while (pOTE <= last)
	{
		compactObject(pOTE);
		pOTE++;
	}

	// Note that this copies VMPointers to cache area
	ProtectConstSpace(PAGE_READONLY);

	// We must inform the interpreter that it needs to update any cached Oops from the forward pointers
	// before we rebuild the free list (which will destroy those pointers to the new OTEs)
	Interpreter::OnCompact();

	// The last used slot will be the slot before the first entry in the free list
	// Using this, round up from the last used slot to the to commit granularity, then uncommit any later slots
	// 
	
	OTE* end = (OTE*)_ROUND2(reinterpret_cast<ULONG_PTR>(m_pFreePointerList + 1), dwAllocationGranularity);

#ifdef _DEBUG
	m_nFreeOTEs = end - m_pFreePointerList;
#endif

	SIZE_T bytesToDecommit = reinterpret_cast<ULONG_PTR>(m_pOT + m_nOTSize) - reinterpret_cast<ULONG_PTR>(end);
	::VirtualFree(end, bytesToDecommit, MEM_DECOMMIT);
	m_nOTSize = end - m_pOT;

	// Now fix up the free list
	OTE* cur = m_pFreePointerList;
	while (cur < end)
	{
		HARDASSERT(cur->isFree());
		cur->m_location = reinterpret_cast<POBJECT>(cur + 1);
		cur++;
	}

	// Could do this before or after check refs, since that can account for Zct state
	PopulateZct(sp);

	CHECKREFERENCES

	HeapCompact();

	TRACE("... OT compacted, size %d, free %d.\n", m_nOTSize, end - m_pFreePointerList);

	Interpreter::scheduleFinalization();

	return m_pFreePointerList - m_pOT;
}