bool C_Graphics::initDirect3D(const C_Window& window) {
	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferDesc.Width  = window.getWidth();
	sd.BufferDesc.Height = window.getHeight();
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// No multisampling
	sd.SampleDesc.Count   = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount  = 1;
	sd.OutputWindow = window.getWindowHandle();
	sd.Windowed     = true;
	sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags        = 0;


	// Create the device
	UINT createDeviceFlags = 0;
	//#if defined(DEBUG) || defined(_DEBUG)  
	//	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
	//#endif
	HRESULT hr =
	D3D10CreateDeviceAndSwapChain(
			0,                 //default adapter
			d_D3DDriverType,
			0,                 // no software device
			createDeviceFlags, 
			D3D10_SDK_VERSION,
			&sd,
			&d_SwapChain,
			&d_D3DDevice);

	if(FAILED(hr)) {
		DEBUGLOG(L"D3DDevice INIT FAILED");
		DXTrace(__FILE__, (DWORD)__LINE__, hr, 0, true);
		return false;
	}

	DEBUGLOG(L"D3DDevice INIT SUCCESSFUL");

	// The remaining steps that need to be carried out for D3D creation
	// also need to be executed every time the window is resized.  So
	// just call the OnResize method here to avoid code duplication.
	onResize(window);

	D3DX10_FONT_DESC fontDesc;
	fontDesc.Height          = 14;
    fontDesc.Width           = 0;
    fontDesc.Weight          = 0;
    fontDesc.MipLevels       = 1;
    fontDesc.Italic          = false;
    fontDesc.CharSet         = DEFAULT_CHARSET;
    fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fontDesc.Quality         = DEFAULT_QUALITY;
    fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
    wcscpy_s(fontDesc.FaceName, L"Times New Roman");

	hr = D3DX10CreateFontIndirect(d_D3DDevice, &fontDesc, &d_Font);

	if(FAILED(hr)) {
		DEBUGLOG(L"Font INIT FAILED");
		return false;
	}

	DEBUGLOG(L"Font INIT SUCCESSFUL");

	// Init the defualt shader
	//d_pDefaultShader = new C_DefaultShader(d_D3DDevice);
	return true;
}