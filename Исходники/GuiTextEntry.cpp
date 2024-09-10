void TextEntry::Draw()
{
	PROFILE_SCOPED()
	m_justFocused = false;

	Graphics::Renderer *pRenderer = Screen::GetRenderer();

	float size[2];
	GetSize(size);

	// find cursor position
	float curs_x, curs_y;
	Gui::Screen::MeasureCharacterPos(m_text, m_cursPos, curs_x, curs_y, m_font.Get());

	if (curs_x - m_scroll > size[0]*0.75f) {
		m_scroll += int(size[0]*0.25f);
	} else if (curs_x - m_scroll < size[0]*0.25f) {
		m_scroll -= int(size[0]*0.25f);
		if (m_scroll < 0) m_scroll = 0;
	}

	//background
	if(!m_background) {
		m_background.reset( new Graphics::Drawables::Rect(pRenderer, vector2f(0.f), vector2f(size[0], size[1]), Color(0,0,0,192), Screen::alphaBlendState));
	}
	m_background->Draw(pRenderer);

	//outline
	const Color c = IsFocused() ? Color::WHITE : Color(192, 192, 192, 255);
	const vector3f boxVts[] = {
		vector3f(0.f, 0.f, 0.f),
		vector3f(size[0],0.f, 0.f),
		vector3f(size[0],size[1], 0.f),
		vector3f(0,size[1], 0.f)
	};
	m_outlines.SetData(2, &boxVts[0], c);
	m_outlines.Draw(pRenderer, Screen::alphaBlendState, Graphics::LINE_LOOP);

	//text
	SetScissor(true);
	Gui::Screen::RenderStringBuffer(m_vb, m_text, 1.0f - m_scroll, 0.0f, c, m_font.Get());
	SetScissor(false);

	//cursor
	const vector3f cursorVts[] = {
		vector3f(curs_x + 1.0f - m_scroll, curs_y + Gui::Screen::GetFontDescender(m_font.Get()) - Gui::Screen::GetFontHeight(m_font.Get()), 0.f),
		vector3f(curs_x + 1.0f - m_scroll, curs_y + Gui::Screen::GetFontDescender(m_font.Get()), 0.f),
	};
	m_cursorLines.SetData(2, &cursorVts[0], Color(128, 128, 128));
	m_cursorLines.Draw(pRenderer, Screen::alphaBlendState);
}