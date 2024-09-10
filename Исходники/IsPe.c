DWORD VerifyPE(HANDLE hFile, BOOL bExecStatus)
{
	HANDLE hMapping = NULL;					// A file mapping object.
	DWORD dwStatus = 1, dwPageFlag = 0, 	// The return status based on the file header, and 
		  dwViewFlag = 0;					// the flags to set [based on the exec status].
		  
	PVOID pFileMap = NULL;					// The start address of the mapped view of the file is stored here.
	PIMAGE_NT_HEADERS peImage;				// A structure containing nec. info on the PE image we are going to be working with.
	
	// Verify the file handle given.
	if(hFile == NULL || hFile == INVALID_HANDLE_VALUE)
	{
		return dwStatus;
	}
	
	// Are we going to execute the image?
	if(bExecStatus == EXEC_YES)
	{
		// Set the execution flags accordingly.
		dwPageFlag = PAGE_EXECUTE_READ;
		dwViewFlag = FILE_MAP_EXECUTE | FILE_MAP_READ;
		
		_ftprintf(stdout, _T("\n Execution flag [YES]\n\n"));
	}
	else
	{	
		// We just want std read access to check for an NT header.
		dwPageFlag = PAGE_READONLY;
		dwViewFlag = FILE_MAP_READ;
		
		_ftprintf(stdout, _T("\n Execution flag [NO]\n\n"));
	}

	// Create a file mapping object.
	hMapping = CreateFileMapping(hFile, NULL, dwPageFlag, 0, 0, NULL);
	
	// Check the status of the file mapping object.
	if(hMapping != NULL)
	{
		// Map the file into memory.
		pFileMap = MapViewOfFile(hMapping, dwViewFlag, 0, 0, 0);

		// Check the status of the object [NULL == invalid file mapping]
		if(pFileMap != NULL)
		{
			// Get a NT header structure.
			peImage = ImageNtHeader(pFileMap);
			
			// Did we get a valid value?
			if(peImage != NULL)
			{	
				// Check for a PE
				if(peImage->Signature == NT_HEADER)
				{
					dwStatus = 0;	// This indicates a valid PE Header.
				}
				else
				{
					dwStatus = 2;	// 	This indicates an invalid PE Header.
				}
			}
		}
		
		// Un-map the file mapping object.
		UnmapViewOfFile(pFileMap);
	}
	
	CloseHandle(hMapping);
	
	return dwStatus;
}