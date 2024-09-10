void *Hunk_Begin (int maxsize, int precommit)
{
	// reserve a huge chunk of memory, but don't commit any yet
	bytes_used = 0;
	bytes_allocated = 0;

#ifdef VIRTUAL_ALLOC_PROFILE
	small_hits = 0;
#endif

	if (!pagesize)
	{
		SYSTEM_INFO sSysInfo;         // useful information about the system
		GetSystemInfo (&sSysInfo);     // initialize the structure
		pagesize = sSysInfo.dwPageSize;
	}

//	tempBuff = NULL;
//	tempBuffSize = TBUFFERLEN;
	hunkmaxsize = maxsize;
#if VIRTUAL_ALLOC
	if (precommit == maxsize)
	{
		membase = VirtualAlloc (NULL, precommit, MEM_COMMIT, PAGE_READWRITE);
		bytes_allocated = precommit;
	}
	else
	{
		membase = VirtualAlloc (NULL, maxsize, MEM_RESERVE, PAGE_NOACCESS);

		if (precommit)
		{
			VirtualAlloc (membase, precommit, MEM_COMMIT, PAGE_READWRITE);
			bytes_allocated = precommit;
		}
	}

#elif CREATE_HEAP
	{
		ULONG lfh = 2;
		membase = HeapCreate (HEAP_NO_SERIALIZE, 524288, 0);
		HeapSetInformation (membase, HeapCompatibilityInformation, &lfh, sizeof(lfh));
	}
#else
	membase = malloc (maxsize);
#endif
	if (!membase)
		Sys_Error ("VirtualAlloc reserve failed");
	return (void *)membase;
}