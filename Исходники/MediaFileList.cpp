HRESULT CMediaFileList::AddVideoFile(BSTR FilePath, IMediaFile **ppResult)
{
	HRESULT hr = CoCreateInstance(CLSID_MediaFile, NULL, 
							  CLSCTX_INPROC_SERVER, 
							  IID_IMediaFile, 
							  (void **)ppResult);

	if (FAILED(hr) || *ppResult == NULL)
		return E_POINTER;
	
	(*ppResult)->AddRef();
	(*ppResult)->put_FilePath(FilePath);
	
	CComBSTR strPosterPath;
	double dDuration = 0;
	hr = GetFileInfo(FilePath, 0, &dDuration, 0, 0, 0, 0, 0, &strPosterPath);
	
	if (SUCCEEDED(hr))
	{
		(*ppResult)->put_Duration(dDuration);
	}
	
	(*ppResult)->put_PosterFramePath(strPosterPath);
	(*ppResult)->put_StartOffset(GetCurrentVideoLength());

	if (dDuration == 0.0)
	{
		(*ppResult)->put_IsImage(VARIANT_TRUE);
		(*ppResult)->put_Duration(7);
	}
	else
		(*ppResult)->put_IsImage(VARIANT_FALSE);

//	USES_CONVERSION;
	DeleteFileW(strPosterPath);

	m_videoList.AddTail(*ppResult);
	
	(*ppResult)->AddRef();

	return S_OK;
}