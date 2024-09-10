bool VirtualMemoryManager::EnsureFreeMemory(size_t size)
{
	if(!inited)
		return false;

	LockMut(vmemMutex);

	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);

	while(ms.dwAvailPhys < size)
	{
		if(LOG && logging)
			LOG->Trace("Freeing memory: need %i, have %i", size, ms.dwAvailPhys);

		if(!DecommitLRU())
		{
			if(LOG)
				LOG->Trace("VMem error: No pages left to free while reserving memory");
			return false;
		}
	}

	return true;
}