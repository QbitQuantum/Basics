LRESULT CPropertyEditWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    CAtlString strFontSize = LoadAtlString(IDS_FONT_SIZE_14);
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
    m_hLabelFont = CreateFontIndirect(&lfLabelFont);

    RECT buttonRect;
    GetClientRect(&buttonRect);
    buttonRect.right -= ms_ButtonWidth + ms_MarginWidth + ms_MarginWidth;
    buttonRect.bottom -= ms_MarginWidth;
    buttonRect.top = buttonRect.bottom - ms_ButtonHeight;
    buttonRect.left = buttonRect.right - ms_ButtonWidth;
    
    m_AddButton.Create(m_hWnd, &buttonRect, LoadAtlString(IDS_ADD), WS_CHILD | BS_DEFPUSHBUTTON, 0, IDC_ADDBUTTON);

    buttonRect.right += ms_ButtonWidth + ms_MarginWidth;
    buttonRect.left += ms_ButtonWidth + ms_MarginWidth;
    
    m_OKButton.Create(m_hWnd, &buttonRect, LoadAtlString(IDS_SAVE), WS_CHILD | BS_DEFPUSHBUTTON, 0, IDC_OKBUTTON);

    return 0;
}