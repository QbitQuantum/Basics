/* virtual */ void
BlockCacheK42::freeBlock(BlockCacheEntry *b)
{
    uval32 blkno = b->getBlockNumber();

    DBC("freeBlock", blkno);

    if (blkno != 0) { 	// we don't add blkno 0 to the cache
	// Sanity check; not necessary in terms of functionality
	HashData *data;
	(void)blockHash.findAndLock(blkno, &data);
	tassertMsg(data != NULL, "freeing block that is not there\n");
	data->unlock();
    }

    BlockCacheEntryK42 *block = (BlockCacheEntryK42*)b;
    block->removeUser();
    tassertMsg(block->getUsers() >= 0, "users %ld\n", block->getUsers());

    if (block->getUsers() == 0) {
#ifdef FREEING_ENTRY_WHEN_NO_USERS
	/* FIXME Notice that for now we're not freeing anything from the cache
	 * hash (the entry is only marked as "empty" in the DHash); if
	 * we were ideally we should have a good cache eviction instead of: */
	if (blkno) { 	// we don't add blkno 0 to the cache
	    if (block->isDirty) {
		block->d->writeBlock(block->blkno, block->data);
		block->isDirty = 0;
	    }
	    blockHash.removeData(blkno);
	    BCSTAT(FREE); // collect statistic about BlockCache
	    // for now we'll leak it, so let's output it
	} else {
	    tassertMsg(0, "debugging");
	    delete block;
	}
#else //#ifdef FREEING_ENTRY_WHEN_NO_USERS
	// Check if it's just an (annonymous) empty page, no need to panic.
	// Just kill/free it.
	if (!blkno) {
	    delete block;
	}
#endif //#ifdef FREEING_ENTRY_WHEN_NO_USERS
    }
}