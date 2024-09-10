bool CDuplicateOutputDx11::GetSpecificAdapter(int idAdapter, IDXGIAdapter** pAdapter)
{
	HRESULT err = S_OK;

	if (!pAdapter)
	{
		return false;
	}

	REFIID iidVal = __uuidof(IDXGIFactory1);
	UINT adapterID = 0;	// adapter index
	IDXGIFactory1* pFactory = NULL;
	if (FAILED(err = CreateDXGIFactory1(iidVal, (void**)&pFactory)))
	{
		return 	false;
	}
	UINT i = 0;
	UINT adapterDeviceID = idAdapter;		// if device id equal zero, use the first device

	DXGI_ADAPTER_DESC dxgiDesc;
	IDXGIAdapter1 *giAdapter = NULL;
	if (pFactory->EnumAdapters1(i, &giAdapter) != S_OK)
	{
		return false;
	}
	if (pFactory)pFactory->Release();
	*pAdapter = giAdapter;
	return true;
}