/// Overriden in derived class to initialize the graphics required for a render loop. The render loop acts as a message pump to the user clients.
/// \return True if success, false if failure
bool DX12Player::InitializeGraphics()
{
    ID3D12Device* graphicsDevice = nullptr;

    UINT frameCount = 2;

    // Initialize all pipeline components necessary to render a frame.
    /// Invoking these calls will allow the DXGI/DX12Server plugins to be injected into our player application.

    // @TODO: In the future, the following commands will invoked by loaded a capture file,
    // initializing, and executing all captured calls. Spinning on the target frame will beat
    // the DX12Server's message loop, allowing communicate with GPUPerfServer.
    IDXGIFactory4* factory = nullptr;
    ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));

    ThrowIfFailed(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&graphicsDevice)));

    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    ID3D12CommandQueue* commandQueue = nullptr;
    ThrowIfFailed(graphicsDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)));

    // Describe and create the swap chain.
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = frameCount;
    swapChainDesc.BufferDesc.Width = m_pPlayerWindow->GetWindowWidth();
    swapChainDesc.BufferDesc.Height = m_pPlayerWindow->GetWindowHeight();
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    // The window handle must be set before being used here.
    swapChainDesc.OutputWindow = m_pPlayerWindow->GetWindowHandle();
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;

    HRESULT res = factory->CreateSwapChain(commandQueue, &swapChainDesc, (IDXGISwapChain**)&m_swapchain);

    ThrowIfFailed(res);

    if (res != S_OK)
    {
        return false;
    }
    else
    {
        return true;
    }

}