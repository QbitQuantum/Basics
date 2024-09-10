bool DX11Engine::CreateSwapChain(HWND handle, UINT xSize, UINT ySize)
{
	mXsize = xSize;
	mYSize = ySize;

	IDXGIDevice* dxgiDevice = nullptr;

	HRESULT hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	if (hr != S_OK)
	{
		return false;
	}
	IDXGIAdapter* dxgiAdapter = nullptr;

	hr = dxgiDevice->GetAdapter(&dxgiAdapter);

	if (hr != S_OK)
	{
		return false;
	}

	IDXGIFactory1* dxgiFactory1 = nullptr;

	hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), (void**)&dxgiFactory1);

	if (hr != S_OK)
	{
		return false;
	}

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = xSize;
	desc.BufferDesc.Height = ySize;
	desc.BufferDesc.RefreshRate.Numerator = 0;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 2;
	desc.OutputWindow = handle;
	desc.Windowed = TRUE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = 0;

	hr = dxgiFactory1->CreateSwapChain(dxgiDevice, &desc, &m_pSwapChain);
	if (hr != S_OK)
	{
		return false;
	}

	
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory1->Release();
	return true;
}