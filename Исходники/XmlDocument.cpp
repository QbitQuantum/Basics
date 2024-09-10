HRESULT STDMETHODCALLTYPE CXMLDocument::Load(/* [in] */ LPSTREAM pStm)
{
	if (pStm == NULL)
	{
		return E_INVALIDARG;
	}

	// Load the XML from the stream
	STATSTG statstg;
	pStm->Stat(&statstg, STATFLAG_NONAME);

	ULONG cbBufSize = statstg.cbSize.LowPart;

	char *pBuffer = new char[cbBufSize];
	if (pBuffer == NULL)
	{
		return E_OUTOFMEMORY;
	}

	memset(pBuffer, 0, cbBufSize);
	pStm->Read(pBuffer, cbBufSize, NULL);

	m_spRoot.Release();
	ParseExpat(pBuffer, cbBufSize, (IXMLDocument *) this, &m_spRoot);

	delete []pBuffer;

	m_nReadyState = READYSTATE_LOADED;

	return S_OK;
}