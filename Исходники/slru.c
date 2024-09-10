void
SimpleLruInit(SlruCtl ctl, const char *name,
			  LWLockId ctllock, const char *subdir)
{
	SlruShared	shared;
	bool		found;

	shared = (SlruShared) ShmemInitStruct(name, SimpleLruShmemSize(), &found);

	if (!IsUnderPostmaster)
	{
		/* Initialize locks and shared memory area */
		char	   *bufptr;
		int			slotno;

		Assert(!found);

		memset(shared, 0, sizeof(SlruSharedData));

		shared->ControlLock = ctllock;

		bufptr = (char *) shared + BUFFERALIGN(sizeof(SlruSharedData));

		for (slotno = 0; slotno < NUM_SLRU_BUFFERS; slotno++)
		{
			shared->page_buffer[slotno] = bufptr;
			shared->page_status[slotno] = SLRU_PAGE_EMPTY;
			shared->page_lru_count[slotno] = 1;
			shared->buffer_locks[slotno] = LWLockAssign();
			bufptr += BLCKSZ;
		}

		/* shared->latest_page_number will be set later */
	}
	else
		Assert(found);

	/*
	 * Initialize the unshared control struct, including directory path. We
	 * assume caller set PagePrecedes.
	 */
	ctl->shared = shared;
	ctl->do_fsync = true;		/* default behavior */
	StrNCpy(ctl->Dir, subdir, sizeof(ctl->Dir));
}