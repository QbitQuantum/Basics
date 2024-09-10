bool PBListBox::Create(PBWindow* pParent, int left, int top, int width, int height)
{
	char defaultFont[32];
	PBWindow::Create(pParent, left, top, width, height, PBWS_VSCROLL);
	snprintf(defaultFont, sizeof(defaultFont), "#LiberationSans,%u,0", (m_itemHeight << 2) / 5);
	m_font = GetThemeFont("dictionary.font.normal", defaultFont);
	updateScrollBar();
	return true;
}