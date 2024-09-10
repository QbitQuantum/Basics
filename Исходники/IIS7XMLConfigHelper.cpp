HRESULT CIIS7XMLConfigHelper::GetApplicationHostConfigDocument(IXMLDOMDocument** pDoc)
{
	// we need a DOM
	CComPtr<IXMLDOMDocument> pDOM;
	HRESULT hr = pDOM.CoCreateInstance(L"MSXML.DOMDocument");
	if (hr != S_OK)
		return hr;

	// get the path to the config file
	CAtlString sApplicationHostPath;
	GetApplicationHostConfigPath(sApplicationHostPath);

	// ask the XML DOM to load the config file
	VARIANT_BOOL bSuccess;
	hr = pDOM->load(CComVariant((const TCHAR*) sApplicationHostPath), &bSuccess);
	if (hr != S_OK)
		return hr;
	
	if (bSuccess != VARIANT_TRUE)
		return E_FAIL;

	// return the pointer
	return pDOM.CopyTo(pDoc);	
}