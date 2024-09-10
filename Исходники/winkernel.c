PVOID GetSectionDllFuncAddr(IN PCHAR lpFunctionName, IN PVOID BaseAddress) 
{
	PVOID functionAddress = NULL;
	PIMAGE_DOS_HEADER dosheader;
	PIMAGE_OPTIONAL_HEADER opthdr;
	PIMAGE_EXPORT_DIRECTORY pExportTable;
	PDWORD arrayOfFunctionAddresses;
	PDWORD arrayOfFunctionNames;
	PWORD arrayOfFunctionOrdinals;
	DWORD Base;
	STRING ntFunctionName, ntFunctionNameSearch;
	PCHAR functionName;
	DWORD functionOrdinal;
	ULONG x;

	ASSERT(lpFunctionName&&BaseAddress);
	dosheader = (PIMAGE_DOS_HEADER)BaseAddress;
	opthdr =(PIMAGE_OPTIONAL_HEADER) ((PBYTE)BaseAddress+dosheader->e_lfanew+24);
	pExportTable =(PIMAGE_EXPORT_DIRECTORY)((PBYTE)BaseAddress + opthdr->DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT]. VirtualAddress);
	// now we can get the exported functions, but note we convert from RVA to address
	arrayOfFunctionAddresses = (PDWORD)( (PBYTE)BaseAddress + pExportTable->AddressOfFunctions);
	arrayOfFunctionNames = (PDWORD)( (PBYTE)BaseAddress + pExportTable->AddressOfNames);
	arrayOfFunctionOrdinals = (PWORD)( (PBYTE)BaseAddress + pExportTable->AddressOfNameOrdinals);
	Base = pExportTable->Base;
	RtlInitString(&ntFunctionNameSearch, lpFunctionName);
	for (x = 0; x < pExportTable->NumberOfFunctions; x++) {
		functionName = (PCHAR)( (PBYTE)BaseAddress + arrayOfFunctionNames[x]);
		RtlInitString(&ntFunctionName, functionName);
		functionOrdinal = arrayOfFunctionOrdinals[x] + Base - 1; // always need to add base, -1 as array counts from 0
		// this is the funny bit.  you would expect the function pointer to simply be arrayOfFunctionAddresses[x]...
		// oh no... thats too simple.  it is actually arrayOfFunctionAddresses[functionOrdinal]!!
		if (RtlCompareString(&ntFunctionName, &ntFunctionNameSearch, TRUE) == 0) {
			functionAddress = (PBYTE)BaseAddress + arrayOfFunctionAddresses[functionOrdinal];
			break;
		}
	}
	return functionAddress;
}