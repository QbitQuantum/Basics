NTSTATUS kull_m_process_getMemoryInformations(PKULL_M_MEMORY_HANDLE memory, PKULL_M_MEMORY_RANGE_ENUM_CALLBACK callBack, PVOID pvArg)
{
	NTSTATUS status = STATUS_NOT_FOUND;
	MEMORY_BASIC_INFORMATION memoryInfos;
	PBYTE currentPage, maxPage;
	PMINIDUMP_MEMORY_INFO_LIST maListeInfo = NULL;
	PMINIDUMP_MEMORY_INFO mesInfos = NULL;
	ULONG i;
	BOOL continueCallback = TRUE;
	
	if(!NT_SUCCESS(NtQuerySystemInformation(KIWI_SystemMmSystemRangeStart, &maxPage, sizeof(PBYTE), NULL)))
		maxPage = MmSystemRangeStart;

	switch(memory->type)
	{
	case KULL_M_MEMORY_TYPE_OWN:
		for(currentPage = 0; (currentPage < maxPage) && continueCallback; currentPage += memoryInfos.RegionSize)
			if(VirtualQuery(currentPage, &memoryInfos, sizeof(MEMORY_BASIC_INFORMATION)) == sizeof(MEMORY_BASIC_INFORMATION))
				continueCallback = callBack(&memoryInfos, pvArg);
			else break;
		status = STATUS_SUCCESS;
		break;
	case KULL_M_MEMORY_TYPE_PROCESS:
		for(currentPage = 0; (currentPage < maxPage) && continueCallback; currentPage += memoryInfos.RegionSize)
			if(VirtualQueryEx(memory->pHandleProcess->hProcess, currentPage, &memoryInfos, sizeof(MEMORY_BASIC_INFORMATION)) == sizeof(MEMORY_BASIC_INFORMATION))
				continueCallback = callBack(&memoryInfos, pvArg);
			else break;
		status = STATUS_SUCCESS;
		break;
	case KULL_M_MEMORY_TYPE_PROCESS_DMP:
		if(maListeInfo = (PMINIDUMP_MEMORY_INFO_LIST) kull_m_minidump_stream(memory->pHandleProcessDmp->hMinidump, MemoryInfoListStream))
		{
			for(i = 0; (i < maListeInfo->NumberOfEntries) && continueCallback; i++)
			{
				mesInfos = (PMINIDUMP_MEMORY_INFO) ((PBYTE) maListeInfo + maListeInfo->SizeOfHeader + (i * maListeInfo->SizeOfEntry));
				memoryInfos.AllocationBase = (PVOID) mesInfos->AllocationBase;
				memoryInfos.AllocationProtect = mesInfos->AllocationProtect;
				memoryInfos.BaseAddress = (PVOID) mesInfos->BaseAddress;
				memoryInfos.Protect = mesInfos->Protect;
				memoryInfos.RegionSize = (SIZE_T) mesInfos->RegionSize;
				memoryInfos.State = mesInfos->State;
				memoryInfos.Type = mesInfos->Type;
				continueCallback = callBack(&memoryInfos, pvArg);
			}
			status = STATUS_SUCCESS;
		}
		break;
	default:
		break;
	}

	return status;
}