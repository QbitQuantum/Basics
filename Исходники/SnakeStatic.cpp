void CEZSnakeCtrl::OnPaint() 
{
	PROC_TRACE;

	CPaintDC dc(this);
	CDC *pdc;
   pdc = &dc;
	CRect rect,rcLeft,rcRight,rcSnake;
	GetClientRect(&rect);

	rcLeft.CopyRect(&rect);
	rcRight.CopyRect(&rect);
	rcSnake.CopyRect(&rect); 

	float nTailpos=(float)m_nTail/(float)m_nMax*(float)rect.right;
	float nHeadpos=(float)m_nPos/(float)m_nMax*(float)rect.right;
	

	rcSnake.left=(long)(m_bReverse?nHeadpos:nTailpos);
	rcSnake.right=(long)(m_bReverse?nTailpos:nHeadpos);

	rcLeft.right=rcSnake.left;
	rcRight.left=rcSnake.right;

   DrawGradient(pdc,rcSnake);

	CBrush brush;
	VERIFY(brush.CreateSolidBrush(m_clrBk));
	pdc->FillRect(&rcLeft, &brush);
	pdc->FillRect(&rcRight,&brush);
	VERIFY(brush.DeleteObject());
	// Do not call CStatic::OnPaint() for painting messages
}