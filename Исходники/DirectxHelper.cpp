IDirect3DDevice9* CreateDevice9(HINSTANCE dll, IDirect3D9** d3d9, D3DADAPTER_IDENTIFIER9 *d3dai)
{
    qDebug("creating d3d9 device...");
    typedef IDirect3D9* (WINAPI *Create9Func)(UINT SDKVersion);
    Create9Func Create9 = (Create9Func)GetProcAddress(dll, "Direct3DCreate9");
    if (!Create9) {
        qWarning("Symbol not found: Direct3DCreate9");
        return NULL;
    }
    *d3d9 = Create9(D3D_SDK_VERSION);
    if (!(*d3d9)) {
        qWarning("Direct3DCreate9 failed");
        return NULL;
    }
    if (d3dai)
        DX_WARN((*d3d9)->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, d3dai));

    D3DPRESENT_PARAMETERS d3dpp;
    InitParameters(&d3dpp);
    DWORD flags = D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING;
    IDirect3DDevice9 *d3d9dev = NULL;
    DX_ENSURE(((*d3d9)->CreateDevice(D3DADAPTER_DEFAULT,
                                     D3DDEVTYPE_HAL, GetShellWindow(),// GetDesktopWindow(), //GetShellWindow()?
                                     flags,
                                     &d3dpp, &d3d9dev))
              , NULL);
    qDebug("IDirect3DDevice9 created");
    return d3d9dev;
}