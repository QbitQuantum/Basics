void CStatusBar::OnScaleChanged()
{
	GETTHEMEFONT(&m_font, _T("StatusBar"), _T("Font"));

	HFONT hPrevFont = (HFONT)SelectObject(m_mdc, m_font);
	SIZE sz;
	GetTextExtentPoint32(m_mdc, _T("Ag"), 2, &sz);
	m_nHeight = SCY(4) + sz.cy + SCY(4);
	SelectObject(m_mdc, hPrevFont);

	Draw();
}