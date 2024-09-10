	// search in IMAGE_IMPORT_DESCRIPTOR for the special module
	BOOL ReplaceIATEntryInImageImportTable(HANDLE hBaseAddress, LPCSTR lpszDllName, LPVOID pfnCurrent, LPVOID pfnNew)
	{
		try
		{
			DWORD dwSize = 0;
			PIMAGE_SECTION_HEADER pFoundHeader = NULL;
			PIMAGE_IMPORT_DESCRIPTOR pImgImportDescriptor
				= (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToDataEx( hBaseAddress
				, TRUE
				, IMAGE_DIRECTORY_ENTRY_IMPORT
				, &dwSize
				, &pFoundHeader
				);
			if( pImgImportDescriptor == NULL ){ return FALSE; }
			while (pImgImportDescriptor->Name)
			{
				if ( lstrcmpiA((CHAR*)((PBYTE)hBaseAddress+pImgImportDescriptor->Name), lpszDllName) == 0 )
				{
					break; // found
				}
				++pImgImportDescriptor;
			}
			if( !pImgImportDescriptor->Name )
				return ReplaceIATEntryInDelayImageImportTable( hBaseAddress, lpszDllName, pfnCurrent, pfnNew);

			// retrieve IAT
			PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)(((LPBYTE)hBaseAddress) + pImgImportDescriptor->FirstThunk);

			// enumerate functions in the IAT
			while(pThunk->u1.Function)
			{
				PDWORD lpAddr = (PDWORD)&(pThunk->u1.Function);
				if(*lpAddr == (DWORD)pfnCurrent)
				{
					// modify the address
					if(::WriteProcessMemory(::GetCurrentProcess(), lpAddr, &pfnNew, sizeof(DWORD), NULL))
						return TRUE;
					else
						return FALSE;
				} 
				pThunk++;
			}
		}
		catch(...)
		{

		}
		return FALSE;
	}