void LTRectMarking::OnMouseUp( CDC* pdcAct, CPoint pt, CPoint ptOffset )
{
	CDC* pDC = p_Screenshot->GetDC();
	int i = pDC->SaveDC();

	CRect rRect = r_Rect;
	rRect.OffsetRect(ptOffset);
	DrawRect(pDC, rRect);

	pDC->RestoreDC(i);
}