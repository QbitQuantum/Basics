// Create Direct3D device and swap chain
HRESULT InitDevice(HWND wnd)
{
    HRESULT hr = S_OK;

    // Get window size
    RECT rc;
    GetClientRect(wnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    // Create D3D11 device and swap chain
    UINT createDeviceFlags = 0;
    #ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    #endif
    ZeroMemory(&g_SwapChainDesc, sizeof(g_SwapChainDesc));
    g_SwapChainDesc.BufferCount = 1;
    g_SwapChainDesc.BufferDesc.Width = width;
    g_SwapChainDesc.BufferDesc.Height = height;
    g_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    g_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    g_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
    g_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    g_SwapChainDesc.OutputWindow = wnd;
    g_SwapChainDesc.SampleDesc.Count = 4;
    g_SwapChainDesc.SampleDesc.Quality = 0;
    g_SwapChainDesc.Windowed = TRUE;
    g_SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    // Try to create a hardware accelerated device with multisample antialiasing first
    hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, 
                                       NULL, 0, D3D11_SDK_VERSION, &g_SwapChainDesc, &g_SwapChain, 
                                       &g_D3DDev, NULL, &g_D3DDevCtx);
    if (FAILED(hr))
    {
        // If failed, try without antialiasing
        g_SwapChainDesc.SampleDesc.Count = 1;
        hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, 
                                           NULL, 0, D3D11_SDK_VERSION, &g_SwapChainDesc, &g_SwapChain, 
                                           &g_D3DDev, NULL, &g_D3DDevCtx);
        if (FAILED(hr))
        {
            // If failed, try to create a reference device
            hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_REFERENCE, NULL, createDeviceFlags, 
                                               NULL, 0, D3D11_SDK_VERSION, &g_SwapChainDesc, &g_SwapChain, 
                                               &g_D3DDev, NULL, &g_D3DDevCtx);
            if (SUCCEEDED(hr))
                MessageBox(wnd, L"No DX11 hardware acceleration found.\nSwitching to REFERENCE driver (very slow).",
                           L"Warning", MB_OK|MB_ICONWARNING);
            else
                return hr;
        }
    }

    // Create a render target and depth-stencil view
    ID3D11Texture2D *backBuffer = NULL, *dsBuffer = NULL;
    hr = g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    if (FAILED(hr))
        return hr;

    hr = g_D3DDev->CreateRenderTargetView(backBuffer, NULL, &g_RenderTargetView);
    backBuffer->Release();
    if (FAILED(hr))
        return hr;

	g_DepthStencilDesc.Width = width;
	g_DepthStencilDesc.Height = height;
	g_DepthStencilDesc.MipLevels = 1;
	g_DepthStencilDesc.ArraySize = 1;
    g_DepthStencilDesc.Format = DXGI_FORMAT_D16_UNORM;
	g_DepthStencilDesc.SampleDesc = g_SwapChainDesc.SampleDesc;
	g_DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	g_DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	g_DepthStencilDesc.CPUAccessFlags = 0;
	g_DepthStencilDesc.MiscFlags = 0;
    hr = g_D3DDev->CreateTexture2D(&g_DepthStencilDesc, NULL, &dsBuffer);
    if (FAILED(hr))
        return hr;
    hr = g_D3DDev->CreateDepthStencilView(dsBuffer, NULL, &g_DepthStencilView);
    dsBuffer->Release();
    if (FAILED(hr))
        return hr;

    g_D3DDevCtx->OMSetRenderTargets(1, &g_RenderTargetView, g_DepthStencilView);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (float)width;
    vp.Height = (float)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_D3DDevCtx->RSSetViewports(1, &vp);

    return S_OK;
}