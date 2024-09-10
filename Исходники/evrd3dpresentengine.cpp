HRESULT D3DPresentEngine::getSwapChainPresentParameters(IMFMediaType *type, D3DPRESENT_PARAMETERS* pp)
{
    ZeroMemory(pp, sizeof(D3DPRESENT_PARAMETERS));

    // Get some information about the video format.

    UINT32 width = 0, height = 0;

    HRESULT hr = MFGetAttributeSize(type, MF_MT_FRAME_SIZE, &width, &height);
    if (FAILED(hr))
        return hr;

    DWORD d3dFormat = 0;

    hr = qt_wmf_getFourCC(type, &d3dFormat);
    if (FAILED(hr))
        return hr;

    ZeroMemory(pp, sizeof(D3DPRESENT_PARAMETERS));
    pp->BackBufferWidth = width;
    pp->BackBufferHeight = height;
    pp->Windowed = TRUE;
    pp->SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp->BackBufferFormat = (D3DFORMAT)d3dFormat;
    pp->hDeviceWindow = ::GetShellWindow();
    pp->Flags = D3DPRESENTFLAG_VIDEO;
    pp->PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

    D3DDEVICE_CREATION_PARAMETERS params;
    hr = m_device->GetCreationParameters(&params);
    if (FAILED(hr))
        return hr;

    if (params.DeviceType != D3DDEVTYPE_HAL)
        pp->Flags |= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    return S_OK;
}