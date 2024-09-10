/*
 *	visibilitymap_truncate - truncate the visibility map
 *
 * The caller must hold AccessExclusiveLock on the relation, to ensure that
 * other backends receive the smgr invalidation event that this function sends
 * before they access the VM again.
 *
 * nheapblocks is the new size of the heap.
 */
void
visibilitymap_truncate(Relation rel, BlockNumber nheapblocks)
{
	BlockNumber newnblocks;

	/* last remaining block, byte, and bit */
	BlockNumber truncBlock = HEAPBLK_TO_MAPBLOCK(nheapblocks);
	uint32		truncByte = HEAPBLK_TO_MAPBYTE(nheapblocks);
	uint8		truncBit = HEAPBLK_TO_MAPBIT(nheapblocks);

#ifdef TRACE_VISIBILITYMAP
	elog(DEBUG1, "vm_truncate %s %d", RelationGetRelationName(rel), nheapblocks);
#endif

	RelationOpenSmgr(rel);

	/*
	 * If no visibility map has been created yet for this relation, there's
	 * nothing to truncate.
	 */
	if (!smgrexists(rel->rd_smgr, VISIBILITYMAP_FORKNUM))
		return;

	/*
	 * Unless the new size is exactly at a visibility map page boundary, the
	 * tail bits in the last remaining map page, representing truncated heap
	 * blocks, need to be cleared. This is not only tidy, but also necessary
	 * because we don't get a chance to clear the bits if the heap is extended
	 * again.
	 */
	if (truncByte != 0 || truncBit != 0)
	{
		Buffer		mapBuffer;
		Page		page;
		char	   *map;

		newnblocks = truncBlock + 1;

		mapBuffer = vm_readbuf(rel, truncBlock, false);
		if (!BufferIsValid(mapBuffer))
		{
			/* nothing to do, the file was already smaller */
			return;
		}

		page = BufferGetPage(mapBuffer);
		map = PageGetContents(page);

		LockBuffer(mapBuffer, BUFFER_LOCK_EXCLUSIVE);

		/* Clear out the unwanted bytes. */
		MemSet(&map[truncByte + 1], 0, MAPSIZE - (truncByte + 1));

		/*
		 * Mask out the unwanted bits of the last remaining byte.
		 *
		 * ((1 << 0) - 1) = 00000000 ((1 << 1) - 1) = 00000001 ... ((1 << 6) -
		 * 1) = 00111111 ((1 << 7) - 1) = 01111111
		 */
		map[truncByte] &= (1 << truncBit) - 1;

		MarkBufferDirty(mapBuffer);
		UnlockReleaseBuffer(mapBuffer);
	}
	else
		newnblocks = truncBlock;

	if (smgrnblocks(rel->rd_smgr, VISIBILITYMAP_FORKNUM) <= newnblocks)
	{
		/* nothing to do, the file was already smaller than requested size */
		return;
	}

	/* Truncate the unused VM pages, and send smgr inval message */
	smgrtruncate(rel->rd_smgr, VISIBILITYMAP_FORKNUM, newnblocks);

	/*
	 * We might as well update the local smgr_vm_nblocks setting. smgrtruncate
	 * sent an smgr cache inval message, which will cause other backends to
	 * invalidate their copy of smgr_vm_nblocks, and this one too at the next
	 * command boundary.  But this ensures it isn't outright wrong until then.
	 */
	if (rel->rd_smgr)
		rel->rd_smgr->smgr_vm_nblocks = newnblocks;
}