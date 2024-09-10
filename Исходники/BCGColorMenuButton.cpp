//*****************************************************************************************
void CBCGColorMenuButton::OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
			BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight,
			BOOL bDrawBorder, BOOL bGrayDisabledButtons)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	CBCGToolbarMenuButton::OnDraw (pDC, rect, pImages, bHorz, bCustomizeMode,
		bHighlight, bDrawBorder, bGrayDisabledButtons);

	if (!IsDrawImage () || pImages == NULL)
	{
		return;
	}

    CPalette* pOldPalette = NULL;
	if (globalData.m_nBitsPerPixel == 8) // 256 colors
	{
		if (m_Palette.GetSafeHandle () == NULL)
		{
			//----------------------------------------
			// Palette not created yet; create it now
			//----------------------------------------
			CBCGColorBar::CreatePalette (m_Colors, m_Palette);
		}

		ASSERT (m_Palette.GetSafeHandle () != NULL);

		pOldPalette = pDC->SelectPalette (&m_Palette, FALSE);
		pDC->RealizePalette ();
	}
	else if (m_Palette.GetSafeHandle () != NULL)
	{
		::DeleteObject (m_Palette.Detach ());
		ASSERT (m_Palette.GetSafeHandle () == NULL);
	}

	ASSERT (pImages != NULL);

	CRect rectColor = pImages->GetLastImageRect ();
	const int nColorBoxSize = CBCGToolBar::IsLargeIcons () && !m_bMenuMode ? 10 : 5;

	rectColor.top = rectColor.bottom - nColorBoxSize;
	rectColor.OffsetRect (0, 1);

	//----------------
	// Draw color bar:
	//----------------
	BOOL bDrawImageShadow = 
		bHighlight && !bCustomizeMode &&
		CBCGVisualManager::GetInstance ()->IsShadowHighlightedImage () &&
		!globalData.IsHighContastMode () &&
		((m_nStyle & TBBS_PRESSED) == 0) &&
		((m_nStyle & TBBS_CHECKED) == 0) &&
		((m_nStyle & TBBS_DISABLED) == 0);

	if (bDrawImageShadow)
	{
		CBrush brShadow (globalData.clrBarShadow);
		pDC->FillRect (rectColor, &brShadow);

		const int nRatio = CBCGToolBar::IsLargeIcons () && !m_bMenuMode ? 2 : 1;

		rectColor.OffsetRect (-nRatio, -nRatio);
	}

	COLORREF color = (m_nStyle & TBBS_DISABLED) ?
		globalData.clrBarShadow :
			(m_Color == (COLORREF)-1 ? m_colorAutomatic : m_Color);

	CBrush br (PALETTERGB(	GetRValue (color),
							GetGValue (color), 
							GetBValue (color)));

	CBrush* pOldBrush = pDC->SelectObject (&br);
	CPen* pOldPen = (CPen*) pDC->SelectStockObject (NULL_PEN);
	
	pDC->Rectangle (&rectColor);

	pDC->SelectObject (pOldPen);
	pDC->SelectObject (pOldBrush);

	if (CBCGVisualManager::GetInstance ()->IsMenuFlatLook ())
	{
		if (color == globalData.clrBarFace)
		{
			pDC->Draw3dRect (rectColor, globalData.clrBarDkShadow, globalData.clrBarDkShadow);
		}
	}
	else
	{
		pDC->Draw3dRect (rectColor, globalData.clrBarShadow, globalData.clrBarLight);
	}
	
    if (pOldPalette != NULL)
	{
        pDC->SelectPalette (pOldPalette, FALSE);
	}
}