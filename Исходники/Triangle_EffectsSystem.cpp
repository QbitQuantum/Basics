HRESULT InitD3D( HWND hWnd )
{
	// Setup a DXGI swap chain descriptor
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );

	sd.BufferCount = 1; // number of buffer
	sd.BufferDesc.Width = 600; // buffer width, can we set it to the screen width?
	sd.BufferDesc.Height = 600; // buffer height, can we set it to the screen height?
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // buffer format, 32 bit color with alpha(RGBA)
	sd.BufferDesc.RefreshRate.Numerator = 60; // refresh rate?
	sd.BufferDesc.RefreshRate.Denominator = 1; // WHAT'S THIS?
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // use buffer as render target
	sd.OutputWindow = hWnd; // output window handle
	sd.SampleDesc.Count = 1; // WHAT'S THIS?
	sd.SampleDesc.Quality = 0; // WHAT'S THIS?
	sd.Windowed = TRUE; // full-screen mode

	HRESULT hr;
	UINT flags = D3D10_CREATE_DEVICE_BGRA_SUPPORT;

#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3D10_CREATE_DEVICE_DEBUG;
#endif 

	// Create device and swap chain
	if (FAILED (hr = D3D10CreateDeviceAndSwapChain( NULL, 
	    D3D10_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		D3D10_SDK_VERSION,
		&sd, 
		&g_pSwapChain,
		&g_pd3dDevice)))
	{
		return hr;
	}

	// Create render target and bind the back-buffer
	ID3D10Texture2D* pBackBuffer;

	// Get a pointer to the back buffer
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID* )&pBackBuffer);
	if (FAILED(hr))
		return hr;

	// Create a render-target view
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);

	// Bind the view
	g_pd3dDevice->OMSetRenderTargets(1, &g_pRenderTargetView, NULL); // WHAT'S OM here mean?

	// Setup the viewport
	D3D10_VIEWPORT vp;
	vp.Width = 640; // this should be similar with the back-buffer width, global it!
	vp.Height = 480;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pd3dDevice->RSSetViewports(1, &vp);

	InitVertexBuffer();
	InitEffects();
		                       
	return S_OK;
}