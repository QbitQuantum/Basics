// from TitanEngine SDK - Property of ReversingLabs www.reversinglabs.com
long long __stdcall hd_FindEx(HANDLE hProcess, LPVOID MemoryStart, DWORD MemorySize, LPVOID SearchPattern, DWORD PatternSize, LPBYTE WildCard)
{
	/*
		Description: Searches for a specific pattern of bytes in a process.
		Syntax: long long FindEx(
				__in HANDLE hProcess, 
				__in LPVOID MemoryStart,
				__in DWORD  MemorySize,
				__in LPVOID SearchPattern,
				__in DWORD  PatternSize, 
				__in_opt    WildCard
				);
		Parameters: - 
		Return value: -
	*/

	int i = NULL;
	int j = NULL;
	ULONG_PTR Return = NULL;
	LPVOID ueReadBuffer = NULL;
	PUCHAR SearchBuffer = NULL;
	PUCHAR CompareBuffer = NULL;
	MEMORY_BASIC_INFORMATION memoryInformation = {};
	ULONG_PTR ueNumberOfBytesRead = NULL;
	LPVOID currentSearchPosition = NULL;
	DWORD currentSizeOfSearch = NULL;
	BYTE nWildCard = NULL;

	if(WildCard == NULL){WildCard = &nWildCard;}
	if(hProcess != NULL && MemoryStart != NULL && MemorySize != NULL){
		if(hProcess != GetCurrentProcess()){
			ueReadBuffer = VirtualAlloc(NULL, MemorySize, MEM_COMMIT, PAGE_READWRITE);
			if(!ReadProcessMemory(hProcess, MemoryStart, ueReadBuffer, MemorySize, &ueNumberOfBytesRead)){
				if(ueNumberOfBytesRead == NULL){
					if(VirtualQueryEx(hProcess, MemoryStart, &memoryInformation, sizeof memoryInformation) != NULL){
						MemorySize = (DWORD)((ULONG_PTR)memoryInformation.BaseAddress + memoryInformation.RegionSize - (ULONG_PTR)MemoryStart);
						if(!ReadProcessMemory(hProcess, MemoryStart, ueReadBuffer, MemorySize, &ueNumberOfBytesRead)){
							VirtualFree(ueReadBuffer, NULL, MEM_RELEASE);
							return(NULL);
						}else{
							SearchBuffer = (PUCHAR)ueReadBuffer;
						}
					}else{
						VirtualFree(ueReadBuffer, NULL, MEM_RELEASE);
						return(NULL);
					}
				}else{
					SearchBuffer = (PUCHAR)ueReadBuffer;
				}
			}else{
				SearchBuffer = (PUCHAR)ueReadBuffer;
			}
		}else{
			SearchBuffer = (PUCHAR)MemoryStart;
		}
		__try{
			CompareBuffer = (PUCHAR)SearchPattern;
			for(i = 0; i < (int)MemorySize && Return == NULL; i++){
				for(j = 0; j < (int)PatternSize; j++){
					if(CompareBuffer[j] != *(PUCHAR)WildCard && SearchBuffer[i + j] != CompareBuffer[j]){
						break;
					}
				}
				if(j == (int)PatternSize){
					Return = (ULONG_PTR)MemoryStart + i;
				}
			}
			VirtualFree(ueReadBuffer, NULL, MEM_RELEASE);
			return(Return);
		}__except(EXCEPTION_EXECUTE_HANDLER){
			VirtualFree(ueReadBuffer, NULL, MEM_RELEASE);
			return(NULL);
		}
	}else{
		return(NULL);