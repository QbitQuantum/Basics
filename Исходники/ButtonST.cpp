void CButtonST::DrawItem(UINT ctrlID, LPDRAWITEMSTRUCT lpDIS)
{
	CDCHandle pDC = lpDIS->hDC;

	CPenHandle	pOldPen;

	// Checkbox or Radiobutton style ?
	if (m_bIsCheckBox)
		{
		m_bIsPressed  =  (lpDIS->itemState & ODS_SELECTED) || m_nCheck;
		}
	// Normal button OR other button style ...
	else
		{
		m_bIsPressed = (lpDIS->itemState & ODS_SELECTED);
		}

	m_bIsFocused  = (lpDIS->itemState & ODS_FOCUS) != 0;
	m_bIsDisabled = (lpDIS->itemState & ODS_DISABLED) != 0;
	
	CRect itemRect = lpDIS->rcItem;

	pDC.SetBkMode(TRANSPARENT);

	if (!m_bIsFlat)
		{
		if (m_bIsFocused || GetDefault())
			{
			CBrush br;
			br.CreateSolidBrush(RGB(0,0,0));  
			pDC.FrameRect(&itemRect, br);
			itemRect.DeflateRect(1, 1);
			}
		}

	// Prepare draw... paint button background

	// Draw transparent?
	if (m_bDrawTransparent)
		{
		PaintBk(pDC);
		}
	else
		{
		OnDrawBackground(pDC, &itemRect);
		}

	// Draw pressed button
	if (m_bIsPressed)
		{
		if (m_bIsFlat)
			{
			if (m_bDrawBorder)
				{
				OnDrawBorder(pDC, &itemRect);
				}
			}
		else    
			{
			CBrush brBtnShadow;
			brBtnShadow.CreateSolidBrush(GetSysColor(COLOR_BTNSHADOW));
			pDC.FrameRect(&itemRect, brBtnShadow);
			}
		}
	else // ...else draw non pressed button
		{
		CPen penBtnHiLight; // White
		CPen pen3DLight;       // Light gray
		CPen penBtnShadow;   // Dark gray
		CPen pen3DDKShadow; // Black

		penBtnHiLight.CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_BTNHILIGHT)); // White
		pen3DLight.CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_3DLIGHT));       // Light gray
		penBtnShadow.CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_BTNSHADOW));   // Dark gray
		pen3DDKShadow.CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_3DDKSHADOW)); // Black

		if (m_bIsFlat)
			{
			if (m_bMouseOnButton && m_bDrawBorder)
				{
				pDC.Draw3dRect(itemRect, ::GetSysColor(COLOR_BTNHILIGHT), ::GetSysColor(COLOR_BTNSHADOW));
				}
			}
		else
			{
			// Draw top-left borders
			// White line
			pOldPen = pDC.SelectPen(penBtnHiLight);
			pDC.MoveTo(itemRect.left, itemRect.bottom-1);
			pDC.LineTo(itemRect.left, itemRect.top);
			pDC.LineTo(itemRect.right, itemRect.top);
			// Light gray line
			pDC.SelectPen(pen3DLight);
			pDC.MoveTo(itemRect.left+1, itemRect.bottom-1);
			pDC.LineTo(itemRect.left+1, itemRect.top+1);
			pDC.LineTo(itemRect.right, itemRect.top+1);
			// Draw bottom-right borders
			// Black line
			pDC.SelectPen(pen3DDKShadow);
			pDC.MoveTo(itemRect.left, itemRect.bottom-1);
			pDC.LineTo(itemRect.right-1, itemRect.bottom-1);
			pDC.LineTo(itemRect.right-1, itemRect.top-1);
			// Dark gray line
			pDC.SelectPen(penBtnShadow);
			pDC.MoveTo(itemRect.left+1, itemRect.bottom-2);
			pDC.LineTo(itemRect.right-2, itemRect.bottom-2);
			pDC.LineTo(itemRect.right-2, itemRect.top);
			//
			pDC.SelectPen(pOldPen);
			}
		}

	// Read the button's title
	CString sTitle;
	int nLen = GetWindowTextLength();
	int nRetLen = GetWindowText(sTitle.GetBufferSetLength(nLen), nLen + 1);

	CRect captionRect = lpDIS->rcItem;

	// Draw the icon
	if (m_csIcons[0].hIcon != 0)
		{
		DrawTheIcon(pDC, !sTitle.IsEmpty(), lpDIS->rcItem, captionRect, m_bIsPressed, m_bIsDisabled);
		}

	if (m_csBitmaps[0].hBitmap != 0)
		{
		pDC.SetBkColor(RGB(255,255,255));
		DrawTheBitmap(pDC, !sTitle.IsEmpty(), lpDIS->rcItem, captionRect, m_bIsPressed, m_bIsDisabled);
		}

	// Write the button title (if any)
	if (!sTitle.IsEmpty())
		{
		// Draw the button's title
		// If button is pressed then "press" title also
		if (m_bIsPressed && !m_bIsCheckBox)
			{
			captionRect.OffsetRect(1, 1);
			}
		// Center text
		CRect centerRect = captionRect;
		pDC.DrawText(sTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
		captionRect.OffsetRect((centerRect.Width() - captionRect.Width())/2, (centerRect.Height() - captionRect.Height())/2);
		pDC.SetBkMode(TRANSPARENT);
		if (m_bIsDisabled)
			{
			captionRect.OffsetRect(1, 1);
			pDC.SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
			pDC.DrawText(sTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
			captionRect.OffsetRect(-1, -1);
			pDC.SetTextColor(::GetSysColor(COLOR_3DSHADOW));
			pDC.DrawText(sTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
			}
		else
			{
			if (m_bMouseOnButton || m_bIsPressed) 
				{
				pDC.SetTextColor(m_crColors[BTNST_COLOR_FG_IN]);
				pDC.SetBkColor(m_crColors[BTNST_COLOR_BK_IN]);
				} 
			else 
				{
				pDC.SetTextColor(m_crColors[BTNST_COLOR_FG_OUT]);
				pDC.SetBkColor(m_crColors[BTNST_COLOR_BK_OUT]);
				}
			pDC.DrawText(sTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
			}
		}
	if (!m_bIsFlat || (m_bIsFlat && m_bDrawFlatFocus))
		{
		// Draw the focus rect
		if (m_bIsFocused)
			{
			CRect focusRect = itemRect;
			focusRect.DeflateRect(3, 3);
			pDC.DrawFocusRect(&focusRect);
			}
		}
}