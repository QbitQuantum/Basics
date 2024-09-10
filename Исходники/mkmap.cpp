IPicture* LoadPicture(_TCHAR *filename)
{
	HANDLE hFile = CreateFile(
						filename, 
						GENERIC_READ, 
						0, 
						NULL, 
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 
						NULL
					);

	if (hFile == INVALID_HANDLE_VALUE) 
		return NULL;

	DWORD   size    = GetFileSize(hFile, NULL);
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, size);

	if( NULL == hGlobal )
	{
		CloseHandle(hFile);
		return NULL;
	}

	void* pData = GlobalLock(hGlobal);

	DWORD dwBytesRead = 0;
	ReadFile(hFile, pData, size, &dwBytesRead, NULL);
	CloseHandle(hFile);

	GlobalUnlock(hGlobal);

	if( dwBytesRead != size )
	{
		GlobalFree(hGlobal);
		return NULL;
	}

	IStream* pStream = NULL;
	if( FAILED(CreateStreamOnHGlobal(hGlobal, TRUE, &pStream)) )
	{
		GlobalFree(hGlobal);
		return NULL;
	}

	IPicture *pPicture = NULL;
	OleLoadPicture(pStream, size, FALSE, IID_IPicture, (LPVOID *) &pPicture);

	SAFE_RELEASE(pStream);
	return pPicture;
}