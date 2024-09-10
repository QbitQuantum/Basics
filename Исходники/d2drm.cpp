IFont*
CDirect2DRM::GetDefaultFont()
{
	static FONTDESC _fontdescHeading =
	  { sizeof(FONTDESC), OLESTR("Century Gothic"), FONTSIZE( 12 ), FW_BOLD, 
     ANSI_CHARSET, FALSE, FALSE, FALSE };

	if (m_pDefFont) {
		m_pDefFont->AddRef();
		return m_pDefFont;
	} else {
		HRESULT hr = OleCreateFontIndirect( &_fontdescHeading, IID_IFont, (LPVOID*)&m_pDefFont);
		m_pDefFont->AddRef();
		//HDC hDC = GetDC(NULL);
		//hr = m_pDefFont->SetHdc(hDC);
		//ReleaseDC(NULL, hDC);
		return m_pDefFont;
	}
}