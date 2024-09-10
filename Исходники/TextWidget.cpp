void TextWidget::setText(const std::string & text) {
	m_text = text;
	Vec2i textSize = m_font->getTextSize(m_text);
	m_rect = Rectf(m_rect.topLeft(), float(textSize.x + 1), float(textSize.y + 1));
}