void CXTPFlowGraphDrawContext::DrawCurve(Gdiplus::GraphicsPath* pPath)
{
	int nCount = pPath->GetPointCount();

	Point* lppt = new Point[nCount];
	pPath->GetPathPoints(lppt, nCount);

	BYTE* pTypes = new BYTE[nCount];
	pPath->GetPathTypes(pTypes, nCount);

	CDC* pDC = CDC::FromHandle(m_hDC);

	int nIndex;
	Point* pptLastMoveTo = NULL;

	HPEN hOldPen = (HPEN)SelectObject(m_hDC, m_hActivePen);

	// for each of the points we have...
	for (nIndex = 0; nIndex <nCount; nIndex++)
	{
		switch(pTypes[nIndex])
		{
			// React to information from the path by drawing the data
			// we received. For each of the points, record our own
			// "last active point" so we can close figures, lines, and
			// Beziers.

		case PathPointTypeStart:
			if (pptLastMoveTo != NULL && nIndex > 0)
				pDC->LineTo(pptLastMoveTo->X, pptLastMoveTo->Y);
			pDC->MoveTo(lppt[nIndex].X, lppt[nIndex].Y);
			pptLastMoveTo = &lppt[nIndex];
			break;

		case PathPointTypeLine | PathPointTypeCloseSubpath:
			pDC->LineTo(lppt[nIndex].X, lppt[nIndex].Y);
			if (pptLastMoveTo != NULL)
				pDC->LineTo(pptLastMoveTo->X, pptLastMoveTo->Y);
			pptLastMoveTo = NULL;
			break;

		case PathPointTypeLine:
			pDC->LineTo(lppt[nIndex].X, lppt[nIndex].Y);
			break;

		case PathPointTypeBezier | PathPointTypeCloseSubpath:
			ASSERT(nIndex + 2 <= nCount);
			pDC->PolyBezierTo((POINT*)&lppt[nIndex], 3);
			nIndex += 2;
			if (pptLastMoveTo != NULL)
				pDC->LineTo(pptLastMoveTo->X, pptLastMoveTo->Y);
			pptLastMoveTo = NULL;
			break;

		case PathPointTypeBezier:
			ASSERT(nIndex + 2 <= nCount);
			pDC->PolyBezierTo((POINT*)&lppt[nIndex], 3);
			nIndex += 2;
			break;
		}
	}

	delete[] lppt;
	delete[] pTypes;

	SelectObject(m_hDC, hOldPen);
}