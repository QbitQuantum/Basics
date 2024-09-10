CPMenuSpecial::CPMenuSpecial ()
{
    DWORD dw;

    // Get normal system colors for these to start
    m_lColorText =    GetSysColor (COLOR_MENUTEXT);
    m_lColorBk =      GetSysColor (COLOR_MENU);
    m_lColorHiText =  GetSysColor (COLOR_HIGHLIGHTTEXT);
    m_lColorHiBk =    GetSysColor (COLOR_HIGHLIGHT);
    m_lColorGrayed =  GetSysColor (COLOR_GRAYTEXT);

    dw = GetMenuCheckMarkDimensions ();

    m_nDefaultCheckHeight = HIWORD(dw);
    m_nWindowsCheckWidth = m_nDefaultCheckWidth = LOWORD(dw);

    m_bmDefaultCheck.LoadOEMBitmap (OBM_CHECK);

    m_nDefaultTextHeight = GetSystemMetrics (SM_CYMENU);

    m_hPalette = NULL;

    //m_hFontHandle = NULL;
}