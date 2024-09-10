STDMETHODIMP CProviderInfo::get_Provider(ProviderRole type, BSTR *pProgID)
{
	if(!pProgID) return E_POINTER;
	HRESULT hr =S_OK;

	CLSID clType= GUID_NULL;

	switch(type)
	{
	case enStructureProvider:
		clType = CLSID_ATFStructureProvider;
		break;
	case enStructureInfo:
		clType = CLSID_ATFStructureInfo;
		break;
	case enPriceProvider: 
		clType = CLSID_ATFPriceProvider;
		break;
	case enPriceInfo:
		clType = CLSID_ATFPriceInfo;
		break;
	case enPriceInfoWithNotify:
		clType = CLSID_ATFPriceInfoWithNotify;
		break;
	}
	BSTR bsData; 
	hr = ProgIDFromCLSID(clType, &bsData);

	if(SUCCEEDED(hr))
		*pProgID = ::SysAllocString(bsData);
	else
		*pProgID = ::SysAllocString(L"");

	return hr;

}