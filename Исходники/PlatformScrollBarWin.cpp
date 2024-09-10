void PlatformScrollbar::paintTrack(GraphicsContext* context, const IntRect& rect, bool start, const IntRect& damageRect) const
{
    if (!damageRect.intersects(rect))
        return;

    int part;
    if (m_orientation == HorizontalScrollbar)
        part = start ? SP_TRACKSTARTHOR : SP_TRACKENDHOR;
    else
        part = start ? SP_TRACKSTARTVERT : SP_TRACKENDVERT;

    int state;
    if (!isEnabled())
        state = TS_DISABLED;
    else if ((m_hoveredPart == BackTrackPart && start) ||
             (m_hoveredPart == ForwardTrackPart && !start))
        state = (m_pressedPart == m_hoveredPart ? TS_ACTIVE : TS_HOVER);
    else
        state = TS_NORMAL;

    bool alphaBlend = false;
    if (scrollbarTheme)
        alphaBlend = IsThemeBackgroundPartiallyTransparent(scrollbarTheme, part, state);
    HDC hdc = context->getWindowsContext(rect, alphaBlend);
    RECT themeRect(rect);
    if (scrollbarTheme)
        DrawThemeBackground(scrollbarTheme, hdc, part, state, &themeRect, 0);
    else {
        DWORD color3DFace = ::GetSysColor(COLOR_3DFACE);
        DWORD colorScrollbar = ::GetSysColor(COLOR_SCROLLBAR);
        DWORD colorWindow = ::GetSysColor(COLOR_WINDOW);
        if ((color3DFace != colorScrollbar) && (colorWindow != colorScrollbar))
            ::FillRect(hdc, &themeRect, HBRUSH(COLOR_SCROLLBAR+1));
        else {
            static WORD patternBits[8] = { 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 };
            HBITMAP patternBitmap = ::CreateBitmap(8, 8, 1, 1, patternBits);
            HBRUSH brush = ::CreatePatternBrush(patternBitmap);
            SaveDC(hdc);
            ::SetTextColor(hdc, ::GetSysColor(COLOR_3DHILIGHT));
            ::SetBkColor(hdc, ::GetSysColor(COLOR_3DFACE));
            ::SetBrushOrgEx(hdc, rect.x(), rect.y(), NULL);
            ::SelectObject(hdc, brush);
            ::FillRect(hdc, &themeRect, brush);
            ::RestoreDC(hdc, -1);
            ::DeleteObject(brush);  
            ::DeleteObject(patternBitmap);
        }
    }
    context->releaseWindowsContext(hdc, rect, alphaBlend);
}