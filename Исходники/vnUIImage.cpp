void UIImage9::setLocation(const aabox2f &rect) {
	m_rect[4].min_corner = rect.min_corner + vector2f(m_widthLeft, m_heightTop);
	m_rect[4].max_corner = rect.max_corner - vector2f(m_widthRight, m_heightBottom);
	
	m_rect[0].min_corner = rect.min_corner;
	m_rect[0].max_corner = m_rect[4].min_corner;
	
	m_rect[1].min_corner.set(m_rect[4].min_corner.x, rect.min_corner.y);
	m_rect[1].max_corner.set(m_rect[4].max_corner.x, m_rect[4].min_corner.y);
	
	m_rect[2].min_corner.set(m_rect[4].max_corner.x, rect.min_corner.y);
	m_rect[2].max_corner.set(rect.max_corner.x, m_rect[4].min_corner.y);
	
	m_rect[3].min_corner.set(rect.min_corner.x, m_rect[4].min_corner.y);
	m_rect[3].max_corner.set(m_rect[4].min_corner.x, m_rect[4].max_corner.y);
	
	m_rect[5].min_corner.set(m_rect[4].max_corner.x, m_rect[4].min_corner.y);
	m_rect[5].max_corner.set(rect.max_corner.x, m_rect[4].max_corner.y);
	
	m_rect[6].min_corner.set(rect.min_corner.x, m_rect[4].max_corner.y);
	m_rect[6].max_corner.set(m_rect[4].min_corner.x, rect.max_corner.y);
	
	m_rect[7].min_corner.set(m_rect[4].min_corner.x, m_rect[4].max_corner.y);
	m_rect[7].max_corner.set(m_rect[4].max_corner.x, rect.max_corner.y);
	
	m_rect[8].min_corner = m_rect[4].max_corner;
	m_rect[8].max_corner = rect.max_corner;
}