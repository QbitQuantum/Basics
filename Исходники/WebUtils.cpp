void DeleteVirtualDir(std::ofstream_t& oLogStream, LPCWSTR lpcwstrAppPath)
{
	HRESULT hr;
	CComPtr<IADsContainer> spADsContainer;
	hr = ADsGetObject(L"IIS://localhost/w3svc/1/root", IID_IADsContainer, (void**)&spADsContainer);
	if(FAILED(hr))
	{
		oLogStream << _T("ADsGetObject '") << L"IIS://localhost/w3svc/1/root" << _T("' failed; result is: ") << hr << _T(".") << std::endl;
		return;
	}

	hr = spADsContainer->Delete(CComBSTR(L"IIsWebVirtualDir"), CComBSTR(lpcwstrAppPath));
	if(FAILED(hr))
	{
		oLogStream << _T("Delete IIsWebVirtualDir'") << lpcwstrAppPath << _T("' failed; result is: ") << hr << _T(".") << std::endl;
		return;
	}

	if(SUCCEEDED(hr))
	{
		oLogStream << _T("DeleteVirtualDir '") << lpcwstrAppPath << _T("' succeeded.") << std::endl;
	}
}