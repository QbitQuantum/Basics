HRESULT CD3DUtils::ProgressiveBlt(IDirect3DSurface9 *pSurfIn, IDirect3DSurface9 *pSurfOut)
{
    if (!m_pVPDevice || !pSurfIn || !pSurfOut) return E_FAIL;

    DXVA2_VideoProcessBltParams blt = {0};
    DXVA2_VideoSample samples[2] = {0};
    RECT SrcRect = {0};
    RECT DstRect = {0};
    D3DSURFACE_DESC SrcDesc, DstDesc;
    IDirect3DSurface9 *pSrc = pSurfIn;
    IDirect3DSurface9 *pDst = pSurfOut;
    REFERENCE_TIME rtStart = 0;
    REFERENCE_TIME rtStop = 1;

    pSrc->GetDesc(&SrcDesc);
    pDst->GetDesc(&DstDesc);

    SrcRect.right = SrcDesc.Width;
    SrcRect.bottom = SrcDesc.Height;
    DstRect.right = DstDesc.Width;
    DstRect.bottom = DstDesc.Height;

    FillDefaultBltInfo(blt);

    blt.TargetFrame = rtStart;
    blt.TargetRect  = DstRect;

    // DXVA2_VideoProcess_Constriction
    blt.ConstrictionSize.cx = blt.TargetRect.right - blt.TargetRect.left;
    blt.ConstrictionSize.cy = blt.TargetRect.bottom - blt.TargetRect.top;

    //
    // Initialize main stream video sample.
    //
    samples[0].Start = rtStart;
    samples[0].End   = rtStop;

    FillDefaultDXVAFormat(samples[0].SampleFormat, DXVA2_SampleProgressiveFrame);

    samples[0].SrcSurface = pSrc;
    samples[0].SrcRect = SrcRect;
    samples[0].DstRect = DstRect;

    samples[0].PlanarAlpha = DXVA2_Fixed32OpaqueAlpha();

    HRESULT hr = m_pVPDevice->VideoProcessBlt(pDst, &blt, samples, 1, NULL);

    return hr;
}