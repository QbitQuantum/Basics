bool DX10_Renderer::InitialiseDeviceAndSwapChain()
{
	// State the Driver to be of type HAL
	m_dx10DriverType = D3D10_DRIVER_TYPE_HARDWARE;

	// Fill out the DXGI Swap Chain Description structure
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferDesc.Width = m_clientWidth;
	swapChainDesc.BufferDesc.Height = m_clientHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 59;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Multi sampling per pixel
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = m_hWnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	// Add Debug Info to the flags when run in Debug mode
	UINT createDeviceFlags = 0;
	#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
	#endif
	
	// Create the Device and Swap Chain
	VALIDATEHR(	D3D10CreateDeviceAndSwapChain(
				0,                 //default adapter
				m_dx10DriverType,
				0,                 // no software device
				createDeviceFlags,
				D3D10_SDK_VERSION,
				&swapChainDesc,
				&m_pDX10SwapChain,
				&m_pDX10Device));

	m_rasterizerDesc.CullMode = D3D10_CULL_BACK; 
	m_rasterizerDesc.FillMode = D3D10_FILL_SOLID;
	m_rasterizerDesc.FrontCounterClockwise = false;
	m_rasterizerDesc.DepthBias = 0;					
	m_rasterizerDesc.DepthBiasClamp = 0;
	m_rasterizerDesc.SlopeScaledDepthBias = 0;
	m_rasterizerDesc.DepthClipEnable = true;
	m_rasterizerDesc.ScissorEnable = false;
	m_rasterizerDesc.MultisampleEnable = false;
	m_rasterizerDesc.AntialiasedLineEnable = false;

	m_pDX10Device->CreateRasterizerState(&m_rasterizerDesc, &m_pRasterizerState);
	m_pDX10Device->RSSetState(m_pRasterizerState);

	// Create the Rasterizer description for culling clockwise when using reflection
	D3D10_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = D3D10_FILL_SOLID;
	rasterizerDesc.CullMode = D3D10_CULL_BACK;
	rasterizerDesc.FrontCounterClockwise = true;

	VALIDATEHR(m_pDX10Device->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState_Reflection));
	
	// Invoke functionality that deals with changing size of the window
	VALIDATE(onResize());

	return true;
}