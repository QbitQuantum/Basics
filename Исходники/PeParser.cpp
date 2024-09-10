bool PeParser::updatePeHeaderChecksum(const WCHAR * targetFile, DWORD fileSize)
{
	PIMAGE_NT_HEADERS32 pNTHeader32 = 0;
	PIMAGE_NT_HEADERS64 pNTHeader64 = 0;
	DWORD headerSum = 0;
	DWORD checkSum = 0;
	bool retValue = false;

	if (!fileSize)
		return retValue;

	HANDLE hFileToMap = CreateFile(targetFile, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if(hFileToMap != INVALID_HANDLE_VALUE)
	{
		HANDLE hMappedFile = CreateFileMapping(hFileToMap, 0, PAGE_READWRITE, 0, 0, 0);
		if(hMappedFile)
		{
			if (GetLastError() != ERROR_ALREADY_EXISTS)
			{
				LPVOID addrMappedDll = MapViewOfFile(hMappedFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

				if (addrMappedDll)
				{
					pNTHeader32 = (PIMAGE_NT_HEADERS32)CheckSumMappedFile(addrMappedDll, fileSize, &headerSum, &checkSum);

					if (pNTHeader32)
					{
						if (pNTHeader32->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
						{
							pNTHeader64 = (PIMAGE_NT_HEADERS64)pNTHeader32;
							pNTHeader64->OptionalHeader.CheckSum = checkSum;
						}
						else
						{
							pNTHeader32->OptionalHeader.CheckSum = checkSum;
						}

						retValue = true;
					}

					UnmapViewOfFile(addrMappedDll);
				}
			}
			CloseHandle(hMappedFile);
		}
		CloseHandle(hFileToMap);
	}

	return retValue;
}