void CLCDBitmap::OnDraw(CLCDGfxBase &rGfx)
{
    if(m_hBitmap)
    {
        HDC hCompatibleDC = CreateCompatibleDC(rGfx.GetHDC());
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, m_hBitmap);
        
        // If monochrome output, don't even bother with alpha blend
        if (LGLCD_BMP_FORMAT_160x43x1 == rGfx.GetLCDScreen()->hdr.Format)
        {
            BitBlt(rGfx.GetHDC(), 0, 0, m_sizeLogical.cx, m_sizeLogical.cy, hCompatibleDC, 0, 0, m_dwROP);
        }
        else
        {
            if(0.001f > fabs(1.0f - m_fZoom))
            {
                BOOL b = FALSE;
                if(m_bAlpha)
                {
                    BLENDFUNCTION opblender = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
                    b = AlphaBlend(rGfx.GetHDC(), 0, 0, m_sizeLogical.cx, m_sizeLogical.cy, hCompatibleDC, 0, 0, m_sizeLogical.cx, m_sizeLogical.cy, opblender);
                }
                else
                {
                    BitBlt(rGfx.GetHDC(), 0, 0, m_sizeLogical.cx, m_sizeLogical.cy, hCompatibleDC, 0, 0, m_dwROP);
                }
            }
            else
            {
                if(m_bAlpha)
                {
                    BLENDFUNCTION opblender = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
                    AlphaBlend(rGfx.GetHDC(), 0, 0, (int)(m_fZoom* m_sizeLogical.cx), (int)(m_fZoom*m_sizeLogical.cy), hCompatibleDC, 0, 0, m_sizeLogical.cx, m_sizeLogical.cy, opblender);
                }
                else
                {
                    BLENDFUNCTION opblender = {AC_SRC_OVER, 0, 255, 0};
                    AlphaBlend(rGfx.GetHDC(), 0, 0, (int)(m_fZoom* m_sizeLogical.cx), (int)(m_fZoom*m_sizeLogical.cy), hCompatibleDC, 0, 0, m_sizeLogical.cx, m_sizeLogical.cy, opblender);
                }
            }
        }
        
        // restores
        SelectObject(hCompatibleDC, hOldBitmap);
        DeleteDC(hCompatibleDC);
    }
}