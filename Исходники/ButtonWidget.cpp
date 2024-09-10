void ButtonWidget::SetPos(Vec2f pos) {
	
	Vec2f scaledSize = RATIO_2(m_size);
	m_rect = Rectf(pos, scaledSize.x, scaledSize.y);
}