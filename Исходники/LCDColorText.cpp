void CLCDColorText::OnDraw(CLCDGfxBase &rGfx)
{
    if(GetBackgroundMode() == OPAQUE)
    {
        HBRUSH backbrush = CreateSolidBrush(m_backColor);

        // clear the clipped area
        RECT rcClp = { 0, 0, m_Size.cx, m_Size.cy };
        FillRect(rGfx.GetHDC(), &rcClp, backbrush);

        // clear the logical area
        RECT rcLog = { 0, 0, m_sizeLogical.cx, m_sizeLogical.cy };
        FillRect(rGfx.GetHDC(), &rcLog, backbrush);

        DeleteObject(backbrush);
    }

    if(m_nTextLength)
    {

        // map mode text, with transparency
        int nOldMapMode = SetMapMode(rGfx.GetHDC(), MM_TEXT);

        int nOldBkMode = SetBkMode(rGfx.GetHDC(), TRANSPARENT);

        // select current font
        HFONT hOldFont = (HFONT)SelectObject(rGfx.GetHDC(), m_hFont);

        // select color
        COLORREF crOldTextColor = SetTextColor(rGfx.GetHDC(), m_crForegroundColor);

        if (m_bRecalcExtent)
        {
            int nTextFormat;

            RECT rExtent;
            // calculate vertical extent with word wrap
            nTextFormat = (m_nTextFormat | DT_WORDBREAK | DT_CALCRECT);
            rExtent.left = rExtent.top = 0;
            rExtent.right = GetWidth();
            rExtent.bottom = GetHeight();
            DrawTextEx(rGfx.GetHDC(), (LPTSTR)m_sText.c_str(), static_cast<int>(m_nTextLength), &rExtent, nTextFormat, &m_dtp);
            m_sizeVExtent.cx = rExtent.right;
            m_sizeVExtent.cy = rExtent.bottom;

            // calculate horizontal extent w/o word wrap
            nTextFormat = (m_nTextFormat | DT_CALCRECT);
            rExtent.left = rExtent.top = 0;
            rExtent.right = GetWidth();
            rExtent.bottom = GetHeight();
            DrawTextEx(rGfx.GetHDC(), (LPTSTR)m_sText.c_str(), static_cast<int>(m_nTextLength), &rExtent, nTextFormat, &m_dtp);
            m_sizeHExtent.cx = rExtent.right;
            m_sizeHExtent.cy = rExtent.bottom;

            m_bRecalcExtent = FALSE;

            //For scrolling
            m_PixelLength = m_sizeHExtent.cx;
            m_StartX = 0;

            if( m_bAutoScroll )
            {
                if( m_PixelLength > GetWidth() )
                {
                    m_ScrollRate = -1*GetHeight();
                }
                else
                {
                    m_ScrollRate = 0;
                }
            }

            if( m_ScrollRate > 0 )
            {
                if( GetWidth() > m_PixelLength + m_ScrollBuffer )
                {
                    m_JumpDistance = -1 * GetWidth();
                }
                else
                {
                    m_JumpDistance = -1 * (m_PixelLength + m_ScrollBuffer);
                }
            }
            else if( m_ScrollRate < 0 )
            {
                if( GetWidth() > m_PixelLength + m_ScrollBuffer )
                {
                    m_JumpDistance = GetWidth();
                }
                else
                {
                    m_JumpDistance = m_PixelLength + m_ScrollBuffer;
                }
            }

            m_LoopX = m_JumpDistance;
        }

        if( IsVisible() )
        {
            if( m_ScrollRate == 0 )
            {
                RECT rBoundary = { 0, 0, 0 + GetLogicalSize().cx, 0 + GetLogicalSize().cy }; 
                DrawTextEx(rGfx.GetHDC(), (LPTSTR)m_sText.c_str(), static_cast<int>(m_nTextLength), &rBoundary, m_nTextFormat, &m_dtp);
            }
            else
            {
                RECT rBoundaryFirst = { m_StartX, 0, 0 + GetLogicalSize().cx, 0 + GetLogicalSize().cy }; 
                RECT rBoundarySecond = { m_LoopX, 0, 0 + GetLogicalSize().cx, 0 + GetLogicalSize().cy }; 

                DrawTextEx(rGfx.GetHDC(), (LPTSTR)m_sText.c_str(), static_cast<int>(m_nTextLength), 
                    &rBoundaryFirst, m_nTextFormat, &m_dtp);
                DrawTextEx(rGfx.GetHDC(), (LPTSTR)m_sText.c_str(), static_cast<int>(m_nTextLength), 
                    &rBoundarySecond, m_nTextFormat, &m_dtp);
            }
        }

        // restores
        SetMapMode(rGfx.GetHDC(), nOldMapMode);
        SetTextColor(rGfx.GetHDC(), crOldTextColor);
        SetBkMode(rGfx.GetHDC(), nOldBkMode);
        SelectObject(rGfx.GetHDC(), hOldFont);
    }
}