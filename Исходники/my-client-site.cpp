STDMETHODIMP MyClientSite::QueryInterface(REFIID riid, void ** ppAny) {
	LPOLESTR riidString;
	HRESULT r = StringFromIID(riid, &riidString);
	if (FAILED(r)) {
		return r;
	}
	std::wcout << L"MyClientSite::QueryInterface " << riidString << std::endl;
	CoTaskMemFree(riidString);
	
    // IID_IUnknown is the REFIID of standard interface IUnknown
    if(riid == IID_IUnknown) {
		// to avoid confusion caused by virtual inheritance
		*ppAny = (IUnknown *)(IOleClientSite *)this;
		
	} else if(riid == IID_IOleClientSite) {
		*ppAny = (IOleClientSite *)this;

    } else {
		*ppAny = NULL;
		return E_NOINTERFACE;
	}
	((IUnknown *)(*ppAny))->AddRef();
	return S_OK;
}