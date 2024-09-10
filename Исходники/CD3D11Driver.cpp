	bool CD3D11Driver::init(SCreationParameters& createParam)
	{
		HRESULT result;
		IDXGIFactory* factory;
		IDXGIAdapter* adapter;
		IDXGIOutput* adapterOutput;
		unsigned int numModes, i, numerator = 0, denominator = 1, stringLength;
		DXGI_MODE_DESC* displayModeList;
		DXGI_ADAPTER_DESC adapterDesc;
		int error;
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		//D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		//D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		//D3D11_RASTERIZER_DESC rasterDesc;
		//D3D11_VIEWPORT viewport;

		//const SCreationParameters& params = mDevice->getCreationParameters();

		// Create a DirectX graphics interface factory.

		mBackBufferWidth = createParam.BackBufferWidth;
		mBackBufferHeight = createParam.BackBufferHeight;

		result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if (FAILED(result))
		{
			return false;
		}

		// Use the factory to create an adapter for the primary graphics interface (video card).
		result = factory->EnumAdapters(0, &adapter);
		if (FAILED(result))
		{
			return false;
		}

		// Enumerate the primary adapter output (monitor).
		result = adapter->EnumOutputs(0, &adapterOutput);
		if (FAILED(result))
		{
			return false;
		}

		// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
		if (FAILED(result))
		{
			return false;
		}

		// Create a list to hold all the possible display modes for this monitor/video card combination.
		displayModeList = new DXGI_MODE_DESC[numModes];
		if (!displayModeList)
		{
			return false;
		}

		// Now fill the display mode list structures.
		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
		if (FAILED(result))
		{
			return false;
		}

		// Now go through all the display modes and find the one that matches the screen width and height.
		// When a match is found store the numerator and denominator of the refresh rate for that monitor.
		for (i = 0; i < numModes; i++)
		{
			if (displayModeList[i].Width == (unsigned int)createParam.BackBufferWidth)
			{
				if (displayModeList[i].Height == (unsigned int)createParam.BackBufferHeight)
				{
					numerator = displayModeList[i].RefreshRate.Numerator;
					denominator = displayModeList[i].RefreshRate.Denominator;
				}
			}
		}

		// Get the adapter (video card) description.
		result = adapter->GetDesc(&adapterDesc);
		if (FAILED(result))
		{
			return false;
		}

		// Store the dedicated video card memory in megabytes.
		mVideoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

		// Convert the name of the video card to a character array and store it.
		error = wcstombs_s(&stringLength, mVideoCardDescription, 128, adapterDesc.Description, 128);
		if (error != 0)
		{
			return false;
		}

		// Release the display mode list.
		delete[] displayModeList;
		displayModeList = 0;

		// Release the adapter output.
		adapterOutput->Release();
		adapterOutput = 0;

		// Release the adapter.
		adapter->Release();
		adapter = 0;

		// Release the factory.
		factory->Release();
		factory = 0;

		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevel;

		/* 如果将这个标志设为DEBUG，则绘制效率大大降低，且帧频极不稳定 */
		//createDeviceFlags = 0;

		HRESULT hr;
		hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE,
			NULL, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &md3dDevice, &featureLevel, &md3dDeviceContext);

		if (FAILED(hr))
			return false;

#if defined(DEBUG) || defined(_DEBUG)
		md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&md3dDebug));
#endif

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			throw std::runtime_error("DirectX11 is not supported!");
			return false;
		}

		UINT numQualityLevels;
		md3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &numQualityLevels);

		IDXGIDevice* dxgiDevice = 0;
		md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		IDXGIAdapter* dxgiAdapter = 0;
		dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
		IDXGIFactory* dxgiFactory = 0;
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;

		// Initialize the swap chain description.
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		// Set the width and height of the back buffer.
		swapChainDesc.BufferDesc.Width = createParam.BackBufferWidth;
		swapChainDesc.BufferDesc.Height = createParam.BackBufferHeight;

		// Set regular 32-bit surface for the back buffer.
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// Set the refresh rate of the back buffer.
		if (createParam.VsyncEnabled)
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
		}
		else
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		}

		// Set multisampling.
		if (createParam.MultiSamplingQuality == 0)
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;

			createParam.MultiSamplingCount = 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = createParam.MultiSamplingCount;
			UINT numQualityLevels;
			md3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &numQualityLevels);

			swapChainDesc.SampleDesc.Quality = min(numQualityLevels - 1, createParam.MultiSamplingQuality);

			createParam.MultiSamplingQuality = swapChainDesc.SampleDesc.Quality;
		}
		
		// set member attributes of class


		// Set to a single back buffer.
		swapChainDesc.BufferCount = 1;

		// Set the usage of the back buffer.
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		// Set the handle for the window to render to.
		swapChainDesc.OutputWindow = (HWND)createParam.BackBufferWindowHandle;

		// Set to full screen or windowed mode.
		if (createParam.WindowStyle & EWS_FULLSCREEN)
		{
			swapChainDesc.Windowed = false;
		}
		else
		{
			swapChainDesc.Windowed = true;
		}

		// Set the scan line ordering and scaling to unspecified.
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		// Discard the back buffer contents after presenting.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// Don't set the advanced flags.
		swapChainDesc.Flags = 0;

		hr = dxgiFactory->CreateSwapChain(md3dDevice, &swapChainDesc, &md3dSwapChain);
		if (FAILED(hr))
			return false;
		ReleaseCOM(dxgiDevice);
		ReleaseCOM(dxgiAdapter);
		ReleaseCOM(dxgiFactory);
		// Get the pointer to the back buffer.

		ID3D11Texture2D* backBuffer;
		result = md3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
		if (FAILED(result))
		{
			return false;
		}
		md3dDevice->CreateRenderTargetView(backBuffer, 0, &mDefaultRenderTargetView);
		ReleaseCOM(backBuffer);

		mDefaultRenderTarget = new CD3D11RenderTarget(md3dDevice, md3dDeviceContext, mDefaultRenderTargetView,
			createParam.BackBufferWidth, createParam.BackBufferHeight);

		// Initialize the description of the depth buffer.
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

		// Setup the viewport for rendering.
		setViewport(0, 0, static_cast<f32>(mBackBufferWidth), static_cast<f32>(mBackBufferHeight));

		//create resource factory
		mResourceFactory = new CD3D11ResourceFactory(
			md3dDevice, md3dDeviceContext, this);
		IResourceFactory::_setInstance(mResourceFactory);

		//create geometry creator
		mGeometryCreator = new CGeometryCreator;
		IGeometryCreator::_setInstance(mGeometryCreator);

		//create material manager
		mMaterialManager = new CMaterialManager;
		IMaterialManager::_setInstance(mMaterialManager);

		//create sampler manager
		mSamplerManager = new CSamplerManager(mResourceFactory);
		ISamplerManager::_setInstance(mSamplerManager);


		// create shadermanager
		mShaderManager = new CShaderManager(mResourceFactory);
		IShaderManager::_setInstance(mShaderManager);

		// create inputlayout manager
		mInputLayoutManager = new CInputLayoutManager(mResourceFactory);
		IInputLayoutManager::_setInstance(mInputLayoutManager);

		//create texture manager
		mTextureManager = new CTextureManager(mDevice, mResourceFactory);
		ITextureManager::_setInstance(mTextureManager);

		//create render state manager
		mRenderStateManager = new CRenderStateManager(mResourceFactory);
		IRenderStateManager::_setInstance(mRenderStateManager);

		//create mesh manager
		mMeshManager = new CMeshManager(mResourceFactory, mGeometryCreator, mTextureManager);
		IMeshManager::_setInstance(mMeshManager);

		
		//create pipeline manager
		mPipeManager = new CPipelineManager(mResourceFactory);
		IPipelineManager::_setInstance(mPipeManager);

		//create resource group manager
		mResourceGroupManager = new CResourceGroupManager(mTextureManager, mShaderManager,
			mInputLayoutManager, mRenderStateManager, mPipeManager, mMaterialManager, mMeshManager, mSamplerManager);
		IResourceGroupManager::_setInstance(mResourceGroupManager);

		//mResourceFactory->setResourceGroupManager(mResourceGroupManager);

		// create default depth-stencil-buffer
		bool multiSampling = (createParam.MultiSamplingCount > 1);


		mDepthStencilSurface = mTextureManager->createDepthStencilSurface("_default_depth_stencil_surface",
			0, 0, createParam.DepthBits, createParam.StencilBits,
			multiSampling, createParam.MultiSamplingCount, createParam.MultiSamplingQuality, true);

		if (!mDepthStencilSurface)
		{
			GF_PRINT_CONSOLE_INFO("Depth Stencil Surface has failed to be created.\n");
			return false;
		}

		D3D11DriverState.DepthStencilSurface = mDepthStencilSurface;
		CD3D11DepthStencilSurface* d3dDepthStencilSurface = dynamic_cast<CD3D11DepthStencilSurface*>(mDepthStencilSurface);
		mDefaultDepthStencilView = d3dDepthStencilSurface->getDepthStencilView();
		D3D11DriverState.DepthStencilView = mDefaultDepthStencilView;


		// create mShadowMapRasterizeState. This state is only for rendering shadow maps.
		D3D11_RASTERIZER_DESC shadowRasterizeState;
		shadowRasterizeState.FillMode = D3D11_FILL_SOLID;
		shadowRasterizeState.CullMode = D3D11_CULL_BACK; // RENDER BACK FACE
		shadowRasterizeState.FrontCounterClockwise = TRUE; 
		shadowRasterizeState.DepthBiasClamp = 0.0f;
		//shadowRasterizeState.DepthBias = 100000;
		//shadowRasterizeState.SlopeScaledDepthBias = 1.0f;
		shadowRasterizeState.DepthBias = 0;
		shadowRasterizeState.SlopeScaledDepthBias = 0;
		shadowRasterizeState.DepthClipEnable = TRUE;
		shadowRasterizeState.ScissorEnable = FALSE;
		shadowRasterizeState.MultisampleEnable = FALSE;
		shadowRasterizeState.AntialiasedLineEnable = FALSE;

		hr = md3dDevice->CreateRasterizerState(&shadowRasterizeState, &mShadowMapRasterizeState);
		if (FAILED(hr))
			return false;

		D3D11DriverState.ShadowMapRasterizerState = mShadowMapRasterizeState;

		return true;
	}