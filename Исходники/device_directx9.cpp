mfxStatus CD3D9Device::Init(
    mfxHDL hWindow,
    mfxU16 nViews,
    mfxU32 nAdapterNum)
{
    mfxStatus sts = MFX_ERR_NONE;

    if (2 < nViews)
        return MFX_ERR_UNSUPPORTED;

    m_nViews = nViews;

    HRESULT hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_pD3D9);
    if (!m_pD3D9 || FAILED(hr))
        return MFX_ERR_DEVICE_FAILED;

    ZeroMemory(&m_D3DPP, sizeof(m_D3DPP));
    sts = FillD3DPP(hWindow, nViews, m_D3DPP);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    hr = m_pD3D9->CreateDeviceEx(
        nAdapterNum,
        D3DDEVTYPE_HAL,
        (HWND)hWindow,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
        &m_D3DPP,
        NULL,
        &m_pD3DD9);
    if (FAILED(hr))
        return MFX_ERR_NULL_PTR;

    if(hWindow)
    {
        hr = m_pD3DD9->ResetEx(&m_D3DPP, NULL);
        if (FAILED(hr))
            return MFX_ERR_UNDEFINED_BEHAVIOR;
        hr = m_pD3DD9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        if (FAILED(hr))
            return MFX_ERR_UNDEFINED_BEHAVIOR;
    }
    UINT resetToken = 0;

    hr = DXVA2CreateDirect3DDeviceManager9(&resetToken, &m_pDeviceManager9);
    if (FAILED(hr))
        return MFX_ERR_NULL_PTR;

    hr = m_pDeviceManager9->ResetDevice(m_pD3DD9, resetToken);
    if (FAILED(hr))
        return MFX_ERR_UNDEFINED_BEHAVIOR;

    m_resetToken = resetToken;

    return sts;
}