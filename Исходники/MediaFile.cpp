int CMediaFile::LoadPicture(char* pstrPath, IPicture** ppPicture)
{
	HANDLE hFile = CreateFile(pstrPath, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;

	DWORD dwSize = GetFileSize(hFile, 0);
	if (dwSize == 0)
		return NULL;

	DWORD dwRead;
	BYTE* pBuff = new BYTE[dwSize];
	ReadFile(hFile, pBuff, dwSize, &dwRead, 0);

	if (dwRead == 0)
		return NULL;

	dwSize = dwRead;
	
	CloseHandle(hFile);

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwSize);
	void* pData = GlobalLock(hGlobal);
	memcpy(pData, pBuff, dwSize);
	GlobalUnlock(hGlobal);

	IStream* pStream = NULL;
	
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) == S_OK)
	{
		HRESULT hr;
		if ((hr = OleLoadPicture(pStream, dwSize, FALSE, IID_IPicture,
		                         (LPVOID *)ppPicture)) == S_OK)
		{
			return 1;
		}
		else
			return NULL;

		pStream->Release();
	}
	else
		return NULL;

	return NULL;
}