void COptionTreeFontSelColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// Validate
	ASSERT(lpDrawItemStruct);

	// Declare variables
	CDC* pDC  = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT state = lpDrawItemStruct->itemState;
    CRect rDraw = lpDrawItemStruct->rcItem;
	CRect rArrow;
	UINT uFrameState;

	// Active popup
	if (m_bPopupActive)
	{
		state |= ODS_SELECTED | ODS_FOCUS;
	}

	// Frame state
	uFrameState = DFCS_BUTTONPUSH | DFCS_ADJUSTRECT;

	// Selected
	if (state & ODS_SELECTED)
	{
		uFrameState |= DFCS_PUSHED;
	}

	// Disabled
	if (state & ODS_DISABLED)
	{
		uFrameState |= DFCS_INACTIVE;
	}
	
	// Draw frame
	pDC->DrawFrameControl(&rDraw, DFC_BUTTON, uFrameState);


	// Offset rectangle if selected
	if (state & ODS_SELECTED)
	{
		rDraw.OffsetRect(1,1);
	}

	// Draw focus
	if (state & ODS_FOCUS) 
    {
		RECT rFocus = {rDraw.left, rDraw.top, rDraw.right - 1, rDraw.bottom};
  
        pDC->DrawFocusRect(&rFocus);
    }
	rDraw.DeflateRect(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

	// Draw arrow
	rArrow.left = rDraw.right - g_ciArrowSizeX - ::GetSystemMetrics(SM_CXEDGE) /2;
	rArrow.right = rArrow.left + g_ciArrowSizeX;
	rArrow.top = (rDraw.bottom + rDraw.top)/2 - g_ciArrowSizeY / 2;
	rArrow.bottom = (rDraw.bottom + rDraw.top)/2 + g_ciArrowSizeY / 2;
	DrawArrow(pDC, &rArrow, 0,(state & ODS_DISABLED) ? ::GetSysColor(COLOR_GRAYTEXT) : RGB(0,0,0));
	rDraw.right = rArrow.left - ::GetSystemMetrics(SM_CXEDGE)/2;

	// Draw seperator
	pDC->DrawEdge(&rDraw, EDGE_ETCHED, BF_RIGHT);
	rDraw.right -= (::GetSystemMetrics(SM_CXEDGE) * 2) + 1 ;
				  
	// Draw color
	if ((state & ODS_DISABLED) == 0)
	{
		pDC->FillSolidRect(&rDraw, (m_crColor == CLR_DEFAULT) ? m_crDefaultColor : m_crColor);

		::FrameRect(pDC->m_hDC, &rDraw, (HBRUSH)::GetStockObject(BLACK_BRUSH));
	}
}