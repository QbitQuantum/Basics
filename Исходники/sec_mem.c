static void unlockMemory( INOUT MEM_INFO_HEADER *memHdrPtr )
	{
	MEM_INFO_HEADER *currentBlockPtr;
	PTR_TYPE block1PageAddress, block2PageAddress;
	const int pageSize = getSysVar( SYSVAR_PAGESIZE );

	assert( isWritePtr( memHdrPtr, sizeof( MEM_INFO_HEADER ) ) );

	/* If the memory block isn't locked, there's nothing to do */
	if( !( memHdrPtr->flags & MEM_FLAG_LOCKED ) )
		return;

	/* Because VirtualLock() works on a per-page basis, we can't unlock a
	   memory block if there's another locked block on the same page.  The
	   only way to manage this is to walk the block list checking to see
	   whether there's another block allocated on the same page.  Although in
	   theory this could make freeing memory rather slow, in practice there
	   are only a small number of allocated blocks to check so it's
	   relatively quick, especially compared to the overhead imposed by the
	   lethargic VC++ allocator.  The only real disadvantage is that the
	   allocation objects remain locked while we do the free, but this
	   isn't any worse than the overhead of touchAllocatedPages().  Note 
	   that the following code assumes that an allocated block will never 
	   cover more than two pages, which is always the case.

	   First we calculate the addresses of the page(s) in which the memory 
	   block resides */
	block1PageAddress = getPageStartAddress( memHdrPtr );
	block2PageAddress = getPageEndAddress( memHdrPtr, memHdrPtr->size );
	if( block1PageAddress == block2PageAddress )
		block2PageAddress = 0;

	/* Walk down the block list checking whether the page(s) contain another 
	   locked block */
	for( currentBlockPtr = krnlData->allocatedListHead; \
		 currentBlockPtr != NULL; currentBlockPtr = currentBlockPtr->next )
		{
		const PTR_TYPE currentPage1Address = \
						getPageStartAddress( currentBlockPtr );
		PTR_TYPE currentPage2Address = \
						getPageEndAddress( currentBlockPtr, currentBlockPtr->size );

		if( currentPage1Address == currentPage2Address )
			currentPage2Address = 0;

		/* If there's another block allocated on either of the pages, don't
		   unlock it */
		if( block1PageAddress == currentPage1Address || \
			block1PageAddress == currentPage2Address )
			{
			block1PageAddress = 0;
			if( !block2PageAddress )
				break;
			}
		if( block2PageAddress == currentPage1Address || \
			block2PageAddress == currentPage2Address )
			{
			block2PageAddress = 0;
			if( !block1PageAddress )
				break;
			}
		}

	/* Finally, if either page needs unlocking, do so.  The supplied size is 
	   irrelevant since the entire page the memory is on is unlocked */
	if( block1PageAddress )
		VirtualUnlock( ( void * ) block1PageAddress, 16 );
	if( block2PageAddress )
		VirtualUnlock( ( void * ) block2PageAddress, 16 );
	}