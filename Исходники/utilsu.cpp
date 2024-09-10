BOOL UtiSetFileDllFlag(LPCSTR lpPath)
{
	BOOL bRet = FALSE;
	DWORD dwSize;
	PVOID pMap;
	PIMAGE_NT_HEADERS pNtHeader;
	DWORD HeaderSum, CheckSum;
	
	pMap = UtiMapFile(lpPath, GENERIC_WRITE|GENERIC_READ, FILE_FLAG_WRITE_THROUGH, PAGE_READWRITE, FILE_MAP_WRITE|FILE_MAP_READ, &dwSize);
	if (pMap)
	{
		pNtHeader = (PIMAGE_NT_HEADERS)RtlImageNtHeader(pMap);
		if (pNtHeader)
		{
			pNtHeader->FileHeader.Characteristics |= IMAGE_FILE_DLL;

			bRet = (BOOL)CheckSumMappedFile(pMap, dwSize, &HeaderSum, &CheckSum);
			if (bRet) pNtHeader->OptionalHeader.CheckSum = CheckSum;
		}

		FlushViewOfFile(pMap, dwSize);
		UnmapViewOfFile(pMap);
	}

	return bRet;
}