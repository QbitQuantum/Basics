//*********************************************************************************************************
void CBCGPVisualManagerVS2008::OnDrawTab (CDC* pDC, CRect rectTab,
						int iTab, BOOL bIsActive, const CBCGPBaseTabWnd* pTabWnd)
{
	ASSERT_VALID (pTabWnd);
	ASSERT_VALID (pDC);

	const COLORREF clrTab = pTabWnd->GetTabBkColor (iTab);
	const BOOL bIsHighlight = (iTab == pTabWnd->GetHighlightedTab ());

	if (globalData.m_nBitsPerPixel <= 8 || globalData.IsHighContastMode () ||
		pTabWnd->IsDialogControl () ||
		pTabWnd->IsFlatTab () || pTabWnd->IsPointerStyle() ||
		clrTab != (COLORREF)-1)
	{
		CBCGPVisualManagerVS2005::OnDrawTab (pDC, rectTab, iTab, bIsActive, pTabWnd);
		return;
	}

	if ((bIsActive || bIsHighlight || m_bOSColors) && pTabWnd->IsVS2005Style ())
	{
		((CBCGPBaseTabWnd*)pTabWnd)->SetTabBkColor (iTab, 
			bIsActive ? m_clrHighlight : 
			bIsHighlight ? m_clrHighlightDnGradientDark : GetThemeColor (m_hThemeButton, 2));

		CBCGPVisualManagerVS2005::OnDrawTab (pDC, rectTab, iTab, bIsActive, pTabWnd);

		((CBCGPBaseTabWnd*)pTabWnd)->SetTabBkColor (iTab, clrTab);
		return;
	}

	if (m_hThemeTab == NULL ||
		pTabWnd->IsOneNoteStyle () || pTabWnd->IsVS2005Style () ||
		pTabWnd->IsLeftRightRounded ())
	{
		CRect rectClip = rectTab;
		rectClip.bottom -= 2;

		CRgn rgn;
		rgn.CreateRectRgnIndirect (&rectClip);

		pDC->SelectClipRgn (&rgn);

		CBCGPVisualManagerVS2005::OnDrawTab (pDC, rectTab, iTab, bIsActive, pTabWnd);
		
		pDC->SelectClipRgn (NULL);
		return;
	}

	int nState = TIS_NORMAL;
	if (bIsActive)
	{
		nState = TIS_SELECTED;
	}
	else if (iTab == pTabWnd->GetHighlightedTab ())
	{
		nState = TIS_HOT;
	}

	rectTab.right += 2;

	if (!bIsActive)
	{
		rectTab.bottom--;
	}
	else if (pTabWnd->GetLocation () == CBCGPBaseTabWnd::LOCATION_BOTTOM)
	{
		rectTab.top--;
		rectTab.bottom++;
	}

	if (rectTab.Width () > 25)	// DrawThemeBackground will draw < 25 width tab bad
	{
		CRect rectDraw = rectTab;

		if (bIsActive && pTabWnd->GetLocation () == CBCGPBaseTabWnd::LOCATION_BOTTOM)
		{
			rectDraw.bottom++;
		}

		(*m_pfDrawThemeBackground) (m_hThemeTab, pDC->GetSafeHdc(), TABP_TABITEM, nState, &rectDraw, 0);

		if (pTabWnd->GetLocation () == CBCGPBaseTabWnd::LOCATION_BOTTOM)
		{
			CBCGPDrawManager dm (*pDC);
			dm.MirrorRect (rectTab, FALSE);
		}
	}

	COLORREF clrTabText = globalData.clrWindowText;

	if (pTabWnd->GetTabTextColor(iTab) != (COLORREF)-1)
	{
		clrTabText = pTabWnd->GetTabTextColor(iTab);
	}
	else
	{
		if (!bIsActive)
		{
			clrTabText = globalData.clrBtnDkShadow;
		}
		else if (m_pfGetThemeColor != NULL)
		{
			(*m_pfGetThemeColor) (m_hThemeTab, TABP_TABITEM, nState, TMT_TEXTCOLOR, &clrTabText);
		}
	}

	COLORREF cltTextOld = pDC->SetTextColor (clrTabText);

	rectTab.right -= 2;

	OnDrawTabContent (pDC, rectTab, iTab, bIsActive, pTabWnd, (COLORREF)-1);

	pDC->SetTextColor (cltTextOld);
}