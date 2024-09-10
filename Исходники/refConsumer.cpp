HRESULT CConsumer::ConnectToETWNameSpace(BSTR bstrNameSpace)
{
	HRESULT hr = S_OK;
	IWbemLocator *pLocator = NULL;
	hr = CoInitialize(0);
	hr = CoCreateInstance(__uuidof(WbemLocator), 
		0,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWbemLocator),
		(LPVOID*) &pLocator);

	if(FAILED(hr))
	{
		wprintf(L"CoCreateInstance failed with 0x%x\r\n", hr);
		goto cleanup;
	}

	hr = pLocator->ConnectServer(bstrNameSpace,
		NULL,NULL,NULL,0L,NULL,NULL,&g_pServices);

	if(FAILED(hr))
	{
		wprintf(L"Connect toServer Failed with 0x%x\r\n",hr);
		goto cleanup;
	}

	hr = CoSetProxyBlanket(g_pServices,
		RPC_C_AUTHN_WINNT,RPC_C_AUTHN_NONE,
		NULL,
		RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL, EOAC_NONE);

	if(FAILED(hr))
	{
		wprintf(L"CoSetProxBlanket Failed with 0x%x\r\n", hr);
		g_pServices->Release();
		g_pServices = NULL;
	}

cleanup:
	if(pLocator)
		pLocator->Release();

	return hr;
}