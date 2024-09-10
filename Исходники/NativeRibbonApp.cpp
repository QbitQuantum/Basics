HRESULT CNativeRibbonApp::SaveRibbonViewSettings(IUIRibbon* pRibbonView, const CString& fileName)
{
	CComPtr<IStream> stream;
	HRESULT hr = SHCreateStreamOnFileEx(fileName, STGM_WRITE | STGM_CREATE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, &stream);
	if (FAILED(hr))
		return hr;

	hr = pRibbonView->SaveSettingsToStream(stream);
	if (FAILED(hr))
	{
		stream->Revert();
		return hr;
	}

	hr = stream->Commit(STGC_DEFAULT);

	return hr;
}