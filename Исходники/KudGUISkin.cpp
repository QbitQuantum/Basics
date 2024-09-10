void KGUISkin::SetBaseColor(KColor & color)
{
	if (m_Color.ToColor() == color.ToColor())
		return;

	m_Color = color;
	RGBQUAD rgb = { color.m_B, color.m_G, color.m_R };	
	KColor::RGB2HSL(&rgb, &H, &S, &L);
	
	m_ReverseColor.m_B = 255 - m_Color.m_B;
	m_ReverseColor.m_G = 255 - m_Color.m_G;
	m_ReverseColor.m_R = 255 - m_Color.m_R;

	m_IncColor = KColor(ColorAdjustLuma(RGB(m_Color.m_R, m_Color.m_G, m_Color.m_B), 200, TRUE));	
	m_DecColor = KColor(ColorAdjustLuma(RGB(m_Color.m_R, m_Color.m_G, m_Color.m_B), -200, TRUE));

	InitialSkin();
}