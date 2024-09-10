int CXTPExcelTabCtrlTheme::DrawTab(CDC* pDC, CXTPExcelTabCtrl* pTabCtrl, const CPoint& pt, bool bSelected, CXTPTcbItem* pTcbItem)
{
	if (pDC == NULL || pTcbItem == NULL || !::IsWindow(pTabCtrl->GetSafeHwnd()))
		return -1;

	// Saves the current state of the device context, we will
	// restore the state when the method looses scope. This will
	// simplify selecting objects.
	const int nSavedDC = pDC->SaveDC();

	const int iHeight = m_cy;
	const int iBase = iHeight / 2;
	const int iWidth = iHeight + iHeight / 2; // 2 bases + 2 margins

	const bool bBottom = (pTabCtrl->GetTabStyle() & FTS_XTP_BOTTOM) == FTS_XTP_BOTTOM;

	pDC->SelectObject(pTabCtrl->GetTabFont(bSelected));
	const CSize szText = pDC->GetTextExtent(pTcbItem->szTabLabel);

	CRect rcText;
	rcText.left = pt.x + iBase + iBase / 2;
	rcText.top = pt.y + ((iHeight - szText.cy)/2)-1;
	rcText.right = rcText.left + szText.cx;
	rcText.bottom = rcText.top + szText.cy;

	COLORREF crBack = GetTabBackColor(pTcbItem);
	COLORREF crFore = GetTabTextColor(pTcbItem);

	if (bSelected)
	{
		crBack = GetSelTabBackColor(pTcbItem);
		crFore = GetSelTabTextColor(pTcbItem);
	}

	CPen penBack(PS_SOLID, 1, crBack);
	CPen penWindow(PS_SOLID, 1, m_clr3DHilight);
	CPen penShadow(PS_SOLID, 1, m_clr3DShadow);
	CPen penOutline(PS_SOLID, 1, m_clrBtnText);

	CBrush brush;
	brush.CreateSolidBrush(crBack);

	POINT points[] =
	{
		{ pt.x, pt.y + iHeight - 1 },
		{ pt.x + iBase - 1, pt.y               },
		{ pt.x + szText.cx + iWidth - iBase - 1, pt.y               },
		{ pt.x + szText.cx + iWidth - 1, pt.y + iHeight - 1 }
	};

	// swap vertical coordinates
	if (bBottom)
	{
		points[0].y = points[1].y;
		points[2].y = points[3].y;
		points[1].y = points[2].y;
		points[3].y = points[0].y;
	}

	pDC->SelectObject(&penOutline);
	pDC->SetBkColor(crBack);
	pDC->SelectObject(&brush);
	pDC->Polygon(points, 4);
	pDC->SetTextColor(crFore);
	pDC->DrawText(pTcbItem->szTabLabel, rcText, DT_CENTER);
	pDC->SelectObject(&penShadow);

	if (bSelected)
	{
		pDC->MoveTo(pt.x + iBase, points[1].y);
		pDC->LineTo(pt.x + iBase * 2 + szText.cx - 1, points[1].y);
		pDC->SelectObject(&penBack);
		pDC->MoveTo(pt.x + 1, points[0].y);
		pDC->LineTo(pt.x + szText.cx + iWidth - 1, points[0].y);
	}
	else
	{
		// highlight line on left
		pDC->SelectObject(&penWindow);
		pDC->MoveTo(pt.x + 1, points[0].y);
		pDC->LineTo(pt.x + 1 + iBase, points[0].y + iHeight);

		// shadow line on top
		pDC->SelectObject(&penShadow);
		pDC->MoveTo(pt.x, points[0].y);
		pDC->LineTo(pt.x + szText.cx + iWidth, points[0].y);

		// shadow line on bottom
		pDC->MoveTo(pt.x + iBase, points[1].y);
		pDC->LineTo(pt.x + szText.cx + iHeight - 1, points[1].y);
	}

	// Cleanup.
	pDC->RestoreDC(nSavedDC);
	brush.DeleteObject();

	return szText.cx + iWidth;
}