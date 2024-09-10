void GMem_Create(void)
{
	if(bGMemIsActive)
		return;

	SYSTEM_INFO SystemInfo;

	GetSystemInfo(&SystemInfo);
	dwGMemPhyPageSize = SystemInfo.dwPageSize;
	dwGMemUsedPhyBytes = ((dwGMemTotalBytes / SystemInfo.dwAllocationGranularity) + (DWORD)(0 < (dwGMemTotalBytes % SystemInfo.dwAllocationGranularity))) 
							* SystemInfo.dwAllocationGranularity;
	dwGMemUsedPhyPageNumber = (ULONG_PTR)(dwGMemUsedPhyBytes / dwGMemPhyPageSize + (DWORD)(0 < (dwGMemUsedPhyBytes % dwGMemPhyPageSize)));
	pulGMemUsedPhyPageArray = new ULONG_PTR[dwGMemUsedPhyPageNumber];

	SetPrivilege(TRUE);
	BOOL bFlag = AllocateUserPhysicalPages(GetCurrentProcess(), &dwGMemUsedPhyPageNumber, pulGMemUsedPhyPageArray);
	SetPrivilege(FALSE);
	if(!bFlag)
	{
		delete pulGMemUsedPhyPageArray;
		return;
	}
	dwGMemUsedPhyBytes = dwGMemUsedPhyPageNumber * dwGMemPhyPageSize;
	dwGMemPageNumber = (DWORD)(dwGMemUsedPhyBytes / dwGMemPageSize);
	dwGMemTotalBytes = dwGMemPageNumber * dwGMemPageSize;

	pGMemAddrHead = VirtualAlloc(NULL, dwGMemUsedPhyBytes, MEM_RESERVE | MEM_PHYSICAL, PAGE_READWRITE);
/*	DWORD dwerr =  GetLastError();*/
	if(!pGMemAddrHead)
	{
		FreeUserPhysicalPages(GetCurrentProcess(), &dwGMemUsedPhyPageNumber, pulGMemUsedPhyPageArray);
		delete pulGMemUsedPhyPageArray;
		return;
	}
	pGMemAddrTail = ((char *)pGMemAddrHead + dwGMemTotalBytes);

	if(!MapUserPhysicalPages(pGMemAddrHead, dwGMemUsedPhyPageNumber, pulGMemUsedPhyPageArray))
	{
		FreeUserPhysicalPages(GetCurrentProcess(), &dwGMemUsedPhyPageNumber, pulGMemUsedPhyPageArray);
		VirtualFree(pGMemAddrHead, 0, MEM_RELEASE);
		delete pulGMemUsedPhyPageArray;
		return;
	}
	
	dwGMemSysUsedBytes = dwGMemUsedPhyPageNumber * sizeof(ULONG_PTR);
	CopyMemory(pGMemAddrHead, pulGMemUsedPhyPageArray, dwGMemSysUsedBytes);
	delete pulGMemUsedPhyPageArray;
	pulGMemUsedPhyPageArray = (PULONG_PTR)pGMemAddrHead;

	pmbGMemUsedFlag = (PGMEM_BLOCK*)(((char*)pGMemAddrHead) + dwGMemSysUsedBytes);
	dwGMemSysUsedBytes += (dwGMemPageNumber * sizeof(PGMEM_BLOCK));
	ZeroMemory(pmbGMemUsedFlag, dwGMemPageNumber * sizeof(PGMEM_BLOCK));

	pmbGMemNodePool = (PGMEM_BLOCK)(((char*)pGMemAddrHead) + dwGMemSysUsedBytes);
	dwGMemSysUsedBytes += (dwGMemPageNumber * sizeof(GMEM_BLOCK));

	DWORD i;
	PGMEM_BLOCK pmbBlock;

	pmbBlock = pmbGMemNodePool;
	pmbBlock->pPrior = NULL;
	for(i = 1; i < dwGMemPageNumber; i++)
	{
		pmbBlock->pNext  = &(pmbGMemNodePool[i]);
		pmbBlock = pmbBlock->pNext ;
	}
	pmbBlock->pNext  = NULL;

	dwGMemUsedBytes = dwGMemPhyPageSize * ((dwGMemSysUsedBytes / dwGMemPhyPageSize) + (0 < (dwGMemSysUsedBytes % dwGMemPhyPageSize)));
	dwGMemSysUsedBytes = dwGMemUsedBytes;

	pmbGMemList = pmbGMemNodePool;
	pmbGMemNodePool = pmbGMemNodePool->pNext;
	pmbGMemList->pPrior = NULL;
	pmbGMemList->pNext  = NULL;
	pmbGMemList->pFreePrior = NULL;
	pmbGMemList->pFreeNext  = NULL;
	pmbGMemList->bIsFree = TRUE;
	pmbGMemList->pAddr = (PGMEM_BLOCK)(((char*)pGMemAddrHead) + dwGMemUsedBytes);
	pmbGMemList->dwSize = dwGMemTotalBytes - dwGMemUsedBytes;
	pmbGMemFreeList = pmbGMemList;

	bGMemIsActive = TRUE;
	InitializeCriticalSection(&csGMemCritical);
}