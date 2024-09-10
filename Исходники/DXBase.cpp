bool DXBase::Initialize(HWND hwnd, int width, int height, bool fullscreen, bool vsync_enabled)
{
	// Store the vsync setting.
	m_vsync_enabled = vsync_enabled;

	// Describe our Buffer
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = width;
	bufferDesc.Height = height;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Set the refresh rate of the back buffer.
	if (m_vsync_enabled)
	{
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
	}
	else
	{
		bufferDesc.RefreshRate.Numerator = 0;
		bufferDesc.RefreshRate.Denominator = 1;
	}

	// Describe our SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Set to full screen or windowed mode.
	if (fullscreen)
	{
		swapChainDesc.Windowed = FALSE;
	}
	else
	{
		swapChainDesc.Windowed = TRUE;
	}

	//D3D_FEATURE_LEVEL featurelevel = D3D_FEATURE_LEVEL_11_0;
	// Create our SwapChain
	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);

	// Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	// Create our Render Target
	m_device->CreateRenderTargetView(BackBuffer, NULL, &m_renderTargetView);
	BackBuffer->Release();

	// Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthBufferDesc;

	depthBufferDesc.Width = width;
	depthBufferDesc.Height = height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the Depth/Stencil View
	m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);

	// Create disabled depth stencil state for 2d objects
	CreateDisabledDepthStencilState();

	// Create default depth stencil state
	CreateDepthStencilState();

	// Set the depth stencil state.
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	// Initialize the depth stencil view.
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Initialize the depth stencil view.
	m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);

	// Set our Render Target
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	// Create the Viewport
	//D3D11_VIEWPORT viewport;
	//ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	
	m_viewport.Width = (float)width;
	m_viewport.Height = (float)height;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;
	

	// Set the Viewport
	m_deviceContext->RSSetViewports(1, &m_viewport);

	// Create default raster state for opaque objects
	CreateRasterState();

	// Create no cull raster state to render primitives behind alpha
	CreateNoCullRasterState();

	CreateEnabledAlphaBlendingState();

	CreateDisabledAlphaBlendingState();

	TurnOnDefaultCulling();

	// Set global matrices
	XMMATRIX world = XMMatrixIdentity();
	XMStoreFloat4x4(&m_world, world);
	
	XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, (float)width / (float)height, 0.1f, 1000.0f);
	XMStoreFloat4x4(&m_projection, projection);

	XMMATRIX ortho = XMMatrixOrthographicLH((float)width, (float)height, 0.1f, 1000.0f);
	XMStoreFloat4x4(&m_ortho, ortho);

	return true;
}