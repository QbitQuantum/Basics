HRESULT CKpInternetStream::WritePartial(const BYTE* pbBuffer, UINT64 uCount,
	UINT64* puWritten)
{
	EnsureInitialized();

	if(m_hFile == NULL) { if(puWritten != NULL) *puWritten = 0; return STG_E_INVALIDHANDLE; }
	if(pbBuffer == NULL) CKPIS_W_FAIL(E_POINTER);
	if(uCount > static_cast<UINT64>(DWORD_MAX)) CKPIS_W_FAIL(E_INVALIDARG);

	DWORD dwWritten = 0;
	const BOOL bRes = InternetWriteFile(m_hFile, pbBuffer, static_cast<DWORD>(
		uCount), &dwWritten);
	if(bRes == FALSE) CKPIS_W_FAIL(STG_E_WRITEFAULT);

	if(puWritten != NULL) *puWritten = dwWritten;
	return S_OK;
}