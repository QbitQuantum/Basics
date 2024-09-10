//
// FUNCTION: GraphicsDeviceInterface::Initialize()
//
// PURPOSE: Initializes Direct3D
// 
bool GraphicsDeviceInterface::Initialize(HWND hWnd, WindowSize* wind) {
	HRESULT hResult;

	// Clear the struct
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// Set the swap chain values
	scd.BufferCount = 1;								// one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// use 32 bit color
	scd.BufferDesc.Width = wind->getWidth();			// set width using windowSize object
	scd.BufferDesc.Height = wind->getHeight();			// set height using windowSize object
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// swap chain is output
	scd.OutputWindow = hWnd;							// window to render into
	scd.SampleDesc.Count = 4;							// use 4 multisamples for antialiasing
	scd.Windowed = wind->getWindowed();					// Sets windowed mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// Allow full-screen switching


	// Create the device, context, and swap chain
	hResult = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL, //D3D_FEATURE_LEVEL_10_0,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_Swapchain,
		&m_Device,
		NULL,
		&m_Context);

	if (hResult != S_OK)
	{
		return FALSE;
	}

	// Retrieves the IDXGIFactory that created "m_Device"
	IDXGIDevice *pDXGIDevice;
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
	IDXGIAdapter *pDXGIAdapter;
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);
	IDXGIFactory *pDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pDXGIFactory);

	// Disables the use of Alt-Enter to switch between fullscreen/windowed
	pDXGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
	
	// Resized the target (window or screen resolution) and back buffers
	m_Swapchain->ResizeTarget(&scd.BufferDesc);
	m_Swapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, scd.Flags);

	// Get the back buffer address
	ID3D11Texture1D *pBackBuffer;
	m_Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// Use the back buffer address to create a render target
	m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_BackBuffer);
	pBackBuffer->Release();

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;

	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	depthBufferDesc.Width = wind->getWidth();
	depthBufferDesc.Height = wind->getHeight();
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 4;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	m_Device->CreateTexture2D(&depthBufferDesc, NULL, &m_DepthStencilBuffer);

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);

	m_Context->OMSetDepthStencilState(m_DepthStencilState, 1);
	
	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	m_Device->CreateDepthStencilView(m_DepthStencilBuffer, NULL, &m_DepthStencilView);

	// set the render target as the back buffer
	m_Context->OMSetRenderTargets(1, &m_BackBuffer, m_DepthStencilView);

	// Set the viewport using windowSize object
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.Width = (float)wind->getWidth();
	viewport.Height = (float)wind->getHeight();

	m_Context->RSSetViewports(1, &viewport);

	// Setup the projection matrix.
	float fieldOfView = (float)D3DX_PI / 4.0f;
	float screenAspect = (float)wind->getWidth() / (float)wind->getHeight();

	// TODO: Make constants for screen depth and screen near.
	// Create the projection matrix for 3D rendering.
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, fieldOfView, screenAspect, 0.1f, 1000.0f);

	InitPipeline();
	InitGraphics();


	return TRUE;
}