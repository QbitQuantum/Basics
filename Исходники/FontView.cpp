int CMainWindow::OnCreate (LPCREATESTRUCT lpcs)
{
    if (CWnd::OnCreate (lpcs) == -1)
        return -1;

	//
	// Create an 8-point MS Sans Serif font to use in the controls.
	//
    m_fontMain.CreatePointFont (80, _T ("MS Sans Serif"));

	//
	// Compute the average width and height of a character in the font.
	//
    CClientDC dc (this);
    CFont* pOldFont = dc.SelectObject (&m_fontMain);
    TEXTMETRIC tm;
    dc.GetTextMetrics (&tm);
    m_cxChar = tm.tmAveCharWidth;
    m_cyChar = tm.tmHeight + tm.tmExternalLeading;
    dc.SelectObject (pOldFont);

	//
	// Create the controls that will appear in the FontView window.
	//
    CRect rect (m_cxChar * 2, m_cyChar, m_cxChar * 48, m_cyChar * 2);
    m_wndLBTitle.Create (_T ("Typefaces"), WS_CHILD | WS_VISIBLE | SS_LEFT,
        rect, this);

    rect.SetRect (m_cxChar * 2, m_cyChar * 2, m_cxChar * 48,
        m_cyChar * 18);
    m_wndListBox.CreateEx (WS_EX_CLIENTEDGE, _T ("listbox"), NULL,
        WS_CHILD | WS_VISIBLE | LBS_STANDARD, rect, this, IDC_LISTBOX);

    rect.SetRect (m_cxChar * 2, m_cyChar * 19, m_cxChar * 48,
        m_cyChar * 20);
    m_wndCheckBox.Create (_T ("Show TrueType fonts only"),  WS_CHILD |
        WS_VISIBLE | BS_AUTOCHECKBOX, rect, this, IDC_CHECKBOX);

    rect.SetRect (m_cxChar * 2, m_cyChar * 21, m_cxChar * 66,
        m_cyChar * 25);
    m_wndGroupBox.Create (_T ("Sample"),  WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        rect, this, (UINT) -1);

    rect.SetRect (m_cxChar * 4, m_cyChar * 22, m_cxChar * 64,
        (m_cyChar * 99) / 4);
    m_wndSampleText.Create (_T (""), WS_CHILD | WS_VISIBLE | SS_CENTER, rect,
        this, IDC_SAMPLE);

    rect.SetRect (m_cxChar * 50, m_cyChar * 2, m_cxChar * 66,
        m_cyChar * 4);
    m_wndPushButton.Create (_T ("Print Sample"), WS_CHILD | WS_VISIBLE |
        WS_DISABLED | BS_PUSHBUTTON, rect, this, IDC_PRINT);

	//
	// Set each control's font to 8-point MS Sans Serif.
	//
    m_wndLBTitle.SetFont (&m_fontMain, FALSE);
    m_wndListBox.SetFont (&m_fontMain, FALSE);
    m_wndCheckBox.SetFont (&m_fontMain, FALSE);
    m_wndGroupBox.SetFont (&m_fontMain, FALSE);
    m_wndPushButton.SetFont (&m_fontMain, FALSE);

	//
	// Fill the list box with typeface names and return.
	//
    FillListBox ();
    return 0;
}