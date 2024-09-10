void CDayPlanSlider::OnSize(int /*width*/, int /*height*/)
{
//    m_dayView.m_layout = false;
//	OutputDebugString(_T("Region resized...\n"));
	m_bar.left = left + quickTabWidth;
	m_bar.right = right - quickTabWidth;
	m_bar.top = top;
	m_bar.bottom = bottom;

	SetRectRgn(m_hRegion, quickTabWidth, 0, quickTabWidth + barWidth + 1, bottom +1);
	CombineRgn(m_hRegion, m_qtRgn, m_hRegion, RGN_OR);
//	SetWindowRgn(m_hwnd, m_hRegion, TRUE); 

}