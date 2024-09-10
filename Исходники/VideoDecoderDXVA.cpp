bool VideoDecoderDXVAPrivate::D3dCreateDeviceFallback()
{
    qDebug("Fallback to d3d9");
    typedef IDirect3D9* (WINAPI *Create9Func)(UINT SDKVersion);
    Create9Func Create9 = (Create9Func)GetProcAddress(hd3d9_dll, "Direct3DCreate9");
    if (!Create9) {
        qWarning("Cannot locate reference to Direct3DCreate9 ABI in DLL");
        return false;
    }
    d3dobj = Create9(D3D_SDK_VERSION);
    if (!d3dobj) {
        qWarning("Direct3DCreate9 failed");
        return false;
    }
    if (FAILED(d3dobj->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &d3dai))) {
        qWarning("IDirect3D9->GetAdapterIdentifier failed");
        ZeroMemory(&d3dai, sizeof(d3dai));
        return false;
    }
    vendor = getVendorName(&d3dai);
    description = QString().sprintf("DXVA2 (%.*s, vendor %lu(%s), device %lu, revision %lu)",
                                    sizeof(d3dai.Description), d3dai.Description,
                                    d3dai.VendorId, qPrintable(vendor), d3dai.DeviceId, d3dai.Revision);
    //if (copy_uswc)
      //  copy_uswc = vendor.toLower() == "intel";
    qDebug("DXVA2 description:  %s", description.toUtf8().constData());

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    // use mozilla's parameters
    d3dpp.Flags                  = D3DPRESENTFLAG_VIDEO;
    d3dpp.Windowed               = TRUE;
    d3dpp.hDeviceWindow          = ::GetShellWindow(); //NULL;
    d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    //d3dpp.MultiSampleType        = D3DMULTISAMPLE_NONE;
    //d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_DEFAULT;
    d3dpp.BackBufferCount        = 1; //0;                  /* FIXME what to put here */
    d3dpp.BackBufferFormat       = D3DFMT_UNKNOWN; //D3DFMT_X8R8G8B8;    /* FIXME what to put here */
    d3dpp.BackBufferWidth        = 1; //0;
    d3dpp.BackBufferHeight       = 1; //0;
    //d3dpp.EnableAutoDepthStencil = FALSE;
    DWORD flags = D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING;
    if (FAILED(d3dobj->CreateDevice(D3DADAPTER_DEFAULT,
                                   D3DDEVTYPE_HAL, GetShellWindow(),// GetDesktopWindow(), //GetShellWindow()?
                                   flags,
                                   &d3dpp, &d3ddev))) {
        qWarning("IDirect3D9->CreateDevice failed");
        d3ddev = 0;
        return false;
    }
    qDebug("IDirect3DDevice9 created....");
    return true;
}