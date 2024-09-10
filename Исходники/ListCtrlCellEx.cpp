void CListCtrlExSortHead::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	// Get the column rect
	CRect rcLabel(lpDrawItemStruct->rcItem);

	// Draw the background
	CBrush br(::GetSysColor(COLOR_3DFACE));
	pDC->FillRect(rcLabel, &br);	

	// Labels are offset by a certain amount  
	// This offset is related to the width of a space character
	int offset = pDC->GetTextExtent(_T(" "), 1).cx*2;

	// Get the column text and format
	TCHAR buf[256];
	HD_ITEM hditem;	

	hditem.mask = HDI_TEXT | HDI_FORMAT;
	hditem.pszText = buf;
	hditem.cchTextMax = 255;

	GetItem(lpDrawItemStruct->itemID, &hditem);

	// Determine format for drawing column label
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS ;

	if (hditem.fmt & HDF_CENTER)
		uFormat |= DT_CENTER;
	else if (hditem.fmt & HDF_RIGHT)
		uFormat |= DT_RIGHT;
	else
		uFormat |= DT_LEFT;

	// Adjust the rect if the mouse button is pressed on it
	if (lpDrawItemStruct->itemState == ODS_SELECTED)
	{
		rcLabel.left++;
		rcLabel.top += 2;
		rcLabel.right++;
	}

	// Adjust the rect further if Sort arrow is to be displayed
	if (lpDrawItemStruct->itemID == static_cast<UINT>(m_iSortColumn))
	{
		rcLabel.right -= 3 * offset;
	}

	rcLabel.left += offset;
	rcLabel.right -= offset;

	// Draw column label
	pDC->DrawText(buf, -1, rcLabel, uFormat);

	// Draw the Sort arrow
	if (lpDrawItemStruct->itemID == static_cast<UINT>(m_iSortColumn))
	{
		CRect rcIcon(lpDrawItemStruct->rcItem);

		// Set up pens to use for drawing the triangle
		CPen penLight(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		CPen penShadow(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		CPen *pOldPen = pDC->SelectObject(&penLight);

		if (!m_bSortDesc)
		{
			// Draw triangle pointing upwards
			pDC->MoveTo(rcIcon.right - 2*offset, offset - 1);
			pDC->LineTo(rcIcon.right - 3*offset/2, rcIcon.bottom - offset);
			pDC->LineTo(rcIcon.right - 5*offset/2-2, rcIcon.bottom - offset);
			pDC->MoveTo(rcIcon.right - 5*offset/2-1, rcIcon.bottom - offset - 1);

			pDC->SelectObject(&penShadow);
			pDC->LineTo(rcIcon.right - 2*offset, offset-2);
		}
		else	
		{
			// Draw triangle pointing downwards
			pDC->MoveTo(rcIcon.right - 3*offset/2, offset-1);
			pDC->LineTo(rcIcon.right - 2*offset-1, rcIcon.bottom - offset + 1);
			pDC->MoveTo(rcIcon.right - 2*offset-1, rcIcon.bottom - offset);

			pDC->SelectObject(&penShadow);
			pDC->LineTo(rcIcon.right - 5*offset/2-1, offset - 1);
			pDC->LineTo(rcIcon.right - 3*offset/2, offset - 1);
		}

		// Restore the pen
		pDC->SelectObject(pOldPen);
	}

}