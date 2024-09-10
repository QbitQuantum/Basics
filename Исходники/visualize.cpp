HRESULT VisualizeFacetracker(IFTImage* pColorImg, IFTResult* pAAMRlt, UINT32 color)
{
    if (!pColorImg->GetBuffer() || !pAAMRlt)
    {
        return E_POINTER;
    }

    // Insufficient data points to render face data
    FT_VECTOR2D* pPts2D;
    UINT pts2DCount;
    HRESULT hr = pAAMRlt->Get2DShapePoints(&pPts2D, &pts2DCount);
    if (FAILED(hr))
    {
        return hr;
    }

    if (pts2DCount < 86)
    {
        return E_INVALIDARG;
    }


    POINT* pFaceModel2DPoint = reinterpret_cast<POINT*>(_malloca(sizeof(POINT) * pts2DCount));
    if (!pFaceModel2DPoint)
    {
        return E_OUTOFMEMORY;
    }


    for (UINT ipt = 0; ipt < pts2DCount; ++ipt)
    {
        pFaceModel2DPoint[ipt].x = LONG(pPts2D[ipt].x + 0.5f);
        pFaceModel2DPoint[ipt].y = LONG(pPts2D[ipt].y + 0.5f);
    }

    for (UINT ipt = 0; ipt < 8; ++ipt)
    {
        POINT ptStart = pFaceModel2DPoint[ipt];
        POINT ptEnd = pFaceModel2DPoint[(ipt+1)%8];
        pColorImg->DrawLine(ptStart, ptEnd, color, 1);
    }

    for (UINT ipt = 8; ipt < 16; ++ipt)
    {
        POINT ptStart = pFaceModel2DPoint[ipt];
        POINT ptEnd = pFaceModel2DPoint[(ipt-8+1)%8+8];
        pColorImg->DrawLine(ptStart, ptEnd, color, 1);
    }

    for (UINT ipt = 16; ipt < 26; ++ipt)
    {
        POINT ptStart = pFaceModel2DPoint[ipt];
        POINT ptEnd = pFaceModel2DPoint[(ipt-16+1)%10+16];
        pColorImg->DrawLine(ptStart, ptEnd, color, 1);
    }

    for (UINT ipt = 26; ipt < 36; ++ipt)
    {
        POINT ptStart = pFaceModel2DPoint[ipt];
        POINT ptEnd = pFaceModel2DPoint[(ipt-26+1)%10+26];
        pColorImg->DrawLine(ptStart, ptEnd, color, 1);
    }

    for (UINT ipt = 36; ipt < 47; ++ipt)
    {
        POINT ptStart = pFaceModel2DPoint[ipt];
        POINT ptEnd = pFaceModel2DPoint[ipt+1];
        pColorImg->DrawLine(ptStart, ptEnd, color, 1);
    }

    for (UINT ipt = 48; ipt < 60; ++ipt)
    {
        POINT ptStart = pFaceModel2DPoint[ipt];
        POINT ptEnd = pFaceModel2DPoint[(ipt-48+1)%12+48];
        pColorImg->DrawLine(ptStart, ptEnd, color, 1);
    }

    for (UINT ipt = 60; ipt < 68; ++ipt)
    {
        POINT ptStart = pFaceModel2DPoint[ipt];
        POINT ptEnd = pFaceModel2DPoint[(ipt-60+1)%8+60];
        pColorImg->DrawLine(ptStart, ptEnd, color, 1);
    }

    for (UINT ipt = 68; ipt < 86; ++ipt)
    {
        POINT ptStart = pFaceModel2DPoint[ipt];
        POINT ptEnd = pFaceModel2DPoint[ipt+1];
        pColorImg->DrawLine(ptStart, ptEnd, color, 1);
    }
    _freea(pFaceModel2DPoint);

    return hr;
}