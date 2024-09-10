void CScribbleView::OnDraw(CDC* pDC)
{
	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Get the invalidated rectangle of the view, or in the case
	// of printing, the clipping region of the printer dc.
	CRect rectClip;
	CRect rectStroke;
	pDC->GetClipBox(&rectClip);
	pDC->LPtoDP(&rectClip);
	rectClip.InflateRect(1, 1); // avoid rounding to nothing

	// Note: CScrollView::OnPaint() will have already adjusted the
	// viewport origin before calling OnDraw(), to reflect the
	// currently scrolled position.

	// The view delegates the drawing of individual strokes to
	// CStroke::DrawStroke().
	CTypedPtrList<CObList,CStroke*>& strokeList = pDoc->m_strokeList;
	POSITION pos = strokeList.GetHeadPosition();
	while (pos != NULL)
	{
		CStroke* pStroke = strokeList.GetNext(pos);
		rectStroke = pStroke->GetBoundingRect();
		pDC->LPtoDP(&rectStroke);
		rectStroke.InflateRect(1, 1); // avoid rounding to nothing
		if (!rectStroke.IntersectRect(&rectStroke, &rectClip))
			continue;
		pStroke->DrawStroke(pDC);
	}
}