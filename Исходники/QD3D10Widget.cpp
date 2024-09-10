HRESULT QD3D10Widget::createSwapChainAndDevice( int width, int height )
{
    UINT createDeviceFlags = 0;

#ifdef _DEBUG
    createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.RefreshRate.Denominator = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = winId();
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Windowed = TRUE;

    D3D10_DRIVER_TYPE driverType = D3D10_DRIVER_TYPE_HARDWARE;

    // create the device and the swap chain
    HRESULT hr = D3D10CreateDeviceAndSwapChain
                 (
                     NULL, // existing DXGI adapter
                     driverType, // driver type
                     NULL, // HMODULE pointing to loaded software rasterizer dll
                     createDeviceFlags, // device creation flags
                     D3D10_SDK_VERSION, // DX sdk version
                     &sd, // swap chain description
                     &m_pSwapChain, // output swap chain
                     &m_pDevice // output device
                 );

    return hr;
}