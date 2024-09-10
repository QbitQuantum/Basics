/*
 * PGSharedMemoryCreate
 *
 * Create a shared memory segment of the given size and initialize its
 * standard header.
 *
 * makePrivate means to always create a new segment, rather than attach to
 * or recycle any existing segment. On win32, we always create a new segment,
 * since there is no need for recycling (segments go away automatically
 * when the last backend exits)
 */
PGShmemHeader *
PGSharedMemoryCreate(Size size, bool makePrivate, int port,
					 PGShmemHeader **shim)
{
	void	   *memAddress;
	PGShmemHeader *hdr;
	HANDLE		hmap,
				hmap2;
	char	   *szShareMem;
	int			i;
	DWORD		size_high;
	DWORD		size_low;
	SIZE_T		largePageSize = 0;
	Size		orig_size = size;
	DWORD		flProtect = PAGE_READWRITE;

	/* Room for a header? */
	Assert(size > MAXALIGN(sizeof(PGShmemHeader)));

	szShareMem = GetSharedMemName();

	UsedShmemSegAddr = NULL;

	if (huge_pages == HUGE_PAGES_ON || huge_pages == HUGE_PAGES_TRY)
	{
		/* Does the processor support large pages? */
		largePageSize = GetLargePageMinimum();
		if (largePageSize == 0)
		{
			ereport(huge_pages == HUGE_PAGES_ON ? FATAL : DEBUG1,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("the processor does not support large pages")));
			ereport(DEBUG1,
					(errmsg("disabling huge pages")));
		}
		else if (!EnableLockPagesPrivilege(huge_pages == HUGE_PAGES_ON ? FATAL : DEBUG1))
		{
			ereport(DEBUG1,
					(errmsg("disabling huge pages")));
		}
		else
		{
			/* Huge pages available and privilege enabled, so turn on */
			flProtect = PAGE_READWRITE | SEC_COMMIT | SEC_LARGE_PAGES;

			/* Round size up as appropriate. */
			if (size % largePageSize != 0)
				size += largePageSize - (size % largePageSize);
		}
	}

retry:
#ifdef _WIN64
	size_high = size >> 32;
#else
	size_high = 0;
#endif
	size_low = (DWORD) size;

	/*
	 * When recycling a shared memory segment, it may take a short while
	 * before it gets dropped from the global namespace. So re-try after
	 * sleeping for a second, and continue retrying 10 times. (both the 1
	 * second time and the 10 retries are completely arbitrary)
	 */
	for (i = 0; i < 10; i++)
	{
		/*
		 * In case CreateFileMapping() doesn't set the error code to 0 on
		 * success
		 */
		SetLastError(0);

		hmap = CreateFileMapping(INVALID_HANDLE_VALUE,	/* Use the pagefile */
								 NULL,	/* Default security attrs */
								 flProtect,
								 size_high, /* Size Upper 32 Bits	*/
								 size_low,	/* Size Lower 32 bits */
								 szShareMem);

		if (!hmap)
		{
			if (GetLastError() == ERROR_NO_SYSTEM_RESOURCES &&
				huge_pages == HUGE_PAGES_TRY &&
				(flProtect & SEC_LARGE_PAGES) != 0)
			{
				elog(DEBUG1, "CreateFileMapping(%zu) with SEC_LARGE_PAGES failed, "
					 "huge pages disabled",
					 size);

				/*
				 * Use the original size, not the rounded-up value, when falling back
				 * to non-huge pages.
				 */
				size = orig_size;
				flProtect = PAGE_READWRITE;
				goto retry;
			}
			else
				ereport(FATAL,
						(errmsg("could not create shared memory segment: error code %lu", GetLastError()),
						 errdetail("Failed system call was CreateFileMapping(size=%zu, name=%s).",
								   size, szShareMem)));
		}

		/*
		 * If the segment already existed, CreateFileMapping() will return a
		 * handle to the existing one and set ERROR_ALREADY_EXISTS.
		 */
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CloseHandle(hmap);	/* Close the handle, since we got a valid one
								 * to the previous segment. */
			hmap = NULL;
			Sleep(1000);
			continue;
		}
		break;
	}

	/*
	 * If the last call in the loop still returned ERROR_ALREADY_EXISTS, this
	 * shared memory segment exists and we assume it belongs to somebody else.
	 */
	if (!hmap)
		ereport(FATAL,
				(errmsg("pre-existing shared memory block is still in use"),
				 errhint("Check if there are any old server processes still running, and terminate them.")));

	free(szShareMem);

	/*
	 * Make the handle inheritable
	 */
	if (!DuplicateHandle(GetCurrentProcess(), hmap, GetCurrentProcess(), &hmap2, 0, TRUE, DUPLICATE_SAME_ACCESS))
		ereport(FATAL,
				(errmsg("could not create shared memory segment: error code %lu", GetLastError()),
				 errdetail("Failed system call was DuplicateHandle.")));

	/*
	 * Close the old, non-inheritable handle. If this fails we don't really
	 * care.
	 */
	if (!CloseHandle(hmap))
		elog(LOG, "could not close handle to shared memory: error code %lu", GetLastError());


	/*
	 * Get a pointer to the new shared memory segment. Map the whole segment
	 * at once, and let the system decide on the initial address.
	 */
	memAddress = MapViewOfFileEx(hmap2, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0, NULL);
	if (!memAddress)
		ereport(FATAL,
				(errmsg("could not create shared memory segment: error code %lu", GetLastError()),
				 errdetail("Failed system call was MapViewOfFileEx.")));



	/*
	 * OK, we created a new segment.  Mark it as created by this process. The
	 * order of assignments here is critical so that another Postgres process
	 * can't see the header as valid but belonging to an invalid PID!
	 */
	hdr = (PGShmemHeader *) memAddress;
	hdr->creatorPID = getpid();
	hdr->magic = PGShmemMagic;

	/*
	 * Initialize space allocation status for segment.
	 */
	hdr->totalsize = size;
	hdr->freeoffset = MAXALIGN(sizeof(PGShmemHeader));
	hdr->dsm_control = 0;

	/* Save info for possible future use */
	UsedShmemSegAddr = memAddress;
	UsedShmemSegSize = size;
	UsedShmemSegID = hmap2;

	/* Register on-exit routine to delete the new segment */
	on_shmem_exit(pgwin32_SharedMemoryDelete, PointerGetDatum(hmap2));

	*shim = hdr;
	return hdr;
}