    bool BasicRenderer::initD3D()
    {
	    unsigned int createDeviceFlags = 0;

    #	if defined(DEBUG) || defined(_DEBUG)
	    createDeviceFlags  |= D3D11_CREATE_DEVICE_DEBUG;
    #	endif

	    D3D_FEATURE_LEVEL featureLevel;
	    HRESULT hr = D3D11CreateDevice(
		    0,
		    m_driverType,
		    0,
		    createDeviceFlags,
		    0, 0,
		    D3D11_SDK_VERSION,
		    &m_device,
		    &featureLevel,
		    &m_context);

	    if (FAILED(hr))
	    {
		    return false;
	    }

	    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	    {
		    return false;
	    }

	    m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMSAAQuality);
	    assert(m_4xMSAAQuality > 0);

	    DXGI_SWAP_CHAIN_DESC swapChainDesc;
	    swapChainDesc.BufferDesc.Width = m_width;
	    swapChainDesc.BufferDesc.Height = m_height;
	    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	    if( m_enable4xMSAA )
	    {
		    swapChainDesc.SampleDesc.Count   = 4;
		    swapChainDesc.SampleDesc.Quality = m_4xMSAAQuality-1;
	    }
	    else
	    {
		    swapChainDesc.SampleDesc.Count   = 1;
		    swapChainDesc.SampleDesc.Quality = 0;
	    }

	    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	    swapChainDesc.BufferCount = 1;
	    swapChainDesc.OutputWindow = reinterpret_cast<HWND>(m_windowHandle);
	    swapChainDesc.Windowed = true;
	    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	    IDXGIDevice* dxgiDevice = 0;
	    m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	    IDXGIDevice* dxgiAdapter = 0;
	    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	    IDXGIFactory* dxgiFactory = 0;
	    dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	    dxgiFactory->CreateSwapChain(m_device, &swapChainDesc, &m_swapChain);

	    releaseCOM(dxgiDevice);
	    releaseCOM(dxgiAdapter);
	    releaseCOM(dxgiFactory);

	    onResize();

	    return true;
    }