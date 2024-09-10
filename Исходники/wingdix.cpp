void CDC::DrawDragRect(LPCRECT lpRect, SIZE size,
	LPCRECT lpRectLast, SIZE sizeLast, CBrush* pBrush, CBrush* pBrushLast)
{
	ASSERT(AfxIsValidAddress(lpRect, sizeof(RECT), FALSE));
	ASSERT(lpRectLast == NULL ||
		AfxIsValidAddress(lpRectLast, sizeof(RECT), FALSE));

	// first, determine the update region and select it
	CRgn rgnNew;
	CRgn rgnOutside, rgnInside;
	rgnOutside.CreateRectRgnIndirect(lpRect);
	CRect rect = *lpRect;
	rect.InflateRect(-size.cx, -size.cy);
	rect.IntersectRect(rect, lpRect);
	rgnInside.CreateRectRgnIndirect(rect);
	rgnNew.CreateRectRgn(0, 0, 0, 0);
	rgnNew.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

	CBrush* pBrushOld = NULL;
	if (pBrush == NULL)
		pBrush = CDC::GetHalftoneBrush();
	if (pBrushLast == NULL)
		pBrushLast = pBrush;

	CRgn rgnLast, rgnUpdate;
	if (lpRectLast != NULL)
	{
		// find difference between new region and old region
		rgnLast.CreateRectRgn(0, 0, 0, 0);
		rgnOutside.SetRectRgn(lpRectLast);
		rect = *lpRectLast;
		rect.InflateRect(-sizeLast.cx, -sizeLast.cy);
		rect.IntersectRect(rect, lpRectLast);
		rgnInside.SetRectRgn(rect);
		rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

		// only diff them if brushes are the same
		if (pBrush->m_hObject == pBrushLast->m_hObject)
		{
			rgnUpdate.CreateRectRgn(0, 0, 0, 0);
			rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
		}
	}
	if (pBrush->m_hObject != pBrushLast->m_hObject && lpRectLast != NULL)
	{
		// brushes are different -- erase old region first
		SelectClipRgn(&rgnLast);
		GetClipBox(&rect);
		pBrushOld = SelectObject(pBrushLast);
		PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATINVERT);
		SelectObject(pBrushOld);
		pBrushOld = NULL;
	}

	// draw into the update/new region
	SelectClipRgn(rgnUpdate.m_hObject != NULL ? &rgnUpdate : &rgnNew);
	GetClipBox(&rect);
	pBrushOld = SelectObject(pBrush);
	PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATINVERT);

	// cleanup DC
	if (pBrushOld != NULL)
		SelectObject(pBrushOld);
	SelectClipRgn(NULL);
}