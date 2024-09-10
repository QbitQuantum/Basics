static 
HRESULT EnableActiveDesktop(bool enable)
{
	CoInitialize(NULL);
	CComQIPtr<IActiveDesktop, &IID_IActiveDesktop>	pIActiveDesktop;
	
	HRESULT		hr;

	hr = pIActiveDesktop.CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER);
	if (!SUCCEEDED(hr))
		return hr;

	COMPONENTSOPT	opt;

	opt.dwSize = sizeof(opt);
	opt.fActiveDesktop = opt.fEnableComponents = enable;
    hr = pIActiveDesktop->SetDesktopItemOptions(&opt, 0);
    if (!SUCCEEDED(hr))
	{
		CoUninitialize();
		return hr;
	}

	hr = pIActiveDesktop->ApplyChanges(AD_APPLY_REFRESH);
	CoUninitialize();
	return hr;
}