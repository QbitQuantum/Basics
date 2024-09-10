void DirectXController::Initialize( void )
{
	WindowController::Get()->Initialize();
	WindowController::Get()->OpenWindow();

	driverType = D3D_DRIVER_TYPE_HARDWARE;
	enable4xMsaa = false;
	msaa4xQuality = 0;
	device.dx = nullptr;
	deviceContext.dx = nullptr;
	swapChain = nullptr;
	depthStencilBuffer = nullptr;
	renderTargetView = nullptr;
	depthStencilView = nullptr;
	ZeroMemory( &viewport, sizeof(D3D11_VIEWPORT) );

	UINT createDeviceFlags = 0;
#if defined(_DEBUG) || defined(DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL requiredFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL featureLevel;
	
	HRESULT hResult = D3D11CreateDevice(
		NULL,					// Adapter
		driverType,				// Driver Type
		NULL,					// Software
		createDeviceFlags,		// Flags
		&requiredFeatureLevel,	// Feature levels
		1,						// num Feature levels
		D3D11_SDK_VERSION,		// SDK Version
		&device.dx,				// Device
		&featureLevel,			// Feature Level
		&deviceContext.dx );	// Device Context


	// Handle any device creation or DirectX version errors
	if( FAILED(hResult) )
	{
		MessageBox(NULL, L"D3D11CreateDevice Failed", NULL, NULL);
		//return false;
	}

	if( featureLevel != requiredFeatureLevel )
	{
		MessageBox(NULL, L"Direct3D Feature Level 11 unsupported", NULL, NULL);
		//return false;
	}

	// Check for 4X MSAA quality support
	HR(device.dx->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		4,
		&msaa4xQuality));
	//assert( msaa4xQuality > 0 ); // Potential problem if quality is 0
	
	// set up swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc) );
	swapChainDesc.BufferCount							= 1;
	swapChainDesc.BufferDesc.Width						= WindowController::Get()->GetWidth();//windowWidth;
	swapChainDesc.BufferDesc.Height						= WindowController::Get()->GetHeight();//windowHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator		= 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator	= 1;
	swapChainDesc.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow							= Win32Controller::Get()->GetHWnd();//hMainWnd;
	swapChainDesc.Windowed								= true;
	swapChainDesc.Flags									= 0;

	if( enable4xMsaa )
	{ // Set up 4x MSAA
		swapChainDesc.SampleDesc.Count   = 4;
		swapChainDesc.SampleDesc.Quality = msaa4xQuality - 1;
	}
	else
	{ // No MSAA
		swapChainDesc.SampleDesc.Count   = 1;
		swapChainDesc.SampleDesc.Quality = 0;
	}

	// To correctly create the swap chain, we must use the IDXGIFactory that
	// was used to create the device.
	IDXGIDevice*	dxgiDevice	= 0;
	IDXGIAdapter*	dxgiAdapter = 0;
	IDXGIFactory*	dxgiFactory = 0;
	HR(device.dx->QueryInterface(	__uuidof(IDXGIDevice),	(void**)&dxgiDevice));
	HR(dxgiDevice->GetParent(	__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));
	HR(dxgiAdapter->GetParent(	__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// Finally make the swap chain and release the DXGI stuff
	HR(dxgiFactory->CreateSwapChain(device.dx, &swapChainDesc, &swapChain));
	ReleaseCOMobjMacro(dxgiDevice);
	ReleaseCOMobjMacro(dxgiAdapter);
	ReleaseCOMobjMacro(dxgiFactory);

	// The remaining steps also need to happen each time the window
	// is resized, so just run the OnResize method
	Resize();
}