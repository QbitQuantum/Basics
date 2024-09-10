bool Prism::DirectX::D3DSwapChainSetup()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = mySetupInfo.myScreenWidth;
    swapChainDesc.BufferDesc.Height = mySetupInfo.myScreenHeight;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
    swapChainDesc.OutputWindow = myHWND;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = true;

    HRESULT result = D3D11CreateDeviceAndSwapChain(NULL,
                     D3D_DRIVER_TYPE_HARDWARE,
                     NULL,
#ifdef RELEASE_BUILD
                     NULL,
#else
                     D3D11_CREATE_DEVICE_DEBUG,
#endif
                     NULL,
                     NULL,
                     D3D11_SDK_VERSION,
                     &swapChainDesc,
                     &mySwapChain,
                     &myDevice,
                     NULL,
                     &myContext);

    if (FAILED(result))
    {
        return false;
    }

#ifdef _DEBUG
    myDebugInterface = nullptr;
    result = myDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&myDebugInterface);
    if (FAILED(result))
    {
        DL_ASSERT("[DirectX]: Failed to Query DebugInterface");
        return false;
    }

    myInfoQueue = nullptr;
    if (FAILED(myDebugInterface->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&myInfoQueue)))
    {
        DL_ASSERT("[DirectX]: Failed to Query InfoQueue");
        return false;
    }

    myInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
    myInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);

    D3D11_MESSAGE_ID hide[] =
    {
        D3D11_MESSAGE_ID_DEVICE_PSSETSHADERRESOURCES_HAZARD,
        D3D11_MESSAGE_ID_DEVICE_OMSETRENDERTARGETS_HAZARD
        // Add more message IDs here as needed
    };

    D3D11_INFO_QUEUE_FILTER filter;
    memset(&filter, 0, sizeof(filter));
    filter.DenyList.NumIDs = _countof(hide);
    filter.DenyList.pIDList = hide;
    myInfoQueue->AddStorageFilterEntries(&filter);
    myInfoQueue->Release();
#endif

    return TRUE;
}