void *Z_Malloc(int iSize, memtag_t eTag, qboolean bZeroit, int iAlign)
{
//	assert(s_Initialized);
	// Zone now initializes on first use. (During static constructors)
	if (!s_Initialized)
		Com_InitZoneMemory();
	
	if (iSize == 0)
	{
#ifdef _DEBUG
		return (void*)(&s_EmptyBlock.start + 1);
#else
		return (void*)(&s_EmptyBlock.header + 1);
#endif
	}

	if (iSize < 0)
	{
		Z_MallocFail("Negative size", iSize, eTag);
		return NULL;
	}

#ifndef _GAMECUBE
	WaitForSingleObject(s_Mutex, INFINITE);
#endif
	
	// Make new/delete memory temporary if requested
	if (eTag == TAG_NEWDEL && s_IsNewDeleteTemp)
	{
		eTag = TAG_TEMP_WORKSPACE;
	}

	// Determine how much space we need with headers and footers
	int header_size = sizeof(ZoneHeader);
	int footer_size = 0;
	if (Z_IsTagLinked(eTag))
	{
		header_size += sizeof(ZoneLinkHeader);
	}
#ifdef _DEBUG
	header_size += sizeof(ZoneDebugHeader);
	footer_size += sizeof(ZoneDebugFooter);
#endif
	int real_size = iSize + header_size + footer_size;
	int align_pad = 0;

	// Get a bit of free memory.  Temporary memory is allocated
	// from the end.  More permanent allocations are done at the
	// begining of the pool.
	ZoneFreeBlock* fblock;
	if (Z_IsTagTemp(eTag))
	{
		fblock = Z_FindLastFree(real_size, header_size, footer_size, 
			iAlign, align_pad);
	}
	else
	{
		fblock = Z_FindFirstFree(real_size, header_size, footer_size, 
			iAlign, align_pad);
	}

	// Did we actually find some memory?
	if (!fblock)
	{
#ifndef _GAMECUBE
		ReleaseMutex(s_Mutex);
#endif
//		if(eTag == TAG_TEMP_SND_RAWDATA) {
		if(eTag == TAG_SND_RAWDATA) {
			return NULL;
		}

		Z_MallocFail("Out of memory", iSize, eTag);
		return NULL;
	}

	// Add any alignment bytes
	real_size += align_pad;

	// Split the free block and get a pointer to the start
	// allocated space.
	void* ablock;
	if (Z_IsTagTemp(eTag))
	{
		ablock = Z_SplitFree(fblock, real_size, false);
		
		// Append align pad to end of block
		Z_SetupAlignmentPad(
			(void*)((char*)ablock + real_size - align_pad), 
			align_pad, false);
	}
	else
	{
		ablock = Z_SplitFree(fblock, real_size, true);

		// Insert align pad at block start
		Z_SetupAlignmentPad(ablock, align_pad, true);
		ablock = (void*)((char*)ablock + align_pad);
	}

	if (!ablock)
	{
		Z_MallocFail("Failed to split", iSize, eTag);
	}

	// Add linking header if necessary
	if (Z_IsTagLinked(eTag))
	{
		ZoneLinkHeader* linked = (ZoneLinkHeader*)ablock;
		linked->m_Next = s_LinkBase;
		linked->m_Prev = NULL;
		if (s_LinkBase)
		{
			s_LinkBase->m_Prev = linked;
		}
		s_LinkBase = linked;

		assert(Z_ValidateLinks());

		// Next...
		ablock = (void*)((char*)ablock + sizeof(ZoneLinkHeader));
	}

	// Setup the header:
	//		31		- alignment flag
	//		25-30	- tag
	//		0-24	- size without headers/footers
	assert(iSize >= 0 && iSize < (1 << 25));
	assert(eTag >= 0 && eTag < 64);
	ZoneHeader* header = (ZoneHeader*)ablock;
	*header = 
		(((unsigned int)eTag) << 25) |
		((unsigned int)iSize);

	if (align_pad)
	{
		*header |= (1 << 31);
	}

	// Next...
	ablock = (void*)((char*)ablock + sizeof(ZoneHeader));

#ifdef _DEBUG
	{
		// Setup the debug markers
		ZoneDebugHeader* debug_header = (ZoneDebugHeader*)ablock;

		ZoneDebugFooter* debug_footer = (ZoneDebugFooter*)((char*)debug_header + 
			(sizeof(ZoneDebugHeader) + iSize));

		*debug_header = ZONE_MAGIC;
		*debug_footer = ZONE_MAGIC;

		// Next...
		ablock = (void*)((char*)ablock + sizeof(ZoneDebugHeader));
	}
#endif

	// Update the stats
	s_Stats.m_SizeAlloc += iSize;
	s_Stats.m_OverheadAlloc += header_size + footer_size + align_pad;
	s_Stats.m_SizesPerTag[eTag] += iSize;
	s_Stats.m_CountAlloc++;
	s_Stats.m_CountsPerTag[eTag]++;

	if (s_Stats.m_SizeAlloc + s_Stats.m_OverheadAlloc > s_Stats.m_PeakAlloc)
	{
		s_Stats.m_PeakAlloc = s_Stats.m_SizeAlloc + s_Stats.m_OverheadAlloc;
	}

	// Return a pointer to data memory
	if (bZeroit)
	{
		memset(ablock, 0, iSize);
	}

	assert(iAlign == 0 || (unsigned int)ablock % iAlign == 0);

	/*
	   This is useful for figuring out who's allocating a certain block of
	   memory.  Please don't remove it.
	if(eTag == TAG_NEWDEL && (unsigned int)ablock >= 0x806c0000 && 
			(unsigned int)ablock <= 0x806c1000 && iSize == 24) {
		int suck = 0;
	}
	if(eTag == TAG_SMALL && (iSize == 7 || iSize == 96)) {
		int suck = 0;
	}
	if(eTag == TAG_CLIENTS) {
		int suck = 0;
	}
	
	if ((unsigned)ablock >= 0x1eb0000 && (unsigned)ablock <= 0x1ec0000 && iSize == 48)
	{
		int suck = 0;
	}
	*/

#ifndef _GAMECUBE
	ReleaseMutex(s_Mutex);
#endif

	return ablock;
}