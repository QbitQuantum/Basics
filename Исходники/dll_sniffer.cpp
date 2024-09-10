MUUID* GetPluginInterfaces(const TCHAR* ptszFileName, bool& bIsPlugin)
{
	bIsPlugin = false;

	HANDLE hFile = CreateFile( ptszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;

	MUUID* pResult = NULL;
	BYTE* ptr = NULL;
	HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL );

	__try {
		__try {
			if (!hMap )
				__leave;

			DWORD dwHSize = 0, filesize = GetFileSize( hFile, &dwHSize );
			if (!filesize || filesize == INVALID_FILE_SIZE || dwHSize)
				__leave;

			if ( filesize < sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS) )
				__leave;

			ptr = (BYTE*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
			if (ptr == NULL)
				__leave;

			PIMAGE_NT_HEADERS pINTH;
			PIMAGE_DOS_HEADER pIDH = (PIMAGE_DOS_HEADER)ptr;
			if ( pIDH->e_magic == IMAGE_DOS_SIGNATURE )
				pINTH = (PIMAGE_NT_HEADERS)(ptr + pIDH->e_lfanew);
			else
				__leave;

			if ((PBYTE)pINTH + sizeof(IMAGE_NT_HEADERS) >= ptr + filesize )
				__leave;
			if ( pINTH->Signature != IMAGE_NT_SIGNATURE )
				__leave;

			int nSections = pINTH->FileHeader.NumberOfSections;
			if (!nSections )
				__leave;

			INT_PTR base;
			PIMAGE_DATA_DIRECTORY pIDD;
			if ( pINTH->FileHeader.Machine == IMAGE_FILE_MACHINE_I386 &&
				  pINTH->FileHeader.SizeOfOptionalHeader >= sizeof(IMAGE_OPTIONAL_HEADER32) &&
				  pINTH->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
			{
				pIDD = (PIMAGE_DATA_DIRECTORY)( (PBYTE)pINTH + offsetof( IMAGE_NT_HEADERS32, OptionalHeader.DataDirectory ));
				base = *(DWORD*)((PBYTE)pINTH + offsetof(IMAGE_NT_HEADERS32, OptionalHeader.ImageBase));
			}
			else if ( pINTH->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64 &&
						 pINTH->FileHeader.SizeOfOptionalHeader >= sizeof(IMAGE_OPTIONAL_HEADER64) &&
						 pINTH->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
			{
				pIDD = (PIMAGE_DATA_DIRECTORY)( (PBYTE)pINTH + offsetof( IMAGE_NT_HEADERS64, OptionalHeader.DataDirectory ));
				base = *(ULONGLONG*)((PBYTE)pINTH + offsetof(IMAGE_NT_HEADERS64, OptionalHeader.ImageBase ));
			}
			else __leave;

			// Export information entry
			DWORD expvaddr = pIDD[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
			DWORD expsize  = pIDD[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
			if (expsize < sizeof(IMAGE_EXPORT_DIRECTORY)) __leave;

			BYTE* pImage = ptr + pIDH->e_lfanew + pINTH->FileHeader.SizeOfOptionalHeader + sizeof(IMAGE_NT_HEADERS) - sizeof(IMAGE_OPTIONAL_HEADER);
			IMAGE_SECTION_HEADER *pExp = getSectionByRVA((IMAGE_SECTION_HEADER *)pImage, nSections, pIDD);
			if (!pExp) __leave;

			BYTE *pSecStart = ptr + pExp->PointerToRawData - pExp->VirtualAddress;
			IMAGE_EXPORT_DIRECTORY *pED = (PIMAGE_EXPORT_DIRECTORY)&pSecStart[expvaddr];
			DWORD *ptrRVA = (DWORD*)&pSecStart[pED->AddressOfNames];
			WORD  *ptrOrdRVA = (WORD*)&pSecStart[pED->AddressOfNameOrdinals];
			DWORD *ptrFuncList = (DWORD*)&pSecStart[pED->AddressOfFunctions];

			MUUID* pIds;
			bool bHasLoad = false, bHasUnload = false, bHasInfo = false, bHasMuuids = false;
			for (size_t i=0; i < pED->NumberOfNames; i++, ptrRVA++, ptrOrdRVA++) {
				char *szName = (char*)&pSecStart[*ptrRVA];
				if (!lstrcmpA(szName, "Load"))
					bHasLoad = true;
				if (!lstrcmpA(szName, "MirandaPluginInfoEx"))
					bHasInfo = true;
				else if (!lstrcmpA(szName, "Unload"))
					bHasUnload = true;
				else if (!lstrcmpA(szName, "MirandaInterfaces")) {
					bHasMuuids = true;
					pIds = (MUUID*)&pSecStart[ ptrFuncList[*ptrOrdRVA]];
				}
				// old plugin, skip it
				else if (!lstrcmpA(szName, "MirandaPluginInterfaces"))
					__leave;
			}

			// a plugin might have no interfaces
			if (bHasLoad && bHasUnload && bHasInfo)
				bIsPlugin = true;

			if (!bHasLoad || !bHasMuuids || !bHasUnload)
				__leave;

			int nLength = 1; // one for MIID_LAST
			for (MUUID* p = pIds; !equalUUID(*p, miid_last); p++)
				nLength++;

			pResult = (MUUID*)mir_alloc( sizeof(MUUID)*nLength);
			if (pResult)
				memcpy(pResult, pIds, sizeof(MUUID)*nLength);
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{};
	}
	__finally
	{
		if (ptr) UnmapViewOfFile(ptr);
		if (hMap) CloseHandle(hMap);
		CloseHandle(hFile);
	};

	return pResult;
}