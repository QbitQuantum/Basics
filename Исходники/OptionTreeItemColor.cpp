void COptionTreeItemColor::DrawControl(CDC *pDC, const RECT &rcRect)
{
	// Declare variables
	HGDIOBJ hOld;
	HGDIOBJ hOldBrush;
	COLORREF crOld;
	int nOldBack;
	CRect rcText, rcColor, rcClient;
	CString strText;
	CBrush bBrush;
	COLORREF crOldBack;

	// Get window rect
	GetClientRect(rcClient);

	// Select font
	hOld = pDC->SelectObject(m_otOption->GetNormalFont());

	// Create bush
	bBrush.CreateSolidBrush(m_crColor);
	
	// Set text color
	if (IsReadOnly() == TRUE || m_otOption->IsWindowEnabled() == FALSE)
	{
		crOld = pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
	}
	else
	{
		crOld = pDC->SetTextColor(GetTextColor());
	}

	// Set background color
	crOldBack = pDC->SetBkColor(GetBackgroundColor());	

	// Set background mode
	nOldBack = pDC->SetBkMode(TRANSPARENT);

	// Select brush
	hOldBrush = pDC->SelectObject(GetSysColorBrush(COLOR_BTNSHADOW));

	// Get color rectangle
	rcColor.left  = rcRect.left + 1;
	rcColor.right = rcColor.left + (long) OT_COLOR_SIZE;
	rcColor.top = rcRect.top + OT_SPACE - 2;
	rcColor.bottom = rcColor.top + (long) OT_COLOR_SIZE;

	// Draw color border
	rcColor.InflateRect(1, 1, 1, 1);
	pDC->PatBlt(rcColor.left, rcColor.top, rcColor.Width(), rcColor.Height(), PATCOPY);

	// Draw color
	rcColor.DeflateRect(1, 1, 1, 1);
	pDC->FillRect(rcColor, &bBrush);

	// Get text rectangle
	rcText.left  = rcColor.right + OT_SPACE;
	rcText.right = rcRect.right;
	rcText.top = rcRect.top;
	rcText.bottom = rcRect.bottom;

	// Get text
	if (GetOption(OT_COLOR_SHOWHEX) == TRUE)
	{
		strText.Format(_T("#%.6X"), m_crColor);
	}
	else
	{
		strText.Format(_T("RGB (%d, %d, %d)"), GetRValue(m_crColor), GetGValue(m_crColor), GetBValue(m_crColor));
	}

	// Draw text
	pDC->DrawText(strText, rcText, DT_SINGLELINE | DT_VCENTER);
	pDC->DrawText(strText, rcText, DT_SINGLELINE | DT_VCENTER | DT_CALCRECT);
	
	// Delete brush
	if (bBrush.GetSafeHandle() != NULL)
	{
		bBrush.DeleteObject();
	}

	// Restore GDI ojects
	pDC->SelectObject(hOldBrush);
	pDC->SelectObject(hOld);
	pDC->SetTextColor(crOld);
	pDC->SetBkMode(nOldBack);
	pDC->SetBkColor(crOldBack);
}