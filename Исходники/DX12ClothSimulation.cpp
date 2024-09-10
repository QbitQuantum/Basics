// Load the rendering pipeline dependencies.
void DX12ClothSimulation::LoadPipeline()
{
#ifdef _DEBUG
	// Enable the D3D12 debug layer.
{
	ComPtr<ID3D12Debug> debugController;
	if ( SUCCEEDED( D3D12GetDebugInterface( IID_PPV_ARGS( &debugController ) ) ) )
	{
		debugController->EnableDebugLayer();
	}
}
#endif

ComPtr<IDXGIFactory4> factory;
ThrowIfFailed( CreateDXGIFactory1( IID_PPV_ARGS( &factory ) ) );

if ( m_useWarpDevice )
{
	ComPtr<IDXGIAdapter> warpAdapter;
	ThrowIfFailed( factory->EnumWarpAdapter( IID_PPV_ARGS( &warpAdapter ) ) );

	ThrowIfFailed( D3D12CreateDevice(
		warpAdapter.Get(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS( &m_device )
		) );
}
else
{
	ComPtr<IDXGIAdapter1> hardwareAdapter;
	GetHardwareAdapter( factory.Get(), &hardwareAdapter );

	ThrowIfFailed( D3D12CreateDevice(
		hardwareAdapter.Get(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS( &m_device )
		) );
}

// Describe and create the command queue.
D3D12_COMMAND_QUEUE_DESC queueDesc = {};
queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

ThrowIfFailed( m_device->CreateCommandQueue( &queueDesc, IID_PPV_ARGS( &m_commandQueue ) ) );

// Describe and create the swap chain.
DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
swapChainDesc.BufferCount = FrameCount;
swapChainDesc.BufferDesc.Width = m_width;
swapChainDesc.BufferDesc.Height = m_height;
swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
swapChainDesc.OutputWindow = m_hwnd;
swapChainDesc.SampleDesc.Count = 1;
swapChainDesc.Windowed = TRUE;

ComPtr<IDXGISwapChain> swapChain;
ThrowIfFailed( factory->CreateSwapChain(
	m_commandQueue.Get(),		// Swap chain needs the queue so that it can force a flush on it.
	&swapChainDesc,
	&swapChain
	) );

ThrowIfFailed( swapChain.As( &m_swapChain ) );

m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

// Create descriptor heaps.
{
	// Describe and create a render target view (RTV) descriptor heap.
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = FrameCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	ThrowIfFailed( m_device->CreateDescriptorHeap( &rtvHeapDesc, IID_PPV_ARGS( &m_rtvHeap ) ) );

	m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );
}

// Create a command allocator for each frame.
for ( UINT n = 0; n < FrameCount; n++ )
{
	ThrowIfFailed( m_device->CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS( &m_commandAllocators[n] ) ) );
}
}