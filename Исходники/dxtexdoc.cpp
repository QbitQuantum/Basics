void CDxtexDoc::GenerateMipMaps() 
{
    LONG lwTempH;
    LONG lwTempW;
    LONG lwPowsW;
    LONG lwPowsH;
    LPDIRECT3DTEXTURE9 pddsNew = NULL;
    D3DFORMAT fmt;
    HRESULT hr;
    LPDIRECT3DDEVICE9 pd3ddev = PDxtexApp()->Pd3ddev();
    LPDIRECT3DTEXTURE9 pmiptex = NULL;
    LPDIRECT3DCUBETEXTURE9 pcubetex = NULL;
    LPDIRECT3DVOLUMETEXTURE9 pvoltex = NULL;
    LPDIRECT3DTEXTURE9 pmiptexNew = NULL;
    LPDIRECT3DCUBETEXTURE9 pcubetexNew = NULL;
    LPDIRECT3DVOLUMETEXTURE9 pvoltexNew = NULL;
    LPDIRECT3DSURFACE9 psurfSrc;
    LPDIRECT3DSURFACE9 psurfDest;
    LPDIRECT3DVOLUME9 pvolSrc;
    LPDIRECT3DVOLUME9 pvolDest;

    if (IsVolumeMap())
        pvoltex = (LPDIRECT3DVOLUMETEXTURE9)m_ptexOrig;
    else if (IsCubeMap())
        pcubetex = (LPDIRECT3DCUBETEXTURE9)m_ptexOrig;
    else
        pmiptex = (LPDIRECT3DTEXTURE9)m_ptexOrig;

    if (pvoltex != NULL)
    {
        D3DVOLUME_DESC vd;
        pvoltex->GetLevelDesc(0, &vd);
        fmt = vd.Format;
    }
    else if (pcubetex != NULL)
    {
        D3DSURFACE_DESC sd;
        pcubetex->GetLevelDesc(0, &sd);
        fmt = sd.Format;
    }
    else
    {
        D3DSURFACE_DESC sd;
        pmiptex->GetLevelDesc(0, &sd);
        fmt = sd.Format;
    }

    lwTempW = m_dwWidth;
    lwTempH = m_dwHeight;
    lwPowsW = 0;
    lwPowsH = 0;
    while (lwTempW > 0)
    {
        lwPowsW++;
        lwTempW = lwTempW / 2;
    }
    while (lwTempH > 0)
    {
        lwPowsH++;
        lwTempH = lwTempH / 2;
    }
    m_numMips = lwPowsW > lwPowsH ? lwPowsW : lwPowsH;

    // Create destination mipmap surface - same format as source
    if (pvoltex != NULL)
    {
        if (FAILED(hr = pd3ddev->CreateVolumeTexture(m_dwWidth, m_dwHeight, m_dwDepth, 
            m_numMips, 0, fmt, D3DPOOL_SYSTEMMEM, &pvoltexNew, NULL)))
        {
            goto LFail;
        }
        hr = pvoltex->GetVolumeLevel(0, &pvolSrc);
        hr = pvoltexNew->GetVolumeLevel(0, &pvolDest);
        hr = D3DXLoadVolumeFromVolume(pvolDest, NULL, NULL, pvolSrc, NULL, NULL, 
            D3DX_DEFAULT, 0);
        ReleasePpo(&pvolSrc);
        ReleasePpo(&pvolDest);
        hr = D3DXFilterVolumeTexture(pvoltexNew, NULL, 0, D3DX_DEFAULT);
    }
    else if (pmiptex != NULL)
    {
        if (FAILED(hr = pd3ddev->CreateTexture(m_dwWidth, m_dwHeight, m_numMips, 
             0, fmt, D3DPOOL_MANAGED, &pmiptexNew, NULL)))
        {
            goto LFail;
        }
        hr = pmiptex->GetSurfaceLevel(0, &psurfSrc);
        hr = pmiptexNew->GetSurfaceLevel(0, &psurfDest);
        hr = D3DXLoadSurfaceFromSurface(psurfDest, NULL, NULL, psurfSrc, NULL, NULL, 
            D3DX_DEFAULT, 0);
        ReleasePpo(&psurfSrc);
        ReleasePpo(&psurfDest);
        hr = D3DXFilterTexture(pmiptexNew, NULL, 0, D3DX_DEFAULT);
    }
    else
    {
        if (FAILED(hr = pd3ddev->CreateCubeTexture(m_dwWidth, m_numMips, 
             0, fmt, D3DPOOL_MANAGED, &pcubetexNew, NULL)))
        {
            goto LFail;
        }
        hr = pcubetex->GetCubeMapSurface(D3DCUBEMAP_FACE_POSITIVE_X, 0, &psurfSrc);
        hr = pcubetexNew->GetCubeMapSurface(D3DCUBEMAP_FACE_POSITIVE_X, 0, &psurfDest);
        hr = D3DXLoadSurfaceFromSurface(psurfDest, NULL, NULL, psurfSrc, NULL, NULL, 
            D3DX_DEFAULT, 0);
        ReleasePpo(&psurfSrc);
        ReleasePpo(&psurfDest);
        hr = pcubetex->GetCubeMapSurface(D3DCUBEMAP_FACE_NEGATIVE_X, 0, &psurfSrc);
        hr = pcubetexNew->GetCubeMapSurface(D3DCUBEMAP_FACE_NEGATIVE_X, 0, &psurfDest);
        hr = D3DXLoadSurfaceFromSurface(psurfDest, NULL, NULL, psurfSrc, NULL, NULL, 
            D3DX_DEFAULT, 0);
        ReleasePpo(&psurfSrc);
        ReleasePpo(&psurfDest);
        hr = pcubetex->GetCubeMapSurface(D3DCUBEMAP_FACE_POSITIVE_Y, 0, &psurfSrc);
        hr = pcubetexNew->GetCubeMapSurface(D3DCUBEMAP_FACE_POSITIVE_Y, 0, &psurfDest);
        hr = D3DXLoadSurfaceFromSurface(psurfDest, NULL, NULL, psurfSrc, NULL, NULL, 
            D3DX_DEFAULT, 0);
        ReleasePpo(&psurfSrc);
        ReleasePpo(&psurfDest);
        hr = pcubetex->GetCubeMapSurface(D3DCUBEMAP_FACE_NEGATIVE_Y, 0, &psurfSrc);
        hr = pcubetexNew->GetCubeMapSurface(D3DCUBEMAP_FACE_NEGATIVE_Y, 0, &psurfDest);
        hr = D3DXLoadSurfaceFromSurface(psurfDest, NULL, NULL, psurfSrc, NULL, NULL, 
            D3DX_DEFAULT, 0);
        ReleasePpo(&psurfSrc);
        ReleasePpo(&psurfDest);
        hr = pcubetex->GetCubeMapSurface(D3DCUBEMAP_FACE_POSITIVE_Z, 0, &psurfSrc);
        hr = pcubetexNew->GetCubeMapSurface(D3DCUBEMAP_FACE_POSITIVE_Z, 0, &psurfDest);
        hr = D3DXLoadSurfaceFromSurface(psurfDest, NULL, NULL, psurfSrc, NULL, NULL, 
            D3DX_DEFAULT, 0);
        ReleasePpo(&psurfSrc);
        ReleasePpo(&psurfDest);
        hr = pcubetex->GetCubeMapSurface(D3DCUBEMAP_FACE_NEGATIVE_Z, 0, &psurfSrc);
        hr = pcubetexNew->GetCubeMapSurface(D3DCUBEMAP_FACE_NEGATIVE_Z, 0, &psurfDest);
        hr = D3DXLoadSurfaceFromSurface(psurfDest, NULL, NULL, psurfSrc, NULL, NULL, 
            D3DX_DEFAULT, 0);
        ReleasePpo(&psurfSrc);
        ReleasePpo(&psurfDest);
        hr = D3DXFilterCubeTexture(pcubetexNew, NULL, 0, D3DX_DEFAULT);
    }

    ReleasePpo(&m_ptexOrig);
    if (pvoltexNew != NULL)
        m_ptexOrig = pvoltexNew;
    else if (pcubetexNew != NULL)
        m_ptexOrig = pcubetexNew;
    else
        m_ptexOrig = pmiptexNew;

    if (m_ptexNew != NULL)
    {
        // Rather than filtering down the (probably-compressed) m_ptexNew 
        // top level, compress each mip level from the (probably-uncompressed)
        // m_ptexOrig levels.
        if (pvoltexNew != NULL)
        {
            D3DVOLUME_DESC vd;
            ((LPDIRECT3DVOLUMETEXTURE9)m_ptexNew)->GetLevelDesc(0, &vd);
            fmt = vd.Format;
        }
        else if (pcubetexNew != NULL)
        {
            D3DSURFACE_DESC sd;
            ((LPDIRECT3DTEXTURE9)m_ptexNew)->GetLevelDesc(0, &sd);
            fmt = sd.Format;
        }
        else
        {
            D3DSURFACE_DESC sd;
            ((LPDIRECT3DCUBETEXTURE9)m_ptexNew)->GetLevelDesc(0, &sd);
            fmt = sd.Format;
        }
        Compress(fmt, FALSE);
    }

    m_bTitleModsChanged = TRUE; // Generate title bar update
    UpdateAllViews(NULL, 1); // tell CView to pick up new surface pointers
    SetModifiedFlag();
    return;

LFail:
    ReleasePpo(&pddsNew);
}