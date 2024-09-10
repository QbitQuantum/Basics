void D3DApplication::InitDirect3D()
{
	// Create the device.

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	HR(D3D10CreateDevice(0, m_DriverType, 0, createDeviceFlags, D3D10_SDK_VERSION, &m_pDevice));

	IDXGIFactory* pFactory;
	HR(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory)));

		// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.
	DXGI_SWAP_CHAIN_DESC swapChainDescription;

	swapChainDescription.BufferDesc.Width					= m_ClientWidth;
	swapChainDescription.BufferDesc.Height					= m_ClientHeight;
	swapChainDescription.BufferDesc.RefreshRate.Numerator	= 60;
	swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDescription.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDescription.BufferDesc.ScanlineOrdering		= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDescription.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;

	// No multisampling.
	swapChainDescription.SampleDesc.Count					= 1;
	swapChainDescription.SampleDesc.Quality					= 0;

	swapChainDescription.BufferUsage						= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.BufferCount						= 1;
	swapChainDescription.OutputWindow						= m_hMainWindow;
	swapChainDescription.Windowed							= true;
	swapChainDescription.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescription.Flags								= 0;
	
	HR(pFactory->CreateSwapChain(m_pDevice, &swapChainDescription, &m_pSwapChain));
	HR(pFactory->MakeWindowAssociation(m_hMainWindow, DXGI_MWA_NO_WINDOW_CHANGES));

	// The remaining steps that need to be carried out for d3d creation
	// also need to be executed every time the window is resized. So
	// just call the OnResize method here to avoid code duplication.

	OnResize();
}