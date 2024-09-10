HRESULT KGraphicsDevice::Init(int32 window_width, int32 window_height)
{
	HRESULT hr;

	m_WindowWidth = window_width;
	m_WindowHeight = window_height;

	//Setup SDL window
	HWND handle;

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "SDL_Init failed: %s", SDL_GetError());
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

	m_MainWindow = SDL_CreateWindow("Conservative Clustered Shading DirectX12", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	SDL_SysWMinfo info;
	//Must init info struct with SDL version info, see documentation for explanation
	SDL_VERSION(&info.version);

	if (SDL_GetWindowWMInfo(m_MainWindow, &info))
		handle = info.info.win.window;
	else
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed to get WMInfo: %s", SDL_GetError());

	uint32 flags = 0;

#ifdef _DEBUG
	{
		ID3D12Debug* debugController;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
		debugController->EnableDebugLayer();

		if (debugController)
			debugController->Release();
	}
#endif

	DXGI_SWAP_CHAIN_DESC descSwapChain;
	ZeroMemory(&descSwapChain, sizeof(descSwapChain));
	descSwapChain.BufferCount = 2;
	descSwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descSwapChain.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;
	descSwapChain.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	descSwapChain.OutputWindow = handle;
	descSwapChain.SampleDesc.Count = 1;
	descSwapChain.Windowed = true;

	hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device));
	if (FAILED(hr))
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed to create D3D12 Device");

	D3D12_FEATURE_DATA_D3D12_OPTIONS opts;
	hr = m_Device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &opts, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS));
	if (FAILED(hr))
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed to CheckFeatureSupport");
	
	//Print hardware opts
	PrintHWopts(opts);

	uint32 node_count = m_Device->GetNodeCount();
	shared_context.log->LogText(LogLevel::DEBUG_PRINT, "Device node count: %d", node_count);

	IDXGIFactory* dxgifactory;
	hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgifactory));
	if (FAILED(hr))
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed to create IDXGIFactory");

	D3D12_COMMAND_QUEUE_DESC queueDesc;
	ZeroMemory(&queueDesc, sizeof(queueDesc));
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	hr = m_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_CommandQueue));
	if (FAILED(hr))
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed to create Command Queue");

	hr = dxgifactory->CreateSwapChain(m_CommandQueue, &descSwapChain, &m_SwapChain);
	if (FAILED(hr))
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed to create SwapChain");

	
	dxgifactory->Release();

	//Set up descriptor heaps
	m_DescHeapCBV_SRV.CreateDescriptorHeap(50, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
	m_DescHeapDSV.CreateDescriptorHeap(2, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	m_DescHeapRTV.CreateDescriptorHeap(20, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	m_DescHeapSampler.CreateDescriptorHeap(1, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

	m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_CommandAllocator));

	m_Device->SetStablePowerState(TRUE);

	hr = m_CommandQueue->GetTimestampFrequency(&m_Freq);
	if (FAILED(hr))
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed GetTimestampFrequency");

	m_ViewPort = { 0.0f, 0.0f, (float)m_WindowWidth, (float)m_WindowHeight, 0.0f, 1.0f };
	m_ScissorRect = { 0, 0, m_WindowWidth, m_WindowHeight };

	m_RTDescriptor[0] = m_DescHeapRTV.GetNewCPUHandle();
	m_RTDescriptor[1] = m_DescHeapRTV.GetNewCPUHandle();

	//Get back buffer and create RTVs
	m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_RenderTarget[0]));
	m_Device->CreateRenderTargetView(m_RenderTarget[0], nullptr, m_RTDescriptor[0]);
	m_RenderTarget[0]->SetName(L"RENDER TARGET");

	m_SwapChain->GetBuffer(1, IID_PPV_ARGS(&m_RenderTarget[1]));
	m_Device->CreateRenderTargetView(m_RenderTarget[1], nullptr, m_RTDescriptor[1]);

	//Create time stamp query heap
	const uint32 num_time_queries = 24;
	D3D12_QUERY_HEAP_DESC desc;
	desc.Type = D3D12_QUERY_HEAP_TYPE_TIMESTAMP;
	desc.Count = num_time_queries;
	desc.NodeMask = 0;

	hr = m_Device->CreateQueryHeap(&desc, IID_PPV_ARGS(&m_TimeStampQueryHeap));
	if (FAILED(hr))
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed to CreateQueryHeap");

	m_Device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK, 0, 0),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(num_time_queries * sizeof(uint64)),
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_TimeStampQueryReadBackRes));
	if (FAILED(hr))
		shared_context.log->LogText(LogLevel::FATAL_ERROR, "Failed to CreateCommittedResource for query readback buffer");

	//Create fence
	m_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence));
	m_CurrentFence = 1;

	m_HandleEvent = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);

	return hr;
}