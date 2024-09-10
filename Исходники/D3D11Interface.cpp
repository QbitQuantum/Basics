	D3D11Interface::D3D11Interface(HWND hwnd, bool fullscreen, unsigned int width, unsigned int height, bool vsyncEnabled)
	{
		
		IDXGIFactory* factory = 0;
		IDXGIAdapter* adapter = 0;
		IDXGIOutput* adapterOutput = 0;
		DXGI_MODE_DESC* displayModeList = 0;
		DXGI_ADAPTER_DESC adapterDesc;
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		D3D_FEATURE_LEVEL featureLevel;
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC dsViewDesc;
		unsigned int numModes;
		unsigned int numerator = 0, denominator = 1;

		//get the monitor refresh rate to prevent performance issues
		//create a DX graphics interface factory
		HRESULT m_lastError = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to create graphics interface factory");
			return;
		}
		//now use it to create an adapter for the primary video card
		m_lastError = factory->EnumAdapters(0, &adapter);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to create graphics adapter");
			return;
		}
		//enumerate the primary monitor
		m_lastError = adapter->EnumOutputs(0, &adapterOutput);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to enumerate primary monitor");
			return;
		}
		//get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM format
		m_lastError = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to get display mode list");
			return;
		}
		//create a list of all the display modes for the monitor/video card
		displayModeList = new DXGI_MODE_DESC[numModes];

		//fill the display mode lists
		m_lastError = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to fill display mode list");
			return;
		}

		//find the correct display mode
		for(unsigned int i = 0; i < numModes; i++)
		{
			if(displayModeList[i].Width == width && displayModeList[i].Height == height)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}

		//lastly, get the name of the video card and the amount of RAM
		m_lastError = adapter->GetDesc(&adapterDesc);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to get adapter info");
			return;
		}
		//store video card RAM in megabytes
		m_videoCardInfo.totalRAM = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

		//get the name of the video card
		m_videoCardInfo.name = adapterDesc.Description;

		delete [] displayModeList;
		displayModeList = 0;

		SAFE_RELEASE(adapterOutput);
		SAFE_RELEASE(adapter);
		SAFE_RELEASE(factory);
		
		//now initialize the swapchain/desc
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferCount = 1; //single back buffer
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //32-bit surface

		if(vsyncEnabled)
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
		}else
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		}

		//using the back buffer as a render target
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hwnd;

		//turn off multisampling
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		swapChainDesc.Windowed = !fullscreen;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //discard back buffer contents after presenting
		swapChainDesc.Flags = 0;

		//using DX 11
		featureLevel = D3D_FEATURE_LEVEL_11_0;

		//create the swapchain, direct3d device, and d3d context
		m_lastError = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);
		if(FAILED(m_lastError))
		{

			std::wstring error = Kiwi::GetD3DErrorString(m_lastError);

			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to create device/swap chain ("+error+L")");
			return;
		}

		//get the back buffer and attach it to the swap chain
		m_lastError = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to attach back buffer");
		}

		//create render target view
		m_lastError = m_device->CreateRenderTargetView(m_backBuffer, NULL, &m_backBufferRenderTargetView);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to create back buffer render target view");;
		}

		//create depth/stencil buffer to allow proper rendering in 3d space and allow for effects
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
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

		m_lastError = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_backBufferDepthBuffer);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to create back buffer depth stencil buffer");;
		}

		//now setup depth stencil to allow control of what type of depth test is done for each pixel
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;
		//for front-facing pixels
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		//for back facing pixels
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		m_lastError = m_device->CreateDepthStencilState(&depthStencilDesc, &m_backBufferDepthState);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to create back buffer depth stencil state");;
		}

		//set the depth stencil state
		m_deviceContext->OMSetDepthStencilState(m_backBufferDepthState, 1);

		//setup the depth stencil buffer so DX will use the buffer as a depth stencil texture
		ZeroMemory(&dsViewDesc, sizeof(dsViewDesc));
		dsViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsViewDesc.Texture2D.MipSlice = 0;

		m_lastError = m_device->CreateDepthStencilView(m_backBufferDepthBuffer, &dsViewDesc, &m_backBufferDepthView);
		if(FAILED(m_lastError))
		{
			throw Kiwi::Exception(L"D3D11Interface::Initialize", L"Failed to create back buffer depth stencil view");;
		}

		//now bind the render target view and depth stencil buffer to the render pipeline
		m_deviceContext->OMSetRenderTargets(1, &m_backBufferRenderTargetView, m_backBufferDepthView);

		//by default, set the primitive type to triangle list
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_fullscreen = fullscreen;
		m_vSyncEnabled = vsyncEnabled;

	}