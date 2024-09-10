/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Zero watermark string From Mui File
//
// In order to make the procedure simple, so use the simplest method.
//
BOOL ZeroWatermarkFromMuiFile(
							  LPCTSTR pszFile,						// The MUI file name
							  PSINGLE_LIST_ENTRY pStringsHead		// Pointer to the string info
							  )
{
	BOOL				bRet			= FALSE;

	HANDLE				hFile			= NULL;
	HANDLE				hMapping		= NULL;
	PUCHAR				pView			= NULL;
	PIMAGE_NT_HEADERS	pNTHeader		= NULL;
	PIMAGE_DOS_HEADER	pDOSHeader		= NULL;
	DWORD				dwHeaderSum		= 0;
	DWORD				dwCorrectSum	= 0;
	DWORD				dwFileSize		= 0;

	__try
	{
		// Open file
		hFile	= CreateFile(pszFile, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if (INVALID_HANDLE_VALUE == hFile)
			__leave;

		dwFileSize	= GetFileSize(hFile, NULL);
		
		// Create mapping
		hMapping	= CreateFileMapping(hFile, 0, PAGE_READWRITE, 0, 0, NULL);
		if (!hMapping)
			__leave;

		// MapView of the PE file
		pView	= (PUCHAR)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (!pView)
			__leave;

		// Make sure it's a valid PE file
		pDOSHeader	= (PIMAGE_DOS_HEADER)pView;
		pNTHeader	= (PIMAGE_NT_HEADERS)(pDOSHeader->e_lfanew + (ULONG_PTR)pDOSHeader);		
		if(pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE || pNTHeader->Signature != IMAGE_NT_SIGNATURE)
			__leave;


		//
		// OK, Ready to Zero the watermark string
		//

		PRES_STRING_INFO	pStrInfo;
		PSINGLE_LIST_ENTRY	psLink		= pStringsHead->Next;

		// Enumerate all entrys
		while(psLink)
		{
			// Get the string info
			pStrInfo	= CONTAINING_RECORD(psLink, RES_STRING_INFO, link);

			// Make sure the info is correct
			if ( (pStrInfo->dwFileOffset > 0x200)
				&& (pStrInfo->dwFileOffset < dwFileSize)
				&& (pStrInfo->dwBytes > 0) )
			{
				// Real work, zero the string
				ZeroMemory((LPVOID)((ULONG_PTR)pView + pStrInfo->dwFileOffset), pStrInfo->dwBytes);
			}

			// Get next entry
			psLink	= psLink->Next;

		} // while(psLink)
			

		//
		// OK, we are try to fix the checksum of this file
		//

		// Get correct checksum of the PE file
		pNTHeader = CheckSumMappedFile((LPVOID)pView, dwFileSize, &dwHeaderSum, &dwCorrectSum);

		//TRACEF(_T("Header checksum: %08X \tCorrect checksum: %0X\n"), dwHeaderSum, dwCorrectSum);

		if (!pNTHeader)
		{
			//TRACEF(_T("Fail to re-checksum.\n"));
			__leave;
		}

		// Update the correct checksum to the file header
		pNTHeader->OptionalHeader.CheckSum = dwCorrectSum;

		//
		// All done, OK!
		//
		bRet	= TRUE;

	} // end try
	__finally
	{
		//
		// Clean up
		//

		if (pView)
			UnmapViewOfFile((LPCVOID)pView);

		if (hMapping)
		{
			if (!CloseHandle(hMapping))
				bRet	= FALSE;
		}

		if (hFile)
		{
			if (!CloseHandle(hFile))
				bRet	= FALSE;
		}

	} //__finally

	return bRet;

} // ZeroWatermarkFromMuiFile()