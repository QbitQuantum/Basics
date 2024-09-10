HANDLE GetFileHandle(_In_ OUTPUT_FILE_TYPE dwOutputFileType, _In_ OUTPUT_DIRECTORY_NAME tOutputDirectoryName, _In_ OUTPUT_FILE_NAME tOutputFileName)
{
	PTCHAR tCurrentDirectory = NULL;
	HANDLE hOutputFile = INVALID_HANDLE_VALUE;
	PTCHAR tOutputFolder = pSyscrwlrOptions->tOutputFolderPath;
	LARGE_INTEGER liDistanceToMove;
	DWORD dwError = 0, dwFileSize = 0, dwRes = 0;

	tCurrentDirectory = (PTCHAR) HeapAlloc(hCrawlerHeap, HEAP_ZERO_MEMORY, sizeof (TCHAR) * MAX_PATH);	
	if (!tCurrentDirectory)
	{
		DEBUG_LOG(D_ERROR, "Error during module current dir allocation\r\nExiting now...");
		DoExit(D_ERROR);
	}

	if ((StringCchCat(tCurrentDirectory, MAX_PATH, tOutputFolder) != S_OK) 
		|| (StringCchCat(tCurrentDirectory, MAX_PATH, TEXT("\\")) != S_OK)
		|| (StringCchCat(tCurrentDirectory, MAX_PATH, OUTPUT_FOLDER_NAME) != S_OK)
		|| (StringCchCat(tCurrentDirectory, MAX_PATH, TEXT("\\")) != S_OK)
		|| (StringCchCat(tCurrentDirectory, MAX_PATH, tOutputDirectoryName) != S_OK)
		|| (StringCchCat(tCurrentDirectory, MAX_PATH, TEXT("\\")) != S_OK))
	{
		DEBUG_LOG(D_WARNING, "Unable to create output path folder.\r\nExiting now...");
		DoExit(D_ERROR);
	}

	dwRes = SHCreateDirectory(NULL, tCurrentDirectory);
	dwError = GetLastError();
	
	// User put relative path, we cannot use SHCreateDirectory
	if ((dwRes != ERROR_SUCCESS) && (dwError == ERROR_BAD_PATHNAME))
	{
		if (CreateFolderRecursively(tCurrentDirectory) != TRUE)
		{
			DEBUG_LOG(D_ERROR, "Unable to manually create directory architecture.\r\nExiting now...");
			DoExit(D_ERROR);
		}
	}
	else if ((dwRes != ERROR_SUCCESS) && (dwError != ERROR_ALREADY_EXISTS))
	{
		DEBUG_LOG(D_ERROR, "Unable to create output directory. Last error: %d.\r\nExiting now...", dwError);
		DoExit(D_ERROR);
	}

	if (StringCchCat(tCurrentDirectory, MAX_PATH, tOutputFileName)  != S_OK)
		goto unableToBuildOutputFilename;

	switch (dwOutputFileType)
	{
	case OUTPUT_FILE_XML:
		if (StringCchCat(tCurrentDirectory, MAX_PATH, TEXT(".xml")) != S_OK)
			goto unableToBuildOutputFilename;
		break;
	case OUTPUT_FILE_CSV:
		if (StringCchCat(tCurrentDirectory, MAX_PATH, TEXT(".csv")) != S_OK)
			goto unableToBuildOutputFilename;
		break;
	default:
		DEBUG_LOG(D_ERROR, "File type unknown.\r\nExiting now...");
		DoExit(D_ERROR);
		break;
	}

	hOutputFile = CreateFile_s(tCurrentDirectory, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOutputFile == INVALID_HANDLE_VALUE)
	{
		DEBUG_LOG(D_WARNING, "Unable to create output file for format: %ws.\r\nExiting now...", tOutputFileName);
		DoExit(D_ERROR);
	}

	dwFileSize = GetFileSize(hOutputFile, NULL);
	if (dwFileSize == INVALID_FILE_SIZE)
	{
		DEBUG_LOG(D_ERROR, "Error during reading FileSize for %ws.\r\nExiting now...", tCurrentDirectory);
		DoExit(D_ERROR);
	}
	else if (dwFileSize == 0)
	{
		goto ReturnHandle;
	}

	ZeroMemory(&liDistanceToMove, sizeof(LARGE_INTEGER));
	if (SetFilePointerEx(hOutputFile, liDistanceToMove, NULL, FILE_END) == INVALID_SET_FILE_POINTER)
	{
		dwError = GetLastError();
		DEBUG_LOG(D_WARNING, "Unable to move file pointer to the end of the file for: %ws (err: %d).\r\nExiting now...", tOutputFileName, dwError);
		DoExit(D_ERROR);
	}

ReturnHandle:
	HeapFree(hCrawlerHeap, NULL, tCurrentDirectory);
	return hOutputFile;

unableToBuildOutputFilename:
	DEBUG_LOG(D_ERROR, "Unable to create out filename.\r\nExiting now...");
	DoExit(D_ERROR);
	return NULL;
}