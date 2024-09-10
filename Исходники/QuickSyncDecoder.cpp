CQuickSyncDecoder::CQuickSyncDecoder(const CQsConfig& cfg, mfxStatus& sts) :
    m_mfxVideoSession(NULL),
    m_mfxImpl(MFX_IMPL_UNSUPPORTED),
    m_Config(cfg),
    m_pmfxDEC(0),
    m_pVideoParams(0),
    m_pFrameAllocator(NULL),
    m_pFrameSurfaces(NULL),
    m_nRequiredFramesNum(0),
    m_nAuxFrameCount(0),
    m_pRendererD3dDeviceManager(NULL),
    m_HwDevice(NULL)
{
    MSDK_ZERO_VAR(m_AllocResponse);

    m_ApiVersion.Major = MIN_REQUIRED_API_VER_MAJOR;
    m_ApiVersion.Minor = MIN_REQUIRED_API_VER_MINOR;
    mfxIMPL impl = MFX_IMPL_AUTO_ANY;

    // Uncomment for SW emulation (Media SDK software DLL must be present)
    //impl = MFX_IMPL_SOFTWARE;

    int d3d9IntelAdapter = 0;
    if (impl != MFX_IMPL_SOFTWARE)
    {
        d3d9IntelAdapter = GetIntelAdapterIdD3D9(NULL);

        // select d3d9 or d3d11 HW implementation base on config and GPU/OS capabilities
        if (d3d9IntelAdapter >= 0 && !m_Config.bDefaultToD3D11)
        {
            impl |= MFX_IMPL_VIA_D3D9;
        }
        else if (m_Config.bEnableD3D11)
        {
            impl |= MFX_IMPL_VIA_D3D11;
        }
        else
        {
            MSDK_TRACE("QsDecoder: Can't create HW decoder, the iGPU is not connected to a screen!\n");
            sts = MFX_ERR_UNSUPPORTED;
            return;
        }
    }

    sts = InitSession(impl);
    if (MSDK_SUCCEEDED(sts) && !m_Config.bEnableD3D11 && 0 > d3d9IntelAdapter)
    {
        MSDK_TRACE("QsDecoder: can't create HW decoder, the iGPU is not connected to a screen!\n");
        sts = MFX_ERR_UNSUPPORTED;
    }
}