static int dxva2_alloc(AVCodecContext *s)
{
    HwAccelContext  *hac = s->opaque;
    DXVA2Context *ctx;
    pDirect3DCreate9      *createD3D = NULL;
    pCreateDeviceManager9 *createDeviceManager = NULL;
    HRESULT hr;
    D3DPRESENT_PARAMETERS d3dpp = {0};
    D3DDISPLAYMODE        d3ddm;
    unsigned resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;

    ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return AVERROR(ENOMEM);

    ctx->deviceHandle = INVALID_HANDLE_VALUE;

    hac->hwaccel_ctx           = ctx;
    hac->hwaccel_uninit        = dxva2_uninit;
    hac->hwaccel_get_buffer    = dxva2_get_buffer;
    hac->hwaccel_retrieve_data = dxva2_retrieve_data;

    ctx->d3dlib = LoadLibrary("d3d9.dll");
    if (!ctx->d3dlib) {
        av_log(NULL, loglevel, "Failed to load D3D9 library\n");
        goto fail;
    }
    ctx->dxva2lib = LoadLibrary("dxva2.dll");
    if (!ctx->dxva2lib) {
        av_log(NULL, loglevel, "Failed to load DXVA2 library\n");
        goto fail;
    }

    createD3D = (pDirect3DCreate9 *)GetProcAddress(ctx->d3dlib, "Direct3DCreate9");
    if (!createD3D) {
        av_log(NULL, loglevel, "Failed to locate Direct3DCreate9\n");
        goto fail;
    }
    createDeviceManager = (pCreateDeviceManager9 *)GetProcAddress(ctx->dxva2lib, "DXVA2CreateDirect3DDeviceManager9");
    if (!createDeviceManager) {
        av_log(NULL, loglevel, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        goto fail;
    }

    ctx->d3d9 = createD3D(D3D_SDK_VERSION);
    if (!ctx->d3d9) {
        av_log(NULL, loglevel, "Failed to create IDirect3D object\n");
        goto fail;
    }

    if (hac->hwaccel_device) {
        adapter = atoi(hac->hwaccel_device);
        av_log(NULL, AV_LOG_INFO, "Using HWAccel device %d\n", adapter);
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
        av_log(NULL, loglevel, "Failed to create Direct3D device\n");
        goto fail;
    }

    hr = createDeviceManager(&resetToken, &ctx->d3d9devmgr);
    if (FAILED(hr)) {
        av_log(NULL, loglevel, "Failed to create Direct3D device manager\n");
        goto fail;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(ctx->d3d9devmgr, ctx->d3d9device, resetToken);
    if (FAILED(hr)) {
        av_log(NULL, loglevel, "Failed to bind Direct3D device to device manager\n");
        goto fail;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(ctx->d3d9devmgr, &ctx->deviceHandle);
    if (FAILED(hr)) {
        av_log(NULL, loglevel, "Failed to open device handle\n");
        goto fail;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(ctx->d3d9devmgr, ctx->deviceHandle, &IID_IDirectXVideoDecoderService, (void **)&ctx->decoder_service);
    if (FAILED(hr)) {
        av_log(NULL, loglevel, "Failed to create IDirectXVideoDecoderService\n");
        goto fail;
    }

    ctx->tmp_frame = av_frame_alloc();
    if (!ctx->tmp_frame)
        goto fail;

    s->hwaccel_context = av_mallocz(sizeof(struct dxva_context));
    if (!s->hwaccel_context)
        goto fail;

    return 0;
fail:
    dxva2_uninit(s);
    return AVERROR(EINVAL);
}