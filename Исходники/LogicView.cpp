void CLogicView::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
	{
		CDC * pDc = GetDC();
		pDc->SetROP2(R2_NOT);
		pDc->MoveTo(m_p.x, m_p.y);
		pDc->LineTo(m_p2.x, m_p2.y);
		pDc->MoveTo(m_p.x, m_p.y);
		pDc->LineTo(point.x, point.y);
		ReleaseDC(pDc);
		m_p2 = point;

	
	
		
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);
}