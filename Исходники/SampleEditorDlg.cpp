void CSampleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_iSize)
		return;

	if (point.y > m_clientRect.bottom)
		return;

	int Block = GetBlock(point.x);
	m_iSelStart = GetPixel(Block);
	m_iSelEnd = m_iSelStart;
	Invalidate();
	RedrawWindow();
	m_bClicked = true;
	CStatic::OnLButtonDown(nFlags, point);
}