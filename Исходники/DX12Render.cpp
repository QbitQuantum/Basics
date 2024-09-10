void DirectX12Render::InitializeDX()
{
	//Initialize the debug layer of DX12
#ifdef _DEBUG
	ComPtr<ID3D12Debug> Debug;

	ThrowFail(D3D12GetDebugInterface(IID_PPV_ARGS(&Debug)), TEXT("Failed to get debug interface"));
	Debug->EnableDebugLayer();

#endif
	//Make a factory so we can get our device along with an adapter to store
	ComPtr<IDXGIFactory4> Factory;
	ThrowFail(CreateDXGIFactory1(IID_PPV_ARGS(&Factory)), TEXT("Failed to create factory"));

	ComPtr<IDXGIAdapter1> Adapter;
	ComPtr<IDXGIAdapter1> TempAdapter;
	//Get our device
	for (UINT i = 0; DXGI_ERROR_NOT_FOUND != Factory->EnumAdapters1(i, &TempAdapter); ++i)
	{
		DXGI_ADAPTER_DESC1 Desc;
		TempAdapter->GetDesc1(&Desc);

		if (Desc.Flags == DXGI_ERROR_NOT_FOUND)
			continue;
		//Fake Create it to make sure it will actually work
		if (S_OK == D3D12CreateDevice(TempAdapter.Get(), D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), NULL))
			break;
	}
	Adapter = TempAdapter.Detach();
	//Create the device for reals
	ThrowFail(D3D12CreateDevice(Adapter.Get(), D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), &Device), TEXT("Failed to create DirectX 12 Device"));

	//Create Command Queue
	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	ThrowFail(Device->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&CommandQueue)), TEXT("Failed to create Command Queue"));

	//Create the swap chain
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};
	SwapDesc.BufferCount = FrameCount;
	SwapDesc.BufferDesc.Width = CWindow::GetWidth();
	SwapDesc.BufferDesc.Height = CWindow::GetHeight();
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapDesc.OutputWindow = CWindow::GethWnd();
	SwapDesc.SampleDesc.Count = 1;
	SwapDesc.Windowed = true;

	//Create a temporary swap chain because CreateSwapChain doesnt support SwapChain3
	ComPtr<IDXGISwapChain> FakeSwap;
	ThrowFail(Factory->CreateSwapChain(
		CommandQueue.Get(),
		&SwapDesc,
		&FakeSwap), TEXT("Fake Swap Chain Failed to create"));
	//.As() makes its TARGET itself not the otherway around. Causes evil shit if you do it the other way
	ThrowFail(FakeSwap.As(&SwapChain), TEXT("Real Swap Chain failed to switch"));
	
	FenceIndex = SwapChain->GetCurrentBackBufferIndex();

	D3D12_DESCRIPTOR_HEAP_DESC RTVDesc = {};
	RTVDesc.NumDescriptors = FrameCount;
	RTVDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RTVDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	ThrowFail(Device->CreateDescriptorHeap(&RTVDesc, IID_PPV_ARGS(&RTVHeap)), TEXT("Descriptor Heap failed to create"));

	HeapSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE RTVHandle( RTVHeap->GetCPUDescriptorHandleForHeapStart());

	for (UINT i = 0; i < FrameCount; i++)
	{
		ThrowFail(SwapChain->GetBuffer(i, IID_PPV_ARGS(&RenderTargets[i])), TEXT("Failed to Get Buffer"));
		Device->CreateRenderTargetView(RenderTargets[i].Get(), nullptr, RTVHandle);
		RTVHandle.Offset(1, HeapSize);
	}

	ThrowFail(Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&CommandAllocator)), TEXT("Command Allocator Failed to Initialize"));
}