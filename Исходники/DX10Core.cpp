bool CDX10Core::Init( HWND hWnd )
{
	m_hWnd = hWnd;

	SetDefaultSettings();

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = m_initDesc.bufferCount;
	sd.BufferDesc.Width = m_initDesc.bufferDesc.width;
	sd.BufferDesc.Height = m_initDesc.bufferDesc.height;
	sd.BufferDesc.Format = ( DXGI_FORMAT ) m_initDesc.bufferDesc.format;
	sd.BufferDesc.RefreshRate.Numerator = m_initDesc.bufferDesc.refreshRate.numerator;
	sd.BufferDesc.RefreshRate.Denominator = m_initDesc.bufferDesc.refreshRate.denominator;
	sd.BufferDesc.ScanlineOrdering			= ( DXGI_MODE_SCANLINE_ORDER ) m_initDesc.bufferDesc.scanlineOrdering;
	sd.BufferDesc.Scaling					= ( DXGI_MODE_SCALING )m_initDesc.bufferDesc.scaling;
	sd.BufferUsage = m_initDesc.bufferUsage;
	sd.OutputWindow = m_initDesc.hOutputWindow;
	sd.SampleDesc.Count = m_initDesc.sampleDesc.count;
	sd.SampleDesc.Quality = m_initDesc.sampleDesc.quality;
	sd.Windowed = m_initDesc.bWindowed;
	sd.Flags = m_initDesc.flags;
	sd.SwapEffect = ( DXGI_SWAP_EFFECT ) m_initDesc.swapEffect;
		
	UINT createDeviceFlags	= 0;
//#if defined(DEBUG) || defined(_DEBUG)  
//	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
//#endif

	HR( D3D10CreateDeviceAndSwapChain1( 
		NULL, 
		D3D10_DRIVER_TYPE_HARDWARE, 
		NULL, 
		createDeviceFlags, 
		D3D10_FEATURE_LEVEL_10_1, 
		D3D10_1_SDK_VERSION, 
		&sd, 
		&m_pSwapChain, 
		&m_pDevice ) );

	InitRenderAndDepthStencilTargets( sd.BufferDesc.Width, sd.BufferDesc.Height );

	// Set the viewport transform.
	D3D10_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = sd.BufferDesc.Width;
	vp.Height   = sd.BufferDesc.Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_pDevice->RSSetViewports( 1, &vp );

	InitMatrices(vp.Width, vp.Height);

	InitRasterizerState();
	InitDepthStencilState();

	InitBasicEffects();

	InitializeBuffers();

	InitFont();

	m_bInitialized = true;
	return true;
}