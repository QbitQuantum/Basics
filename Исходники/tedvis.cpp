BOOL CVisualDrawContext::SelectSmallFont() 
{
    CAtlString strFontSize = LoadAtlString(IDS_FONT_SIZE_12);
    CAtlString strFontFace = LoadAtlString(IDS_FONT_FACE_ARIAL);

    LOGFONT lfLabelFont;
    lfLabelFont.lfHeight = _wtol(strFontSize);
    lfLabelFont.lfWidth = 0;
    lfLabelFont.lfEscapement = 0;
    lfLabelFont.lfOrientation = 0;
    lfLabelFont.lfWeight = FW_DONTCARE;
    lfLabelFont.lfItalic = FALSE;
    lfLabelFont.lfUnderline = FALSE;
    lfLabelFont.lfStrikeOut = FALSE;
    lfLabelFont.lfCharSet = DEFAULT_CHARSET;
    lfLabelFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lfLabelFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lfLabelFont.lfQuality = DEFAULT_QUALITY;
    lfLabelFont.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
    wcscpy_s(lfLabelFont.lfFaceName, 32, strFontFace);
    
    HFONT hSmallFont = CreateFontIndirect(&lfLabelFont);
    if(NULL == hSmallFont)
    {
        return FALSE;
    }
    
    m_State.m_hOldFont = SelectObject(m_hBgBuffer, hSmallFont);
    if(NULL == m_State.m_hOldFont)
    {
        DeleteObject(hSmallFont);
        return FALSE;
    }
    
    return true;
}