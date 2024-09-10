HRESULT
CSite::HrStreamToFile(LPSTREAM pStream, LPCTSTR fileName)
{
	HRESULT hr = S_OK;
	HGLOBAL hMem = NULL;
	LPVOID memBuf = NULL;
	DWORD memSize = 0;
	CFile file;

	if (file.Open(fileName, CFile::modeCreate | CFile::modeReadWrite, NULL) == FALSE)
		return E_FAIL;

	hr = GetHGlobalFromStream(pStream, &hMem);

	ASSERT(SUCCEEDED(hr));

	memSize = GlobalSize(hMem);
	VERIFY(memBuf = GlobalLock(hMem));

	file.Write(memBuf, memSize);

	// Reference count of hMem not checked here
	// since we can't assume how many times the
	// Stream has locked it

	GlobalUnlock(hMem); 
	file.Close();

	return hr;
}