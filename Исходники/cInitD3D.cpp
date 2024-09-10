// ´ÙÀÌ·ºÆ® °´Ã¼ ÃÊ±âÈ­
// - °¢Á¾±â´ÉÀ» Áö¿øÇÏ´Â°¡ Ã¼Å©ÇÏ°í(´ÙÁß »ùÇÃ¸µ µî), ½º¿ÒÃ¼ÀÎ, ÄÄ °´Ã¼ µîÀ» »ý¼º, Á¦°ÅÇÑ´Ù.
bool cInitD3D::InitDirect3D()
{
	// µð¹ÙÀÌ½º, µð¹ÙÀÌ½º ÄÁÅØ½ºÆ® »ý¼º
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,                 // default adapter
		md3dDriverType,
		0,                 // no software device
		createDeviceFlags,
		0, 0,              // default feature level array
		D3D11_SDK_VERSION,
		&md3dDevice,
		&featureLevel,
		&md3dImmediateContext);

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	// ¹é¹öÆÛ¿¡ 4X MSAA Ç°Áú Áö¿øÀ» È®ÀÎ
	HR(md3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality));
	assert(m4xMsaaQuality > 0);

	// ½º¿ÒÃ¼ÀÎ »ý¼º
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = mClientWidth;
	sd.BufferDesc.Height = mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ´ÙÁß »ùÇÃ¸µ À¯¹« (Use 4X MSAA?) 
	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	// ¹öÆÛ »ý¼º
	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount  = 1;
	sd.OutputWindow = mhMainWnd;
	sd.Windowed     = true;
	sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags		= 0;

	// µð¹ÙÀÌ½º »ý¼º
	IDXGIDevice* dxgiDevice = 0;
	HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// ½º¿ÒÃ¼ÀÎ »ý¼º ¹× È®ÀÎ
	HR(dxgiFactory->CreateSwapChain(md3dDevice, &sd, &mSwapChain));

	// ÄÄ °´Ã¼ »èÁ¦
	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	// Ã¢ Å©±â Á¶Àý (ÄÚµå Áßº¹ ÇÇÇÏ±â À§ÇØ »ç¿ë)
	OnResize();

	return true;
}