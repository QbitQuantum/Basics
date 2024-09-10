bool PBLineEdit::Create(PBWindow* pParent, int left, int top, int width, int height, PBENTERSTYPE style)
{
	char defaultFont[32];
	PBWindow::Create(pParent, left, top, width, height);

	style = PBES_TEXT;
	// font prepare
	snprintf(defaultFont, sizeof(defaultFont), "#LiberationSans,%u,0", (height << 2) / 5);
	m_font = GetThemeFont("dictionary.font.normal", defaultFont);

	m_enterstyle = PBES_TEXT;

	// clearing m_text
	memset(m_text, 0, sizeof(m_text));
	return true;
}