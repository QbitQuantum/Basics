BOOL CLogListCtrl::OnEraseBkgnd(CDC* pDC)
{
	int itemCount = GetItemCount();

	if (!itemCount)
	{
		return CListCtrl::OnEraseBkgnd(pDC);
	}

	RECT clientRect;
	RECT itemRect;
	int topIndex = GetTopIndex();
	int maxItems = GetCountPerPage();
	int drawnItems = itemCount < maxItems ? itemCount : maxItems;
	CRect rcClip;

	GetClientRect(&clientRect);

	rcClip = clientRect;
	GetItemRect(topIndex, &itemRect, LVIR_BOUNDS);
	clientRect.bottom = itemRect.top;

	if (m_crWindowTextBk != CLR_NONE)
	{
		pDC->FillSolidRect(&clientRect,GetBkColor());
	}
	else
	{
		rcClip.top = itemRect.top;
	}

	if(topIndex + maxItems >= itemCount) 
	{
		GetClientRect(&clientRect);
		GetItemRect(topIndex + drawnItems - 1, &itemRect, LVIR_BOUNDS);
		clientRect.top = itemRect.bottom;
		rcClip.bottom = itemRect.bottom;
		if (m_crWindowTextBk != CLR_NONE)
		{
			pDC->FillSolidRect(&clientRect, GetBkColor());
		}
	}

	if (itemRect.right < clientRect.right) 
	{
		GetClientRect(&clientRect);
		clientRect.left = itemRect.right;
		rcClip.right = itemRect.right;
		if (m_crWindowTextBk != CLR_NONE)
		{
			pDC->FillSolidRect(&clientRect, GetBkColor());
		}
	}

	if (m_crWindowTextBk == CLR_NONE)
	{
		CRect rcClipBox;
		pDC->GetClipBox(&rcClipBox);
		rcClipBox.SubtractRect(&rcClipBox, &rcClip);

		if (!rcClipBox.IsRectEmpty())
		{
			pDC->ExcludeClipRect(&rcClip);
			CListCtrl::OnEraseBkgnd(pDC);
			InvalidateRect(&rcClip, FALSE);
		}
	}

	return TRUE;
} 