bool D3D10App::initAPI(const DXGI_FORMAT backBufferFmt, const DXGI_FORMAT depthBufferFmt, const int samples, const uint flags){
	backBufferFormat = backBufferFmt;
	depthBufferFormat = depthBufferFmt;
	msaaSamples = samples;

//	if (screen >= GetSystemMetrics(SM_CMONITORS)) screen = 0;

	IDXGIFactory *dxgiFactory;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void **) &dxgiFactory))){
		ErrorMsg("Couldn't create DXGIFactory");
		return false;
	}

	IDXGIAdapter *dxgiAdapter;
	if (dxgiFactory->EnumAdapters(0, &dxgiAdapter) == DXGI_ERROR_NOT_FOUND){
		ErrorMsg("No adapters found");
		return false;
	}

//	DXGI_ADAPTER_DESC adapterDesc;
//	dxgiAdapter->GetDesc(&adapterDesc);

	IDXGIOutput *dxgiOutput;
	if (dxgiAdapter->EnumOutputs(0, &dxgiOutput) == DXGI_ERROR_NOT_FOUND){
		ErrorMsg("No outputs found");
		return false;
	}

	DXGI_OUTPUT_DESC oDesc;
	dxgiOutput->GetDesc(&oDesc);


	// Find a suitable fullscreen format
	int targetHz = 85;
	DXGI_RATIONAL fullScreenRefresh;
	int fsRefresh = 60;
	fullScreenRefresh.Numerator = fsRefresh;
	fullScreenRefresh.Denominator = 1;
	char str[128];

	uint nModes = 0;
	dxgiOutput->GetDisplayModeList(backBufferFormat, 0, &nModes, NULL);
	DXGI_MODE_DESC *modes = new DXGI_MODE_DESC[nModes];
	dxgiOutput->GetDisplayModeList(backBufferFormat, 0, &nModes, modes);

	resolution->clear();
	for (uint i = 0; i < nModes; i++){
		if (modes[i].Width >= 640 && modes[i].Height >= 480){
			sprintf(str, "%dx%d", modes[i].Width, modes[i].Height);
			int index = resolution->addItemUnique(str);

			if (int(modes[i].Width) == fullscreenWidth && int(modes[i].Height) == fullscreenHeight){
				int refresh = modes[i].RefreshRate.Numerator / modes[i].RefreshRate.Denominator;
				if (abs(refresh - targetHz) < abs(fsRefresh - targetHz)){
					fsRefresh = refresh;
					fullScreenRefresh = modes[i].RefreshRate;
				}
				resolution->selectItem(index);
			}
		}
	}
	delete modes;

	sprintf(str, "%s (%dx%d)", getTitle(), width, height);

	DWORD wndFlags = 0;
	int x, y, w, h;
	if (fullscreen){
		wndFlags |= WS_POPUP;
		x = y = 0;
		w = width;
		h = height;
	} else {
		wndFlags |= WS_OVERLAPPEDWINDOW;

		RECT wRect;
		wRect.left = 0;
		wRect.right = width;
		wRect.top = 0;
		wRect.bottom = height;
		AdjustWindowRect(&wRect, wndFlags, FALSE);

		MONITORINFO monInfo;
		monInfo.cbSize = sizeof(monInfo);
		GetMonitorInfo(oDesc.Monitor, &monInfo);

		w = min(wRect.right  - wRect.left, monInfo.rcWork.right  - monInfo.rcWork.left);
		h = min(wRect.bottom - wRect.top,  monInfo.rcWork.bottom - monInfo.rcWork.top);
		x = (monInfo.rcWork.left + monInfo.rcWork.right  - w) / 2;
		y = (monInfo.rcWork.top  + monInfo.rcWork.bottom - h) / 2;
	}


	hwnd = CreateWindow("Humus", str, wndFlags, x, y, w, h, HWND_DESKTOP, NULL, hInstance, NULL);

	RECT rect;
	GetClientRect(hwnd, &rect);

	// Create device and swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferDesc.Width  = rect.right;
	sd.BufferDesc.Height = rect.bottom;
	sd.BufferDesc.Format = backBufferFormat;
	sd.BufferDesc.RefreshRate = fullScreenRefresh;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = (BOOL) (!fullscreen);
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	DWORD deviceFlags = D3D10_CREATE_DEVICE_SINGLETHREADED;
#ifdef _DEBUG
    deviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	if (FAILED(D3D10CreateDevice(dxgiAdapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, deviceFlags, D3D10_SDK_VERSION, &device))){
		ErrorMsg("Couldn't create D3D10 device");
		return false;
	}

	while (msaaSamples > 0){
		UINT nQuality;
		if (SUCCEEDED(device->CheckMultisampleQualityLevels(backBufferFormat, msaaSamples, &nQuality)) && nQuality > 0){
			if ((flags & NO_SETTING_CHANGE) == 0) antiAliasSamples = msaaSamples;
			break;
		} else {
			msaaSamples -= 2;
		}
	}
	sd.SampleDesc.Count = msaaSamples;
	sd.SampleDesc.Quality = 0;

	if (FAILED(dxgiFactory->CreateSwapChain(device, &sd, &swapChain))){
		ErrorMsg("Couldn't create swapchain");
		return false;
	}

	// We'll handle Alt-Enter ourselves thank you very much ...
	dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);

	dxgiOutput->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();


	if (!createBuffers()) return false;


	if (fullscreen){
		captureMouse(!configDialog->isVisible());
	}

	renderer = new Direct3D10Renderer(device);
	((Direct3D10Renderer *) renderer)->setFrameBuffer(backBufferRTV, depthBufferDSV);

	antiAlias->selectItem(antiAliasSamples / 2);

	linearClamp = renderer->addSamplerState(LINEAR, CLAMP, CLAMP, CLAMP);
	defaultFont = renderer->addFont("../Textures/Fonts/Future.dds", "../Textures/Fonts/Future.font", linearClamp);
	blendSrcAlpha = renderer->addBlendState(SRC_ALPHA, ONE_MINUS_SRC_ALPHA);
	noDepthTest  = renderer->addDepthState(false, false);
	noDepthWrite = renderer->addDepthState(true,  false);
	cullNone  = renderer->addRasterizerState(CULL_NONE);
	cullBack  = renderer->addRasterizerState(CULL_BACK);
	cullFront = renderer->addRasterizerState(CULL_FRONT);

	return true;
}