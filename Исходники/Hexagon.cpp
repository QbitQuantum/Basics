void CHexagon::Draw(CDC &dc)
{
	dc.BeginPath();
	dc.MoveTo(m_dCenterX - m_A, m_dCenterY);
	dc.LineTo(m_dCenterX - m_A * 1/2, m_dCenterY - m_A * sqrt(3.)/2);
	dc.LineTo(m_dCenterX + m_A * 1/2, m_dCenterY - m_A * sqrt(3.)/2);
	dc.LineTo(m_dCenterX + m_A, m_dCenterY);
	dc.LineTo(m_dCenterX + m_A * 1/2, m_dCenterY + m_A * sqrt(3.)/2);
	dc.LineTo(m_dCenterX - m_A * 1/2, m_dCenterY + m_A * sqrt(3.)/2);
	dc.LineTo(m_dCenterX - m_A, m_dCenterY);
	dc.EndPath();
	dc.StrokeAndFillPath();
}