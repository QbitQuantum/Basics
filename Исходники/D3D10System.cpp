D3D10System::D3D10System()
{
    HRESULT err;

#ifdef USE_DXGI1_2
    REFIID iidVal = OSGetVersion() >= 8 ? __uuidof(IDXGIFactory2) : __uuidof(IDXGIFactory1);
#else
    REFIID iidVal = __uuidof(IDXGIFactory1);
#endif

    UINT adapterID = GlobalConfig->GetInt(TEXT("Video"), TEXT("Adapter"), 0);

    IDXGIFactory1 *factory;
    if(FAILED(err = CreateDXGIFactory1(iidVal, (void**)&factory)))
        CrashError(TEXT("Could not create DXGI factory"));

    IDXGIAdapter1 *adapter;
    if(FAILED(err = factory->EnumAdapters1(adapterID, &adapter)))
        CrashError(TEXT("Could not get DXGI adapter"));

    //------------------------------------------------------------------

    DXGI_SWAP_CHAIN_DESC swapDesc;
    zero(&swapDesc, sizeof(swapDesc));
    swapDesc.BufferCount = 2;
    swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapDesc.BufferDesc.Width  = App->renderFrameWidth;
    swapDesc.BufferDesc.Height = App->renderFrameHeight;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.Flags = 0;
    swapDesc.OutputWindow = hwndRenderFrame;
    swapDesc.SampleDesc.Count = 1;
    swapDesc.Windowed = TRUE;

    bDisableCompatibilityMode = 1;//AppConfig->GetInt(TEXT("Video"), TEXT("DisableD3DCompatibilityMode"), 1) != 0;

    UINT createFlags = D3D10_CREATE_DEVICE_BGRA_SUPPORT;
    if(GlobalConfig->GetInt(TEXT("General"), TEXT("UseDebugD3D")))
        createFlags |= D3D10_CREATE_DEVICE_DEBUG;

    D3D10_FEATURE_LEVEL1 level = bDisableCompatibilityMode ? D3D10_FEATURE_LEVEL_10_1 : D3D10_FEATURE_LEVEL_9_3;

    //D3D10_CREATE_DEVICE_DEBUG
    //D3D11_DRIVER_TYPE_REFERENCE, D3D11_DRIVER_TYPE_HARDWARE
    err = D3D10CreateDeviceAndSwapChain1(adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, createFlags, level, D3D10_1_SDK_VERSION, &swapDesc, &swap, &d3d);
    if(FAILED(err))
    {
        bDisableCompatibilityMode = !bDisableCompatibilityMode;
        level = bDisableCompatibilityMode ? D3D10_FEATURE_LEVEL_10_1 : D3D10_FEATURE_LEVEL_9_3;
        err = D3D10CreateDeviceAndSwapChain1(adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, createFlags, level, D3D10_1_SDK_VERSION, &swapDesc, &swap, &d3d);
    }

    if(FAILED(err))
        CrashError(TEXT("Could not create D3D10 device and swap chain.  This error can happen for one of the following reasons:\r\n\r\n1.) Your GPU is not supported (DirectX 10 support is required - many integrated laptop GPUs do not support DX10)\r\n2.) You're running Windows Vista without the \"Platform Update\"\r\n3.) Your video card drivers are out of date"));

    adapter->Release();
    factory->Release();

    //------------------------------------------------------------------

    Log(TEXT("Loading up D3D10..."));

    D3D10_DEPTH_STENCIL_DESC depthDesc;
    zero(&depthDesc, sizeof(depthDesc));
    depthDesc.DepthEnable = FALSE;

    err = d3d->CreateDepthStencilState(&depthDesc, &depthState);
    if(FAILED(err))
        CrashError(TEXT("Unable to create depth state"));

    d3d->OMSetDepthStencilState(depthState, 0);

    //------------------------------------------------------------------

    D3D10_RASTERIZER_DESC rasterizerDesc;
    zero(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D10_FILL_SOLID;
    rasterizerDesc.CullMode = D3D10_CULL_NONE;
    rasterizerDesc.FrontCounterClockwise = FALSE;
    rasterizerDesc.DepthClipEnable = TRUE;

    err = d3d->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
    if(FAILED(err))
        CrashError(TEXT("Unable to create rasterizer state"));

    d3d->RSSetState(rasterizerState);

    //------------------------------------------------------------------

    rasterizerDesc.ScissorEnable = TRUE;

    err = d3d->CreateRasterizerState(&rasterizerDesc, &scissorState);
    if(FAILED(err))
        CrashError(TEXT("Unable to create scissor state"));

    //------------------------------------------------------------------

    ID3D10Texture2D *backBuffer = NULL;
    err = swap->GetBuffer(0, IID_ID3D10Texture2D, (void**)&backBuffer);
    if(FAILED(err))
        CrashError(TEXT("Unable to get back buffer from swap chain"));

    err = d3d->CreateRenderTargetView(backBuffer, NULL, &swapRenderView);
    if(FAILED(err))
        CrashError(TEXT("Unable to get render view from back buffer"));

    backBuffer->Release();

    //------------------------------------------------------------------

    D3D10_BLEND_DESC disabledBlendDesc;
    zero(&disabledBlendDesc, sizeof(disabledBlendDesc));
    for(int i=0; i<8; i++)
    {
        disabledBlendDesc.BlendEnable[i]        = TRUE;
        disabledBlendDesc.RenderTargetWriteMask[i] = D3D10_COLOR_WRITE_ENABLE_ALL;
    }
    disabledBlendDesc.BlendOpAlpha          = D3D10_BLEND_OP_ADD;
    disabledBlendDesc.BlendOp               = D3D10_BLEND_OP_ADD;
    disabledBlendDesc.SrcBlendAlpha         = D3D10_BLEND_ONE;
    disabledBlendDesc.DestBlendAlpha        = D3D10_BLEND_ZERO;
    disabledBlendDesc.SrcBlend              = D3D10_BLEND_ONE;
    disabledBlendDesc.DestBlend             = D3D10_BLEND_ZERO;

    err = d3d->CreateBlendState(&disabledBlendDesc, &disabledBlend);
    if(FAILED(err))
        CrashError(TEXT("Unable to create disabled blend state"));

    this->BlendFunction(GS_BLEND_SRCALPHA, GS_BLEND_INVSRCALPHA, 1.0f);
    bBlendingEnabled = true;
}