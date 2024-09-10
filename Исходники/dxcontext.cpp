	void D3DContext::InitD3D(HWND hWnd)
	{
		m_MSAAEnabled = true;

		HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, m_DebugLayerEnabled ? D3D11_CREATE_DEVICE_DEBUG : D3D11_CREATE_DEVICE_SINGLETHREADED, NULL, NULL, D3D11_SDK_VERSION, &dev, &m_D3DFeatureLevel, &devcon);
		dev->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_MSAAQuality);
		// assert(m_MSAAQuality > 0);

		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		scd.BufferDesc.Width = m_Properties.width;
		scd.BufferDesc.Height = m_Properties.height;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		scd.SampleDesc.Count = m_MSAAEnabled ? 4 : 1;
		scd.SampleDesc.Quality = m_MSAAEnabled ? (m_MSAAQuality - 1) : 0;

		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 3;
		scd.OutputWindow = hWnd;
		scd.Windowed = !m_Properties.fullscreen;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGIDevice* dxgiDevice = 0;
		IDXGIAdapter* dxgiAdapter = 0;
		IDXGIFactory* dxgiFactory = 0;

		dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
		dxgiFactory->CreateSwapChain(dev, &scd, &swapchain);

		dxgiFactory->Release();
		dxgiAdapter->Release();
		dxgiDevice->Release();

		if (m_DebugLayerEnabled)
		{
			dev->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&m_DebugLayer));
			m_DebugLayer->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY);

			ID3D11InfoQueue* infoQueue;
			dev->QueryInterface(__uuidof(ID3D11InfoQueue), reinterpret_cast<void**>(&infoQueue));
			D3D11_MESSAGE_ID hide[] = { D3D11_MESSAGE_ID_DEVICE_DRAW_SAMPLER_NOT_SET };
			D3D11_INFO_QUEUE_FILTER filter;
			memset(&filter, 0, sizeof(filter));
			filter.DenyList.NumIDs = 1;
			filter.DenyList.pIDList = hide;
			infoQueue->AddStorageFilterEntries(&filter);
		}

		Resize();
	}