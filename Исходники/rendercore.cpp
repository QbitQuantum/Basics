bool RenderCore::EnumerateDisplayAdapters(std::vector<IDXGIAdapter1 *> *dxgiAdapters)
{
	IDXGIAdapter1 *pAdapter;
	IDXGIFactory1 *pFactory = nullptr;
	HRESULT hr;

	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory);
	if (FAILED(hr)) {
		return false;
	}
	
	for (UINT i = 0; pFactory->EnumAdapters1(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
		dxgiAdapters->push_back(pAdapter);
		//m_VideoAdapterList.push_back(pAdapter);
	}

	if (pFactory) {
		pFactory->Release();
	}

	return true;
};