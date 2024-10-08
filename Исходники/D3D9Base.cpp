bool D3D9_Init(HWND wnd, bool windowed, std::string *error_message) {
    hWnd = wnd;

    DIRECT3DCREATE9EX g_pfnCreate9ex;

    hD3D9 = LoadLibrary(TEXT("d3d9.dll"));
    if (!hD3D9) {
        ELOG("Missing d3d9.dll");
        *error_message = "D3D9.dll missing - try reinstalling DirectX.";
        return false;
    }

    int d3dx_version = LoadD3DX9Dynamic();
    if (!d3dx_version) {
        *error_message = "D3DX DLL not found! Try reinstalling DirectX.";
        return false;
    }

    g_pfnCreate9ex = (DIRECT3DCREATE9EX)GetProcAddress(hD3D9, "Direct3DCreate9Ex");
    has9Ex = (g_pfnCreate9ex != NULL) && IsVistaOrHigher();

    if (has9Ex) {
        HRESULT result = g_pfnCreate9ex(D3D_SDK_VERSION, &d3dEx);
        d3d = d3dEx;
        if (FAILED(result)) {
            FreeLibrary(hD3D9);
            *error_message = "D3D9Ex available but context creation failed. Try reinstalling DirectX.";
            return false;
        }
    } else {
        d3d = Direct3DCreate9(D3D_SDK_VERSION);
        if (!d3d) {
            FreeLibrary(hD3D9);
            *error_message = "Failed to create D3D9 context. Try reinstalling DirectX.";
            return false;
        }
    }

    D3DCAPS9 d3dCaps;

    D3DDISPLAYMODE d3ddm;
    if (FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
        *error_message = "GetAdapterDisplayMode failed";
        d3d->Release();
        return false;
    }

    adapterId = D3DADAPTER_DEFAULT;
    if (FAILED(d3d->GetDeviceCaps(adapterId, D3DDEVTYPE_HAL, &d3dCaps))) {
        *error_message = "GetDeviceCaps failed (???)";
        d3d->Release();
        return false;
    }

    HRESULT hr;
    if (FAILED(hr = d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT,
                                           D3DDEVTYPE_HAL,
                                           d3ddm.Format,
                                           D3DUSAGE_DEPTHSTENCIL,
                                           D3DRTYPE_SURFACE,
                                           D3DFMT_D24S8))) {
        if (hr == D3DERR_NOTAVAILABLE) {
            *error_message = "D24S8 depth/stencil not available";
            d3d->Release();
            return false;
        }
    }

    DWORD dwBehaviorFlags = D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE;
    if (d3dCaps.VertexProcessingCaps != 0)
        dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else
        dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    int xres, yres;
    GetRes(xres, yres);

    memset(&pp, 0, sizeof(pp));
    pp.BackBufferWidth = xres;
    pp.BackBufferHeight = yres;
    pp.BackBufferFormat = d3ddm.Format;
    pp.MultiSampleType = D3DMULTISAMPLE_NONE;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.Windowed = windowed;
    pp.hDeviceWindow = wnd;
    pp.EnableAutoDepthStencil = true;
    pp.AutoDepthStencilFormat = D3DFMT_D24S8;
    pp.PresentationInterval = (g_Config.bVSync) ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

    if (has9Ex) {
        if (windowed && IsWin7OrLater()) {
            // This new flip mode gives higher performance.
            // TODO: This makes it slower?
            //pp.BackBufferCount = 2;
            //pp.SwapEffect = D3DSWAPEFFECT_FLIPEX;
        }
        hr = d3dEx->CreateDeviceEx(adapterId, D3DDEVTYPE_HAL, wnd, dwBehaviorFlags, &pp, NULL, &deviceEx);
        device = deviceEx;
    } else {
        hr = d3d->CreateDevice(adapterId, D3DDEVTYPE_HAL, wnd, dwBehaviorFlags, &pp, &device);
    }

    if (FAILED(hr)) {
        *error_message = "Failed to create D3D device";
        d3d->Release();
        return false;
    }

    device->BeginScene();
    DX9::pD3Ddevice = device;
    DX9::pD3DdeviceEx = deviceEx;

    if (!DX9::CompileShaders(*error_message)) {
        *error_message = "Unable to compile shaders: " + *error_message;
        device->EndScene();
        device->Release();
        d3d->Release();
        DX9::pD3Ddevice = nullptr;
        DX9::pD3DdeviceEx = nullptr;
        device = nullptr;
        UnloadD3DXDynamic();
        return false;
    }

    DX9::fbo_init(d3d);

    if (deviceEx && IsWin7OrLater()) {
        // TODO: This makes it slower?
        //deviceEx->SetMaximumFrameLatency(1);
    }

    return true;
}