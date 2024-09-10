	bool UGraphicsDevice::Init(int inClientHeight, int inClientWidth)
	{
		LOG(LogGraphicsDevice, Log, "Graphics Device initialization begin...\n");

		if (!XMVerifyCPUSupport())
		{
			LOG(LogGraphicsDevice, Error, "Init() Failed to verify DirectX Math library support\n");
			return false;
		}

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = inClientWidth;
		swapChainDesc.BufferDesc.Height = inClientHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = UGameWindow::GetHWnd();
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Windowed = true;

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		D3D_FEATURE_LEVEL featureLevel;
		HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
												   createDeviceFlags, featureLevels, _countof(featureLevels),
												   D3D11_SDK_VERSION, &swapChainDesc, &mD3dSwapChain, &mD3dDevice,
												   &featureLevel, &mD3dDeviceCtx);

		if (hr == E_INVALIDARG)
		{
			hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
											   nullptr, createDeviceFlags, &featureLevels[1], _countof(featureLevels) - 1,
											   D3D11_SDK_VERSION, &swapChainDesc, &mD3dSwapChain, &mD3dDevice, &featureLevel,
											   &mD3dDeviceCtx);
		}

		if (FAILED(hr))
		{
			LOG(LogGraphicsDevice, Error, "Init() Failed to create graphics device and swap chain\n");
			return false;
		}

		if (!CreateBackBuffer())
		{
			LOG(LogGraphicsDevice, Error, "Init() Failed to create the application back buffer render target view\n");
			return false;
		}

		SetViewport(inClientHeight, inClientWidth);

		LOG(LogGraphicsDevice, Log, "Graphics Device initialization successful\n");
		return true;
	}