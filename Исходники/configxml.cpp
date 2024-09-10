HRESULT CreateStreamWriter(LPCWSTR path, IXmlWriter **ppWriter, IStream **ppFileStream)
{
	HRESULT hr = S_FALSE;

	if(ppWriter != NULL && ppFileStream != NULL)
	{
		hr = CreateXmlWriter(IID_PPV_ARGS(ppWriter), NULL);
		EXIT_NOT_S_OK(hr);

		hr = SHCreateStreamOnFileW(path, STGM_WRITE | STGM_CREATE, ppFileStream);
		EXIT_NOT_S_OK(hr);

		hr = (*ppWriter)->SetOutput(*ppFileStream);
	}

NOT_S_OK:
	return hr;
}