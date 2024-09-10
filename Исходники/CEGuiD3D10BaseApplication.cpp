//----------------------------------------------------------------------------//
bool CEGuiD3D10BaseApplication::initialiseDirect3D(unsigned int width,
    unsigned int height, bool windowed)
{
    HRESULT res;

    // init sqap chain descriptor structure
    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(scd));
    scd.BufferCount = 1;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = pimpl->d_window;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = windowed;

    // initialise main parts of D3D
    res = D3D10CreateDeviceAndSwapChain(0, D3D10_DRIVER_TYPE_HARDWARE,
                                        0, 0, D3D10_SDK_VERSION,
                                        &scd, &pimpl->d_swapChain,
                                        &pimpl->d_device);
    if (SUCCEEDED(res))
    {

        // obtain handle to thr back buffer of the swap chain
        ID3D10Texture2D* back_buffer;
        res = pimpl->d_swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D),
                                            (LPVOID*)&back_buffer);

        if (SUCCEEDED(res))
        {
            ID3D10RenderTargetView* rtview;

            // create render target view using the back buffer
            res = pimpl->d_device->
                CreateRenderTargetView(back_buffer, 0, &rtview);

            // release handle to buffer - we have done all we needed to with it.
            back_buffer->Release();

            if (SUCCEEDED(res))
            {
                // bind the back-buffer render target to get the output.
                pimpl->d_device->
                    OMSetRenderTargets(1, &rtview, 0);

                // set a basic viewport.
                D3D10_VIEWPORT view_port;
                view_port.Width    = width;
                view_port.Height   = height;
                view_port.MinDepth = 0.0f;
                view_port.MaxDepth = 1.0f;
                view_port.TopLeftX = 0;
                view_port.TopLeftY = 0;
                pimpl->d_device->RSSetViewports(1, &view_port);

                // complete window initialisation
                ShowWindow(pimpl->d_window, SW_NORMAL);
                UpdateWindow(pimpl->d_window);

                return true;
            }

            rtview->Release();
        }

        pimpl->d_swapChain->Release();
        pimpl->d_device->Release();
        pimpl->d_swapChain = 0;
        pimpl->d_device = 0;
    }

    MessageBox(0, "Failed to correctly initialise Direct3D 10",
               Win32AppHelper::APPLICATION_NAME, MB_ICONERROR|MB_OK);

    return false;
}