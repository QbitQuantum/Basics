//*********************************************************************************
void CBCGPShadowRenderer::DrawFrame (CDC* pDC, CRect rect, UINT index/* = 0*/, BYTE alphaSrc/* = 255*/)
{
    struct XHVTypes
    {
        CBCGPToolBarImages::ImageAlignHorz horz;
        CBCGPToolBarImages::ImageAlignVert vert;
    };

    XHVTypes corners[4] =
    {
        {CBCGPToolBarImages::ImageAlignHorzLeft , CBCGPToolBarImages::ImageAlignVertTop},
        {CBCGPToolBarImages::ImageAlignHorzRight, CBCGPToolBarImages::ImageAlignVertTop},
        {CBCGPToolBarImages::ImageAlignHorzLeft , CBCGPToolBarImages::ImageAlignVertBottom},
        {CBCGPToolBarImages::ImageAlignHorzRight, CBCGPToolBarImages::ImageAlignVertBottom}
    };

    XHVTypes sides[4] =
    {
        {CBCGPToolBarImages::ImageAlignHorzLeft   , CBCGPToolBarImages::ImageAlignVertStretch},
        {CBCGPToolBarImages::ImageAlignHorzRight  , CBCGPToolBarImages::ImageAlignVertStretch},
        {CBCGPToolBarImages::ImageAlignHorzStretch, CBCGPToolBarImages::ImageAlignVertTop},
        {CBCGPToolBarImages::ImageAlignHorzStretch, CBCGPToolBarImages::ImageAlignVertBottom}
    };

    CRect rectImage (m_Params.m_rectImage);
    int ind = index;
    if (m_Bitmap.GetCount () == 1)
    {
        rectImage.OffsetRect (0, m_Params.m_rectImage.Size ().cy * ind);
        ind = 0;
    }

    CRect rt  (rect);
    CRect rectCorners (m_Params.m_rectCorners);
    CRect rectSides   (m_Params.m_rectSides);

    rt.left   += rectCorners.left;
    rt.top    += rectCorners.top;
    rt.right  -= rectCorners.right;
    rt.bottom -= rectCorners.bottom;

    BOOL bRTL = CBCGPToolBarImages::IsRTL ();

    if (rt.Width () > 0 || rt.Height () > 0)
    {
        if (rt.Height () > 0)
        {
            if (bRTL && !m_bMirror)
            {
                if (rectSides.left > 0)
                {
                    CRect r (rt);
                    r.left  = rect.left;
                    r.right = r.left + rectSides.left;

                    CRect rectPart (rectImage.left,
                                    rectImage.top + rectCorners.top, rectImage.left + rectSides.left, rectImage.bottom - rectCorners.bottom);

                    m_Bitmap.DrawEx (pDC, r, ind, sides[0].horz, sides[0].vert, rectPart, alphaSrc);
                }
            }
            else
            {
                if (rectSides.right > 0)
                {
                    CRect r (rt);
                    r.right = rect.right;
                    r.left  = r.right - rectSides.right;

                    CRect rectPart;
                    if (m_bMirror)
                    {
                        rectPart = CRect (rectImage.left,
                                          rectImage.top + rectCorners.top, rectImage.left + rectSides.right, rectImage.bottom - rectCorners.bottom);
                    }
                    else
                    {
                        rectPart = CRect (rectImage.right - rectSides.right,
                                          rectImage.top + rectCorners.top, rectImage.right, rectImage.bottom - rectCorners.bottom);
                    }

                    m_Bitmap.DrawEx (pDC, r, ind, sides[1].horz, sides[1].vert, rectPart, alphaSrc);
                }
            }
        }

        if (rt.Width () > 0)
        {
            if (rectSides.bottom > 0)
            {
                CRect r (rt);
                r.bottom = rect.bottom;
                r.top    = r.bottom - rectSides.bottom;

                CRect rectPart  (rectImage.left + rectCorners.left,
                                 rectImage.bottom - rectSides.bottom, rectImage.right - rectCorners.right, rectImage.bottom);

                m_Bitmap.DrawEx (pDC, r, ind, sides[3].horz, sides[3].vert, rectPart, alphaSrc);
            }
        }

        if (bRTL && !m_bMirror)
        {
            if (rectCorners.left > 0 && rectCorners.top > 0)
            {
                CRect rectPart (CPoint (rectImage.left, rectImage.top),
                                CSize (rectCorners.left, rectCorners.top));

                m_Bitmap.DrawEx (pDC, rect, ind, corners[0].horz, corners[0].vert, rectPart, alphaSrc);
            }

            if (rectCorners.left > 0 && rectCorners.bottom > 0)
            {
                CRect rectPart = CRect (CPoint (rectImage.left, rectImage.bottom - rectCorners.bottom),
                                        CSize (rectCorners.left, rectCorners.bottom));

                m_Bitmap.DrawEx (pDC, rect, ind, corners[2].horz, corners[2].vert, rectPart, alphaSrc);
            }

            if (rectCorners.right > 0 && rectCorners.bottom > 0)
            {
                CRect rectPart (CPoint (rectImage.right - rectCorners.right, rectImage.bottom - rectCorners.bottom),
                                CSize (rectCorners.right, rectCorners.bottom));

                m_Bitmap.DrawEx (pDC, rect, ind, corners[3].horz, corners[3].vert, rectPart, alphaSrc);
            }
        }
        else
        {
            if (rectCorners.right > 0 && rectCorners.top > 0)
            {
                CRect rectPart;
                if (m_bMirror)
                {
                    rectPart = CRect (CPoint (rectImage.left, rectImage.top),
                                      CSize (rectCorners.right, rectCorners.top));
                }
                else
                {
                    rectPart = CRect (CPoint (rectImage.right - rectCorners.right, rectImage.top),
                                      CSize (rectCorners.right, rectCorners.top));
                }

                m_Bitmap.DrawEx (pDC, rect, ind, corners[1].horz, corners[1].vert, rectPart, alphaSrc);
            }

            if (rectCorners.left > 0 && rectCorners.bottom > 0)
            {
                CRect rectPart;
                if (m_bMirror)
                {
                    rectPart = CRect (CPoint (rectImage.right - rectCorners.left, rectImage.bottom - rectCorners.bottom),
                                      CSize (rectCorners.left, rectCorners.bottom));
                }
                else
                {
                    rectPart = CRect (CPoint (rectImage.left, rectImage.bottom - rectCorners.bottom),
                                      CSize (rectCorners.left, rectCorners.bottom));
                }

                m_Bitmap.DrawEx (pDC, rect, ind, corners[2].horz, corners[2].vert, rectPart, alphaSrc);
            }

            if (rectCorners.right > 0 && rectCorners.bottom > 0)
            {
                CRect rectPart;
                if (m_bMirror)
                {
                    rectPart = CRect (CPoint (rectImage.left, rectImage.bottom - rectCorners.bottom),
                                      CSize (rectCorners.right, rectCorners.bottom));
                }
                else
                {
                    rectPart = CRect (CPoint (rectImage.right - rectCorners.right, rectImage.bottom - rectCorners.bottom),
                                      CSize (rectCorners.right, rectCorners.bottom));
                }

                m_Bitmap.DrawEx (pDC, rect, ind, corners[3].horz, corners[3].vert, rectPart, alphaSrc);
            }
        }
    }
}