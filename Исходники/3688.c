ULONG GetWin32kBase()
{
	ULONG i, Count, Status, BytesRet;
	PSYSTEM_MODULE_INFORMATION pSMI;
	
	Status=NtQuerySystemInformation(SystemModuleInformation, pSMI, 0, &BytesRet); //allocation length
	if(Status!=STATUS_INFO_LENGTH_MISMATCH)
		printf("Error with NtQuerySystemInformation : 0x%x : %d \n", Status, RtlNtStatusToDosError(Status));
	
	pSMI=(PSYSTEM_MODULE_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BytesRet);
	
	Status=NtQuerySystemInformation(SystemModuleInformation, pSMI, BytesRet, &BytesRet);
	
	if(Status!=STATUS_SUCCESS)
		printf("Error with NtQuerySystemInformation : 0x%x : %d \n", Status, RtlNtStatusToDosError(Status));
	
	/*
	The data returned to the SystemInformation buffer is a ULONG count of the number of
	handles followed immediately by an array of 
	SYSTEM_MODULE_INFORMATION.
	*/
	
	Count=*(PULONG)pSMI;
	pSMI=(PSYSTEM_MODULE_INFORMATION)((PUCHAR)pSMI+4);
	
	for(i=0; i<Count; i++)
	{	
		if(StrStr((pSMI+i)->ImageName, "win32k.sys"))
			return (ULONG)(pSMI+i)->Base;
	}
	
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, pSMI);
	
	return 0;	
}	