DWORD ConnectionLimit::ComputeCheckSum(LPCTSTR path)
{
	DWORD dwHeaderSum;
	DWORD dwCheckSum;
	PVOID oldValue = NULL;
	if(IsWow64())
	{
		MyWow64DisableWow64FsRedirection(&oldValue);
	}
	HANDLE hFile=CreateFile(path,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if(IsWow64())
	{
		MyWow64RevertWow64FsRedirection(oldValue);
	}
	if(hFile==INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	HANDLE mapping = CreateFileMapping(hFile,0,PAGE_READWRITE,0,0,NULL);
	if(!mapping)
	{
		CloseHandle(hFile);
		return 0;
	}		
	unsigned char* pView=(unsigned char *)MapViewOfFile(mapping,FILE_MAP_ALL_ACCESS,0,0,0);
	if(!pView)
	{
		CloseHandle(mapping);
		CloseHandle(hFile);
		return 0;
	}		
	DWORD nFileSize=GetFileSize(hFile,NULL);
	PIMAGE_NT_HEADERS pHeader=CheckSumMappedFile((LPVOID)pView,nFileSize,&dwHeaderSum,&dwCheckSum);	
	pHeader->OptionalHeader.CheckSum=dwCheckSum;
	pHeader=CheckSumMappedFile((LPVOID)pView,nFileSize,&dwHeaderSum,&dwCheckSum);	
	UnmapViewOfFile((LPCVOID)pView);
	CloseHandle(mapping);
	CloseHandle(hFile);			
	return dwCheckSum;
}