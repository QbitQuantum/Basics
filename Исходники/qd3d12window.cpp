void QD3D12WindowPrivate::initialize()
{
    Q_Q(QD3D12Window);

    if (initialized)
        return;

    swapChainBufferCount = 2;

    HWND hwnd = reinterpret_cast<HWND>(q->winId());

    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        debugController->EnableDebugLayer();

    ComPtr<IDXGIFactory4> factory;
    if (FAILED(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory)))) {
        qWarning("Failed to create DXGI");
        return;
    }

    ComPtr<IDXGIAdapter1> adapter;
    getHardwareAdapter(factory.Get(), &adapter);

    bool warp = true;
    if (adapter) {
        HRESULT hr = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
        if (SUCCEEDED(hr))
            warp = false;
        else
            qWarning("Failed to create device: 0x%x", hr);
    } else {
        qWarning("No usable hardware adapters found");
    }

    if (warp) {
        qDebug("Using WARP");
        ComPtr<IDXGIAdapter> warpAdapter;
        factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));
        HRESULT hr = D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
        if (FAILED(hr)) {
            qWarning("Failed to create WARP device: 0x%x", hr);
            return;
        }
    }

    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)))) {
        qWarning("Failed to create command queue");
        return;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = swapChainBufferCount;
    swapChainDesc.BufferDesc.Width = q->width() * q->devicePixelRatio();
    swapChainDesc.BufferDesc.Height = q->height() * q->devicePixelRatio();
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // D3D12 requires the flip model
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.SampleDesc.Count = 1; // Flip does not support MSAA so no choice here
    swapChainDesc.Windowed = TRUE;

    ComPtr<IDXGISwapChain> baseSwapChain;
    HRESULT hr = factory->CreateSwapChain(commandQueue.Get(), &swapChainDesc, &baseSwapChain);
    if (FAILED(hr)) {
        qWarning("Failed to create swap chain: 0x%x", hr);
        return;
    }
    if (FAILED(baseSwapChain.As(&swapChain))) {
        qWarning("Failed to cast swap chain");
        return;
    }

    factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);

    if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)))) {
        qWarning("Failed to create command allocator");
        return;
    }

    if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_BUNDLE, IID_PPV_ARGS(&bundleAllocator)))) {
        qWarning("Failed to create command bundle allocator");
        return;
    }

    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = swapChainBufferCount + extraRenderTargetCount;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    if (FAILED(device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap)))) {
        qWarning("Failed to create render target view descriptor heap");
        return;
    }
    rtvStride = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1 + extraRenderTargetCount;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    if (FAILED(device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap)))) {
        qWarning("Failed to create depth stencil heap");
        return;
    }
    dsvStride = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

    setupRenderTargets();

    initialized = true;

    q->initializeD3D();
}