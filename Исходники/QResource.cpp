BOOL WINAPI AddToEFSFile(
	IN EFSHANDLEFORWRITE hEFSFile,
	IN LPCSTR lpszFileName,
	IN DWORD dwComponentID,
	IN DWORD dwFileID,
	IN DWORD dwData,
	IN DWORD dwFlags
)
{
	assert(hEFSFile);
	assert(lpszFileName);

	// Check for unsupported flags. Right now all flags are unsupported.
	if (dwFlags)
		return FALSE;

	// Extract the EFS archive structure
	EFSFILEHANDLEFORWRITE *pEFSFile = (EFSFILEHANDLEFORWRITE *)hEFSFile;

	assert(pEFSFile->hFile != INVALID_HANDLE_VALUE);
	assert(pEFSFile->pDirectory);

	// If we've exceeded the number of entries in the directory table, we need to allocate a bigger one
	if (pEFSFile->nNumDirectoryEntries >= pEFSFile->nMaxDirectoryEntries)
	{
		DWORD nNumDirEntriesToAlloc = pEFSFile->nMaxDirectoryEntries * 2,
			nNumBytesToAlloc = nNumDirEntriesToAlloc * sizeof(EFSDIRECTORYENTRY);
		EFSDIRECTORYENTRY *pNewDirectory = (EFSDIRECTORYENTRY *)malloc(nNumBytesToAlloc);

		if (!pNewDirectory)
			return FALSE;

		// Copy the entrees over
		DWORD nNumBytesToCopy = pEFSFile->nMaxDirectoryEntries * sizeof(EFSDIRECTORYENTRY);
		memcpy(pNewDirectory, pEFSFile->pDirectory, nNumBytesToCopy);
		ZeroMemory((LPBYTE)pNewDirectory + nNumBytesToCopy, nNumBytesToAlloc - nNumBytesToCopy);

		// Replace the old directory entirely
		free(pEFSFile->pDirectory);

		pEFSFile->pDirectory = pNewDirectory;
		pEFSFile->nMaxDirectoryEntries = nNumDirEntriesToAlloc;
	}

	// Open the file to add to the EFS archive
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	// Add the file using AddUncompressedToEFSFile
	BOOL bRetVal = FALSE;
	// AddUncompressedToEFSFile may trash the directory even if the addition fails, so we need to make sure we always write it again (mark the archive as modified)
	pEFSFile->bModified = TRUE;

	EFSDIRECTORYENTRY *pDirEntry = &pEFSFile->pDirectory[pEFSFile->nNumDirectoryEntries];
	if (AddUncompressedToEFSFile(pEFSFile, hFile, pDirEntry))
	{
		// Success. Fill in the file data not filled in by AddUncompressedToEFSFile.
		pDirEntry->dwComponentID = dwComponentID;
		pDirEntry->dwFileID = dwFileID;
		pDirEntry->dwData = dwData;
		pDirEntry->dwFlags = 0;

		// Update the archive state
		pEFSFile->dwInsertPoint += pDirEntry->dwSize;
		pEFSFile->nNumDirectoryEntries++;

		bRetVal = TRUE;
	}

	CloseHandle(hFile);

	return bRetVal;
}