HRESULT STDMETHODCALLTYPE OBGEDirect3D9::CreateDevice(
    UINT Adapter,
    D3DDEVTYPE DeviceType,
    HWND hFocusWindow,
    DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS *pPresentationParameters,
    IDirect3DDevice9 **ppReturnedDeviceInterface) {

    HRESULT hr;
    D3DFORMAT asbak;

#if 0
    /* check if the format isn't possibly really available */
    if (MultiSample.Get() && (pPresentationParameters->MultiSampleType == D3DMULTISAMPLE_NONE)) {
        D3DFORMAT frmt = D3DFMT_UNKNOWN;
        if (IsHDR())
            frmt = D3DFMT_A16B16G16R16F;
        else
            frmt = D3DFMT_A8R8G8B8;

        hr = m_d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, frmt, FALSE, (D3DMULTISAMPLE_TYPE)MultiSample.Get(), NULL);
        if (SUCCEEDED(hr)) {
            pPresentationParameters->MultiSampleType = (D3DMULTISAMPLE_TYPE)MultiSample.Get();
            pPresentationParameters->MultiSampleQuality = 0;
            pPresentationParameters->Flags &= ~D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
        }
    }
#endif

    /* replace whatever by INTZ for example if possible */
    pPresentationParameters->AutoDepthStencilFormat =
        GetDepthBufferFormat(m_d3d, asbak =
                                 pPresentationParameters->AutoDepthStencilFormat,
                             pPresentationParameters->MultiSampleType);

    /* try -> fail -> restore */
    hr = m_d3d->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags,
                             pPresentationParameters, ppReturnedDeviceInterface);
    if (!SUCCEEDED(hr)) {
        pPresentationParameters->AutoDepthStencilFormat = asbak;
        hr = m_d3d->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags,
                                 pPresentationParameters, ppReturnedDeviceInterface);
    }

    _MESSAGE("OD3D9: Device queried from 0x%08x", _ReturnAddress());
    _MESSAGE("OD3D9: Queue %d, MS-type %d, MS-quality %d",
             pPresentationParameters->BackBufferCount,
             pPresentationParameters->MultiSampleType,
             pPresentationParameters->MultiSampleQuality);

    // Return our device
    if (SUCCEEDED(hr))
        *ppReturnedDeviceInterface = new OBGEDirect3DDevice9(this, *ppReturnedDeviceInterface);

    return hr;
}