void DeviceManDX12::Create(HWND hWnd)
{
	Destroy();
#ifndef NDEBUG
	ComPtr<ID3D12Debug> debug;
	if (S_OK == D3D12GetDebugInterface(IID_PPV_ARGS(&debug)))
	{
		debug->EnableDebugLayer();
	}
#endif
	ComPtr<IDXGIFactory4> factory;
	if (S_OK != CreateDXGIFactory1(IID_PPV_ARGS(&factory))) {
		Destroy();
		return;
	}
	ComPtr<IDXGIAdapter1> adapter;
	for (int i = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(i, &adapter); i++) {
		if (S_OK == D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device))) {
			break;
		}
	}
	if (!device) {
		Destroy();
		return;
	}

	D3D12_COMMAND_QUEUE_DESC queueDesc;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = 0;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;
	if (S_OK != device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue))) {
		Destroy();
		return;
	}

	RECT rc;
	GetClientRect(hWnd, &rc);

	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = numFrameBuffers;
	sd.BufferDesc.Width = rc.right - rc.left;
	sd.BufferDesc.Height = rc.bottom - rc.top;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;

	ComPtr<IDXGISwapChain> sc;
	if (S_OK != factory->CreateSwapChain(commandQueue.Get(), &sd, &sc)) {
		Destroy();
		return;
	}
	if (S_OK != sc.As(&swapChain)) {
		Destroy();
		return;
	}

	const D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = { D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 1 };
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	for (int i = 0; i < numFrameBuffers; i++) {
		FrameResources& res = frameResources[i];
		if (S_OK != swapChain->GetBuffer(i, IID_PPV_ARGS(&res.renderTarget))) {
			Destroy();
			return;
		}
		device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&res.commandAllocator));

		const D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = { D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, maxSrvs, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE };
		device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&res.srvHeap));

		res.constantBuffer = afCreateUBO(maxConstantBufferBlocks * 0x100);
		D3D12_RANGE readRange = {};
		HRESULT hr = res.constantBuffer->Map(0, &readRange, (void**)&res.mappedConstantBuffer);
		assert(hr == S_OK);
		assert(res.mappedConstantBuffer);
	}

	IVec2 size = { (int)sd.BufferDesc.Width, (int)sd.BufferDesc.Height };
	depthStencil = afCreateTexture2D(AFDT_DEPTH_STENCIL, size, nullptr, true);

	const D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = { D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1 };
	device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	device->CreateDepthStencilView(depthStencil.Get(), nullptr, dsvHandle);

	factory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameResources[0].commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
	commandList->Close();

	if (S_OK != device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence))) {
		Destroy();
		return;
	}
	BeginScene();
}