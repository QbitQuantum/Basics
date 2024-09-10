void CHSScrollBar::DrawBorder( CDC* pDC )
{
	CPen Pen;
	Pen.CreatePenIndirect(&m_logpen.GetPen(HsLOGPEN::hor));
	CPen* pOldPen;
	pOldPen = pDC->SelectObject(&Pen);

	// 画上边框
	pDC->MoveTo(m_rect.left,  m_rect.top);
	pDC->LineTo(m_rect.right, m_rect.top);

	// 画下边框
	pDC->MoveTo(m_rect.left,  m_rect.bottom);
	pDC->LineTo(m_rect.right, m_rect.bottom);

	Pen.DeleteObject();
	Pen.CreatePenIndirect(&m_logpen.GetPen(HsLOGPEN::ver));
	pDC->SelectObject(&Pen);

	// 画左边框
	pDC->MoveTo(m_rect.left, m_rect.top);
	pDC->LineTo(m_rect.left, m_rect.bottom);

	// 画右边框
	pDC->MoveTo(m_rect.right, m_rect.top);
	pDC->LineTo(m_rect.right, m_rect.bottom);

	pDC->SelectObject(pOldPen);
	Pen.DeleteObject();
}