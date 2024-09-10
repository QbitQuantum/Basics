    void D3D11Render::init_device()
    {
    
		////////////////////////Create buffer desc////////////////////////////
		RECT   rect;
		GetClientRect(getHwnd(), &rect);
		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
		bufferDesc.Width                   = rect.right - rect.left;
		bufferDesc.Height                  = rect.bottom - rect.top;
		bufferDesc.RefreshRate.Numerator   = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

		//Create swapChain Desc
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapChainDesc.BufferDesc         = bufferDesc;
		swapChainDesc.SampleDesc.Count   = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount        = 1;
		swapChainDesc.OutputWindow       = getHwnd();
		swapChainDesc.Windowed           = TRUE;
		swapChainDesc.SwapEffect         = DXGI_SWAP_EFFECT_DISCARD;


		///////////////////////////////////////////////////////////////////////////
		HRESULT hr;
		//Create the double buffer chain
		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
			NULL, NULL, NULL, NULL, D3D11_SDK_VERSION,
			&swapChainDesc, &m_pSwapChain, &m_pD3D11Device,
			NULL, &m_pD3D11DeviceContext);
		//DebugHR(hr);

		//Create back buffer, buffer also is a texture
		ID3D11Texture2D *pBackBuffer;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
		hr = m_pD3D11Device->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		pBackBuffer->Release();
		//DebugHR(hr);


		///////////////////////////Creaete Depth/Stencil Buffer/////////////////////////////////
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		depthStencilDesc.Width              =  rect.right - rect.left;
		depthStencilDesc.Height             =  rect.bottom - rect.top;
		depthStencilDesc.MipLevels          = 1;
		depthStencilDesc.ArraySize          = 1;
		depthStencilDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count   = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage              = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags     = 0;
		depthStencilDesc.MiscFlags          = 0;

		m_pD3D11Device->CreateTexture2D(&depthStencilDesc, NULL, &m_pDepthStencilBuffer);
		m_pD3D11Device->CreateDepthStencilView(m_pDepthStencilBuffer, NULL, &m_pDepthStencilView);
		m_pD3D11DeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
    
    
    	// Setup the raster description which will determine how and what polygons will be drawn.
    	D3D11_RASTERIZER_DESC rasterDesc;
    	rasterDesc.AntialiasedLineEnable = false;
    	rasterDesc.CullMode              = D3D11_CULL_BACK;
    	rasterDesc.DepthBias             = 0;
    	rasterDesc.DepthBiasClamp        = 0.0f;
    	rasterDesc.DepthClipEnable       = true;
    	rasterDesc.FillMode              = D3D11_FILL_SOLID;
    	rasterDesc.FrontCounterClockwise = false;
    	rasterDesc.MultisampleEnable     = false;
    	rasterDesc.ScissorEnable         = false;
    	rasterDesc.SlopeScaledDepthBias  = 0.0f;
    	
		// Create the rasterizer state from the description we just filled out.
    	hr = m_pD3D11Device->CreateRasterizerState(&rasterDesc, &m_pRasterState);
    	//DebugHR(hr);
    
    
    	///////////////////////////////////////////////////////////////////////////////
    
    	unsigned int numModes, i, numerator, denominator, stringLength;
    	IDXGIFactory* factory;
    	IDXGIAdapter* adapter;
    	IDXGISurface *surface;
    	DXGI_ADAPTER_DESC adapterDesc;
    
    	// Create a DirectX graphics interface factory.
    	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    	// Use the factory to create an adapter for the primary graphics interface (video card).
    	factory->EnumAdapters(0, &adapter);
    	adapter->GetDesc(&adapterDesc);
    	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
    
    	// Convert the name of the video card to a character array and store it.
    	m_videoCardInfo = std::wstring(L"Video Card: ") + adapterDesc.Description;
    
    }