void RenderCharacterSys(FontGlyphConsumer& sw, double x, double y, int ch, Font fnt)
{
	HFONT hfont = GetWin32Font(fnt, 0);
	if(hfont) {
		HDC hdc = Win32_IC();
		HFONT ohfont = (HFONT) ::SelectObject(hdc, hfont);
		GLYPHMETRICS gm;
		MAT2 m_matrix;
		memset(&m_matrix, 0, sizeof(m_matrix));
		m_matrix.eM11.value = 1;
		m_matrix.eM22.value = 1;
		int gsz = GetGlyphOutlineW(hdc, ch, GGO_NATIVE, &gm, 0, NULL, &m_matrix);
		if(gsz < 0)
			return;
		StringBuffer gb(gsz);
		gsz = GetGlyphOutlineW(hdc, ch, GGO_NATIVE, &gm, gsz, ~gb, &m_matrix);
		if(gsz < 0)
			return;
		RenderCharPath(~gb, gsz, sw, x, y + fnt.GetAscent());
		::SelectObject(hdc, ohfont);
	}
}