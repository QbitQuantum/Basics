void CD3D10Renderer::Init(HWND hWnd, bool bWindowed, int width, int height)
{
	// D3D10 Device
#ifdef _DEBUG
	HR(D3D10CreateDevice(0, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_DEBUG, D3D10_SDK_VERSION, &m_pD3DDevice));
#else
	HR(D3D10CreateDevice(0, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &m_pD3DDevice));
#endif
	// Used to create a swap chain separately
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pFactory) );

	//CheckMultiSampleSupport();

	// DXGI swap chain description (the "new" presentation params!)
	ZeroMemory(&m_swapDescription, sizeof(m_swapDescription));
	m_swapDescription.BufferCount							= 1;
	m_swapDescription.BufferDesc.Width						= width;
	m_swapDescription.BufferDesc.Height						= height;
	m_swapDescription.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UNORM;
	m_swapDescription.BufferDesc.RefreshRate.Numerator		= 60;
	m_swapDescription.BufferDesc.RefreshRate.Denominator	= 1;
	m_swapDescription.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	m_swapDescription.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_swapDescription.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_swapDescription.Flags									= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	m_swapDescription.OutputWindow							= hWnd;
	m_swapDescription.SampleDesc.Count						= m_MSAA.Count;
	m_swapDescription.SampleDesc.Quality					= m_MSAA.Quality;
	m_swapDescription.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
	m_swapDescription.Windowed								= bWindowed;

	HR(m_pFactory->CreateSwapChain(m_pD3DDevice, &m_swapDescription, &m_pD3DSwapChain));

	// Create D3D10 Device and Swap Chain
	//HR(D3D10CreateDeviceAndSwapChain(
	//	0,								// Default device adapter
	//	D3D10_DRIVER_TYPE_HARDWARE,		// Device driver type
	//	NULL,							// No need for software rasterizer
	//	D3D10_CREATE_DEVICE_DEBUG,		// Debugging flags
	//	D3D10_SDK_VERSION,				// SDK Version
	//	&m_swapDescription,				// Swap chain description
	//	&m_pD3DSwapChain,				// Swap chain
	//	&m_pD3DDevice));				// Returned D3D10 Device 

	//if(!CheckMultiSampleSupport())
	//{
	//	m_MSAA.Count	= 1;
	//	m_MSAA.Quality	= 0;
	//}

	// Create Render Target View
	HR(m_pD3DSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&m_pD3DBackbuffer)));
	HR(m_pD3DDevice->CreateRenderTargetView(m_pD3DBackbuffer, 0, &m_pD3DRenderTargetView));
	m_pD3DBackbuffer->Release();

	// Create the Depth/Stencil Buffer and View
	ZeroMemory(&m_D3DDepthStencilDesc, sizeof(m_D3DDepthStencilDesc));
	m_D3DDepthStencilDesc.Width				 = width;
	m_D3DDepthStencilDesc.Height			 = height;
	m_D3DDepthStencilDesc.MipLevels			 = 1;
	m_D3DDepthStencilDesc.ArraySize			 = 1;
	m_D3DDepthStencilDesc.Format			 = DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_D3DDepthStencilDesc.SampleDesc.Count	 = m_MSAA.Count;
	m_D3DDepthStencilDesc.SampleDesc.Quality = m_MSAA.Quality;
	m_D3DDepthStencilDesc.Usage				 = D3D10_USAGE_DEFAULT;
	m_D3DDepthStencilDesc.BindFlags			 = D3D10_BIND_DEPTH_STENCIL;
	m_D3DDepthStencilDesc.CPUAccessFlags	 = 0;
	m_D3DDepthStencilDesc.MiscFlags			 = 0;

	// Bind Depth/Stencil buffer resource to pipeline
	HR(m_pD3DDevice->CreateTexture2D(&m_D3DDepthStencilDesc, 0, &m_pDepthStencilBuffer));
	HR(m_pD3DDevice->CreateDepthStencilView(m_pDepthStencilBuffer, 0, &m_pDepthStencilView));


	// Bind views to output merger stage
	m_pD3DDevice->OMSetRenderTargets(1, &m_pD3DRenderTargetView, m_pDepthStencilView);

	// Set up view port
	m_D3DViewport.TopLeftX	= 0;
	m_D3DViewport.TopLeftY	= 0;
	m_D3DViewport.Width		= width;
	m_D3DViewport.Height	= height;
	m_D3DViewport.MinDepth	= 0.0f;
	m_D3DViewport.MaxDepth	= 1.0f;

	m_pD3DDevice->RSSetViewports(1, &m_D3DViewport);


}