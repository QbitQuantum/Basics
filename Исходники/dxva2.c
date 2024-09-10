static int create_device(struct lavc_ctx *s)
{
    DXVA2Context *ctx = s->hwdec_priv;
    pDirect3DCreate9      *createD3D = NULL;
    HRESULT hr;
    D3DPRESENT_PARAMETERS d3dpp = {0};
    D3DDISPLAYMODE        d3ddm;
    UINT adapter = D3DADAPTER_DEFAULT;

    if (s->hwdec_info && s->hwdec_info->hwctx && s->hwdec_info->hwctx->d3d_ctx) {
        ctx->d3d9device = s->hwdec_info->hwctx->d3d_ctx->d3d9_device;
        if (ctx->d3d9device) {
            IDirect3D9_AddRef(ctx->d3d9device);
            MP_VERBOSE(ctx, "Using VO-supplied device %p.\n", ctx->d3d9device);
            return 0;
        }
    }

    ctx->d3dlib = LoadLibrary(L"d3d9.dll");
    if (!ctx->d3dlib) {
        MP_ERR(ctx, "Failed to load D3D9 library\n");
        goto fail;
    }

    createD3D = (pDirect3DCreate9 *)GetProcAddress(ctx->d3dlib, "Direct3DCreate9");
    if (!createD3D) {
        MP_ERR(ctx, "Failed to locate Direct3DCreate9\n");
        goto fail;
    }

    ctx->d3d9 = createD3D(D3D_SDK_VERSION);
    if (!ctx->d3d9) {
        MP_ERR(ctx, "Failed to create IDirect3D object\n");
        goto fail;
    }

    IDirect3D9_GetAdapterDisplayMode(ctx->d3d9, adapter, &d3ddm);
    d3dpp.Windowed         = TRUE;
    d3dpp.BackBufferWidth  = 640;
    d3dpp.BackBufferHeight = 480;
    d3dpp.BackBufferCount  = 0;
    d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
    d3dpp.Flags            = D3DPRESENTFLAG_VIDEO;

    hr = IDirect3D9_CreateDevice(ctx->d3d9, adapter, D3DDEVTYPE_HAL, GetShellWindow(),
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                 &d3dpp, &ctx->d3d9device);
    if (FAILED(hr)) {
        MP_ERR(ctx, "Failed to create Direct3D device\n");
        goto fail;
    }

    return 0;

fail:
    return -1;
}